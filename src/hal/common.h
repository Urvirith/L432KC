#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdbool.h>

/* Standard Bit Shifts for 32-bit words */
#define BIT_0       ((uint32_t)1 << 0)
#define BIT_1       ((uint32_t)1 << 1)
#define BIT_2       ((uint32_t)1 << 2)
#define BIT_3       ((uint32_t)1 << 3)
#define BIT_4       ((uint32_t)1 << 4)
#define BIT_5       ((uint32_t)1 << 5)
#define BIT_6       ((uint32_t)1 << 6)
#define BIT_7       ((uint32_t)1 << 7)
#define BIT_8       ((uint32_t)1 << 8)
#define BIT_9       ((uint32_t)1 << 9)
#define BIT_10      ((uint32_t)1 << 10)
#define BIT_11      ((uint32_t)1 << 11)
#define BIT_12      ((uint32_t)1 << 12)
#define BIT_13      ((uint32_t)1 << 13)
#define BIT_14      ((uint32_t)1 << 14)
#define BIT_15      ((uint32_t)1 << 15)
#define BIT_16      ((uint32_t)1 << 16)
#define BIT_17      ((uint32_t)1 << 17)
#define BIT_18      ((uint32_t)1 << 18)
#define BIT_19      ((uint32_t)1 << 19)
#define BIT_20      ((uint32_t)1 << 20)
#define BIT_21      ((uint32_t)1 << 21)
#define BIT_22      ((uint32_t)1 << 22)
#define BIT_23      ((uint32_t)1 << 23)
#define BIT_24      ((uint32_t)1 << 24)
#define BIT_25      ((uint32_t)1 << 25)
#define BIT_26      ((uint32_t)1 << 26)
#define BIT_27      ((uint32_t)1 << 27)
#define BIT_28      ((uint32_t)1 << 28)
#define BIT_29      ((uint32_t)1 << 29)
#define BIT_30      ((uint32_t)1 << 30)
#define BIT_31      ((uint32_t)1 << 31)

/* Standard Bit Masks for 32-bit words */
#define MASK_1_BIT  (uint32_t)0x00000001
#define MASK_2_BIT  (uint32_t)0x00000003
#define MASK_3_BIT  (uint32_t)0x00000007
#define MASK_4_BIT  (uint32_t)0x0000000F
#define MASK_5_BIT  (uint32_t)0x0000001F
#define MASK_6_BIT  (uint32_t)0x0000003F
#define MASK_7_BIT  (uint32_t)0x0000007F
#define MASK_8_BIT  (uint32_t)0x000000FF
#define MASK_9_BIT  (uint32_t)0x000001FF
#define MASK_10_BIT (uint32_t)0x000003FF
#define MASK_11_BIT (uint32_t)0x000007FF
#define MASK_12_BIT (uint32_t)0x00000FFF
#define MASK_13_BIT (uint32_t)0x00001FFF
#define MASK_14_BIT (uint32_t)0x00003FFF
#define MASK_15_BIT (uint32_t)0x00007FFF
#define MASK_16_BIT (uint32_t)0x0000FFFF
#define MASK_17_BIT (uint32_t)0x0001FFFF
#define MASK_18_BIT (uint32_t)0x0003FFFF
#define MASK_19_BIT (uint32_t)0x0007FFFF
#define MASK_20_BIT (uint32_t)0x000FFFFF
#define MASK_21_BIT (uint32_t)0x001FFFFF
#define MASK_22_BIT (uint32_t)0x003FFFFF
#define MASK_23_BIT (uint32_t)0x007FFFFF
#define MASK_24_BIT (uint32_t)0x00FFFFFF
#define MASK_25_BIT (uint32_t)0x01FFFFFF
#define MASK_26_BIT (uint32_t)0x03FFFFFF
#define MASK_27_BIT (uint32_t)0x07FFFFFF
#define MASK_28_BIT (uint32_t)0x0FFFFFFF
#define MASK_29_BIT (uint32_t)0x1FFFFFFF
#define MASK_30_BIT (uint32_t)0x3FFFFFFF
#define MASK_31_BIT (uint32_t)0x7FFFFFFF
#define MASK_32_BIT (uint32_t)0xFFFFFFFF

// Enumeration of avaliable ranges of clocks
typedef enum msi_range {
    Clk100kHz, 
    Clk200kHz, 
    Clk400kHz, 
    Clk800kHz, 
    Clk1MHz, 
    Clk2MHz, 
    Clk4MHz, 
    Clk8MHz, 
    Clk16MHz, 
    Clk24MHz, 
    Clk32MHz, 
    Clk48MHz
} MSI_Range;

/* DELAY TIME FOR 50us, 1MHz = 1 Cycle Per Microsecond, Therefore 16 Mhz * 50 cycles = 800 Cycles = 50us */
#define TIMEOUT (uint32_t)(16 * 50)

/* Public Functions */
/* 32-Bit Functions */
bool get_ptr_vol_bit_u32(volatile uint32_t *ptr, uint32_t value);                               /* Get a pointer bit in a u32 ptr Example value (10000 >> 5) -> 1 */
void set_ptr_vol_bit_u32(volatile uint32_t *ptr, uint32_t value);                               /* Set a pointer bit in a u32 ptr Example value (1 << 5) */
void clr_ptr_vol_bit_u32(volatile uint32_t *ptr, uint32_t value);                               /* Clear a pointer bit in a u32 ptr Example value (1 << 5) */
uint32_t get_ptr_vol_u32(volatile uint32_t *ptr, uint32_t offset, uint32_t mask);               /* Get a pointer bit in a u32 ptr Example value (10000 >> 5) -> 1 */
void set_ptr_vol_u32(volatile uint32_t *ptr, uint32_t offset, uint32_t mask, uint32_t value);   /* Write to a pointer with offset and mask size, ensure mask >= value */
uint8_t get_ptr_vol_raw_u8(volatile uint8_t *ptr);                                              /* Get a pointer value */
void set_ptr_vol_raw_u8(volatile uint8_t *ptr, uint8_t value);                                  /* Write to a pointer with raw value */
uint32_t get_ptr_vol_raw_u32(volatile uint32_t *ptr);                                           /* Get a pointer value */
void set_ptr_vol_raw_u32(volatile uint32_t *ptr, uint32_t value);                               /* Write to a pointer with raw value */

#endif /* COMMON_H_ */