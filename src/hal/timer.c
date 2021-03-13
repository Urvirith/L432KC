#include "common.h"
#include "timer.h"

/* Register Masks */
/* CR1 */
#define CMS_MASK            MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */
#define CKD_MASK            MASK_2_BIT      /* Mode is mask required, here we set the mask to two bit 11 */

/* Register Bits */
/* CR1 */
#define EN_BIT              BIT_0           /* 0 = Disabled, 1 = Enabled */
#define UDIS_BIT            BIT_1           /* Update event, 0 = EN, 1 = DISABLED */
#define URS_BIT             BIT_2           /* 0 = All events enables, 1 = Only OF or UF Events */
#define OPM_BIT             BIT_3           /* 0 = Continous, 1 = ONS (clears en bit) */
#define DIR_BIT             BIT_4           /* 0 = Upcounter, 1 = Downcounter (ONLY ACTIVE IF CMS = 00) */
#define ARPE_BIT            BIT_7           /* 0 ARR = Not Buffered, 1 = Buffered */
#define UIFREMAP_BIT        BIT_11          /* Output, 0 = Pulse, 1 = Toggle */

/* SR */
#define UPDATE_BIT          BIT_0


/* Register Offsets */
/* CR1 */
#define CMS_OFFSET          5               /* 00 = Edge Aligned     01 = Center Aligned Down     10 = Center Aligned Up     11 - Center Aligned Up */
#define CKD_OFFSET          8               /* 00 = Tdts = Tclk_int  01 = Tdts = 2*Tclk_int       10 = Tdts = 4*Tclk_int     11 - Reserved */
/* SR */
#define UPDATE_OFFSET       0 
/* CNT */
#define CLEAR_CNT           (uint32_t)0  

void timer_open(TIMER_TypeDef *ptr, uint32_t ons, uint32_t dir) {
    clr_ptr_vol_bit_u32(&ptr->CR1, UDIS_BIT);
    clr_ptr_vol_bit_u32(&ptr->CR1, URS_BIT);

    if (ons == Timer_Ons) {
        set_ptr_vol_bit_u32(&ptr->CR1, OPM_BIT);
    } else {
        clr_ptr_vol_bit_u32(&ptr->CR1, OPM_BIT);
    }

    if (dir == Timer_Down) {
        set_ptr_vol_bit_u32(&ptr->CR1, DIR_BIT);
    } else {
        clr_ptr_vol_bit_u32(&ptr->CR1, DIR_BIT);
    }

    set_ptr_vol_u32(&ptr->CR1, CMS_OFFSET, CMS_MASK, 0);
    clr_ptr_vol_bit_u32(&ptr->CR1, ARPE_BIT);
    set_ptr_vol_u32(&ptr->CR1, CKD_OFFSET, CKD_MASK, 0);
    clr_ptr_vol_bit_u32(&ptr->CR1, UIFREMAP_BIT);
}

bool timer_get_flag(TIMER_TypeDef *ptr) {
    return get_ptr_vol_bit_u32(&ptr->SR, UPDATE_OFFSET);
}

void timer_clr_flag(TIMER_TypeDef *ptr) {
    clr_ptr_vol_bit_u32(&ptr->SR, UPDATE_BIT);
}

uint32_t timer_read_count(TIMER_TypeDef *ptr) {
    return get_ptr_vol_raw_u32(&ptr->CNT);
}

void timer_clr_count(TIMER_TypeDef *ptr) {
    set_ptr_vol_raw_u32(&ptr->CNT, CLEAR_CNT);
}

void timer_start(TIMER_TypeDef *ptr) {
    set_ptr_vol_bit_u32(&ptr->CR1, EN_BIT);
}

void timer_stop(TIMER_TypeDef *ptr) {
    clr_ptr_vol_bit_u32(&ptr->CR1, EN_BIT);
}

void timer_set_time(TIMER_TypeDef *ptr, uint32_t time, uint32_t clock_speed, uint32_t prescale) {
    uint32_t value = 0;

    if (prescale == 0) {
        value = time * clock_speed;
    } else {
        value = (time * clock_speed) / prescale;
    }

    set_ptr_vol_raw_u32(&ptr->PSC, prescale);
    set_ptr_vol_raw_u32(&ptr->ARR, value);
}

