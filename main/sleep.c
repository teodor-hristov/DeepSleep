#include "sleep.h"
#include "file_common.h"

static const char *TAG = "SLEEP";
static const char *errorFilePath = "/spiffs/wakeup_error";

void setWakeUpPin(const gpio_num_t wakeUpPin) {
  const bool isValid = esp_sleep_is_valid_wakeup_gpio(wakeUpPin);
  assert(isValid);

  const esp_err_t externalWakeUp = esp_sleep_enable_ext0_wakeup(wakeUpPin, 1);
  assert(externalWakeUp == ESP_OK);
}

void startDeepSleep(const uint64_t wakeupInterval) {
  // esp_sleep_enable_timer_wakeup can return error if wakeupInterval is too
  // short
  const esp_err_t wakeupErr = esp_sleep_enable_timer_wakeup(wakeupInterval);
  assert(wakeupErr == ESP_OK);

  // Disconnect internal circuit and set GPIO to hold position. Prevents power
  // consumption.
  const bool isRTCGPIO = rtc_gpio_is_valid_gpio(ESP32_WROOM_PIN) == ESP_OK;
  if (isRTCGPIO) {
    ESP_LOGI(TAG, "GPIO12 is RTC. Let's put it on hold.");
    (void)rtc_gpio_isolate(ESP32_WROOM_PIN);
  }

  setWakeUpPin(WAKEUP_PIN);
  (void)esp_deep_sleep_start();
}

void validateWakeUpState() {
  const esp_sleep_wakeup_cause_t wakeReason = esp_sleep_get_wakeup_cause();
  switch (wakeReason) {
  case ESP_SLEEP_WAKEUP_EXT0:
    ESP_LOGW(TAG, "Woke up on-demand.");
    break;
  case ESP_SLEEP_WAKEUP_TIMER:
    ESP_LOGW(TAG, "Regular wake up.");
    break;
  default:
    ESP_LOGE(TAG, "Unknown reason for wakeup.");
    saveError(wakeReason);
    break;
  }

  // Check if error file exists.
  if (fileExists(errorFilePath)) {
    ESP_LOGE(TAG, "There was unexpected wake up.");
    dumpFile(errorFilePath);
    (void)remove(errorFilePath);
  }
}