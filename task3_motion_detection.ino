#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Define the PIR sensor and Buzzer pins
#define PIR_PIN 13
#define BUZZER_PIN 12

void Task3(void *parameter) {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  while (1) {
    if (digitalRead(PIR_PIN) == HIGH) {
      digitalWrite(BUZZER_PIN, HIGH);  // Turn on the Buzzer if motion is detected
    } else {
      digitalWrite(BUZZER_PIN, LOW);   // Turn off the Buzzer if no motion
    }
    vTaskDelay(500 / portTICK_PERIOD_MS); // Run every 500 milliseconds
  }
}
