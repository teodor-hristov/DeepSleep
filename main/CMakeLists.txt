idf_component_register(SRCS "main.c" "sleep.c" "file_common.c" INCLUDE_DIRS "")
target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_VERBOSE")

add_compile_definitions(WAKEUP_PIN=GPIO_NUM_33)
add_compile_definitions(ESP32_WROOM_PIN=GPIO_NUM_12)
add_compile_definitions(TTS_MINUTES=15)