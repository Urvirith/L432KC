#ifndef MCP6050_H_
#define MCP6050_H_

#include "../../hal/common.h"
#include "../../hal/i2c.h"

/* Public Functions */
void mcp6050_init(I2C_TypeDef *ptr);
void mcp6050_read_gyro(I2C_TypeDef *ptr, uint8_t *buf, uint32_t len);
void mcp6050_read_accel(I2C_TypeDef *ptr, uint8_t *buf, uint32_t len);
void mcp6050_read_temp(I2C_TypeDef *ptr, uint8_t *buf, uint32_t len);
bool mcp6050_check_fail(uint8_t *buf, uint32_t len);

#endif /* MCP6050_H_ */