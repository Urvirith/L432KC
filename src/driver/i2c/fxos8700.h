#ifndef FXOS8700_H_
#define FXOS8700_H_

#include "common.h"

/* Enumerations */
/* Speed of I2C bus, 10KHz, 100KHz 400KHz or Plus mode */
enum fxos8700_range {Fxos8700_Accel_2G, Fxos8700_Accel_4G, Fxos8700_Accel_8G};

/* Public Functions */
bool fxos8700_init(I2C_TypeDef *ptr, uint8_t range);
bool fxos8700_read(I2C_TypeDef *ptr, uint8_t range, int16_t *buf, uint32_t len);
bool fxos8700_check_fail(uint16_t *buf, uint32_t len);

#endif /* FXOS8700_H_ */