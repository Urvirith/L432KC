#include "common.h"
#include "i2c.h"



#include "usart.h"


/* Register Masks */
/* CR2 */
#define ADDR_10_MASK        MASK_10_BIT
#define ADDR_7_MASK         MASK_9_BIT
#define NBYTES_MASK         MASK_8_BIT
/* TIMINGR */
#define SCL_MASK            MASK_8_BIT
#define DEL_MASK            MASK_4_BIT


/* Register Bits */
/* CR1 */
#define PE_BIT              BIT_0
/* CR2 */
#define RD_WRN_BIT          BIT_10          // Transfer direction (master mode) 0: Master requests a write transfer. 1: Master requests a read transfer.
#define ADDR_10_BIT         BIT_11          // 10-bit addressing mode (master mode) 0: The master operates in 7-bit addressing mode, 1: The master operates in 10-bit addressing mode
#define HEAD_10_BIT         BIT_12          // 10-bit address header only read direction (master receiver mode) 0: The master sends the complete 10 bit slave address read sequence:
                                            // Start + 2 bytes 10bit address in write direction + Restart + 1st 7 bits of the 10 bit address in read direction.
                                            // 1: The master only sends the 1st 7 bits of the 10 bit address, followed by Read direction.
#define START_BIT           BIT_13          // This bit is set by software, and cleared by hardware after the Start followed by the address sequence is sent, by an arbitration loss, by a timeout error detection, or when PE = 0.
                                            // It can also be cleared by software by writing ‘1’ to the ADDRCF bit in the I2C_ICR register. 0: No Start generation. 1: Restart/Start generation:
#define STOP_BIT            BIT_14          // The bit is set by software, cleared by hardware when a STOP condition is detected, or when PE = 0. In Master Mode: 0: No Stop generation. 1: Stop generation after current byte transfer.
#define NACK_BIT            BIT_15          // The bit is set by software, cleared by hardware when the NACK is sent, or when a STOP condition or an Address matched is received, or when PE=0. 0: an ACK is sent after current received byte. 1: a NACK is sent after current received byte.
#define RELOAD_BIT          BIT_24          // 0: The transfer is completed after the NBYTES data transfer (STOP or RESTART follows). 1: The transfer is not completed after the NBYTES data transfer (NBYTES is reloaded). TCR flag is set when NBYTES data are transferred, stretching SCL low.
#define AUTOEND_BIT         BIT_25          // 0: software end mode: TC flag is set when NBYTES data are transferred, stretching SCL low. 1: Automatic end mode: a STOP condition is automatically sent when NBYTES data are transferred.

/* ISR */
// CONST FOR THE ISR AND ICR PG. 1234
#define TXIS_BIT            BIT_1
#define RXNE_BIT            BIT_2
#define TC_BIT              BIT_6


/* Register Offsets */
/* CR2 */
#define ADDR_10_OFFSET      0
#define ADDR_7_OFFSET       1
#define NBYTES_OFFSET       16              // The number of bytes to be transmitted/received is programmed there. This field is don’t care in slave mode with SBC=0.
#define START_OFFSET        13              // This bit is set by software, and cleared by hardware after the Start followed by the address sequence is sent, by an arbitration loss, by a timeout error detection, or when PE = 0.
                                            // It can also be cleared by software by writing ‘1’ to the ADDRCF bit in the I2C_ICR register. 0: No Start generation. 1: Restart/Start generation:
#define STOP_OFFSET         14 

/* TIMINGR */
#define SCLL_OFFSET         0
#define SCLH_OFFSET         8
#define SDADEL_OFFSET       16
#define SCLDEL_OFFSET       20
#define PRESC_OFFSET        28

/* SETUP */
#define READ                false
#define WRITE               true
#define LEN_1_BYTE          1
     
/* Private Functions */
static void set_timing_register(I2C_TypeDef *ptr, uint32_t scll, uint32_t sclh, uint32_t sdadel, uint32_t scldel, uint32_t presc);

 // Initalization Flow ->
    // Clear PE bit in I2C_CR1
    // Configure ANFOFF and DNF[3:0] in I2C_CR1
    // Configure PRESC[3:0],
    // SDADEL[3:0], SCLDEL[3:0], SCLH[7:0], SCLL[7:0]  in I2C_TIMINGR
    // Configure NOSTRETCH in I2C_CR1
    // Set PE bit in I2C_CR1
    // End
    // INORDER TO RUN THE I2C SETUP YOU MUST FIRST I2C CLK AS APART OF THE CLOCK REGISTER AT PG. 163
void i2c_open(I2C_TypeDef *ptr, uint32_t sclk_mhz, uint32_t mode) {
    clr_ptr_vol_bit_u32(&ptr->CR1, PE_BIT);
    
    switch(sclk_mhz) {
        case Clk8MHz:
            switch(mode) {
                case I2C_Sm_10KHz:
                    set_timing_register(ptr, 0xC7, 0xC3, 0x02, 0x04, 0x01);
                    break;
                case I2C_Sm_100KHz:
                    set_timing_register(ptr, 0x13, 0x0F, 0x02, 0x04, 0x01);
                    break;
                case I2C_Fm_400KHz:
                    set_timing_register(ptr, 0x09, 0x03, 0x01, 0x03, 0x00);
                    break;
                case I2C_Fm_Plus:
                    set_timing_register(ptr, 0x06, 0x03, 0x00, 0x01, 0x00);
                    break;
                default:
                    set_timing_register(ptr, 0xC7, 0xC3, 0x02, 0x04, 0x01);
                    break;
            }
            break;
        case Clk16MHz:
            switch(mode) {
                case I2C_Sm_10KHz:
                    set_timing_register(ptr, 0xC7, 0xC3, 0x02, 0x04, 0x03);
                    break;
                case I2C_Sm_100KHz:
                    set_timing_register(ptr, 0x13, 0x0F, 0x02, 0x04, 0x03);
                    break;
                case I2C_Fm_400KHz:
                    set_timing_register(ptr, 0x09, 0x03, 0x02, 0x03, 0x01);
                    break;
                case I2C_Fm_Plus:
                    set_timing_register(ptr, 0x04, 0x02, 0x00, 0x02, 0x00);
                    break;
                default:
                    set_timing_register(ptr, 0xC7, 0xC3, 0x02, 0x04, 0x03);
                    break;
            }
            break;
        case Clk48MHz:
            switch(mode) {
                case I2C_Sm_10KHz:
                    set_timing_register(ptr, 0xC7, 0xC3, 0x02, 0x04, 0x0B);
                    break;
                case I2C_Sm_100KHz:
                    set_timing_register(ptr, 0x13, 0x0F, 0x02, 0x04, 0x0B);
                    break;
                case I2C_Fm_400KHz:
                    set_timing_register(ptr, 0x09, 0x03, 0x03, 0x03, 0x05);
                    break;
                case I2C_Fm_Plus:
                    set_timing_register(ptr, 0x03, 0x01, 0x00, 0x01, 0x05);
                    break;
                default:
                    set_timing_register(ptr, 0xC7, 0xC3, 0x02, 0x04, 0x0B);
                    break;
            }
            break;
        default:
            set_timing_register(ptr, 0x19, 0x06, 0x00, 0x03, 0x00);           // DEFAULT SPEED USED FOR TESTING
            break;
    }

    set_ptr_vol_bit_u32(&ptr->CR1, PE_BIT);
}

void i2c_start_bus(I2C_TypeDef *ptr) { 
    set_ptr_vol_bit_u32(&ptr->CR1, PE_BIT);
}

void i2c_stop_bus(I2C_TypeDef *ptr) { 
    clr_ptr_vol_bit_u32(&ptr->CR1, PE_BIT);

    volatile uint32_t i = 0; // CONVERT TO FAULT TIMER, VOLITILE WILL PREVENT OPTIMIZATION
    while (i < 100000) {
        i++;
    }
}

// • Addressing mode (7-bit or 10-bit): ADD10 • Slave address to be sent: SADD[9:0]
    // • Transfer direction: RD_WRN
    // • In case of 10-bit address read: HEAD10R bit. HEAD10R must be configure to indicate if the complete address sequence must be sent, or only the header in case of a direction change.
    // • The number of bytes to be transferred: NBYTES[7:0]. If the number of bytes is equal to or greater than 255 bytes, NBYTES[7:0] must initially be filled with 0xFF.
void i2c_setup(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint32_t byte_cnt, bool write) {
    if (addr_10bit) {
        set_ptr_vol_bit_u32(&ptr->CR2, ADDR_10_BIT);
        set_ptr_vol_u32(&ptr->CR2, ADDR_10_OFFSET, ADDR_10_MASK, slave_addr);

        if (req_10bit) {
            set_ptr_vol_bit_u32(&ptr->CR2, HEAD_10_BIT);
        } else {
            clr_ptr_vol_bit_u32(&ptr->CR2, HEAD_10_BIT);
        }
    } else {
        clr_ptr_vol_bit_u32(&ptr->CR2, ADDR_10_BIT);
        set_ptr_vol_u32(&ptr->CR2, ADDR_7_OFFSET, ADDR_7_MASK, slave_addr);
    }

    if (write) {
        clr_ptr_vol_bit_u32(&ptr->CR2, RD_WRN_BIT);
    } else {
        set_ptr_vol_bit_u32(&ptr->CR2, RD_WRN_BIT);
    }

    set_ptr_vol_u32(&ptr->CR2, NBYTES_OFFSET, NBYTES_MASK, byte_cnt);

    // TO BE CHANGED TO BINARY SWITCH IF BYTE CNT >= 255;
    clr_ptr_vol_bit_u32(&ptr->CR2, RELOAD_BIT);
    clr_ptr_vol_bit_u32(&ptr->CR2, AUTOEND_BIT);
}

bool i2c_start(I2C_TypeDef *ptr) {
    set_ptr_vol_bit_u32(&ptr->CR2, START_BIT);

    uint32_t i = 0; // CONVERT TO FAULT TIMER

    while (get_ptr_vol_bit_u32(&ptr->CR2, START_BIT)){
        if (i > 100000) {
            return false;
        }

        i++;
    }

    return true;
}

bool i2c_stop(I2C_TypeDef *ptr) {
    set_ptr_vol_bit_u32(&ptr->CR2, STOP_BIT);

    uint32_t i = 0; // CONVERT TO FAULT TIMER

    while (get_ptr_vol_bit_u32(&ptr->CR2, STOP_BIT)){
        if (i > 1000000) {
            return false;
        }

        i++;
    }

    return true;
}

bool i2c_tc(I2C_TypeDef *ptr) {
    uint32_t i = 0; // CONVERT TO FAULT TIMER

    while (!get_ptr_vol_bit_u32(&ptr->ISR, TC_BIT)){
        if (i > 100000) {
            return false;
        }

        i++;
    }
    return true;
}

// p. 1202
// In the case of a read transfer, the RXNE flag is set after each byte reception, after the 8th SCL pulse.
// An RXNE event generates an interrupt if the RXIE bit is set in the I2C_CR1 register. The flag is cleared when I2C_RXDR is read.
// If the total number of data bytes to be received is greater than 255, reload mode must be selected by setting the RELOAD bit in the I2C_CR2 register.
// In this case, when NBYTES[7:0] data have been transferred, the TCR flag is set and the SCL line is stretched low until NBYTES[7:0] is written to a non-zero value.
// • When RELOAD=0 and NBYTES[7:0] data have been transferred:
//      – In automatic end mode (AUTOEND=1), a NACK and a STOP are automatically sent after the last received byte.
//      – In software end mode (AUTOEND=0), a NACK is automatically sent after the last received byte,
//        the TC flag is set and the SCL line is stretched low in order to allow software actions:
//          A RESTART condition can be requested by setting the START bit in the I2C_CR2 register with the proper slave address configuration, and number of bytes to be transferred.
//          Setting the START bit clears the TC flag and the START condition, followed by slave address, are sent on the bus.
//          A STOP condition can be requested by setting the STOP bit in the I2C_CR2 register. Setting the STOP bit clears the TC flag and the STOP condition is sent on the bus.
    
bool i2c_read(I2C_TypeDef *ptr, uint8_t* buf, int len) {
    uint32_t i = 0; 

    while(i < len){
        uint32_t t = 0; // CONVERT TO FAULT TIMER

        while (!get_ptr_vol_bit_u32(&ptr->ISR, RXNE_BIT)){
            if (t > 100000) {
                return false;
            }

            t++;
        }

        buf[i] = get_ptr_vol_raw_u8((volatile uint8_t *)&ptr->RXDR);
        i++;
    }
    return true;
}

uint8_t i2c_read_u8(I2C_TypeDef *ptr) {
    uint32_t i = 0; 

    while (!get_ptr_vol_bit_u32(&ptr->ISR, RXNE_BIT)){
        if (i > 100000) {
            return 0;
        }
        i++;
    }
        
    return get_ptr_vol_raw_u8((volatile uint8_t *)&ptr->RXDR);
}

void i2c_std_read(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t* buf_write, uint32_t len_write,  uint8_t* buf_read, uint32_t len_read) {
    i2c_setup(ptr, slave_addr, addr_10bit, req_10bit, len_write, WRITE);
    i2c_start(ptr);
    i2c_write(ptr, buf_write, len_write);
    i2c_tc(ptr);
    i2c_setup(ptr, slave_addr, addr_10bit, req_10bit, len_read, READ);
    i2c_start(ptr);
    i2c_read(ptr, buf_read, len_read);
    i2c_tc(ptr);
    i2c_stop(ptr);

    //return 0; // CAN BE USED LATER FOR ALARMING OR TURN TO VOID
}

uint8_t i2c_std_read_u8(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t byte_write) {
    i2c_setup(ptr, slave_addr, addr_10bit, req_10bit, LEN_1_BYTE, WRITE);
    i2c_start(ptr);
    i2c_write_u8(ptr, byte_write);
    i2c_tc(ptr);
    i2c_setup(ptr, slave_addr, addr_10bit, req_10bit, LEN_1_BYTE, READ);
    i2c_start(ptr);
    uint8_t byte = i2c_read_u8(ptr);
    i2c_tc(ptr);
    i2c_stop(ptr);

    return byte; // CAN BE USED LATER FOR ALARMING OR TURN TO VOID
}

// p. 1198
// In the case of a write transfer,
// the TXIS flag is set after each byte transmission, after the 9th SCL pulse when an ACK is received.
// A TXIS event generates an interrupt if the TXIE bit is set in the I2C_CR1 register.
// The flag is cleared when the I2C_TXDR register is written with the next data byte to be transmitted.
// The number of TXIS events during the transfer corresponds to the value programmed in NBYTES[7:0].
// If the total number of data bytes to be sent is greater than 255, reload mode must be selected by setting the RELOAD bit in the I2C_CR2 register.
// In this case, when NBYTES data have been transferred, the TCR flag is set and the SCL line is stretched low until NBYTES[7:0] is written to a non-zero value.
// The TXIS flag is not set when a NACK is received.
//  • When RELOAD=0 and NBYTES data have been transferred:
//      – In automatic end mode (AUTOEND=1), a STOP is automatically sent.
//      – In software end mode (AUTOEND=0), the TC flag is set and the SCL line is stretched low in order to perform software actions:
//          A RESTART condition can be requested by setting the START bit in the I2C_CR2 register with the proper slave address configuration, and number of bytes to be transferred.
//          Setting the START bit clears the TC flag and the START condition is sent on the bus. A STOP condition can be requested by setting the STOP bit in the I2C_CR2 register.
//          Setting the STOP bit clears the TC flag and the STOP condition is sent on the bus.
//  • If a NACK is received: the TXIS flag is not set, and a STOP condition is automatically sent after the NACK reception.
//    the NACKF flag is set in the I2C_ISR register, and an interrupt is generated if the NACKIE bit is set.
bool i2c_write(I2C_TypeDef *ptr, uint8_t* buf, int len) {
    uint32_t i = 0; 

    while(i < len){
        uint32_t t = 0; // CONVERT TO FAULT TIMER

        while (!get_ptr_vol_bit_u32(&ptr->ISR, TXIS_BIT)){
            if (t > 100000) {
                return false;
            }
            t++;
        }

        set_ptr_vol_raw_u32(&ptr->TXDR, buf[i]);
        i++;
    }
    return true;
}

bool i2c_write_u8(I2C_TypeDef *ptr, uint8_t byte) {
    uint32_t i = 0; 

    while (!get_ptr_vol_bit_u32(&ptr->ISR, TXIS_BIT)){
        if (i > 100000) {
            return false;
        }
        i++;
    }

    set_ptr_vol_raw_u32(&ptr->TXDR, byte);
    return true;
}

uint8_t i2c_std_write(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t* buf, uint32_t len) {
    i2c_setup(ptr, slave_addr, addr_10bit, req_10bit, len, WRITE);
    bool start = i2c_start(ptr);
    bool write = i2c_write(ptr, buf, len);
    bool tc = i2c_tc(ptr);
    bool stop = i2c_stop(ptr);

    uint8_t val = 0;
    if (!start) {
        val += 1;
    }

    if (!write) {
        val += 2;
    }

    if (!tc) {
        val += 4;
    }

    if (!stop) {
        val += 8;
    }


    return val;       // CAN BE USED LATER FOR ALARMING OR TURN TO VOID
}

// PG. 1522-1523 (MATH TREE)
static void set_timing_register(I2C_TypeDef *ptr, uint32_t scll, uint32_t sclh, uint32_t sdadel, uint32_t scldel, uint32_t presc) {
    set_ptr_vol_u32(&ptr->TIMINGR, SCLL_OFFSET, SCL_MASK, scll);
    set_ptr_vol_u32(&ptr->TIMINGR, SCLH_OFFSET, SCL_MASK, sclh);
    set_ptr_vol_u32(&ptr->TIMINGR, SDADEL_OFFSET, DEL_MASK, sdadel);
    set_ptr_vol_u32(&ptr->TIMINGR, SCLDEL_OFFSET, DEL_MASK, scldel);  
    set_ptr_vol_u32(&ptr->TIMINGR, PRESC_OFFSET, DEL_MASK, presc);
}