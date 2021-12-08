#include "common.h"
#include "usart.h"

/* Register Masks */
/* CR1 */
#define OVER8_MASK          MASK_4_BIT
/* CR2 */
#define STOP_BIT_MASK       MASK_2_BIT
/* BRR */
#define BAUD_RATE_MASK      MASK_16_BIT
/* RTOR */
#define RTO_TIMEO_MASK      MASK_24_BIT

/* Register Bits */
/* CR1 */
#define UE_BIT              BIT_0
#define RE_BIT              BIT_2
#define TE_BIT              BIT_3
#define OVER_8_BIT          BIT_15
/* CR2 */
#define RTOEN_BIT           BIT_23
/* ICR */
#define FECF_BIT            BIT_1
#define ORECR_BIT           BIT_3
#define IDLECF_BIT          BIT_4
#define RTOCF_BIT           BIT_11
/* ISR */
#define FE_BIT              BIT_1
#define ORE_BIT             BIT_3
#define IDLE_BIT            BIT_4
#define RXNE_BIT            BIT_5
#define TC_BIT              BIT_6
#define TXE_BIT             BIT_7


/* Register Offsets */
/* CR2 */
#define STOP_BIT_OFFSET     12
/* BRR */
#define BAUD_RATE_OFFSET    0
/* RTOR */
#define RTO_TIMEO_OFFSET    0
     
/* Register Shifts */
/* CR1 */
#define OVER8_SHIFT         1

/* Private Functions */
static uint32_t clock_setup(USART_BaudRate baud, uint32_t sclk_khz, USART_OverSample over8);

void usart_open(USART_TypeDef *ptr, USART_WordLength word_len, USART_StopLength stop, USART_BaudRate baud, uint32_t sclk_khz, USART_OverSample over8) { 
    if (word_len == USART_8_Bits) {             // Set the word length, based off the split bits in CR1
        clr_ptr_vol_bit_u32(&ptr->CR1, BIT_12);
        clr_ptr_vol_bit_u32(&ptr->CR1, BIT_24);
    } else if (word_len == USART_9_Bits) {
        set_ptr_vol_bit_u32(&ptr->CR1, BIT_12);
        clr_ptr_vol_bit_u32(&ptr->CR1, BIT_24);
    } else if (word_len == USART_7_Bits) {
        clr_ptr_vol_bit_u32(&ptr->CR1, BIT_12);
        set_ptr_vol_bit_u32(&ptr->CR1, BIT_24);
    } else {                                    // If loaded with not standard default to 8 bits
        clr_ptr_vol_bit_u32(&ptr->CR1, BIT_12);
        clr_ptr_vol_bit_u32(&ptr->CR1, BIT_24);
    }

    if (over8 == USART_Oversample_8) {
        set_ptr_vol_bit_u32(&ptr->CR1, OVER_8_BIT);
    } else {
        clr_ptr_vol_bit_u32(&ptr->CR1, OVER_8_BIT);
    }

    set_ptr_vol_bit_u32(&ptr->CR2, RTOEN_BIT);
    set_ptr_vol_u32(&ptr->BRR, BAUD_RATE_OFFSET, BAUD_RATE_MASK, clock_setup(baud, sclk_khz, over8));
    set_ptr_vol_u32(&ptr->CR2, STOP_BIT_OFFSET, STOP_BIT_MASK, stop);
    set_ptr_vol_bit_u32(&ptr->CR1, UE_BIT);
    set_ptr_vol_bit_u32(&ptr->CR1, RE_BIT);
    set_ptr_vol_u32(&ptr->RTOR, RTO_TIMEO_OFFSET, RTO_TIMEO_MASK, RTO_TIMEO_VALUE);
}


// p. 1205
// Character reception procedure
// 1. Program the M bits in USART_CR1 to define the word length.
// 2. Select the desired baud rate using the baud rate register USART_BRR
// 3. Program the number of stop bits in USART_CR2.
// 4. Enable the USART by writing the UE bit in USART_CR1 register to 1.
// 5. Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take place.
//    Configure the DMA register as explained in multibuffer communication.
// 6. Set the RE bit USART_CR1.
//    This enables the receiver which begins searching for a start bit.

// When a character is received:
// • The RXNE bit is set to indicate that the content of the shift register is transferred to the RDR.
//   In other words, data has been received and can be read (as well as its associated error flags).
// • An interrupt is generated if the RXNEIE bit is set.
// • The error flags can be set if a frame error, noise or an overrun error has been detected during reception. PE flag can also be set with RXNE.
// • In multibuffer, RXNE is set after every byte received and is cleared by the DMA read of the Receive data Register.
// • In single buffer mode, clearing the RXNE bit is performed by a software read to the USART_RDR register.
//   The RXNE flag can also be cleared by writing 1 to the RXFRQ in the USART_RQR register.
//   The RXNE bit must be cleared before the end of the reception of the next character to avoid an overrun error.
bool usart_get_read(USART_TypeDef *ptr){
    return get_ptr_vol_bit_u32(&ptr->ISR, RXNE_BIT);
}

// MOVE TO a uint8_t pointer can slim down the data being transfered here. Set up test for reading USART and reflecting!!
int usart_read(USART_TypeDef *ptr, uint8_t* buf, int len){
    set_ptr_vol_raw_u32(&ptr->ICR, RTOCF_BIT);
    set_ptr_vol_raw_u32(&ptr->ICR, FECF_BIT);
    set_ptr_vol_raw_u32(&ptr->ICR, IDLECF_BIT);
    set_ptr_vol_raw_u32(&ptr->ICR, ORECR_BIT);

    int i = 0; // Index based on len
    int t = 0; // Index for loop trap, if line goes idle, prevent being trapped by dead line. Convert to fail timer for more accurate usage.

    while(i < len) {
        if (usart_get_read(ptr)) {
            buf[i] = get_ptr_vol_raw_u8((volatile uint8_t *)&ptr->RDR);
            t = 0;
            i++;
        }

        if (get_ptr_vol_bit_u32(&ptr->ISR, FE_BIT) | get_ptr_vol_bit_u32(&ptr->ISR, IDLE_BIT) | get_ptr_vol_bit_u32(&ptr->ISR, ORE_BIT)) {
            return -1;
        }

        if (t > TIMEOUT) {
            return -2;
        }

        t++;
    }
}

// p. 1202
// Character transmission procedure
// 1. Program the M bits in USART_CR1 to define the word length.
// 2. Select the desired baud rate using the USART_BRR register.
// 3. Program the number of stop bits in USART_CR2.
// 4. Enable the USART by writing the UE bit in USART_CR1 register to 1.
// 5. Select DMA enable (DMAT) in USART_CR3 if multibuffer communication is to take place.
//    Configure the DMA register as explained in multibuffer communication.
// 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
// 7. Write the data to send in the USART_TDR register (this clears the TXE bit).
//    Repeat this for each data to be transmitted in case of single buffer.
// 8. After writing the last data into the USART_TDR register, wait until TC=1.
//    This indicates that the transmission of the last frame is complete.
//    This is required for instance when the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
void usart_write(USART_TypeDef *ptr, uint8_t* buf, int len){
    set_ptr_vol_bit_u32(&ptr->CR1, TE_BIT);

    int i = 0;
    while(i < len){
        if (get_ptr_vol_bit_u32(&ptr->ISR, TXE_BIT)) {
            set_ptr_vol_raw_u8((volatile uint8_t *)&ptr->TDR, buf[i]);
            i++;
        }
    }

    while (get_ptr_vol_bit_u32(&ptr->ISR, TC_BIT) == false) {
        // SPIN TO WAIT UNTILL THE BIT IS COMPLETE#
    }

    clr_ptr_vol_bit_u32(&ptr->CR1, TE_BIT);
}

// USARTDIV is an unsigned fixed point number that is coded on the USART_BRR register.
// • When OVER8 = 0, BRR = USARTDIV.
// • When OVER8 = 1 – BRR[2:0] = USARTDIV[3:0] shifted 1 bit to the right.
//   – BRR[3] must be kept cleared.
//   – BRR[15:4] = USARTDIV[15:4]
static uint32_t clock_setup(USART_BaudRate baud, uint32_t sclk_khz, USART_OverSample over8) {
    if (over8 == USART_Oversample_8) {
        uint32_t baud_div = ((sclk_khz * SCLK_HZ) * 2) / baud;

        return ((baud_div & (~OVER8_MASK)) & ((baud_div & OVER8_MASK) >> OVER8_SHIFT));
    } else {
        return  ((sclk_khz * SCLK_HZ) / baud)   ;
    }
}
