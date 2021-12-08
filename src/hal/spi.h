#ifndef SPI_H_
#define SPI_H_

// SPI DRIVER
// ARM SPI MODULE
// SPI Description - is on pg 1699

/* Serial Peripheral Interface */

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR1;              // Control Register 1
    volatile uint32_t CR2;              // Control Register 2
    volatile uint32_t SR;               // Baud Rate Register Register
    volatile uint32_t DR;               // Guard Time / Prescaler Register
    volatile uint32_t CRCPR;            // Receiver Timeout Register
    volatile uint32_t RXCRCPR;          // Request Register
    volatile uint32_t TXCRCPR;          // Interrupt And Status Register
} SPI_TypeDef;

/* Enumerations */

// Baud Rate Control 000: fPCLK/2 001: fPCLK/4 010: fPCLK/8 011: fPCLK/16 100: fPCLK/32 101: fPCLK/64 110: fPCLK/128 111: fPCLK/256
/* Enumeration For Baud Rate Divisor */
typedef enum spi_baud_rate {
    SPI_Div_2,
    SPI_Div_4,
    SPI_Div_8,
    SPI_Div_16,
    SPI_Div_32,
    SPI_Div_64,
    SPI_Div_128,
    SPI_Div_256
} SPI_BaudRate;

// These bits configure the data length for SPI transfers.
// 0000: Not used 0001: Not used 0010: Not used 
// 0011: 4-bit 0100: 5-bit 0101: 6-bit
// 0110: 7-bit 0111: 8-bit 1000: 9-bit
// 1001: 10-bit 1010: 11-bit 1011: 12-bit
// 1100: 13-bit 1101: 14-bit 1110: 15-bit
// 1111: 16-bit
// If software attempts to write one of the “Not used” values, 
// they are forced to the value “0111”(8-bit)
/* Enumeration For Word Size */
typedef enum spi_data_size {
    SPI_Bits_4      = 0x03,
    SPI_Bits_5      = 0x04,
    SPI_Bits_6      = 0x05,
    SPI_Bits_7      = 0x06,
    SPI_Bits_8      = 0x07,
    SPI_Bits_9      = 0x08,
    SPI_Bits_10     = 0x09,
    SPI_Bits_11     = 0x0A,
    SPI_Bits_12     = 0x0B,
    SPI_Bits_13     = 0x0C,
    SPI_Bits_14     = 0x0D,
    SPI_Bits_15     = 0x0E,
    SPI_Bits_16     = 0x0F
} SPI_DataSize;

// CPHA = 0 READS THE FIRST BIT ON RISING EDGE OF CLOCK, CPHA = 1 READS THE FIRST BIT ON FALLING EDGE OF CLOCK
// CPOL IS HOW THE CLOCK BEHAVES, CPOL = TRUE, CLOCK IS HIGH UNTIL USED, FALSE CLOCK IS LOW UNTILL USED
/* Enumeration For Clock Setup */
typedef enum spi_clock_setup {
    SPI_RisingEdgeClockLow,
    SPI_FallingEdgeClockLow,
    SPI_RisingEdgeClockHigh,
    SPI_FallingEdgeClockHigh
} SPI_ClockSetup;

// Least Significant Bit First, Most Significiant Bit First
/* Enumeration For Bit Transmission Setup */
typedef enum spi_bit_first {
    SPI_Msb,
    SPI_Lsb
} SPI_BitFirst;

/* Public Functions */
void spi_open(SPI_TypeDef *ptr, SPI_BaudRate br, SPI_ClockSetup cs, SPI_BitFirst bit, SPI_DataSize ds);
void spi_enable(SPI_TypeDef *ptr);
void spi_disable(SPI_TypeDef *ptr);
bool spi_get_read(SPI_TypeDef *ptr);
uint32_t spi_read(SPI_TypeDef *ptr, uint8_t* buf, int len);
void spi_write(SPI_TypeDef *ptr, uint8_t* buf, int len);
bool spi_error(SPI_TypeDef *ptr);
uint32_t spi_error_byte(SPI_TypeDef *ptr);

#endif /* SPI_H_ */
