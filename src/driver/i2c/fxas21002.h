#ifndef FXAS21002_H_
#define FXAS21002_H_

#include "../../hal/common.h"

/* Enumerations */
/* Sensitivity of Gyro Scope in DPS */
enum fxas21002_range {Fxas21002_Gyro_2000DPS, Fxas21002_Gyro_1000DPS, Fxas21002_Gyro_500DPS, Fxas21002_Gyro_250DPS};

/* Public Functions */
bool fxas210002_init(I2C_TypeDef *ptr, uint8_t range);
bool fxas210002_read(I2C_TypeDef *ptr, uint8_t range, int16_t *buf, uint32_t len);
bool fxas210002_check_fail(uint16_t *buf, uint32_t len);
void wait_loop();

#endif /* FXAS21002_H_ */