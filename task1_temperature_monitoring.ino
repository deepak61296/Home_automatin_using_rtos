// task1_temperature_monitoring.ino
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <DHT.h>
#include "globals.h"

void Task1(void *parameter) {
  dht.begin();  // Initialize the DHT sensor
  while (1) {
    if (xSemaphoreTake(dhtMutex, portMAX_DELAY)) {
      float temperature = dht.readTemperature();
      float humidity = dht.readHumidity();

      if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
      } else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
      }
      xSemaphoreGive(dhtMutex);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Run every 2 seconds
  }
}
