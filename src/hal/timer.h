#ifndef TIMER_H_
#define TIMER_H_

// TIMER DRIVER
// ARM TIMER MODULE - FREE RUNNING COUNTERS -32kHz or 25MHz
// Timer Description - is on pg 965

/* Timers */

/* Register Base */
#define TIMER1_BASE         (uint32_t)0x40012C00
#define TIMER2_BASE         (uint32_t)0x40000000
#define TIMER3_BASE         (uint32_t)0x40000400
#define TIMER6_BASE         (uint32_t)0x40001000
#define TIMER7_BASE         (uint32_t)0x40001400
#define TIMER15_BASE        (uint32_t)0x40014000
#define TIMER16_BASE        (uint32_t)0x40014400

/* Timer Rcc Bits */
#define TIMER2_RCC_ENABLE    BIT_0

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR1;      // Control Register 1
    volatile uint32_t CR2;      // Control Register 2
    volatile uint32_t SMCR;     // Slave Mode Control Register
    volatile uint32_t DIER;     // DMA/ Interrupt Enable Register
    volatile uint32_t SR;       // Status Register
    volatile uint32_t EGR;      // Event Generation Register
    volatile uint32_t CCMR1;    // Capture/Compare Mode Register 1
    volatile uint32_t CCMR2;    // Capture/Compare Mode Register 2
    volatile uint32_t CCER;     // Capture/Compare Enable Register
    volatile uint32_t CNT;      // Counter Register
    volatile uint32_t PSC;      // Prescaler Register
    volatile uint32_t ARR;      // Auto Reload Register
    volatile uint32_t RCR;      // Repetition Counter Register
    volatile uint32_t CCR1;     // Capture/Compare Register 1
    volatile uint32_t CCR2;     // Capture/Compare Register 2
    volatile uint32_t CCR3;     // Capture/Compare Register 3
    volatile uint32_t CCR4;     // Capture/Compare Register 4
    volatile uint32_t BDTR;     // Break and Dead-Time Register
    volatile uint32_t DCR;      // DMA Control Register
    volatile uint32_t DMAR;     // DMA Address Register
    volatile uint32_t OR1;      // Option Register 1
} TIMER_TypeDef;

/* Enumerations */
// 0 = Continous, 1 = ONS (clears en bit)
enum timer_type {Timer_Cont, Timer_Ons};
// 0 = Upcounter, 1 = Downcounter
enum timer_direction {Timer_Upcount, Timer_Down};

/* Public Functions */
void timer_open(TIMER_TypeDef *ptr, uint32_t ons, uint32_t dir);
bool timer_get_flag(TIMER_TypeDef *ptr);
void timer_clr_flag(TIMER_TypeDef *ptr);
uint32_t timer_read_count(TIMER_TypeDef *ptr);
void timer_clr_count(TIMER_TypeDef *ptr);
void timer_start(TIMER_TypeDef *ptr);
void timer_stop(TIMER_TypeDef *ptr);
void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale);

#endif /* TIMER_H_ */