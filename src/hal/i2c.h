#ifndef I2C_H_
#define I2C_H_

/* Register Base */

#define ADDR_7_BIT_ACT      false
#define ADDR_10_BIT_ACT     true


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
/* Speed of I2C bus, 10KHz, 100KHz 400KHz or Plus mode */
typedef enum i2c_timing_mode {
    I2C_Sm_10KHz,
    I2C_Sm_100KHz,
    I2C_Fm_400KHz,
    I2C_Fm_Plus
} I2C_TimingMode;

/* Public Functions */
void i2c_open(I2C_TypeDef *ptr, uint32_t sclk_mhz, uint32_t mode);
void i2c_start_bus(I2C_TypeDef *ptr);
void i2c_stop_bus(I2C_TypeDef *ptr);
void i2c_setup(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint32_t byte_cnt, bool write);
bool i2c_start(I2C_TypeDef *ptr);
bool i2c_stop(I2C_TypeDef *ptr);
bool i2c_tc(I2C_TypeDef *ptr);
bool i2c_read(I2C_TypeDef *ptr, uint8_t* buf, int len);
uint8_t i2c_read_u8(I2C_TypeDef *ptr);
bool i2c_write(I2C_TypeDef *ptr, uint8_t* buf, int len);
bool i2c_write_u8(I2C_TypeDef *ptr, uint8_t byte);

/* Public Combined Functions */
void i2c_std_read(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t* buf_write, uint32_t len_write,  uint8_t* buf_read, uint32_t len_read);
uint8_t i2c_std_write(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t* buf, uint32_t len);
uint8_t i2c_std_read_u8(I2C_TypeDef *ptr, uint32_t slave_addr, bool addr_10bit, bool req_10bit, uint8_t byte_write);
#endif /* I2C_H_ */