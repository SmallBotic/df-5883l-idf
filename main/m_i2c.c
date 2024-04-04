#include "m_i2c.h"

esp_err_t i2c_master_init(i2c_port_t i2c_num, gpio_num_t sda, gpio_num_t scl) {
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = sda;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = scl;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
  conf.clk_flags = 0;

  i2c_param_config(i2c_num, &conf);
  return i2c_driver_install(i2c_num, conf.mode, I2C_MASTER_RX_BUF_DISABLE,
                            I2C_MASTER_TX_BUF_DISABLE, 0);
}

void m_i2c_master_write_slave_register(uint8_t slave_addr, uint8_t write_reg,
                                       uint8_t *data_wr, size_t size) {
  // Write data to the slave
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, slave_addr << 1 | I2C_MASTER_WRITE, true);
  i2c_master_write_byte(cmd, write_reg, true);
  i2c_master_write(cmd, data_wr, size, true);
  i2c_master_stop(cmd);
  i2c_master_cmd_begin(SELECTED_I2C, cmd, 1000 / portTICK_PERIOD_MS);
  i2c_cmd_link_delete(cmd);
}