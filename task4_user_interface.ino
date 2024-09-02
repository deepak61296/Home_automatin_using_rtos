// task4_user_interface.ino
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <LiquidCrystal_I2C.h>
#include "globals.h"

void Task4(void *parameter) {
  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the LCD backlight

  while (1) {
    if (xSemaphoreTake(dhtMutex, portMAX_DELAY)) {
      float temperature = dht.readTemperature();
      xSemaphoreGive(dhtMutex);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(temperature);
      lcd.print(" C");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS); // Update every 2 seconds
  }
}
