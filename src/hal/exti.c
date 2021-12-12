#include "common.h"
#include "exti.h"

void gpio_set_imr1(EXTI_TypeDef *ptr, uint32_t value){
    set_ptr_vol_bit_u32(&ptr->IMR1, value);
}