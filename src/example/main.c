// WORKING EXAMPLE FOR THE STM32L432KC
// THIS WILL ACTIVATE AND DEACTIVE THE GREEN USER LED ON THE BOARD,
// IT ALSO SHOWS HOW TO GET ACCESS TO REGISTERS, AND FORM VOLITILE POINTERS FOR USE LATER
// VOLITILE TELLS THE COMPILER TO NOT OPTIMIZE THE MEMORY LOCATIONS 


#include <stdint.h>

/* GPIO Port B REGISTERS */
#define GPIOB_BASE          (uint32_t)0x48000400                            /* GPIO Port B base address */
#define GPIOB_MODER         *((volatile uint32_t *) (GPIOB_BASE  + 0x00))   /* Port B Mode register */
#define GPIOB_OTYPER        *((volatile uint32_t *) (GPIOB_BASE  + 0x04))   /* Port B Output Type Register */
#define GPIOB_BSRR          *((volatile uint32_t *) (GPIOB_BASE  + 0x18))   /* Output Data Set And Reset Register */

#define PORTB_AHBEN         1                                               /* GPIOB Enable is located on AHB2 Board Bit 1 */


/* Reset and Clock Control (RCC) */
#define RCC_BASE            (uint32_t)0x40021000                            /* RCC base address */
#define RCC_CR              *((volatile uint32_t *) (RCC_BASE + 0x00))      /* Clock Control Register */
#define RCC_AHB2ENR         *((volatile uint32_t *) (RCC_BASE + 0x4C))      /* AHB1 Enable Register */

/* User required */
#define PORTB_PIN3         3U                                               /* USER LED on GPIO B Bus, Pin 3 */
#define MASK_2_BIT         3U                                               /* 2 bit mask, example 0011 = 3U */

/* Extern Keyword Allows To Be Call */
extern void system_init() {
    RCC_AHB2ENR |= (1 << PORTB_AHBEN);
}

extern void start() { 
    GPIOB_MODER &= (~(MASK_2_BIT << (PORTB_PIN3 * 2)));
    GPIOB_MODER |= (1 << (PORTB_PIN3 * 2));
    GPIOB_OTYPER &= (~(1 << PORTB_PIN3));

    int i = 0;
    while (1) {
        for (i = 0; i < 1000000; ++i) {
            if (i == 500000) {
                GPIOB_BSRR = (1 << PORTB_PIN3);
            } else if (i == 0) {
                GPIOB_BSRR = (1 << (PORTB_PIN3 + 16));
            }
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}
