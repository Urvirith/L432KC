#ifndef RCC_H_
#define RCC_H_

// RCC DRIVER
// ARM RCC MODULE
// RCC Description - is on pg 195

/* Reset and Clock Control (RCC) */

/* Register Base */
/* Defined In The Board Specific Folder */

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CR;               // Control Register
    volatile uint32_t ICSCR;            // Internal Clock Sources Calibration Register
    volatile uint32_t CFGR;             // Clock Configuration Register    
    volatile uint32_t PLL_CFGR;         // PLL Configuration Register
    volatile uint32_t PLL_SAI1_CFGR;    // PLL SAI1 Configuration Register
    volatile uint32_t RESERVED_1;       // Reserved Area
    volatile uint32_t CIER;             // Clock Interrupt Enable Register
    volatile uint32_t CIFR;             // Clock Interrupt Flag Status Register
    volatile uint32_t CICR;             // Clock Interrupt Clear Register
    volatile uint32_t RESERVED_2;       // Reserved Area
    volatile uint32_t AHB1_RSTR;        // AHB1 Peripheral Reset Register
    volatile uint32_t AHB2_RSTR;        // AHB2 Peripheral Reset Register
    volatile uint32_t AHB3_RSTR;        // AHB3 Peripheral Reset Register
    volatile uint32_t RESERVED_3;       // Reserved Area
    volatile uint32_t APB1_RSTR1;       // APB1 Peripheral Reset Register 1
    volatile uint32_t APB1_RSTR2;       // APB1 Peripheral Reset Register 2
    volatile uint32_t APB2_RSTR;        // APB2 Peripheral Reset Register
    volatile uint32_t RESERVED_4;       // Reserved Area
    volatile uint32_t AHB1_ENR;         // AHB1 Peripheral Enable Register
    volatile uint32_t AHB2_ENR;         // AHB2 Peripheral Enable Register
    volatile uint32_t AHB3_ENR;         // AHB3 Peripheral Enable Register
    volatile uint32_t RESERVED_5;       // Reserved Area
    volatile uint32_t APB1_ENR1;        // APB1 Peripheral Enable Register 1
    volatile uint32_t APB1_ENR2;        // APB1 Peripheral Enable Register 2
    volatile uint32_t APB2_ENR;         // APB2 Peripheral Enable Register
    volatile uint32_t RESERVED_6;       // Reserved Area
    volatile uint32_t AHB1_SM_ENR;      // AHB1 Peripheral Sleep And Stop Modes Enable Register
    volatile uint32_t AHB2_SM_ENR;      // AHB2 Peripheral Sleep And Stop Modes Enable Register
    volatile uint32_t AHB3_SM_ENR;      // AHB3 Peripheral Sleep And Stop Modes Enable Register
    volatile uint32_t RESERVED_7;       // Reserved Area
    volatile uint32_t APB1_SM_ENR1;     // APB1 Peripheral Sleep And Stop Modes Enable Register 1
    volatile uint32_t APB1_SM_ENR2;     // APB1 Peripheral Sleep And Stop Modes Enable Register 2
    volatile uint32_t APB2_SM_ENR;      // APB2 Peripheral Sleep And Stop Modes Enable Register
    volatile uint32_t RESERVED_8;       // Reserved Area
    volatile uint32_t CCIPR1;           // Peripherals Independent Clock Configuration Register
    volatile uint32_t BDCR;             // Backup Domain Control Register
    volatile uint32_t CSR;              // Control Status Register
    volatile uint32_t CRRCR;            // Clock Recovery RC Register
    volatile uint32_t CCIPR2;           // Peripherals Independent Clock Configuration Register
} RCC_TypeDef;

/* Public Functions */
void rcc_write_msi_range(RCC_TypeDef *ptr, MSI_Range freq_khz);
void rcc_write_ahb1_enr(RCC_TypeDef *ptr, uint32_t bit_num);
void rcc_write_ahb2_enr(RCC_TypeDef *ptr, uint32_t bit_num);
void rcc_write_ahb3_enr(RCC_TypeDef *ptr, uint32_t bit_num);
void rcc_write_apb1_enr1(RCC_TypeDef *ptr, uint32_t bit_num);
void rcc_write_apb1_enr2(RCC_TypeDef *ptr, uint32_t bit_num);
void rcc_write_apb2_enr(RCC_TypeDef *ptr, uint32_t bit_num);
void rcc_write_ccipr1(RCC_TypeDef *ptr, uint32_t offset, uint32_t value);

#endif /* RCC_H_ */
