#include "common.h"

/* Get a pointer bit in a u32 ptr Example value (10000 >> 5) -> 1 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
bool get_ptr_vol_bit_u32(volatile uint32_t *ptr, uint32_t value) {
    if ((*ptr & value) > 0) {
        return true;
    } else {
        return false;
    }
}

/* Set a pointer bit in a u32 ptr Example value (1 << 5), 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
void set_ptr_vol_bit_u32(volatile uint32_t *ptr, uint32_t value){
    *ptr |= value; 
}

/* Clear a pointer bit in a u32 ptr Example value (1 << 5) 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
void clr_ptr_vol_bit_u32(volatile uint32_t *ptr, uint32_t value){
    *ptr &= (~value); 
}

/* Get a pointer bit in a u32 ptr Example value (10000 >> 5) -> 1 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
uint32_t get_ptr_vol_u32(volatile uint32_t *ptr, uint32_t offset, uint32_t mask){
    return((*ptr >> offset) & mask); 
}

/* Write to a pointer with offset and mask size, ensure mask >= value 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
void set_ptr_vol_u32(volatile uint32_t *ptr, uint32_t offset, uint32_t mask, uint32_t value){
    *ptr &= (~(mask << offset));
    *ptr |= (value << offset);
}

/* Get a pointer value 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
uint8_t get_ptr_vol_raw_u8(volatile uint8_t *ptr){
    return *ptr; 
}

/* Write to a pointer with raw value, ensure mask >= value 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
void set_ptr_vol_raw_u8(volatile uint8_t *ptr, uint8_t value){
    *ptr = value;
}

/* Get a pointer value 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
uint32_t get_ptr_vol_raw_u32(volatile uint32_t *ptr){
    return *ptr; 
}

/* Write to a pointer with raw value, ensure mask >= value 
   If passing a stuct pointer ie. GPIOB->ODR, you can pass by reference &GPIO->ODR */
void set_ptr_vol_raw_u32(volatile uint32_t *ptr, uint32_t value){
    *ptr = value;
}