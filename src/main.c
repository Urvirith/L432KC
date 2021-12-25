//DUMMY MAIN TO ALLOW FOR THE TURN ON AND OFF OF LED IN C
//USED TO TROUBLE SHOOT REST OF CODE

#include "board/l432kc.h"
#include "hal/common.h"
#include "hal/gpio.h"
#include "hal/rcc.h"
#include "hal/timer.h"
#include "hal/nvic.h"
#include "main.h"


/*---------------------*/
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE) 
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)                 /* GPIO Structure Declare */
#define TIMER2              ((TIMER_TypeDef *) TIMER2_BASE)
#define TIMER7              ((TIMER_TypeDef *) TIMER7_BASE)
#define NVIC                ((NVIC_TypeDef *) NVIC_BASE)

extern void sys_init() {
    rcc_write_msi_range(RCC, Clk16MHz);
    rcc_write_ahb2_enr(RCC, GPIOA_RCC_AHB2_ENABLE);
    rcc_write_ahb2_enr(RCC, GPIOB_RCC_AHB2_ENABLE);
    rcc_write_apb1_enr1(RCC, TIMER2_RCC_APB1R1_ENABLE);
    rcc_write_apb1_enr1(RCC, TIMER7_RCC_APB1R1_ENABLE);
}

extern void start() { 
    /* USER LED SETUP */
    gpio_type(GPIOB, USER_LED, Gpio_Output, Gpio_Push_Pull, AF0);
    gpio_type(GPIOA, LED1, Gpio_Output, Gpio_Push_Pull, AF0);
    gpio_type(GPIOA, LED2, Gpio_Output, Gpio_Push_Pull, AF0);
    gpio_type(GPIOA, LED3, Gpio_Output, Gpio_Push_Pull, AF0);
    //gpio_pupd(GPIOA, LED1, Gpio_PullDown);

    /* TIMER SETUP */
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 2000, 16000, 500);

    timer_open(TIMER7, Timer_Ons, Timer_Upcount);
    timer_set_interrupt(TIMER7);
    timer_ons_delay(TIMER7, 500);

    nvic_enable_interrupt(NVIC, TIM7_IRQ);
    timer_set_time(TIMER7, 1000, 16000, 1000);
    timer_start(TIMER7);
    timer_start(TIMER2);

    int i = 0;
    
    while (1) {
        if (timer_get_flag(TIMER2)) {
            timer_clr_flag(TIMER2);

            switch(i) {
                case 0:
                    gpio_set_pin(GPIOA, LED1_BIT);
                    gpio_clr_pin(GPIOA, LED2_BIT);
                    gpio_clr_pin(GPIOA, LED3_BIT);
                    break;
                case 1:
                    gpio_clr_pin(GPIOA, LED1_BIT);
                    gpio_set_pin(GPIOA, LED2_BIT);
                    gpio_clr_pin(GPIOA, LED3_BIT);
                    break;
                case 2:
                    gpio_clr_pin(GPIOA, LED1_BIT);
                    gpio_clr_pin(GPIOA, LED2_BIT);
                    gpio_set_pin(GPIOA, LED3_BIT);
                    break;
            }

            if (i < 3) {
                i += 1;
            } else {
                i = 0;
            }
        }
    }
}

extern void __aeabi_unwind_cpp_pr0() {
    //loop {}
}

volatile uint8_t led = 0;

/* BEING USED TO TEST THE NVIC */
extern void TIM7_IRQHandler() { 
    timer_clr_flag(TIMER7);

    if (led == 0) {
        gpio_set_pin(GPIOB, USER_LED_BIT);
        led = 1;
    } else {
        gpio_clr_pin(GPIOB, USER_LED_BIT);
        led = 0;
    }

    timer_start(TIMER7);
}
