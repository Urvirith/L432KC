#include "common.h"
#include "nvic.h"

#define NVIC_32BIT      (uint32_t)32
#define NVIC_8BIT       (uint32_t)8
#define NVIC_ARRAYSIZE  (uint32_t)8
#define NVIC_IPR_SIZE   (uint32_t)60

/* Private Functions */
static uint32_t nvic_get_reg(uint32_t irq_num);
static uint32_t nvic_get_bit(uint32_t irq_num);
static uint8_t nvic_get_priority(uint8_t priority, uint8_t sub_priority);

/* Enable NVIC Interrupt */
void nvic_enable_interrupt(NVIC_TypeDef *ptr, uint32_t irq_num) {
    if (nvic_get_reg(irq_num) < NVIC_ARRAYSIZE) {
        set_ptr_vol_bit_u32(&ptr->ISER[nvic_get_reg(irq_num)], nvic_get_bit(irq_num));
    }
}

/* Set NVIC Interrupt Priority */
void nvic_set_priority(NVIC_TypeDef *ptr, uint32_t irq_num, uint8_t priority, uint8_t sub_priority) {
    if (irq_num < NVIC_IPR_SIZE) {
        set_ptr_vol_raw_u8(&ptr->IPR[irq_num], nvic_get_priority(priority, sub_priority));
    }
}

/* Private Function To Get The Bit By (x % 32) ex. 47 % 32 = 15 -> 1 << 15 */
static uint32_t nvic_get_reg(uint32_t irq_num) {
    return (irq_num / NVIC_32BIT);
}

/* Private Function To Get The Bit By (x % 32) ex. 47 % 32 = 15 -> 1 << 15 */
static uint32_t nvic_get_bit(uint32_t irq_num) {
    return (1 << (irq_num % NVIC_32BIT));
}

/* Private Function To Get The Priority */
static uint8_t nvic_get_priority(uint8_t priority, uint8_t sub_priority) {
    return (((priority) << (6)) | (((sub_priority) & (0x3)) << (4)));
}
