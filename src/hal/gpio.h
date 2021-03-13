#ifndef GPIO_H_
#define GPIO_H_

// GPIO DRIVER
// ARM GPIO MODULE
// GPIO Description - is on pg 235

/* General Purpose I/O */

/* Register Base */
#define GPIOA_BASE          (uint32_t)0x48000000
#define GPIOB_BASE          (uint32_t)0x48000400                          /* GPIO Port B base address */
#define GPIOC_BASE          (uint32_t)0x48000800

/* GPIO Rcc Bits */
#define GPIOA_RCC_ENABLE    BIT_0
#define GPIOB_RCC_ENABLE    BIT_1

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t MODER;    // Mode Register
    volatile uint32_t OTYPER;   // Output Type Register
    volatile uint32_t OSPEEDR;  // Output Speed Register
    volatile uint32_t PUPDR;    // Pull up Pull Down Register
    volatile uint32_t IDR;      // Input Data Register
    volatile uint32_t ODR;      // Output Data Register
    volatile uint32_t BSRR;     // Bit Set Reset Register
    volatile uint32_t LCKR;     // Configuration Lock Register
    volatile uint32_t AFRL;     // Alternate Function Low Register
    volatile uint32_t AFRH;     // Alternate Function High Register
    volatile uint32_t BRR;      // Bit Reset Register
} GPIO_TypeDef;

/* Enumerations */
// 00: Input mode     01: General purpose output mode     10: Alternate function mode     11: Analog mode (reset state)
enum gpio_mode {Gpio_Input, Gpio_Output, Gpio_Alternate, Gpio_Analogue};

// 0: Output Push Pull     1: Output Open Drain
enum gpio_otype {Gpio_Push_Pull, Gpio_Open_Drain};

// 00: Low speed     01: Medium speed     10: High speed     11: Very high speed
enum gpio_ospeed {Gpio_Low_Speed, Gpio_Medium_Speed, Gpio_High_Speed, Gpio_Very_High_Speed};

// 00: No pull-up, pull-down     01: Pull-up     10: Pull-down     11: Reserved
enum gpio_pupd {Gpio_PullUp, Gpio_PullDown, Gpio_PullUp_PullDown};

/* 0000: AF0     0001: AF1     0010: AF2     0011: AF3     0100: AF4     0101: AF5
   0110: AF6     0111: AF7     1000: AF8     1001: AF9     1010: AF10    1011: AF11
   1100: AF12    1101: AF13    1110: AF14    1111: AF15                             */
enum gpio_alt_func {AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15};

/* Public Functions */
bool gpio_get_pin(GPIO_TypeDef *ptr, uint32_t offset);
void gpio_set_pin(GPIO_TypeDef *ptr, uint32_t value);
void gpio_clr_pin(GPIO_TypeDef *ptr, uint32_t value);
void gpio_set_lock(GPIO_TypeDef *ptr, uint32_t value);
void gpio_clr_lock(GPIO_TypeDef *ptr, uint32_t value);
void gpio_io_type(GPIO_TypeDef *ptr, uint32_t bit, uint32_t mode, uint32_t otype, uint32_t alt_func);

#endif /* GPIO_H_ */
