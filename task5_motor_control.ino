#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Define the motor control pins
#define DIRECTION_PIN 26
#define STEP_PIN 25
#define LED_PIN 2

// PID constants
extern float Kp;
extern float Ki;
extern float Kd;
extern float setpoint;
extern float previousError;
extern float integral;

// Create a mutex for accessing shared resources
extern SemaphoreHandle_t motorMutex;

void Task5(void *parameter) {
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  while (1) {
    float temperature;
    if (xSemaphoreTake(dhtMutex, portMAX_DELAY)) {
      temperature = dht.readTemperature();
      xSemaphoreGive(dhtMutex);
    }

    if (!isnan(temperature)) {
      float error = setpoint - temperature;
      integral += error;
      float derivative = error - previousError;
      float output = Kp * error + Ki * integral + Kd * derivative;
      previousError = error;

      if (temperature > 27.0) {
        digitalWrite(DIRECTION_PIN, HIGH);
      } else if (temperature < 25.0) {
        digitalWrite(DIRECTION_PIN, LOW);
      } else {
        output = 0;
      }

      int steps = abs(output);
      if (xSemaphoreTake(motorMutex, portMAX_DELAY)) {
        for (int n = 0; n < steps; n++) {
          digitalWrite(STEP_PIN, HIGH);
          delayMicroseconds(20);
          digitalWrite(STEP_PIN, LOW);
          delay(10);
          digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        }
        xSemaphoreGive(motorMutex);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Run every 100 milliseconds
  }
}
