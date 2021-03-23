#ifndef PCA9685_H_
#define PCA9685_H_

#include "../../hal/common.h"
#include "../../hal/i2c.h"

/* Enumerations */
/* Possible PINS on PCA9685 */
enum pca9685_range {
    Pca9685_Pin0, 
    Pca9685_Pin1, 
    Pca9685_Pin2, 
    Pca9685_Pin3, 
    Pca9685_Pin4, 
    Pca9685_Pin5, 
    Pca9685_Pin6, 
    Pca9685_Pin7, 
    Pca9685_Pin8, 
    Pca9685_Pin9, 
    Pca9685_Pin10, 
    Pca9685_Pin11,
    Pca9685_Pin12,
    Pca9685_Pin13,
    Pca9685_Pin14,
    Pca9685_Pin15
};

/* Public Functions */
bool pca9685_init(I2C_TypeDef *ptr, uint32_t freq);
bool pca9685_reset(I2C_TypeDef *ptr, uint32_t freq);
bool pca9685_set_pin(I2C_TypeDef *ptr, uint8_t pin_num, uint16_t val, bool invert);

#endif /* PCA9685_H_ */