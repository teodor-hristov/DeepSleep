#include "esp_random.h"
#include "file_common.h"
#include "sleep.h"

static const char *TAG = "MAIN";

void readSensor() { ESP_LOGI(TAG, "Sensor reading: %lu", esp_random() % 100); }

void app_main(void) {
  initFileSystem();
  validateWakeUpState();
  readSensor();
  startDeepSleep(wakeupInterval);
}
