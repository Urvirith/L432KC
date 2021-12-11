#ifndef L432KC_H_
#define L432KC_H_

/* Notes */
/* 1 Mhz = 1,000,000 CPS */
/* 1 Mhz = 1 CPus */

/* Register Base */
/* Reset and Clock Control (RCC) */
#define RCC_BASE                    ((uint32_t)0x40021000)                  /* RCC base address */

/* General Purpose I/O */
#define GPIOA_BASE                  ((uint32_t)0x48000000)                  /* GPIO Port A base address */
#define GPIOB_BASE                  ((uint32_t)0x48000400)                  /* GPIO Port B base address */
#define GPIOC_BASE                  ((uint32_t)0x48000800)                  /* GPIO Port C base address */
#define GPIOH_BASE                  ((uint32_t)0x48001C00)                  /* GPIO Port H base address */

/* Timers */
#define TIMER1_BASE                 ((uint32_t)0x40012C00)
#define TIMER2_BASE                 ((uint32_t)0x40000000)
#define TIMER3_BASE                 ((uint32_t)0x40000400)
#define TIMER6_BASE                 ((uint32_t)0x40001000)
#define TIMER7_BASE                 ((uint32_t)0x40001400)
#define TIMER15_BASE                ((uint32_t)0x40014000)
#define TIMER16_BASE                ((uint32_t)0x40014400)

/* USART (Universal Synchronous and Asynchronous Receiver Transmitter) */
#define USART1_BASE                 ((uint32_t)0x40013800)
#define USART2_BASE                 ((uint32_t)0x40004400)     
#define USART3_BASE                 ((uint32_t)0x40004800)

/* Inter-Integrated Circuit (I2C) */
#define I2C1_BASE                   ((uint32_t)0x40005400)
#define I2C2_BASE                   ((uint32_t)0x40005800)
#define I2C3_BASE                   ((uint32_t)0x40005C00)

/* Serial Peripheral Interface */
#define SPI1_BASE                   ((uint32_t)0x40013000)
#define SPI2_BASE                   ((uint32_t)0x40003800)
#define SPI3_BASE                   ((uint32_t)0x40003C00)

/* CAN Interface */
#define CAN_BASE                    ((uint32_t)0x40006400)

/* System Control Base */
#define NVIC_BASE                   ((uint32_t)0xE000E100)

/* GLOBALS DEDICATED SPECIFICALLY TO THE L432KC BOARD THAT ARE UNIQUE TO THE PINS AND SIZE OF THE CPU */
/* RCC */
#define GPIOA_RCC_AHB2_ENABLE       BIT_0
#define GPIOB_RCC_AHB2_ENABLE       BIT_1

/* USER LED*/
#define PORTB_PIN3                  3
#define USER_LED                    PORTB_PIN3
#define USER_LED_BIT                BIT_3

/* LED OUTPUTS */
#define PORTA_PIN0                  0
#define LED1                        PORTA_PIN0
#define LED1_BIT                    BIT_0

#define PORTA_PIN1                  1
#define LED2                        PORTA_PIN1
#define LED2_BIT                    BIT_1

#define PORTA_PIN3                  3
#define LED3                        PORTA_PIN3
#define LED3_BIT                    BIT_3

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
#define TIMER7_RCC_APB1R1_ENABLE    BIT_5

/* NVIC Enumerated Set Of All Interrupts On STM32L4 controllers */
typedef enum nvic_irq {
    WWDG_IRQ,	                    /*  0  Window Watchdog interrupt */
    PVD_PVM_IRQ,	                /*  1  PVD/PVM1/PVM2(1)/PVM3/PVM4 through EXTI */
    RTC_TAMP_STAMP_IRQ,	            /*  2  RTC Tamper or TimeStamp /CSS on LSE through EXTI line 19 interrupts */
    RTC_WKUP_IRQ,	                /*  3  RTC Wakeup timer through EXTI line 20 interrupt */
    FLASH_IRQ,	                    /*  4  Flash global interrupt */
    RCC_IRQ,	                    /*  5  RCC global interrupt */
    EXTI0_IRQ,	                    /*  6  EXTI Line0 interrupt */
    EXTI1_IRQ,	                    /*  7  EXTI Line1 interrupt */
    EXTI2_IRQ,	                    /*  8  EXTI Line2 interrupt */
    EXTI3_IRQ,	                    /*  9  EXTI Line3 interrupt */
    EXTI4_IRQ,	                    /* 10  EXTI Line4 interrupt */
    DMA1_CH1_IRQ,	                /* 11  DMA1 channel 1 interrupt */
    DMA1_CH2_IRQ,	                /* 12  DMA1 channel 2 interrupt */
    DMA1_CH3_IRQ,	                /* 13  DMA1 channel 3 interrupt */
    DMA1_CH4_IRQ,	                /* 14  DMA1 channel 4 interrupt */
    DMA1_CH5_IRQ,	                /* 15  DMA1 channel 5 interrupt */
    DMA1_CH6_IRQ,	                /* 16  DMA1 channel 6 interrupt */
    DMA1_CH7_IRQ,	                /* 17  DMA1 channel 7 interrupt */
    ADC1_2_IRQ,	                    /* 18  ADC1 and ADC2(2) global interrupt */
    CAN1_TX_IRQ,	                /* 19  CAN1_TX interrupts */
    CAN1_RX0_IRQ,	                /* 20  CAN1_RX0 interrupts */
    CAN1_RX1_IRQ,	                /* 21  CAN1_RX1 interrupt */
    CAN1_SCE_IRQ,	                /* 22  CAN1_SCE interrupt */
    EXTI9_5_IRQ,	                /* 23  EXTI Line[9:5] interrupts */
    TIM1_BRK_TIM15_IRQ,	            /* 24  TIM1 Break/TIM15 global interrupts  */
    TIM1_UP_TIM16_IRQ,	            /* 25  TIM1 Update/TIM16 global interrupts */
    TIM1_TRG_COM_IRQ,	            /* 26  TIM1 trigger and commutation interrupt */
    TIM1_CC_IRQ,	                /* 27  TIM1 capture compare interrupt */
    TIM2_IRQ,	                    /* 28  TIM2 global interrupt */
    TIM3_IRQ,	                    /* 29  TIM3 global interrupt */
    I2C1_EV_IRQ =           31,	    /* 31  I2C1 event interrupt  */
    I2C1_ER_IRQ,	                /* 32  I2C1 error interrupt */
    I2C2_EV_IRQ,	                /* 33  I2C2 event interrupt */
    I2C2_ER_IRQ,	                /* 34  I2C2 error interrupt */
    SPI1_IRQ,	                    /* 35  SPI1 global interrupt */
    SPI2_IRQ,	                    /* 36  SPI2 global interrupt */
    USART1_IRQ,	                    /* 37  USART1 global interrupt */
    USART2_IRQ,	                    /* 38  USART2 global interrupt */
    USART3_IRQ,	                    /* 39  USART3 global interrupt */
    EXTI15_10_IRQ,	                /* 40  EXTI Line[15:10] interrupts */
    RTC_ALARM_IRQ,	                /* 41  RTC alarms through EXTI line 18 interrupts */
    SDMMC1_IRQ =            49,	    /* 49  SDMMC1 global interrupt */
    SPI3_IRQ =              51,	    /* 51  SPI3 global interrupt */
    UART4_IRQ,	                    /* 52  UART4 global interrupt */
    TIM6_DACUNDER_IRQ =     54,	    /* 54  TIM6 global and DAC1(1) underrun interrupts */
    TIM7_IRQ,	                    /* 55  TIM7 global interrupt */
    DMA2_CH1_IRQ,	                /* 56  DMA2 channel 1 interrupt */
    DMA2_CH2_IRQ,	                /* 57  DMA2 channel 2 interrupt */
    DMA2_CH3_IRQ,	                /* 58  DMA2 channel 3 interrupt */
    DMA2_CH4_IRQ,	                /* 59  DMA2 channel 4 interrupt */
    DMA2_CH5_IRQ,	                /* 60  DMA2 channel 5 interrupt */
    DFSDM1_FLT0_IRQ,	            /* 61  DFSDM1_FLT0 global interrupt */
    DFSDM1_FLT1_IRQ,	            /* 62  DFSDM1_FLT1 global interrupt */
    COMP_IRQ =              64,	    /* 64  COMP1/COMP2(1) through EXTI lines 21/22 interrupts */
    LPTIM1_IRQ,	                    /* 65  LPTIM1 global interrupt */
    LPTIM2_IRQ,	                    /* 66  LPTIM2 global interrupt */
    USB_FS_IRQ,	                    /* 67  USB event interrupt through EXTI line 17 */
    DMA2_CH6_IRQ,	                /* 68  DMA2 channel 6 interrupt */
    DMA2_CH7_IRQ,	                /* 69  DMA2 channel 7 interrupt */
    LPUART1_IRQ,	                /* 70  LPUART1 global interrupt */
    QUADSPI_IRQ,	                /* 71  QUADSPI global interrupt */
    I2C3_EV_IRQ,	                /* 72  I2C3 event interrupt  */
    I2C3_ER_IRQ,	                /* 73  I2C3 error interrupt */
    SAI1_IRQ,	                    /* 74  SAI1 global interrupt */
    SWPMI1_IRQ =            76,	    /* 76  SWPMI1 global interrupt */
    TSC_IRQ,	                    /* 77  TSC global interrupt */
    LCD_IRQ,	                    /* 78  LCD global interrupt */
    AES_IRQ,	                    /* 79  AES global interrupt */
    RNG_IRQ,	                    /* 80  RNG global interrupt */
    FPU_IRQ,	                    /* 81  Floating point interrupt */
    CRS_IRQ,	                    /* 82  CRS interrupt */
    I2C4_EV_IRQ,	                /* 83  I2C4 event interrupt, wakeup through EXTI line 40 */
    I2C4_ER_IRQ,	                /* 84  I2C4 error interrupt */
} NVIC_IRQ;

#endif /* L552ZE_H_ */