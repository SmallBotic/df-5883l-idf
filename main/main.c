#include <stdio.h>

#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "m_i2c.h"
#include "qmc5883l.h"

void app_main(void) {
  struct df_qmc5883 qmc;
  ESP_LOGW("MAIN", "STRUCT CREATED");
  i2c_master_init(I2C_NUM_0, 21, 22);
  ESP_LOGW("MAIN", "I2C initialized");
  qmcInit(&qmc, 0x0D);
  ESP_LOGW("MAIN", "QMC initialized");

// Formula: (deg + (min / 60.0)) / (180 / PI);
  float declinationAngle = (0 + (39.0 / 60.0)) / (180 / PI);
  setDeclinationAngle(&qmc, declinationAngle);

  // xTaskCreatePinnedToCore(qmc5883_run, "qmc_task", 4096, /*&qmc_params*/
  //                         &qmc, 1, NULL, 1);
  while (true) {
    readRaw(&qmc);

    float x = (float)qmc.v.XAxis;
    float y = (float)qmc.v.YAxis;
    float z = (float)qmc.v.ZAxis;

    float cx = qmc.v.AngleXY;
    float cy =qmc.v.AngleXZ;
    float cz = qmc.v.AngleYZ;

    getHeadingDegrees(&qmc);

    float headingDegrees = qmc.v.HeadingDegress;


    ESP_LOGW("MAIN", "[MAG]: %f %f %f [CAL]: %f %f %f [DIR]: %f [AZM]:", x, y, z, cx, cy, cz, headingDegrees);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
