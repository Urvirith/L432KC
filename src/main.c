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
#include "driver/i2c/fxas21002.h"
//#include "driver/i2c/fxos8700.h"

/*REMOVE WITH MAKE FILE*/
//#include "hal/common.c"
//#include "hal/gpio.c"
//#include "hal/rcc.c"
//#include "hal/timer.c"
//#include "hal/usart.c"
//#include "hal/i2c.c"
//#include "driver/i2c/fxas21002.c"
//#include "driver/i2c/fxos8700.c"

/*---------------------*/
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE) 
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)                 /* GPIO Structure Declare */
#define TIMER2              ((TIMER_TypeDef *) TIMER2_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define LEN                 8

extern void system_init() {
    rcc_write_msi_range(RCC, _16MHz);
    rcc_write_ahb2_enr(RCC, GPIOA_RCC_AHB2_ENABLE);
    rcc_write_ahb2_enr(RCC, GPIOB_RCC_AHB2_ENABLE);
    rcc_write_apb1_enr1(RCC, TIMER2_RCC_APB1R1_ENABLE);
    rcc_write_apb1_enr1(RCC, USART2_RCC_APB1R1_ENABLE);
    rcc_write_apb1_enr1(RCC, I2C1_RCC_APB1R1_ENABLE);
}

extern void start() { 
    /* USER LED SETUP */
    gpio_type(GPIOB, USER_LED, Gpio_Output, Gpio_Push_Pull, AF0);
    /* USART SETUP */
    gpio_type(GPIOA, USART2_TX, Gpio_Alternate, Gpio_Push_Pull, USART2_GPIO_AF);
    gpio_type(GPIOA, USART2_RX, Gpio_Alternate, Gpio_Push_Pull, USART2_GPIO_AF);
    /* I2C SETUP */
    gpio_type(GPIOB, I2C1_SCL, Gpio_Alternate, Gpio_Open_Drain, I2C1_GPIO_AF);
    gpio_type(GPIOB, I2C1_SDA, Gpio_Alternate, Gpio_Open_Drain, I2C1_GPIO_AF);
    gpio_speed(GPIOB, I2C1_SCL, Gpio_Low_Speed);
    gpio_speed(GPIOB, I2C1_SDA, Gpio_Low_Speed);
    gpio_pupd(GPIOB, I2C1_SCL, Gpio_NoPupd);
    gpio_pupd(GPIOB, I2C1_SDA, Gpio_NoPupd);
    /* TIMER SETUP */
    timer_open(TIMER2, Timer_Cont, Timer_Upcount);
    timer_set_time(TIMER2, 500, 16000, 1500);
    timer_start(TIMER2);
    /* DRIVER SETUP */
    usart_open(USART2, USART_8_Bits, USART_1_StopBit, USART_9600_BAUD, 16000, USART_Oversample_16);
    i2c_open(I2C1, _16MHz, I2C_Fm_400KHz);

    while (!timer_get_flag(TIMER2)) {

    }
    timer_clr_flag(TIMER2);

    fxas210002_init(I2C1, Fxas21002_Gyro_250DPS);
    //fxos8700_init(I2C1, Fxos8700_Accel_2G);

    while (!timer_get_flag(TIMER2)) {

    }
    timer_clr_flag(TIMER2);

    uint8_t buf_fxas[8] = {0x03, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x0D};
    uint16_t buffer_fxas[3] = {0, 0, 0};
    //uint8_t buf_fxos[14] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x0D};
    //uint16_t buffer_fxos[6] = {0, 0, 0, 0, 0, 0};

    int i = 0;
    
    while (1) {
        if (timer_get_flag(TIMER2)) {
            fxas210002_read(I2C1, Fxas21002_Gyro_250DPS, buffer_fxas, 3);
            buf_fxas[1] = (uint8_t) ((buffer_fxas[0] >> 8) & 0xFF);
            buf_fxas[2] = (uint8_t) ((buffer_fxas[0] >> 0) & 0xFF);
            buf_fxas[3] = (uint8_t) ((buffer_fxas[1] >> 8) & 0xFF);
            buf_fxas[4] = (uint8_t) ((buffer_fxas[1] >> 0) & 0xFF);
            buf_fxas[5] = (uint8_t) ((buffer_fxas[2] >> 8) & 0xFF);
            buf_fxas[6] = (uint8_t) ((buffer_fxas[2] >> 0) & 0xFF);

            usart_write(USART2, buf_fxas, 8);

            /*
            fxos8700_read(I2C1, Fxos8700_Accel_2G, buffer_fxos, 6);
            buf_fxos[1] = (uint8_t) ((buffer_fxos[0] >> 8) & 0xFF);
            buf_fxos[2] = (uint8_t) ((buffer_fxos[0] >> 0) & 0xFF);
            buf_fxos[3] = (uint8_t) ((buffer_fxos[1] >> 8) & 0xFF);
            buf_fxos[4] = (uint8_t) ((buffer_fxos[1] >> 0) & 0xFF);
            buf_fxos[5] = (uint8_t) ((buffer_fxos[2] >> 8) & 0xFF);
            buf_fxos[6] = (uint8_t) ((buffer_fxos[2] >> 0) & 0xFF);
            buf_fxos[7] = (uint8_t) ((buffer_fxos[3] >> 8) & 0xFF);
            buf_fxos[8] = (uint8_t) ((buffer_fxos[3] >> 0) & 0xFF);
            buf_fxos[9] = (uint8_t) ((buffer_fxos[4] >> 8) & 0xFF);
            buf_fxos[10] = (uint8_t) ((buffer_fxos[4] >> 0) & 0xFF);
            buf_fxos[11] = (uint8_t) ((buffer_fxos[5] >> 8) & 0xFF);
            buf_fxos[12] = (uint8_t) ((buffer_fxos[5] >> 0) & 0xFF);
            
            usart_write(USART2, buf_fxos, 14);
            */

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