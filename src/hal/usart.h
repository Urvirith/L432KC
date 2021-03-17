#ifndef USART_H_
#define USART_H_

// USART DRIVER
// ARM USART MODULE
// USART Description - is on pg 1194

    // Any USART bidirectional communication requires a minimum of two pins: Receive data In (RX) and Transmit data Out (TX):
    // • RX: Receive data Input. This is the serial data input.
    //   Oversampling techniques are used for data recovery by discriminating between valid incoming data and noise.
    // • TX: Transmit data Output. When the transmitter is disabled, the output pin returns to its I/O port configuration.
    //   When the transmitter is enabled and nothing is to be transmitted, the TX pin is at high level.
    //   In Single-wire and Smartcard modes, this I/O is used to transmit and receive the data

    // Serial data are transmitted and received through these pins in normal USART mode. The frames are comprised of:
    // • An Idle Line prior to transmission or reception
    // • A start bit • A data word (7, 8 or 9 bits) least significant bit first
    // • 0.5, 1, 1.5, 2 stop bits indicating that the frame is complete
    // • The USART interface uses a baud rate generator • A status register (USART_ISR)
    // • Receive and transmit data registers (USART_RDR, USART_TDR)
    // • A baud rate register (USART_BRR)
    // • A guard-time register (USART_GTPR) in case of Smartcard mode.

    // Refer to Section 38.8: USART registers on page 1238 for the definitions of each bit.
    // The following pin is required to interface in synchronous mode and Smartcard mode:
    // • CK: Clock output. This pin outputs the transmitter data clock for synchronous transmission corresponding to SPI master mode
    //  (no clock pulses on start bit and stop bit, and a software option to send a clock pulse on the last data bit).
    //  In parallel, data can be received synchronously on RX. This can be used to control peripherals that have shift registers.
    //  The clock phase and polarity are software programmable. In Smartcard mode, CK output can provide the clock to the smartcard.

    // The following pins are required in RS232 Hardware flow control mode:
    // • CTS: Clear To Send blocks the data transmission at the end of the current transfer when high
    // • RTS: Request to send indicates that the USART is ready to receive data (when low).
    // The following pin is required in RS485 Hardware control mode:
    // • DE: Driver Enable activates the transmission mode of the external transceiver.

/* Register Base */
#define USART1_BASE         (uint32_t)0x40013800
#define USART2_BASE         (uint32_t)0x40004400
#define USART3_BASE         (uint32_t)0x40004800

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR1;      // Control Register 1
    volatile uint32_t CR2;      // Control Register 2
    volatile uint32_t CR3;      // Control Register 2
    volatile uint32_t BRR;      // Baud Rate Register Register
    volatile uint32_t GTPR;     // Guard Time / Prescaler Register
    volatile uint32_t RTOR;     // Receiver Timeout Register
    volatile uint32_t RQR;      // Request Register
    volatile uint32_t ISR;      // Interrupt And Status Register
    volatile uint32_t ICR;      // Interrupt Flag Clear Register
    volatile uint32_t RDR;      // Receive Data Register
    volatile uint32_t TDR;      // Transmit Data Register
} USART_TypeDef;

/* Enumerations */
enum usart_over_sample {USART_Oversample_16, USART_Oversample_8};
enum usart_word_length {USART_8_Bits, USART_9_Bits, USART_7_Bits};
enum usart_stop_length {USART_1_StopBit, USART_0_5_StopBit, USART_2_StopBit, USART_1_5_StopBit};
enum usart_baud_rate {
    USART_1200_BAUD      = 1200, 
    USART_1800_BAUD      = 1800,
    USART_2400_BAUD      = 2400, 
    USART_4800_BAUD      = 4800,
    USART_9600_BAUD      = 9600, 
    USART_19200_BAUD     = 19200,
    USART_28800_BAUD     = 28800, 
    USART_38400_BAUD     = 38400,
    USART_57600_BAUD     = 57600, 
    USART_76800_BAUD     = 76800,
    USART_115200_BAUD    = 115200, 
    USART_230400_BAUD    = 230400,
    USART_460800_BAUD    = 460800, 
    USART_576000_BAUD    = 576000,
    USART_921600_BAUD    = 921600, 
};

/* Public Functions */
void usart_open(USART_TypeDef *ptr, uint32_t word_len, uint32_t stop, uint32_t baud, uint32_t sclk_khz, uint32_t over8);
bool usart_get_read(USART_TypeDef *ptr);
int usart_read(USART_TypeDef *ptr, uint8_t* buf, int len);
void usart_write(USART_TypeDef *ptr, uint8_t* buf, int len);

#endif /* USART_H_ */