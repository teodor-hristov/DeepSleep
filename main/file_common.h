#ifndef __FILE_COMMON__
#define __FILE_COMMON__

#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_spiffs.h"
#include "time.h"
#include <stdio.h>

void initFileSystem();
void saveError(const esp_sleep_wakeup_cause_t reason);
bool fileExists(const char *filename);
void dumpFile(const char *filename);

#endif