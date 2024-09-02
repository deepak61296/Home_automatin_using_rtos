#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void Task6(void *parameter) {
  while (1) {
    Serial.println("Monitoring system health...");
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Run every 5 seconds
  }
}
