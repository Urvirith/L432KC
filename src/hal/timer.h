#ifndef TIMER_H_
#define TIMER_H_

// TIMER DRIVER
// ARM TIMER MODULE - FREE RUNNING COUNTERS -32kHz or 25MHz
// Timer Description - is on pg 1181

/* Timers */

/* Register Base */
/* Defined In The Board Specific Folder */

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR1;              // Control Register 1
    volatile uint32_t CR2;              // Control Register 2
    volatile uint32_t SMCR;             // Slave Mode Control Register
    volatile uint32_t DIER;             // DMA/ Interrupt Enable Register
    volatile uint32_t SR;               // Status Register
    volatile uint32_t EGR;              // Event Generation Register
    volatile uint32_t CCMR1;            // Capture/Compare Mode Register 1
    volatile uint32_t CCMR2;            // Capture/Compare Mode Register 2
    volatile uint32_t CCER;             // Capture/Compare Enable Register
    volatile uint32_t CNT;              // Counter Register
    volatile uint32_t PSC;              // Prescaler Register
    volatile uint32_t ARR;              // Auto Reload Register
    volatile uint32_t RCR;              // Repetition Counter Register
    volatile uint32_t CCR1;             // Capture/Compare Register 1
    volatile uint32_t CCR2;             // Capture/Compare Register 2
    volatile uint32_t CCR3;             // Capture/Compare Register 3
    volatile uint32_t CCR4;             // Capture/Compare Register 4
    volatile uint32_t BDTR;             // Break and Dead-Time Register
    volatile uint32_t DCR;              // DMA Control Register
    volatile uint32_t DMAR;             // DMA Address Register
    volatile uint32_t OR1;              // Option Register 1
} TIMER_TypeDef;

/* Enumerations */
// 0 = Continous, 1 = ONS (clears en bit)
typedef enum timer_type {
    Timer_Cont, 
    Timer_Ons
} TIMER_Type;

// 0 = Upcounter, 1 = Downcounter
typedef enum timer_direction {
    Timer_Upcount,
    Timer_Down
} TIMER_Direction;

/* Public Functions */
void timer_open(TIMER_TypeDef *ptr, TIMER_Type ons, TIMER_Direction dir);
bool timer_get_flag(TIMER_TypeDef *ptr);
void timer_clr_flag(TIMER_TypeDef *ptr);
void timer_set_interrupt(TIMER_TypeDef *ptr);
uint32_t timer_read_count(TIMER_TypeDef *ptr);
void timer_clr_count(TIMER_TypeDef *ptr);
void timer_start(TIMER_TypeDef *ptr);
void timer_stop(TIMER_TypeDef *ptr);
void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale);
void timer_set_pwm_ccr1(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ccr2(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ccr3(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ccr4(TIMER_TypeDef *ptr, uint32_t cnt);
void timer_set_pwm_ch1(TIMER_TypeDef *ptr);
void timer_set_pwm_ch2(TIMER_TypeDef *ptr);
void timer_set_pwm_ch3(TIMER_TypeDef *ptr);
void timer_set_pwm_ch4(TIMER_TypeDef *ptr);
void timer_ons_delay(TIMER_TypeDef * ptr, uint32_t time_us);

#endif /* TIMER_H_ */
