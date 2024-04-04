#ifndef M_I2C_H_
#define M_I2C_H_

#include "driver/i2c.h"
#include "esp_err.h"

#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define SELECTED_I2C I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

esp_err_t i2c_master_init(i2c_port_t i2c_num, gpio_num_t sda, gpio_num_t scl);
void m_i2c_master_write_slave_register(uint8_t slave_addr, uint8_t write_reg,
                                       uint8_t *data_wr, size_t size);

#endif // M_I2C_H_