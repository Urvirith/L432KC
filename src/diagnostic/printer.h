#ifndef PRINTER_H_
#define PRINTER_H_

// THERE WAS A PLAN FOR THIS WIL HAVE TO REVISIT

#include <stdio.h>
#include <stdint.h>

// Register Base
#define GPIOA   (uint32_t)0x48000000
#define GPIOB   (uint32_t)0x48000400
#define GPIOC   (uint32_t)0x48000800

// STANDARD BIT MOVES USED COMMONLY IN DRIVERS
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

enum msi_range {_100kHz, _200kHz, _400kHz, _800kHz, _1MHz, _2MHz, _4MHz, _8MHz, _16MHz, _24MHz, _32MHz, _48MHz};

void print_message(uint32_t x);

#endif // 