#ifndef __SLEEP__
#define __SLEEP__

#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_system.h"

static const uint32_t microSecToMinuteFactor = 60000000;
static const uint64_t wakeupInterval = TTS_MINUTES * microSecToMinuteFactor;

void setWakeUpPin(const gpio_num_t wakeUpPin);
void startDeepSleep(const uint64_t wakeupInterval);
void validateWakeUpState();

#endif