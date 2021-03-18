#include "pca9685.h"
#include "i2c.h"

// Library for use of the fxos8700
// This will set to high accuracy accel and magnotometer

#define INDEX_BREAK             50

// AREA FOR THE PCA9685
#define ADDR_PCA9685            0x40            // DEFAULT ADDRESS OF PCA9685

#define MODE1_REG               0x00
#define CTRL_REG1               0x13

#define MODE1_RESTART           0x80
#define MODE1_SLEEP             0x10
#define MODE1_START             0xA1

#define PRESCALE_REG            0xFE
#define LED0_ON_L               0x06

/* PCA9685 DATASHEET LIMITS */
#define FREQ_OSSC               25000000        // FREQ OF INTERNAL OSCILLATOR IN DATASHEET
#define PRESCALE_MAX            255
#define PRESCALE_MIN            3
#define FREQ_MAX                3500
#define FREQ_MIN                1
#define ON_OFF_MAX              4096
#define ON_OFF_MIN              0

#define ADDR_ARRAY              2
#define PWM_ARRAY               5
#define SHIFT_BYTE              8

/* CONSTANTS */
const uint8_t reset[ADDR_ARRAY] =       {MODE1_REG, MODE1_RESTART}; 

/* Private Functions */
static void set_pwm_freq(I2C_TypeDef *ptr, uint32_t freq);
static void set_pwm(I2C_TypeDef *ptr, uint8_t pin_num, uint16_t on, uint16_t off);

bool pca9685_init(I2C_TypeDef *ptr, uint32_t freq) {
    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &reset, ADDR_ARRAY);

    volatile uint32_t i = 0;
    if (i < 100000) { // PLACE A SEQUENCE TIMER HERE
        i++;
    }

    set_pwm_freq(ptr, freq);
}

bool pca9685_reset(I2C_TypeDef *ptr, uint32_t freq) {
    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &reset, ADDR_ARRAY);

    volatile uint32_t i = 0;
    if (i < 100000) { // PLACE A SEQUENCE TIMER HERE
        i++;
    }
}

bool pca9685_set_pin(I2C_TypeDef *ptr, uint8_t pin_num, uint16_t val, bool invert) {
    if (invert) {
        if(val >= ON_OFF_MAX) {
            set_pwm(ptr, pin_num, ON_OFF_MIN, ON_OFF_MAX);
        } else if (val == ON_OFF_MIN) {
            set_pwm(ptr, pin_num, ON_OFF_MAX, ON_OFF_MIN);
        } else {
            set_pwm(ptr, pin_num, ON_OFF_MIN, ON_OFF_MAX - val);
        }
    } else {
        if(val >= ON_OFF_MAX) {
            set_pwm(ptr, pin_num, ON_OFF_MAX, ON_OFF_MIN);
        } else if (val == ON_OFF_MIN) {
            set_pwm(ptr, pin_num, ON_OFF_MIN, ON_OFF_MAX);
        } else {
            set_pwm(ptr, pin_num, ON_OFF_MIN, val);
        }
    }
}


static void set_pwm_freq(I2C_TypeDef *ptr, uint32_t freq) {
    uint32_t freq_val = 0;
    uint8_t prescale_val = 0;

    if (freq > FREQ_MAX) { // Check frequency boundries
        freq_val = FREQ_MAX;
    } else if (freq < FREQ_MIN) {
        freq_val = FREQ_MIN;
    } else {
        freq_val = freq;
    }

    uint32_t prescale = ((((FREQ_OSSC / (freq_val * 4096) * 10)) + 5) - 10) / 10;

    if (prescale > PRESCALE_MAX) { // Check frequency boundries
        prescale_val = (uint8_t)PRESCALE_MAX;
    } else if (prescale < PRESCALE_MIN) {
        prescale_val = (uint8_t)PRESCALE_MIN;
    } else {
        prescale_val = (uint8_t)prescale;
    }

    uint8_t old_mode = i2c_std_read_u8(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, MODE1_REG);
    uint8_t sleep[ADDR_ARRAY] = {MODE1_REG, ((old_mode & !MODE1_RESTART) | MODE1_SLEEP)};
    uint8_t pres[ADDR_ARRAY] = {PRESCALE_REG, prescale_val};
    uint8_t awake[ADDR_ARRAY] = {MODE1_REG, old_mode};
    uint8_t start[ADDR_ARRAY] = {MODE1_REG, old_mode | MODE1_START};

    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &sleep, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &pres, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &awake, ADDR_ARRAY);

    volatile uint32_t i = 0;
    if (i < 100000) { // PLACE A SEQUENCE TIMER HERE
        i++;
    }

    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &awake, ADDR_ARRAY);
}

static void set_pwm(I2C_TypeDef *ptr, uint8_t pin_num, uint16_t on, uint16_t off) {
    uint8_t pwm[PWM_ARRAY] = {LED0_ON_L + 4 * pin_num, (uint8_t)on, (uint8_t)(on >> SHIFT_BYTE), (uint8_t)off, (uint8_t)(off >> SHIFT_BYTE)};
    i2c_std_write(ptr, ADDR_PCA9685, ADDR_7_BIT, ADDR_7_BIT, &pwm, PWM_ARRAY);
}
