#include"printer.h"

// THERE WAS A PLAN FOR THIS WIL HAVE TO REVISIT

// Local Function
static uint32_t bitU32(uint32_t bit_num); 

void print_message(uint32_t x) {
    printf("%d\n", x);
}

static uint32_t bitU32(uint32_t bit_num) {
    switch(bit_num) {
        case 0:
        return BIT_0;
        case 1:
        return BIT_1;
        case 2:
        return BIT_2;
        case 3:
        return BIT_3;
        case 4:
        return BIT_4;
        case 5:
        return BIT_5;
        case 6:
        return BIT_6;
        case 7:
        return BIT_7;
        case 8:
        return BIT_8;
        case 9:
        return BIT_9;
        case 10:
        return BIT_10;
        case 11:
        return BIT_11;
        case 12:
        return BIT_12;
        case 13:
        return BIT_13;
        case 14:
        return BIT_14;
        case 15:
        return BIT_15;
        case 16:
        return BIT_16;
        case 17:
        return BIT_17;
        case 18:
        return BIT_18;
        case 19:
        return BIT_19;
        case 20:
        return BIT_20;
        case 21:
        return BIT_21;
        case 22:
        return BIT_22;
        case 23:
        return BIT_23;
        case 24:
        return BIT_24;
        case 25:
        return BIT_25;
        case 26:
        return BIT_26;
        case 27:
        return BIT_27;
        case 28:
        return BIT_28;
        case 29:
        return BIT_29;
        case 30:
        return BIT_30;
        case 31:
        return BIT_31;
        default:
        return BIT_0;
    }
}
