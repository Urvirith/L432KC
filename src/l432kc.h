#ifndef L432KC_H_
#define L432KC_H_

/* GLOBALS DEDICATED SPECIFICALLY TO THE L432KC BOARD THAT ARE UNIQUE TO THE PINS AND SIZE OF THE CPU */
/* RCC */
#define GPIOA_RCC_AHB2_ENABLE       BIT_0
#define GPIOB_RCC_AHB2_ENABLE       BIT_1

/* USER LED*/
#define PORTB_PIN3                  3
#define USER_LED                    PORTB_PIN3
#define USER_LED_BIT                BIT_3

/* USART 2*/
/* RCC */
#define USART2_RCC_APB1R1_ENABLE    BIT_17
/* GPIO */
#define USART2_GPIO_AF              AF7
/* PINS */
#define PORTA_PIN2                  2   //A7    TX
#define PORTA_PIN3                  3   //A2    RX
#define USART2_TX                   PORTA_PIN2
#define USART2_RX                   PORTA_PIN3

/* I2C 1*/
/* RCC */
#define I2C1_RCC_APB1R1_ENABLE      BIT_21
/* GPIO */
#define I2C1_GPIO_AF                AF4
/* PINS */
#define PORTB_PIN6                  6   //D5    SCL
#define PORTB_PIN7                  7   //D4    SDA
#define I2C1_SCL                    PORTB_PIN6
#define I2C1_SDA                    PORTB_PIN7

/* TIMER */
/* RCC */
#define TIMER2_RCC_APB1R1_ENABLE    BIT_0


#endif /* MAIN_H_ */