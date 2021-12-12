#ifndef EXTI_H_
#define EXTI_H_

// EXTI DRIVER
// ARM EXTI MODULE
// EXTI Description - is on pg 325

/* Extending Interrupts And Events Controllers */

/* Register Base */
/* Defined In The Board Specific Folder */

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t IMR1;             // Interrupt Mask Register 1
    volatile uint32_t EMR1;             // Event Mask Register 1
    volatile uint32_t RTSR1;            // Rising Trigger Selection Register 1
    volatile uint32_t FTSR1;            // Falling Trigger Selection Register 1
    volatile uint32_t SWIER1;           // Software Interrupt Event Register 1
    volatile uint32_t PR1;              // Pending Register 1
    volatile uint32_t IMR2;             // Interrupt Mask Register 2
    volatile uint32_t EMR2;             // Event Mask Register 2
    volatile uint32_t RTSR2;            // Rising Trigger Selection Register 2
    volatile uint32_t FTSR2;            // Falling Trigger Selection Register 2
    volatile uint32_t SWIER2;           // Software Interrupt Event Register 2
    volatile uint32_t PR2;              // Pending Register 2
} EXTI_TypeDef;

/* Public Functions */
void gpio_set_imr1(EXTI_TypeDef *ptr, uint32_t value);

#endif /* EXTI_H_ */