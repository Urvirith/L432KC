/**************************************************************************//**
 * @file     startup_ARMCM4.S
 * @brief    CMSIS-Core(M) Device Startup File for Cortex-M4 Device
 * @version  V2.2.0
 * @date     26. May 2021
 ******************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

                .syntax  unified
                .arch    armv7e-m

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    MemManage_Handler                  /* -12 MPU Fault Handler */
                .long    BusFault_Handler                   /* -11 Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVC Handler */
                .long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long    WWDG_IRQHandler	                /*  0  Window Watchdog interrupt */
                .long    PVD_PVM_IRQHandler	                /*  1  PVD/PVM1/PVM2(1)/PVM3/PVM4 through EXTI */
                .long    RTC_TAMP_STAMP_IRQHandler	        /*  2  RTC Tamper or TimeStamp /CSS on LSE through EXTI line 19 interrupts */
                .long    RTC_WKUP_IRQHandler	            /*  3  RTC Wakeup timer through EXTI line 20 interrupt */
                .long    FLASH_IRQHandler	                /*  4  Flash global interrupt */
                .long    RCC_IRQHandler	                    /*  5  RCC global interrupt */
                .long    EXTI0_IRQHandler	                /*  6  EXTI Line0 interrupt */
                .long    EXTI1_IRQHandler	                /*  7  EXTI Line1 interrupt */
                .long    EXTI2_IRQHandler	                /*  8  EXTI Line2 interrupt */
                .long    EXTI3_IRQHandler	                /*  9  EXTI Line3 interrupt */
                .long    EXTI4_IRQHandler	                /* 10  EXTI Line4 interrupt */
                .long    DMA1_CH1_IRQHandler	            /* 11  DMA1 channel 1 interrupt */
                .long    DMA1_CH2_IRQHandler	            /* 12  DMA1 channel 2 interrupt */
                .long    DMA1_CH3_IRQHandler	            /* 13  DMA1 channel 3 interrupt */
                .long    DMA1_CH4_IRQHandler	            /* 14  DMA1 channel 4 interrupt */
                .long    DMA1_CH5_IRQHandler	            /* 15  DMA1 channel 5 interrupt */
                .long    DMA1_CH6_IRQHandler	            /* 16  DMA1 channel 6 interrupt */
                .long    DMA1_CH7_IRQHandler	            /* 17  DMA1 channel 7 interrupt */
                .long    ADC1_2_IRQHandler	                /* 18  ADC1 and ADC2(2) global interrupt */
                .long    CAN1_TX_IRQHandler	                /* 19  CAN1_TX interrupts */
                .long    CAN1_RX0_IRQHandler	            /* 20  CAN1_RX0 interrupts */
                .long    CAN1_RX1_IRQHandler	            /* 21  CAN1_RX1 interrupt */
                .long    CAN1_SCE_IRQHandler	            /* 22  CAN1_SCE interrupt */
                .long    EXTI9_5_IRQHandler	                /* 23  EXTI Line[9:5] interrupts */
                .long    TIM1_BRK_TIM15_IRQHandler	        /* 24  TIM1 Break/TIM15 global interrupts  */
                .long    TIM1_UP_TIM16_IRQHandler	        /* 25  TIM1 Update/TIM16 global interrupts */
                .long    TIM1_TRG_COM_IRQHandler	        /* 26  TIM1 trigger and commutation interrupt */
                .long    TIM1_CC_IRQHandler	                /* 27  TIM1 capture compare interrupt */
                .long    TIM2_IRQHandler	                /* 28  TIM2 global interrupt */
                .long    TIM3_IRQHandler	                /* 29  TIM3 global interrupt */
                .long    0	                                /* 30  Reserved */
                .long    I2C1_EV_IRQHandler	                /* 31  I2C1 event interrupt  */
                .long    I2C1_ER_IRQHandler	                /* 32  I2C1 error interrupt */
                .long    I2C2_EV_IRQHandler	                /* 33  I2C2 event interrupt */
                .long    I2C2_ER_IRQHandler	                /* 34  I2C2 error interrupt */
                .long    SPI1_IRQHandler	                /* 35  SPI1 global interrupt */
                .long    SPI2_IRQHandler	                /* 36  SPI2 global interrupt */
                .long    USART1_IRQHandler	                /* 37  USART1 global interrupt */
                .long    USART2_IRQHandler	                /* 38  USART2 global interrupt */
                .long    USART3_IRQHandler	                /* 39  USART3 global interrupt */
                .long    EXTI15_10_IRQHandler	            /* 40  EXTI Line[15:10] interrupts */
                .long    RTC_ALARM_IRQHandler	            /* 41  RTC alarms through EXTI line 18 interrupts */
                .long    0	                                /* 42  Reserved */
                .long    0	                                /* 43  Reserved */
                .long    0	                                /* 44  Reserved */
                .long    0	                                /* 45  Reserved */
                .long    0	                                /* 46  Reserved */
                .long    0	                                /* 47  Reserved */
                .long    0	                                /* 48  Reserved */
                .long    SDMMC1_IRQHandler	                /* 49  SDMMC1 global interrupt */
                .long    0	                                /* 50  Reserved */
                .long    SPI3_IRQHandler	                /* 51  SPI3 global interrupt */
                .long    UART4_IRQHandler	                /* 52  UART4 global interrupt */
                .long    0	                                /* 53  Reserved */
                .long    TIM6_DACUNDER_IRQHandler	        /* 54  TIM6 global and DAC1(1) underrun interrupts */
                .long    TIM7_IRQHandler	                /* 55  TIM7 global interrupt */
                .long    DMA2_CH1_IRQHandler	            /* 56  DMA2 channel 1 interrupt */
                .long    DMA2_CH2_IRQHandler	            /* 57  DMA2 channel 2 interrupt */
                .long    DMA2_CH3_IRQHandler	            /* 58  DMA2 channel 3 interrupt */
                .long    DMA2_CH4_IRQHandler	            /* 59  DMA2 channel 4 interrupt */
                .long    DMA2_CH5_IRQHandler	            /* 60  DMA2 channel 5 interrupt */
                .long    DFSDM1_FLT0_IRQHandler	            /* 61  DFSDM1_FLT0 global interrupt */
                .long    DFSDM1_FLT1_IRQHandler	            /* 62  DFSDM1_FLT1 global interrupt */
                .long    0	                                /* 63  Reserved */
                .long    COMP_IRQHandler	                /* 64  COMP1/COMP2(1) through EXTI lines 21/22 interrupts */
                .long    LPTIM1_IRQHandler	                /* 65  LPTIM1 global interrupt */
                .long    LPTIM2_IRQHandler	                /* 66  LPTIM2 global interrupt */
                .long    USB_FS_IRQHandler	                /* 67  USB event interrupt through EXTI line 17 */
                .long    DMA2_CH6_IRQHandler	            /* 68  DMA2 channel 6 interrupt */
                .long    DMA2_CH7_IRQHandler	            /* 69  DMA2 channel 7 interrupt */
                .long    LPUART1_IRQHandler	                /* 70  LPUART1 global interrupt */
                .long    QUADSPI_IRQHandler	                /* 71  QUADSPI global interrupt */
                .long    I2C3_EV_IRQHandler	                /* 72  I2C3 event interrupt  */
                .long    I2C3_ER_IRQHandler	                /* 73  I2C3 error interrupt */
                .long    SAI1_IRQHandler	                /* 74  SAI1 global interrupt */
                .long    0	                                /* 75  Reserved */
                .long    SWPMI1_IRQHandler	                /* 76  SWPMI1 global interrupt */
                .long    TSC_IRQHandler	                    /* 77  TSC global interrupt */
                .long    LCD_IRQHandler	                    /* 78  LCD global interrupt */
                .long    AES_IRQHandler	                    /* 79  AES global interrupt */
                .long    RNG_IRQHandler	                    /* 80  RNG global interrupt */
                .long    FPU_IRQHandler	                    /* 81  Floating point interrupt */
                .long    CRS_IRQHandler	                    /* 82  CRS interrupt */
                .long    I2C4_EV_IRQHandler	                /* 83  I2C4 event interrupt, wakeup through EXTI line 40 */
                .long    I2C4_ER_IRQHandler	                /* 84  I2C4 error interrupt */

                .space   (139 * 4)                          /* Interrupts 85 .. 224 are left out */
__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
                bl       sys_init

                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]                /* source address */
                ldr      r2, [r4, #4]            /* destination address */
                ldr      r3, [r4, #8]            /* word count */
                lsls     r3, r3, #2              /* byte count */

.L_loop0_0:
                subs     r3, #4                  /* decrement byte count */
                ittt     ge
                ldrge    r0, [r1, r3]
                strge    r0, [r2, r3]
                bge      .L_loop0_0

                adds     r4, #12
                b        .L_loop0
.L_loop0_done:

                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]                /* destination address */
                ldr      r2, [r3, #4]            /* word count */
                lsls     r2, r2, #2              /* byte count */
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4                  /* decrement byte count */
                itt      ge
                strge    r0, [r1, r2]
                bge      .L_loop2_0

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:

                bl       start

                .fnend
                .size    Reset_Handler, . - Reset_Handler

/* The default macro is not used for HardFault_Handler
 * because this results in a poor debug illusion.
 */
                .thumb_func
                .type    HardFault_Handler, %function
                .weak    HardFault_Handler
                .fnstart
HardFault_Handler:
                b        .
                .fnend
                .size    HardFault_Handler, . - HardFault_Handler

                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  WWDG_IRQHandler	                /*  0  Window Watchdog interrupt */
                Set_Default_Handler  PVD_PVM_IRQHandler	                /*  1  PVD/PVM1/PVM2(1)/PVM3/PVM4 through EXTI */
                Set_Default_Handler  RTC_TAMP_STAMP_IRQHandler	        /*  2  RTC Tamper or TimeStamp /CSS on LSE through EXTI line 19 interrupts */
                Set_Default_Handler  RTC_WKUP_IRQHandler	            /*  3  RTC Wakeup timer through EXTI line 20 interrupt */
                Set_Default_Handler  FLASH_IRQHandler	                /*  4  Flash global interrupt */
                Set_Default_Handler  RCC_IRQHandler	                    /*  5  RCC global interrupt */
                Set_Default_Handler  EXTI0_IRQHandler	                /*  6  EXTI Line0 interrupt */
                Set_Default_Handler  EXTI1_IRQHandler	                /*  7  EXTI Line1 interrupt */
                Set_Default_Handler  EXTI2_IRQHandler	                /*  8  EXTI Line2 interrupt */
                Set_Default_Handler  EXTI3_IRQHandler	                /*  9  EXTI Line3 interrupt */
                Set_Default_Handler  EXTI4_IRQHandler	                /* 10  EXTI Line4 interrupt */
                Set_Default_Handler  DMA1_CH1_IRQHandler	            /* 11  DMA1 channel 1 interrupt */
                Set_Default_Handler  DMA1_CH2_IRQHandler	            /* 12  DMA1 channel 2 interrupt */
                Set_Default_Handler  DMA1_CH3_IRQHandler	            /* 13  DMA1 channel 3 interrupt */
                Set_Default_Handler  DMA1_CH4_IRQHandler	            /* 14  DMA1 channel 4 interrupt */
                Set_Default_Handler  DMA1_CH5_IRQHandler	            /* 15  DMA1 channel 5 interrupt */
                Set_Default_Handler  DMA1_CH6_IRQHandler	            /* 16  DMA1 channel 6 interrupt */
                Set_Default_Handler  DMA1_CH7_IRQHandler	            /* 17  DMA1 channel 7 interrupt */
                Set_Default_Handler  ADC1_2_IRQHandler	                /* 18  ADC1 and ADC2(2) global interrupt */
                Set_Default_Handler  CAN1_TX_IRQHandler	                /* 19  CAN1_TX interrupts */
                Set_Default_Handler  CAN1_RX0_IRQHandler	            /* 20  CAN1_RX0 interrupts */
                Set_Default_Handler  CAN1_RX1_IRQHandler	            /* 21  CAN1_RX1 interrupt */
                Set_Default_Handler  CAN1_SCE_IRQHandler	            /* 22  CAN1_SCE interrupt */
                Set_Default_Handler  EXTI9_5_IRQHandler	                /* 23  EXTI Line[9:5] interrupts */
                Set_Default_Handler  TIM1_BRK_TIM15_IRQHandler	        /* 24  TIM1 Break/TIM15 global interrupts  */
                Set_Default_Handler  TIM1_UP_TIM16_IRQHandler	        /* 25  TIM1 Update/TIM16 global interrupts */
                Set_Default_Handler  TIM1_TRG_COM_IRQHandler	        /* 26  TIM1 trigger and commutation interrupt */
                Set_Default_Handler  TIM1_CC_IRQHandler	                /* 27  TIM1 capture compare interrupt */
                Set_Default_Handler  TIM2_IRQHandler	                /* 28  TIM2 global interrupt */
                Set_Default_Handler  TIM3_IRQHandler	                /* 29  TIM3 global interrupt */
                Set_Default_Handler  I2C1_EV_IRQHandler	                /* 31  I2C1 event interrupt  */
                Set_Default_Handler  I2C1_ER_IRQHandler	                /* 32  I2C1 error interrupt */
                Set_Default_Handler  I2C2_EV_IRQHandler	                /* 33  I2C2 event interrupt */
                Set_Default_Handler  I2C2_ER_IRQHandler	                /* 34  I2C2 error interrupt */
                Set_Default_Handler  SPI1_IRQHandler	                /* 35  SPI1 global interrupt */
                Set_Default_Handler  SPI2_IRQHandler	                /* 36  SPI2 global interrupt */
                Set_Default_Handler  USART1_IRQHandler	                /* 37  USART1 global interrupt */
                Set_Default_Handler  USART2_IRQHandler	                /* 38  USART2 global interrupt */
                Set_Default_Handler  USART3_IRQHandler	                /* 39  USART3 global interrupt */
                Set_Default_Handler  EXTI15_10_IRQHandler	            /* 40  EXTI Line[15:10] interrupts */
                Set_Default_Handler  RTC_ALARM_IRQHandler	            /* 41  RTC alarms through EXTI line 18 interrupts */
                Set_Default_Handler  SDMMC1_IRQHandler	                /* 49  SDMMC1 global interrupt */
                Set_Default_Handler  SPI3_IRQHandler	                /* 51  SPI3 global interrupt */
                Set_Default_Handler  UART4_IRQHandler	                /* 52  UART4 global interrupt */
                Set_Default_Handler  TIM6_DACUNDER_IRQHandler	        /* 54  TIM6 global and DAC1(1) underrun interrupts */
                Set_Default_Handler  TIM7_IRQHandler	                /* 55  TIM7 global interrupt */
                Set_Default_Handler  DMA2_CH1_IRQHandler	            /* 56  DMA2 channel 1 interrupt */
                Set_Default_Handler  DMA2_CH2_IRQHandler	            /* 57  DMA2 channel 2 interrupt */
                Set_Default_Handler  DMA2_CH3_IRQHandler	            /* 58  DMA2 channel 3 interrupt */
                Set_Default_Handler  DMA2_CH4_IRQHandler	            /* 59  DMA2 channel 4 interrupt */
                Set_Default_Handler  DMA2_CH5_IRQHandler	            /* 60  DMA2 channel 5 interrupt */
                Set_Default_Handler  DFSDM1_FLT0_IRQHandler	            /* 61  DFSDM1_FLT0 global interrupt */
                Set_Default_Handler  DFSDM1_FLT1_IRQHandler	            /* 62  DFSDM1_FLT1 global interrupt */
                Set_Default_Handler  COMP_IRQHandler	                /* 64  COMP1/COMP2(1) through EXTI lines 21/22 interrupts */
                Set_Default_Handler  LPTIM1_IRQHandler	                /* 65  LPTIM1 global interrupt */
                Set_Default_Handler  LPTIM2_IRQHandler	                /* 66  LPTIM2 global interrupt */
                Set_Default_Handler  USB_FS_IRQHandler	                /* 67  USB event interrupt through EXTI line 17 */
                Set_Default_Handler  DMA2_CH6_IRQHandler	            /* 68  DMA2 channel 6 interrupt */
                Set_Default_Handler  DMA2_CH7_IRQHandler	            /* 69  DMA2 channel 7 interrupt */
                Set_Default_Handler  LPUART1_IRQHandler	                /* 70  LPUART1 global interrupt */
                Set_Default_Handler  QUADSPI_IRQHandler	                /* 71  QUADSPI global interrupt */
                Set_Default_Handler  I2C3_EV_IRQHandler	                /* 72  I2C3 event interrupt  */
                Set_Default_Handler  I2C3_ER_IRQHandler	                /* 73  I2C3 error interrupt */
                Set_Default_Handler  SAI1_IRQHandler	                /* 74  SAI1 global interrupt */
                Set_Default_Handler  SWPMI1_IRQHandler	                /* 76  SWPMI1 global interrupt */
                Set_Default_Handler  TSC_IRQHandler	                    /* 77  TSC global interrupt */
                Set_Default_Handler  LCD_IRQHandler	                    /* 78  LCD global interrupt */
                Set_Default_Handler  AES_IRQHandler	                    /* 79  AES global interrupt */
                Set_Default_Handler  RNG_IRQHandler	                    /* 80  RNG global interrupt */
                Set_Default_Handler  FPU_IRQHandler	                    /* 81  Floating point interrupt */
                Set_Default_Handler  CRS_IRQHandler	                    /* 82  CRS interrupt */
                Set_Default_Handler  I2C4_EV_IRQHandler	                /* 83  I2C4 event interrupt, wakeup through EXTI line 40 */
                Set_Default_Handler  I2C4_ER_IRQHandler	                /* 84  I2C4 error interrupt */


                .end
                