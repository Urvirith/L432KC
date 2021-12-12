#include "common.h"
#include "gpio.h"

/* Register Masks */
#define MODER_MASK          MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */
#define OSPEED_MASK         MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */
#define PUPD_MASK           MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */
#define AF_MASK             MASK_4_BIT      /* Mode is mask required, here we set the mask to four bit 1111 */

/* Register Offsets */
#define MODER_OFFSET        2               /* Mode is two bits wide, shift by an offset of 2 */
#define OSPEED_OFFSET       2               /* Output Speed is two bits wide, shift by an offset of 2 */
#define PUPD_OFFSET         2               /* Pu Speed is two bits wide, shift by an offset of 2 */
#define AF_OFFSET           4               /* Alternate Function is four bits wide, shift by an offset of 4 */

bool gpio_get_pin(GPIO_TypeDef *ptr, uint32_t value){
    return get_ptr_vol_bit_u32(&ptr->IDR, value);
}

void gpio_set_pin(GPIO_TypeDef *ptr, uint32_t value){
    set_ptr_vol_bit_u32(&ptr->ODR, value);
}

void gpio_clr_pin(GPIO_TypeDef *ptr, uint32_t value){
    clr_ptr_vol_bit_u32(&ptr->ODR, value);
}

void gpio_set_lock(GPIO_TypeDef *ptr, uint32_t value){
    set_ptr_vol_bit_u32(&ptr->LCKR, value);
}

void gpio_clr_lock(GPIO_TypeDef *ptr, uint32_t value){
    clr_ptr_vol_bit_u32(&ptr->LCKR, value);
}

void gpio_type(GPIO_TypeDef *ptr, uint32_t bit, GPIO_Mode mode, GPIO_OType otype, GPIO_AltFunction alt_func) {
    set_ptr_vol_u32(&ptr->MODER, bit * MODER_OFFSET, MODER_MASK, mode);
    switch (otype) {
        case Gpio_Open_Drain:
            set_ptr_vol_bit_u32(&ptr->OTYPER, (1 << bit));
            break;
        case Gpio_Push_Pull:
            clr_ptr_vol_bit_u32(&ptr->OTYPER, (1 << bit));
            break;
    }

    if (mode == Gpio_Alternate) {
        if (bit <= 7) {
            set_ptr_vol_u32(&ptr->AFRL, bit * AF_OFFSET, AF_MASK, alt_func);
        } else {
            set_ptr_vol_u32(&ptr->AFRH, (bit - 8) * AF_OFFSET, AF_MASK, alt_func);
        }
    }
}

void gpio_speed(GPIO_TypeDef *ptr, uint32_t bit, GPIO_OSpeed speed) {
    set_ptr_vol_u32(&ptr->OSPEEDR, bit * OSPEED_OFFSET, OSPEED_MASK, speed);
}

void gpio_pupd(GPIO_TypeDef *ptr, uint32_t bit, GPIO_PuPd pupd) {
    set_ptr_vol_u32(&ptr->PUPDR, bit * PUPD_OFFSET, PUPD_MASK, pupd);
}
