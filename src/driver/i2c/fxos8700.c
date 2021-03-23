#include "fxos8700.h"

// Library for use of the fxos8700
// This will set to high accuracy accel and magnotometer

#define INDEX_BREAK             50

// AREA FOR THE FXOS8700
#define ADDR_FXOS8700           0x1F

#define ACCEL_REG_STATUS        0x00 // CURRENTLY USED

#define CTRL_XYZ                0x0E
#define CTRL_REG1               0x2A
#define CTRL_REG2               0x2B
#define MCTRL_REG1              0x5B
#define MCTRL_REG2              0x5C

#define CTRL_REG1_ACT           (uint8_t)BIT_0
#define CTRL_REG1_LOW_NOISE     (uint8_t)BIT_2
#define CTRL_REG1_DR400         (uint8_t)BIT_3

#define CTRL_REG2_HIGH_RES      (uint8_t)BIT_1
#define CTRL_REG2_RESET         (uint8_t)BIT_6

#define CTRL_MREG1_HMS          3 << 0          // HYBRID MODE
#define CTRL_MREG1_OSR          7 << 2          // OVER SAMPLE SET TO MAX
#define CTRL_MREG1_ACAL         (uint8_t)BIT_7  // OVER SAMPLE SET TO MAX

#define CTRL_MREG2_HYB          (uint8_t)BIT_5  // HYBRID MODE

// RANGE SELECTION
#define ACCEL_MG_RANGE_2G       4               // 4.0984 or 0.244
#define ACCEL_MG_RANGE_4G       2               // 2.0492 or 0.488
#define ACCEL_MG_RANGE_8G       1               // 1.0246 or 0.976

#define ADDR_ARRAY              2
#define ADDR                    1
#define RAW_DATA_ARRAY          13

bool fxos8700_init(I2C_TypeDef *ptr, uint8_t range) {
    uint32_t i = 0;
    uint8_t reset[ADDR_ARRAY] =       {CTRL_REG2, CTRL_REG2_RESET};
    uint8_t resol[ADDR_ARRAY] =       {CTRL_REG2, CTRL_REG2_HIGH_RES};                                       /* High resolution */ 
    uint8_t hybrid[ADDR_ARRAY] =      {MCTRL_REG1, (CTRL_MREG1_ACAL | CTRL_MREG1_HMS | CTRL_MREG1_OSR)};     /* Hybrid Mode, Over Sampling Rate = 16 */
    uint8_t hymode[ADDR_ARRAY] =      {MCTRL_REG2, CTRL_MREG2_HYB}; 

    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, reset, ADDR_ARRAY);

    while ((i2c_std_read_u8(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, CTRL_REG2) & CTRL_REG2_RESET) == CTRL_REG2_RESET) {
        if (i > INDEX_BREAK) {
            return false;
        }
        i++;
    }

    uint8_t rng[ADDR_ARRAY] = {CTRL_XYZ, range};
    uint8_t cr1[ADDR_ARRAY] = {CTRL_REG1, CTRL_REG1_LOW_NOISE | CTRL_REG1_DR400};    /* Active, Normal Mode, Low Noise, 400Hz in Hybrid Mode */

    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, rng, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, resol, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, cr1, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, hybrid, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, hymode, ADDR_ARRAY);


    cr1[1] |= CTRL_REG1_ACT;
    i2c_std_write(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, cr1, ADDR_ARRAY);

    return true;
}

// RETURNS [X, Y, Z] in [F32] FOR BOTH ACCEL AND MAG
bool fxos8700_read(I2C_TypeDef *ptr, uint8_t range, int16_t *buf, uint32_t len) {
    if (len < 6) {
        return false;
    }

    uint8_t addr_status[ADDR] =       {ACCEL_REG_STATUS};
    uint8_t raw_data[RAW_DATA_ARRAY] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int16_t accel_x_raw = 0;
    int16_t accel_y_raw = 0;
    int16_t accel_z_raw = 0;
    int16_t accel_x_scale = 0;
    int16_t accel_y_scale = 0;
    int16_t accel_z_scale = 0;
    int16_t mag_x_raw = 0;
    int16_t mag_y_raw = 0;
    int16_t mag_z_raw = 0;

    i2c_std_read(ptr, ADDR_FXOS8700, ADDR_7_BIT_ACT, ADDR_7_BIT_ACT, addr_status, ADDR, raw_data, RAW_DATA_ARRAY);

    accel_x_raw = ((((int16_t)raw_data[1]) << 8) | (((int16_t)raw_data[2]) << 0)) >> 2;
    accel_y_raw = ((((int16_t)raw_data[3]) << 8) | (((int16_t)raw_data[4]) << 0)) >> 2;
    accel_z_raw = ((((int16_t)raw_data[5]) << 8) | (((int16_t)raw_data[6]) << 0)) >> 2;
    mag_x_raw = (((int16_t)raw_data[7]) << 8) | (((int16_t)raw_data[8]) << 0);
    mag_y_raw = (((int16_t)raw_data[9]) << 8) | (((int16_t)raw_data[10]) << 0);
    mag_z_raw = (((int16_t)raw_data[11]) << 8) | (((int16_t)raw_data[12]) << 0);

    switch(range) {
        case Fxos8700_Accel_2G:
            accel_x_scale = (accel_x_raw * 10) / ACCEL_MG_RANGE_2G;
            accel_y_scale = (accel_y_raw * 10) / ACCEL_MG_RANGE_2G;
            accel_z_scale = (accel_z_raw * 10) / ACCEL_MG_RANGE_2G;
            break;
        case Fxos8700_Accel_4G:
            accel_x_scale = (accel_x_raw * 10) / ACCEL_MG_RANGE_4G;
            accel_y_scale = (accel_y_raw * 10) / ACCEL_MG_RANGE_4G;
            accel_z_scale = (accel_z_raw * 10) / ACCEL_MG_RANGE_4G;
            break;
        case Fxos8700_Accel_8G:
            accel_x_scale = (accel_x_raw * 10) / ACCEL_MG_RANGE_8G;
            accel_y_scale = (accel_y_raw * 10) / ACCEL_MG_RANGE_8G;
            accel_z_scale = (accel_z_raw * 10) / ACCEL_MG_RANGE_8G;
            break;
        default:
            break;
    }

    buf[0] = accel_x_scale;
    buf[1] = accel_y_scale;
    buf[2] = accel_z_scale;
    buf[3] = mag_x_raw;
    buf[4] = mag_y_raw;
    buf[5] = mag_z_raw;

    return true;
}

bool fxos8700_check_fail(uint16_t *buf, uint32_t len) {
    uint32_t i = 0;

    while (i < len) {
        if (buf[i] != 0) {
            return false;
        }

        i++;
    }

    return true;
}