#ifndef NVIC_H_
#define NVIC_H_

// NVIC DRIVER
// ARM NVIC MODULE
// NVIC Description - is on pg 320
// NVIC Registers (Programming Manual) - is on 320

/* Nested vectored interrupt controller (NVIC) */

typedef struct {
	volatile uint32_t   ISER[8];		// Interrupt Set-Enable register
	volatile uint32_t   Reserved0[24];	// Offset
	volatile uint32_t   ICER[8]; 	    // Interrupt Clear-Enable register
	volatile uint32_t   Reserved1[24];  // Offset
	volatile uint32_t   ISPR[8];		// Interrupt Set-Pending Registers
	volatile uint32_t   Reserved2[24];	// Offset
	volatile uint32_t   ICPR[8];		// Interrupt Clear-Pending Registers
	volatile uint32_t   Reserved3[24];	// Offset
	volatile uint32_t   IABR[8];		// Interrupt Active Bit Registers
	volatile uint32_t   Reserved4[56];	// Offset
	volatile uint8_t    IPR[60];		// Interrupt Priority Registers
} NVIC_TypeDef;

/* Public Functions */
void nvic_enable_interrupt(NVIC_TypeDef *ptr, uint32_t irq_num);
void nvic_set_priority(NVIC_TypeDef *ptr, uint32_t irq_num, uint8_t priority, uint8_t sub_priority);

#endif /* NVIC_H_ */
