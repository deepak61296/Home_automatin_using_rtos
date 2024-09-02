#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Define the LED and LDR pins
#define LED1_PIN 4
#define LDR_PIN 14

void Task2(void *parameter) {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  while (1) {
    int ldrValue = digitalRead(LDR_PIN);
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    if (ldrValue == LOW) {
      digitalWrite(LED1_PIN, HIGH);  // Turn on LED1 when it's dark
    } else {
      digitalWrite(LED1_PIN, LOW);   // Turn off LED1 when there's light
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Run every 1 second
  }
}
