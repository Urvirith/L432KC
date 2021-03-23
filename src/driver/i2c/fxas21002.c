#include "fxas21002.h"

// Library for use of the fxos8700
// This will set to high accuracy accel and magnotometer

#define INDEX_BREAK             50

// AREA FOR THE FXOS8700
#define ADDR_FXAS21002          0x21

#define GYRO_REG_STATUS         0x00 // CURRENTLY USED

#define CTRL_REG0               0x0D
#define CTRL_REG1               0x13

#define CTRL_REG1_STANDBY       0x00
#define CTRL_REG1_ACTIVE        0x0E
#define CTRL_REG1_RESET         (uint8_t)BIT_6

// RANGE SELECTION
#define GYRO_RANGE_250DPS       128             // 0.0078125
#define GYRO_RANGE_500DPS       64              // 0.015625
#define GYRO_RANGE_1000DPS      32              // 0.03125
#define GYRO_RANGE_2000DPS      16              // 0.0625

#define ADDR_ARRAY              2
#define ADDR                    1
#define RAW_DATA_ARRAY          7

bool fxas210002_init(I2C_TypeDef *ptr, uint8_t range) {
    uint32_t i = 0;
    //let mut cr1;
    uint8_t standby[ADDR_ARRAY] =     {CTRL_REG1, CTRL_REG1_STANDBY};
    uint8_t reset[ADDR_ARRAY] =       {CTRL_REG1, CTRL_REG1_RESET};

    i2c_std_write(ptr, ADDR_FXAS21002, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, standby, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_FXAS21002, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, reset, ADDR_ARRAY);

    while ((i2c_std_read_u8(ptr, ADDR_FXAS21002, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, CTRL_REG1) & CTRL_REG1_RESET) == CTRL_REG1_RESET) {
        if (i > INDEX_BREAK) {
            return false;
        }
        i++;
    }

    uint8_t cr1[ADDR_ARRAY] = {CTRL_REG0, range}; 
    uint8_t active[ADDR_ARRAY] = {CTRL_REG1, CTRL_REG1_ACTIVE};

    i2c_std_write(ptr, ADDR_FXAS21002, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, cr1, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_FXAS21002, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, active, ADDR_ARRAY);

    return true;
}

// RETURNS [X, Y, Z] in [F32] FOR BOTH ACCEL AND MAG
bool fxas210002_read(I2C_TypeDef *ptr, uint8_t range, int16_t *buf, uint32_t len) {
    if (len < 3) {
        return false;
    }

    uint8_t addr_status[ADDR] = {GYRO_REG_STATUS};
    uint8_t raw_data[RAW_DATA_ARRAY] = {0, 0, 0, 0, 0, 0, 0};
    int16_t x_raw = 0;
    int16_t y_raw = 0;
    int16_t z_raw = 0;

    i2c_std_read(ptr, ADDR_FXAS21002, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, addr_status, ADDR, raw_data, RAW_DATA_ARRAY);

    x_raw = ((((int16_t)raw_data[1]) << 8) | (((int16_t)raw_data[2]) << 0));
    y_raw = ((((int16_t)raw_data[3]) << 8) | (((int16_t)raw_data[4]) << 0));
    z_raw = ((((int16_t)raw_data[5]) << 8) | (((int16_t)raw_data[6]) << 0));

    switch(range) {
        case Fxas21002_Gyro_250DPS:
            buf[0] = x_raw / GYRO_RANGE_250DPS;
            buf[1] = y_raw / GYRO_RANGE_250DPS;
            buf[2] = z_raw / GYRO_RANGE_250DPS;
            break;
        case Fxas21002_Gyro_500DPS:
            buf[0] = x_raw / GYRO_RANGE_500DPS;
            buf[1] = y_raw / GYRO_RANGE_500DPS;
            buf[2] = z_raw / GYRO_RANGE_500DPS;
            break;
        case Fxas21002_Gyro_1000DPS:
            buf[0] = x_raw / GYRO_RANGE_1000DPS;
            buf[1] = y_raw / GYRO_RANGE_1000DPS;
            buf[2] = z_raw / GYRO_RANGE_1000DPS;
            break;
        case Fxas21002_Gyro_2000DPS:
            buf[0] = x_raw / GYRO_RANGE_2000DPS;
            buf[1] = y_raw / GYRO_RANGE_2000DPS;
            buf[2] = z_raw / GYRO_RANGE_2000DPS;
            break;
        default:
            break;
    }

    return true;
}

bool fxas210002_check_fail(uint16_t *buf, uint32_t len) {
    uint32_t i = 0;

    while (i < len) {
        if (buf[i] != 0) {
            return false;
        }

        i++;
    }

    return true;
}

void wait_loop(){
    volatile uint32_t i = 0;

    while (i < 10000000) {
        i++;
    }
}