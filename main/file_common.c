#include "./file_common.h"

static const char *TAG = "FILE_COMMON";
static const char *errorFilePath = "/spiffs/wakeup_error";

void initFileSystem() {
  esp_vfs_spiffs_conf_t conf = {.base_path = "/spiffs",
                                .partition_label = NULL,
                                .max_files = 10,
                                .format_if_mount_failed = true};

  esp_err_t ret = esp_vfs_spiffs_register(&conf);
  if (ret != ESP_OK) {
    ESP_LOGI(TAG, "Failed to initialize SPIFFS");
    return;
  }
}

void saveError(const esp_sleep_wakeup_cause_t reason) {
  time_t now;
  time(&now);

  FILE *f = fopen(errorFilePath, "w");
  if (f == NULL) {
    ESP_LOGI(TAG, "Failed to open file for writing");
    return;
  }

  fprintf(f, "Reason: %d. Timestamp: %s", reason, ctime(&now));
  fclose(f);
}

bool fileExists(const char *filename) {
  if (!filename) {
    return false;
  }

  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    fclose(file);
    return true;
  }

  return false;
}

void dumpFile(const char *filename) {
  if (!filename) {
    return;
  }

  ESP_LOGI(TAG, "Opening file: %s", filename);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    ESP_LOGI(TAG, "Failed to open file");
    return;
  }

  // Read and print file content
  char line[128];
  ESP_LOGI(TAG, "File content:");
  while (fgets(line, sizeof(line), file) != NULL) {
    ESP_LOGI(TAG, "%s", line);
  }

  fclose(file);
}