#include "mcp6050.h"
#include "common.h"
#include "i2c.h"

// AREA FOR THE GY-521 / MCP6050
#define ADDR_MCP_0              0x68
#define ADDR_ARRAY              2
#define REG_ARRAY               1
#define ADDR_7_BIT              false

const uint8_t mcp_wakeup[ADDR_ARRAY]    =   {0x6B, 0x00};   // HW LW in that order BE transfer
const uint8_t mcp_gyro[ADDR_ARRAY]      =   {0x1B, 0x00};   // HW LW in that order BE transfer
const uint8_t mcp_acc[ADDR_ARRAY]       =   {0x1C, 0x00};   // HW LW in that order BE transfer

const uint8_t mcp_gyro_reg[REG_ARRAY]   =   {0x43};         // HW LW in that order BE transfer
const uint8_t mcp_acc_reg[REG_ARRAY]    =   {0x3B};         // HW LW in that order BE transfer
const uint8_t mcp_temp_reg[REG_ARRAY]   =   {0x41};         // HW LW in that order BE transfer

void mcp6050_init(I2C_TypeDef *ptr) {
    i2c_std_write(ptr, ADDR_MCP_0, ADDR_7_BIT, ADDR_7_BIT, &mcp_wakeup, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_MCP_0, ADDR_7_BIT, ADDR_7_BIT, &mcp_gyro, ADDR_ARRAY);
    i2c_std_write(ptr, ADDR_MCP_0, ADDR_7_BIT, ADDR_7_BIT, &mcp_acc, ADDR_ARRAY);
}

void mcp6050_read_gyro(I2C_TypeDef *ptr, uint8_t *buf, uint32_t len) {
    i2c_std_read(ptr, ADDR_MCP_0, ADDR_7_BIT, ADDR_7_BIT, &mcp_gyro_reg, REG_ARRAY, buf, len);
}

void mcp6050_read_accel(I2C_TypeDef *ptr, uint8_t *buf, uint32_t len) {
    i2c_std_read(ptr, ADDR_MCP_0, ADDR_7_BIT, ADDR_7_BIT, &mcp_acc_reg, REG_ARRAY, buf, len);
}

void mcp6050_read_temp(I2C_TypeDef *ptr, uint8_t *buf, uint32_t len) {
    i2c_std_read(ptr, ADDR_MCP_0, ADDR_7_BIT, ADDR_7_BIT, &mcp_temp_reg, REG_ARRAY, buf, len);
}

bool mcp6050_check_fail(uint8_t *buf, uint32_t len) {
    uint32_t i = 0;

    while (i < len) {
        if (buf[i] != 0) {
            return false;
        }

        i++;
    }

    return true;
}