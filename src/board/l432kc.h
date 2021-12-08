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

/* Reset and Clock Control (RCC) */
#define RCC_GPIOA_AHB2EN            BIT_0                                   /* GPIOA Enable is located on AHB2 Board Bit 0 */
#define RCC_GPIOB_AHB2EN            BIT_1                                   /* GPIOB Enable is located on AHB2 Board Bit 1 */
#define RCC_GPIOC_AHB2EN            BIT_2                                   /* GPIOC Enable is located on AHB2 Board Bit 2 */
#define RCC_GPIOD_AHB2EN            BIT_3                                   /* GPIOD Enable is located on AHB2 Board Bit 3 */
#define RCC_GPIOE_AHB2EN            BIT_4                                   /* GPIOE Enable is located on AHB2 Board Bit 4 */
#define RCC_GPIOF_AHB2EN            BIT_5                                   /* GPIOE Enable is located on AHB2 Board Bit 4 */

/* General Purpose I/O */
/* NUCLEO BOARD PIN OUT SPECIFICS - NUCLEO - L552ZE-Q */
#define GPIOC_PIN7                  (uint32_t)7                             /* USER GREEN LED on GPIO C Bus, Pin 7  */
#define LED_GRN_PIN                 GPIOC_PIN7                              /* USER GREEN LED on GPIO C Bus, Pin 7  */
#define LED_GRN                     BIT_7                                   /* USER GREEN LED on GPIO C Bus, Pin 7  */
#define GPIOB_PIN7                  (uint32_t)7                             /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define LED_BLU_PIN                 GPIOB_PIN7                              /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define LED_BLU                     BIT_7                                   /* USER BLUE LED on GPIO B Bus, Pin 7   */
#define GPIOA_PIN9                  (uint32_t)9                             /* USER RED LED on GPIO A Bus, Pin 9    */
#define LED_RED_PIN                 GPIOA_PIN9                              /* USER RED LED on GPIO A Bus, Pin 9    */
#define LED_RED                     BIT_9                                   /* USER RED LED on GPIO A Bus, Pin 9    */

/* PWM Motor Driver Pins */
#define GPIOF_PIN7                  (uint32_t)7                             /* USER PIN on GPIO F Bus, Pin 7        */
#define GPIOF_PIN8                  (uint32_t)8                             /* USER PIN on GPIO F Bus, Pin 8        */
#define GPIOF_PIN9                  (uint32_t)9                             /* USER PIN on GPIO F Bus, Pin 9        */
#define GPIOE_PIN2                  (uint32_t)2                             /* USER PIN on GPIO E Bus, Pin 2       */
#define AXIS_ENABLE                 GPIOE_PIN2
#define DIR_Z_AXIS                  GPIOF_PIN8
#define DIR_Y_AXIS                  GPIOF_PIN7
#define DIR_X_AXIS                  GPIOF_PIN9
#define AXIS_ENABLE_PIN             BIT_2
#define DIR_Z_AXIS_PIN              BIT_8
#define DIR_Y_AXIS_PIN              BIT_7
#define DIR_X_AXIS_PIN              BIT_9

/* TIMER3 PWM CH1 */
#define GPIOE_PIN3                  (uint32_t)3                             /* PWM TIMER 3 on GPIO E Bus, Pin 3   */
#define TIM3_PWM1_PIN               GPIOE_PIN3                              /* PWM TIMER 3 on GPIO E Bus, Pin 3   */
#define TIM3_PWM1_AF                AF2                                     /* PWM TIMER 3 on GPIO E Bus, Pin 3   */

/* TIMER3 PWM CH2 */
#define GPIOE_PIN4                  (uint32_t)4                             /* PWM TIMER 3 on GPIO E Bus, Pin 4   */
#define TIM3_PWM2_PIN               GPIOE_PIN4                              /* PWM TIMER 3 on GPIO E Bus, Pin 4   */
#define TIM3_PWM2_AF                AF2                                     /* PWM TIMER 3 on GPIO E Bus, Pin 4   */

/* TIMER3 PWM CH3 */
#define GPIOE_PIN5                  (uint32_t)5                             /* PWM TIMER 3 on GPIO E Bus, Pin 5   */
#define TIM3_PWM3_PIN               GPIOE_PIN5                              /* PWM TIMER 3 on GPIO E Bus, Pin 5   */
#define TIM3_PWM3_AF                AF2                                     /* PWM TIMER 3 on GPIO E Bus, Pin 5   */

/* TIMER3 PWM CH4 */
#define GPIOE_PIN6                  (uint32_t)6                             /* PWM TIMER 3 on GPIO E Bus, Pin 6   */
#define TIM3_PWM4_PIN               GPIOE_PIN6                              /* PWM TIMER 3 on GPIO E Bus, Pin 6   */
#define TIM3_PWM4_AF                AF2                                     /* PWM TIMER 3 on GPIO E Bus, Pin 6   */

/* Timer */
#define RCC_TIMER2_APB1R1EN         BIT_0
#define RCC_TIMER3_APB1R1EN         BIT_1
#define RCC_TIMER4_APB1R1EN         BIT_2

/* USART (Universal Synchronous and Asynchronous Receiver Transmitter) */
#define RCC_USART3_APB1R1EN         BIT_18
#define GPIOD_PIN8                  (uint32_t)8                             /* GPIO Bus D Pin 8 TX - D1   */
#define GPIOD_PIN9                  (uint32_t)9                             /* GPIO Bus D Pin 9 RX - D0   */
#define USART3_TX                   GPIOD_PIN8
#define USART3_RX                   GPIOD_PIN9

/* GPIO SETUP */
#define USART_MODE                  Gpio_Alternate
#define USART_OTYPE                 Gpio_Push_Pull
#define USART_AF                    AF7

/* SPI (Serial Peripheral Interface) */
/* SPI 1*/
/* RCC */
#define RCC_SPI1_APB2REN            BIT_12
#define GPIOB_PIN4                  (uint32_t)4                             /* GPIO Bus B Pin 4 MISO  */
#define GPIOB_PIN5                  (uint32_t)5                             /* GPIO Bus B Pin 5 MOSI  */
#define GPIOB_PIN3                  (uint32_t)3                             /* GPIO Bus B Pin 3 SCK   */
#define GPIOA_PIN4                  (uint32_t)4                             /* GPIO Bus A Pin 4 NSS   */
#define GPIOA_PIN7                  (uint32_t)7                             /* GPIO Bus A Pin 7 SS - D11  */
#define SPI1_MISO                   GPIOB_PIN4
#define SPI1_MOSI                   GPIOB_PIN5
#define SPI1_SCK                    GPIOB_PIN3
#define SPI1_NSS                    GPIOA_PIN4
#define SPI1_SS                     GPIOA_PIN7                              /* This Is An Input */

/* GPIO SETUP */
#define SPI_MODE                    Gpio_Alternate
#define SPI_OTYPE                   Gpio_Push_Pull
#define SPI_AF                      AF5

/* SPI 2*/
/* RCC */
//#define RCC_SPI2_APB1R1EN:        BIT14

/* SPI 3*/
/* RCC */
//#define RCC_SPI3_APB1R1EN:        BIT15


/* I2C 1*/
//#define I2C1_RCC_APB1R1_ENABLE:     u32 = common::BIT_21;
//#define PORTB_PIN6:                 u32 = 6;    //D5    SCL
//#define PORTB_PIN7:                 u32 = 7;    //D4    SDA
//#define I2C1_SCL:                   u32 = PORTB_PIN6;
//#define I2C1_SDA:                   u32 = PORTB_PIN7;

/* GPIO SETUP */
//#define CAN_MODE:                   gpio::Mode = gpio::Mode::Alt;
//#define CAN_OTYPE:                  gpio::OType = gpio::OType::PushPull;
//#define CAN_AF:                     gpio::AltFunc = gpio::AltFunc::Af9;
//#define CAN_OSPEED:                 gpio::OSpeed = gpio::OSpeed::High;
//#define CAN_PUPD:                   gpio::Pupd = gpio::Pupd::Pu;

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


enum nvic_irq {
    WWDG_IRQ,                   /*  0       Window Watchdog */
    PDV_PVM_IRQ,                /*  1       PVD/PVM1/PVM2/PVM3/PVM4 through EXTI lines 16/35/36/37/38 interrupts */
    RTC_IRQ,                    /*  2       RTC secure global interrupts (EXTI line 18) */
    RTC_S_IRQ,                  /*  3       RTC secure global interrupts (EXTI line 18) */
    TAMP_IRQ,                   /*  4       Tamper global interrupt (EXTI line 19) */
    TAMP_S_IRQ,                 /*  5       Tamper secure global interrupt (EXTI line 20) */
    FLASH_IRQ,                  /*  6       Flash memory global interrupt */
    FLASH_S_IRQ,                /*  7       Flash memory secure global interrupt */
    GTZC_IRQ,                   /*  8       TZIC secure global interrupt */
    RCC_IRQ,                    /*  9       RCC global interrupt */
    RCC_S_IRQ,                  /*  10      RCC secure global interrupt */
    EXTI0_IRQ,                  /*  11      EXTI Line0 interrupt */ 
    EXTI1_IRQ,                  /*  12      EXTI Line1 interrupt */
    EXTI2_IRQ,                  /*  13      EXTI Line2 interrupt */
    EXTI3_IRQ,                  /*  14      EXTI Line3 interrupt */
    EXTI4_IRQ,                  /*  15      EXTI Line4 interrupt */
    EXTI5_IRQ,                  /*  16      EXTI Line5 interrupt */
    EXTI6_IRQ,                  /*  17      EXTI Line6 interrupt */
    EXTI7_IRQ,                  /*  18      EXTI Line7 interrupt */
    EXTI8_IRQ,                  /*  19      EXTI Line8 interrupt */
    EXTI9_IRQ,                  /*  20      EXTI Line9 interrupt */
    EXTI10_IRQ,                 /*  21      EXTI Line10 interrupt */
    EXTI11_IRQ,                 /*  22      EXTI Line11 interrupt */
    EXTI12_IRQ,                 /*  23      EXTI Line12 interrupt */
    EXTI13_IRQ,                 /*  24      EXTI Line13 interrupt */
    EXTI14_IRQ,                 /*  25      EXTI Line14 interrupt */
    EXTI15_IRQ,                 /*  26      EXTI Line15 interrupt */
    DMAMUX1_IRQ,                /*  27      DMAMUX1 non-secure interrupt */
    DMAMUX1_S_IRQ,              /*  28      DMAMUX1 secure interrupt */
    DMA1_Channel1_IRQ,          /*  29      DMA1 Channel 1 interrupt */
    DMA1_Channel2_IRQ,          /*  30      DMA1 Channel 2 interrupt */
    DMA1_Channel3_IRQ,          /*  31      DMA1 Channel 3 interrupt */
    DMA1_Channel4_IRQ,          /*  32      DMA1 Channel 4 interrupt */
    DMA1_Channel5_IRQ,          /*  33      DMA1 Channel 5 interrupt */
    DMA1_Channel6_IRQ,          /*  34      DMA1 Channel 6 interrupt */
    DMA1_Channel7_IRQ,          /*  35      DMA1 Channel 7 interrupt */
    DMA1_Channel8_IRQ,          /*  36      DMA1 Channel 8 interrupt */
    ADC1_2_IRQ,                 /*  37      ADC1 & ADC2 interrupt */
    DAC_IRQ,                    /*  38      DAC1&2 underrun errors interrupt */
    FDCAN1_IT0_IRQ,             /*  39      FDCAN1 Interrupt 0 interrupt */
    FDCAN1_IT1_IRQ,             /*  40      FDCAN1 Interrupt 1 interrupt */
    TIM1_BRK_IRQ,               /*  41      TIM1 Break interrupt */
    TIM1_UP_IRQ,                /*  42      TIM1 Update interrupt */
    TIM1_TRG_COM_IRQ,           /*  43      TIM1 Trigger and Commutation interrupt */
    TIM1_CC_IRQ,                /*  44      TIM1 Capture Compare interrupt */
    TIM2_IRQ,                   /*  45      TIM2 interrupt */
    TIM3_IRQ,                   /*  46      TIM3 interrupt */
    TIM4_IRQ,                   /*  47      TIM4 interrupt */
    TIM5_IRQ,                   /*  48      TIM5 interrupt */
    TIM6_IRQ,                   /*  49      TIM6 interrupt */
    TIM7_IRQ,                   /*  50      TIM7 interrupt */
    TIM8_BRK_IRQ,               /*  51      TIM8 Break interrupt */
    TIM8_UP_IRQ,                /*  52      TIM8 Update interrupt */
    TIM8_TRG_COM_IRQ,           /*  53      TIM8 Trigger and Commutation interrupt */
    TIM8_CC_IRQ,                /*  54      TIM8 Capture Compare interrupt */
    I2C1_EV_IRQ,                /*  55      I2C1 Event interrupt */
    I2C1_ER_IRQ,                /*  56      I2C1 Error interrupt */
    I2C2_EV_IRQ,                /*  57      I2C2 Event interrupt */
    I2C2_ER_IRQ,                /*  58      I2C2 Error interrupt */
    SPI1_IRQ,                   /*  59      SPI1 interrupt */
    SPI2_IRQ,                   /*  60      SPI2 interrupt */
    USART1_IRQ,                 /*  61      USART1 interrupt */
    USART2_IRQ,                 /*  62      USART2 interrupt */
    USART3_IRQ,                 /*  63      USART3 interrupt */
    UART4_IRQ,                  /*  64      UART4 interrupt */
    UART5_IRQ,                  /*  65      UART5 interrupt */
    LPUART1_IRQ,                /*  66      LP UART1 interrupt */
    LPTIM1_IRQ,                 /*  67      LP TIM1 interrupt */
    LPTIM2_IRQ,                 /*  68      LP TIM2 interrupt */
    TIM15_IRQ,                  /*  69      TIM15 interrupt */
    TIM16_IRQ,                  /*  70      TIM16 interrupt */
    TIM17_IRQ,                  /*  71      TIM17 interrupt */
    COMP_IRQ,                   /*  72      COMP1&2 interrupt */
    USB_FS_IRQ,                 /*  73      USB FS interrupt */
    CRS_IRQ,                    /*  74      CRS interrupt */
    FMC_IRQ,                    /*  75      FMC interrupt */
    OCTOSPI1_IRQ,               /*  76      OctoSPI1 global interrupt */
    SDMMC1_IRQ = 78,            /*  78      SDMMC1 interrupt */
    DMA2_Channel1_IRQ,          /*  80      DMA2 Channel 1 interrupt */
    DMA2_Channel2_IRQ,          /*  81      DMA2 Channel 2 interrupt */
    DMA2_Channel3_IRQ,          /*  82      DMA2 Channel 3 interrupt */
    DMA2_Channel4_IRQ,          /*  83      DMA2 Channel 4 interrupt */
    DMA2_Channel5_IRQ,          /*  84      DMA2 Channel 5 interrupt */
    DMA2_Channel6_IRQ,          /*  85      DMA2 Channel 6 interrupt */
    DMA2_Channel7_IRQ,          /*  86      DMA2 Channel 7 interrupt */
    DMA2_Channel8_IRQ,          /*  87      DMA2 Channel 8 interrupt */
    I2C3_EV_IRQ,                /*  88      I2C3 event interrupt */
    I2C3_ER_IRQ,                /*  89      I2C3 error interrupt */
    SAI1_IRQ,                   /*  90      Serial Audio Interface 1 global interrupt */
    SAI2_IRQ,                   /*  91      Serial Audio Interface 2 global interrupt */
    TSC_IRQ,                    /*  92      Touch Sense Controller global interrupt */
    RNG_IRQ = 94,               /*  94      RNG global interrupt */
    FPU_IRQ,                    /*  95      FPU interrupt */
    HASH_IRQ,                   /*  96      HASH interrupt */
    LPTIM3_IRQ = 98,            /*  98      LP TIM3 interrupt */
    SPI3_IRQ,                   /*  99      SPI3 interrupt */
    I2C4_ER_IRQ,                /*  100     I2C4 error interrupt */
    I2C4_EV_IRQ,                /*  101     I2C4 event interrupt */
    DFSDM1_FLT0_IRQ,            /*  102     DFSDM1 Filter 0 global interrupt */
    DFSDM1_FLT1_IRQ,            /*  103     DFSDM1 Filter 1 global interrupt */
    DFSDM1_FLT2_IRQ,            /*  104     DFSDM1 Filter 2 global interrupt */
    DFSDM1_FLT3_IRQ,            /*  105     DFSDM1 Filter 3 global interrupt */
    UCPD1_IRQ,                  /*  106     UCPD1 interrupt */
    ICACHE_IRQ,                 /*  107     ICACHE interrupt */
};

#endif /* L552ZE_H_ */