//DUMMY MAIN TO ALLOW FOR THE TURN ON AND OFF OF LED IN C
//USED TO TROUBLE SHOOT REST OF CODE

#include "l432kc.h"
#include "main.h"
#include "hal/common.h"
#include "hal/gpio.h"
#include "hal/rcc.h"
#include "hal/timer.h"
#include "hal/usart.h"
#include "hal/i2c.h"

/*REMOVE WITH MAKE FILE*/
#include "hal/common.c"
#include "hal/gpio.c"
#include "hal/rcc.c"
#include "hal/timer.c"
#include "hal/usart.c"
#include "hal/i2c.c"

/*---------------------*/
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE) 
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)                 /* GPIO Structure Declare */
#define TIMER2              ((TIMER_TypeDef *) TIMER2_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)

extern void system_init() {
    rcc_write_msi_range(RCC, _16MHz);
    rcc_write_ahb2_enr(RCC, GPIOA_RCC_AHB2_ENABLE);
    rcc_write_ahb2_enr(RCC, GPIOB_RCC_AHB2_ENABLE);
    rcc_write_apb1_enr1(RCC, TIMER2_RCC_APB1R1_ENABLE);
    rcc_write_apb1_enr1(RCC, USART2_RCC_APB1R1_ENABLE);
    rcc_write_apb1_enr1(RCC, I2C1_RCC_APB1R1_ENABLE);
}

extern void start() { 
    gpio_io_type(GPIOB, USER_LED, Gpio_Output, Gpio_Push_Pull, AF0);
    gpio_io_type(GPIOA, USART2_TX, Gpio_Alternate, Gpio_Push_Pull, USART2_GPIO_AF);
    gpio_io_type(GPIOA, USART2_RX, Gpio_Alternate, Gpio_Push_Pull, USART2_GPIO_AF);
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 50, 16000, 1500);
    timer_start(TIMER2);
    usart_open(USART2, USART_8_Bits, USART_1_StopBit, USART_9600_BAUD, 16000, USART_Oversample_16);

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