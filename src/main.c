//DUMMY MAIN TO ALLOW FOR THE TURN ON AND OFF OF LED IN C
//USED TO TROUBLE SHOOT REST OF CODE

#include "main.h"
#include "hal/common.h"
#include "hal/gpio.h"
#include "hal/rcc.h"
#include "hal/timer.h"
#include "hal/usart.h"

/*REMOVE WITH MAKE FILE*/
#include "hal/common.c"
#include "hal/gpio.c"
#include "hal/rcc.c"
#include "hal/timer.c"
#include "hal/usart.c"

/*---------------------*/
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE) 
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)                 /* GPIO Structure Declare */
#define TIMER2              ((TIMER_TypeDef *) TIMER2_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)

#define PORTB_PIN3          3
#define USER_LED            PORTB_PIN3
#define USER_LED_BIT        BIT_3

#define PORTA_PIN2          2     //A7        TX
#define PORTA_PIN3          3     //A2        RX

extern void system_init() {
    rcc_write_msi_range(RCC, _32MHz);
    rcc_write_ahb2_enr(RCC, GPIOA_RCC_ENABLE);
    rcc_write_ahb2_enr(RCC, GPIOB_RCC_ENABLE);
    rcc_write_apb1_enr1(RCC, TIMER2_RCC_ENABLE);
    rcc_write_apb1_enr1(RCC, USART2_RCC_ENABLE);
}

extern void start() { 
    gpio_io_type(GPIOB, USER_LED, Gpio_Output, Gpio_Push_Pull, AF0);
    gpio_io_type(GPIOA, PORTA_PIN2, Gpio_Alternate, Gpio_Push_Pull, USART2_GPIO_AF);
    gpio_io_type(GPIOA, PORTA_PIN3, Gpio_Alternate, Gpio_Push_Pull, USART2_GPIO_AF);
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 50, 32000, 1500);
    timer_start(TIMER2);
    usart_open(USART2, USART_8_Bits, USART_1_StopBit, USART_9600_BAUD, 32000, USART_Oversample_16);

    uint8_t readarray[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D};
    uint8_t failarray[2] = {0x39, 0x0D};
    
    int i = 0;
    
    while (1) {
        if (usart_get_read(USART2)) { // This will shut off the loop if we dont see a good read flag
            if (usart_read(USART2, readarray, 8) < 0 ) {
                usart_write(USART2, failarray, 2);
            } else {
                usart_write(USART2, readarray, 9);
            }
        }

        if (timer_get_flag(TIMER2)) {
            if (i == 0) {
                gpio_set_pin(GPIOB, USER_LED_BIT);
                i = 1;
            } else {
                gpio_clr_pin(GPIOB, USER_LED_BIT);
                i = 0;
            }
            timer_clr_flag(TIMER2);
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}

// 
/*void wait_loop() {
    for (i = 0; i < 1000000; ++i) {
        if (i == 500000) {
            gpio_set_pin(GPIOB, USER_LED_BIT);
        } else if (i == 0) {
            gpio_clr_pin(GPIOB, USER_LED_BIT);
        }
    }
}*/ 