#ifndef I2C_H_
#define I2C_H_

/* Register Base */
#define I2C1_BASE           (uint32_t)0x40005400 
//#define I2C2_BASE           (uint32_t)0x40005800 Does not exist in the 432KC
#define I2C3_BASE           (uint32_t)0x40005C00

/* USART Rcc Bits */
#define USART2_RCC_ENABLE   BIT_17

/* USART GPIO Bits */
#define I2C_GPIO_AF         AF4

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR1;      // Control Register 1
    volatile uint32_t CR2;      // Control Register 2
    volatile uint32_t OAR1;     // Own Address Register 1
    volatile uint32_t OAR2;     // Own Address Register 2
    volatile uint32_t TIMINGR;  // Timing Register
    volatile uint32_t TIMEOUTR; // Timeout Register
    volatile uint32_t ISR;      // Interrupt And Status Register
    volatile uint32_t ICR;      // Interrupt Flag Clear Register
    volatile uint32_t PECR;     // PEC Register
    volatile uint32_t RXDR;     // Receive Data Register
    volatile uint32_t TXDR;     // Transmit Data Register
} I2C_TypeDef;

/* Enumerations */
// 0 = Continous, 1 = ONS (clears en bit)
enum i2c_timing_mode {I2C_Sm_10KHz, I2C_Sm_100KHz, I2C_Fm_400KHz, I2C_Fm_Plus};

/* Public Functions */
void i2c_open(I2C_TypeDef *ptr, uint32_t sclk_mhz, uint32_t mode);
void i2c_start_bus(I2C_TypeDef *ptr, uint32_t sclk_mhz, uint32_t mode);
void i2c_stop_bus(I2C_TypeDef *ptr, uint32_t sclk_mhz, uint32_t mode);
void i2c_setup(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint32_t byte_cnt, bool write);
bool i2c_start(I2C_TypeDef *ptr);
bool i2c_stop(I2C_TypeDef *ptr);
bool i2c_tc(I2C_TypeDef *ptr);
bool i2c_read(I2C_TypeDef *ptr, uint8_t* buf, int len);
uint8_t i2c_read_u8(I2C_TypeDef *ptr);
bool i2c_write(I2C_TypeDef *ptr, uint8_t* buf, int len);
bool i2c_write_u8(I2C_TypeDef *ptr, uint8_t* buf, int len);

/* Public Combined Functions */
uint32_t i2c_std_read(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t* buf_write, uint32_t len_write,  uint8_t* buf_read, uint32_t len_read);
bool i2c_std_write(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t* buf, uint32_t len);

#endif /* I2C_H_ */