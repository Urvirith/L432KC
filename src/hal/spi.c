#include "common.h"
#include "spi.h"

/* Register Masks */
/* CR1 */
#define BR_MASK             MASK_3_BIT
/* CR2 */
#define DS_MASK             MASK_4_BIT
/* SR */
#define LVL_MASK            MASK_2_BIT
#define ERROR_MASK          MASK_3_BIT

/* Register Bits */
/* CR1 */
#define CPHA_BIT            BIT_0
#define CPOL_BIT            BIT_1
#define MSTR_BIT            BIT_2
#define SPE_BIT             BIT_6
#define LSB_FIRST_BIT       BIT_7
#define SSI_BIT             BIT_8
#define SSM_BIT             BIT_9
#define CRCL_BIT            BIT_11
#define CRCNEXT_BIT         BIT_12
#define CRCEN_BIT           BIT_13
/* CR2 */
#define FRXTH_BIT           BIT_12
/* SR */
#define RXNE_BIT            BIT_0
#define TXE_BIT             BIT_1
#define CRCERR_BIT          BIT_4
#define MODF_BIT            BIT_5
#define OVR_BIT             BIT_6
#define BSY_BIT             BIT_7
#define FRE_BIT             BIT_8

/* Register Offsets */
/* CR1 */
#define BR_OFFSET           3
/* CR2 */
#define DS_OFFSET           8
/* SR */
#define ERROR_OFFSET        4
#define FRLVL_OFFSET        9
#define FTLVL_OFFSET        11

/* SPI Setup */
/*
    1.Write proper GPIO registers: Configure GPIO for MOSI, MISO and SCK pins.
    2.  Write to the SPI_CR1 register:
        a)  Configure the serial clock baud rate using the BR[2:0] bits (Note: 4).
        b)  Configure the CPOL and CPHA bits combination to define one of the 
            four relationships between the data transfer and the serial clock 
            (CPHA must be cleared in NSSP mode). 
            (Note: 2 - except the case when CRC is enabled at TI mode).
        c)  Select simplex or half-duplex mode by configuring RXONLY or BIDIMODE and BIDIOE 
            (RXONLY and BIDIMODE can't be set at the same time).
        d)  Configure the LSBFIRST bit to define the frame format (Note: 2).
        e)  Configure the CRCL and CRCEN bits if CRC is needed 
            (while SCK clock signal is at idle state).
        f)  Configure SSM and SSI (Notes: 2 & 3).
        g)  Configure the MSTR bit (in multimaster NSS configuration, avoid conflict state on 
            NSS if master is configured to prevent MODF error).
    3.  Write to SPI_CR2 register:
        a)  Configure the DS[3:0] bits to select the data length for the transfer.
        b)  Configure SSOE (Notes: 1 & 2 & 3).
        c)  Set the FRF bit if the TI protocol is required (keep NSSP bit cleared in TI mode).
        d)  Set the NSSP bit if the NSS pulse mode between two data units is required 
            (keep CHPA and TI bits cleared in NSSP mode).
        e)  Configure the FRXTH bit. The RXFIFO threshold must be aligned to the 
            read access size for the SPIx_DR register.
        f)  Initialize LDMA_TX and LDMA_RX bits if DMA is used in packed mode.
    4.      Write to SPI_CRCPR register: Configure the CRC polynomial if needed.
*/
void spi_open(SPI_TypeDef *ptr, SPI_BaudRate br, SPI_ClockSetup cs, SPI_BitFirst bit, SPI_DataSize ds) {
    clr_ptr_vol_bit_u32(&ptr->CR1, SPE_BIT);
    set_ptr_vol_u32(&ptr->CR1, BR_OFFSET, BR_MASK, br);

    switch (cs) {
        case SPI_RisingEdgeClockLow:
            clr_ptr_vol_bit_u32(&ptr->CR1, CPHA_BIT);
            clr_ptr_vol_bit_u32(&ptr->CR1, CPOL_BIT);
            break;
        case SPI_FallingEdgeClockLow:
            set_ptr_vol_bit_u32(&ptr->CR1, CPHA_BIT);
            clr_ptr_vol_bit_u32(&ptr->CR1, CPOL_BIT);
            break;
        case SPI_RisingEdgeClockHigh:
            clr_ptr_vol_bit_u32(&ptr->CR1, CPHA_BIT);
            set_ptr_vol_bit_u32(&ptr->CR1, CPOL_BIT);
            break;
        case SPI_FallingEdgeClockHigh:
            set_ptr_vol_bit_u32(&ptr->CR1, CPHA_BIT);
            set_ptr_vol_bit_u32(&ptr->CR1, CPOL_BIT);
            break;
    }

    switch (bit) {
        case SPI_Msb:
            clr_ptr_vol_bit_u32(&ptr->CR1, LSB_FIRST_BIT);
            break;
        case SPI_Lsb:
            set_ptr_vol_bit_u32(&ptr->CR1, LSB_FIRST_BIT);
            break;
    }
    
    set_ptr_vol_bit_u32(&ptr->CR1, CRCL_BIT);                /* Set CRC To 8-Bit */
    set_ptr_vol_bit_u32(&ptr->CR1, CRCEN_BIT);               /* Set CRC Enabled  */
    set_ptr_vol_bit_u32(&ptr->CR1, SSI_BIT);                /* Set CRC To 8-Bit */
    set_ptr_vol_bit_u32(&ptr->CR1, SSM_BIT); 
    set_ptr_vol_bit_u32(&ptr->CR1, MSTR_BIT);                /* Set Master Mode  */
    set_ptr_vol_u32(&ptr->CR2, DS_OFFSET, DS_MASK, ds);      /* Set Datasize     */
}

void spi_enable(SPI_TypeDef *ptr) {
    set_ptr_vol_bit_u32(&ptr->CR1, SPE_BIT);
}

/*
    The correct disable procedure is (except when receive only mode is used):
    1. Wait until FTLVL[1:0] = 00 (no more data to transmit).
    2. Wait until BSY=0 (the last data frame is processed).
    3. Disable the SPI (SPE=0).
    4. Read data until FRLVL[1:0] = 00 (read all the received data).
    The correct disable procedure for certain receive only modes is:
    Note:
    1. Interrupt the receive flow by disabling SPI (SPE=0) in the specific time window while
    the last data frame is ongoing.
    2. Wait until BSY=0 (the last data frame is processed).
    3. Read data until FRLVL[1:0] = 00 (read all the received data).
*/
void spi_disable(SPI_TypeDef *ptr) {
    while(get_ptr_vol_u32(&ptr->SR, FTLVL_OFFSET, LVL_MASK) != 0) { 
        // Wait For Busy 
    }

    while(get_ptr_vol_bit_u32(&ptr->SR, BSY_BIT)) { 
        // Wait For Busy 
    }

    clr_ptr_vol_bit_u32(&ptr->CR1, SPE_BIT);
}

/* Read Flag Function */
bool spi_get_read(SPI_TypeDef *ptr) {
    return get_ptr_vol_bit_u32(&ptr->SR, RXNE_BIT);
}

/* Read Function */
uint32_t spi_read(SPI_TypeDef *ptr, uint8_t* buf, int len) {
    uint32_t i = 0; // Index based on len
    uint32_t t = 0; // Time Out Rotation
    
    while(i < len) {
        if (get_ptr_vol_u32(&ptr->SR, FRLVL_OFFSET, LVL_MASK) != 0) {
            buf[i] = get_ptr_vol_raw_u8((volatile uint8_t *)&ptr->DR);
            t = 0;
            i++;
        }

        if (t < TIMEOUT) { // Check to see if delayed more than 50us
            t++;
        } else {
            return i;
        }
    }

    return i;
}

/* Write Function */
void spi_write(SPI_TypeDef *ptr, uint8_t* buf, int len) {
    uint32_t i = 0;
    
    while(i < len) {
        if (get_ptr_vol_u32(&ptr->SR, FTLVL_OFFSET, LVL_MASK) != 3) {
            set_ptr_vol_raw_u8((volatile uint8_t *)&ptr->DR, buf[i]);
            i++;
        }
    }

    set_ptr_vol_bit_u32(&ptr->CR1, CRCNEXT_BIT);    
}

/* Get An Error */
bool spi_error(SPI_TypeDef *ptr) {
    if (get_ptr_vol_bit_u32(&ptr->SR, CRCERR_BIT) || get_ptr_vol_bit_u32(&ptr->SR, MODF_BIT) || get_ptr_vol_bit_u32(&ptr->SR, OVR_BIT)) {
        return true;
    } else {
        return false;
    }
}

/* Get The Exact Error Our Of The SR */
uint32_t spi_error_byte(SPI_TypeDef *ptr) {
    return get_ptr_vol_u32(&ptr->SR, ERROR_OFFSET, ERROR_MASK);
}
