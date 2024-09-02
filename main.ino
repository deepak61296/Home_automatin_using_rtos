// main.ino
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "globals.h"

// Define the DHT sensor type
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// PID constants
float Kp = 2.0;
float Ki = 0.5;
float Kd = 1.0;

// PID control variables
float setpoint = 26.0; // Desired temperature setpoint
float previousError = 0;
float integral = 0;

// Create mutexes for accessing shared resources
SemaphoreHandle_t dhtMutex;
SemaphoreHandle_t lcdMutex;
SemaphoreHandle_t motorMutex;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize LEDs and DHT sensor
  pinMode(LED1_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  dht.begin();

  // Create mutexes
  dhtMutex = xSemaphoreCreateMutex();
  lcdMutex = xSemaphoreCreateMutex();
  motorMutex = xSemaphoreCreateMutex();

  // Create Tasks
  xTaskCreate(Task1, "Task1", 10000, NULL, 1, NULL); // Temperature Monitoring
  xTaskCreate(Task2, "Task2", 10000, NULL, 1, NULL); // Lighting Control
  xTaskCreate(Task3, "Task3", 10000, NULL, 2, NULL); // Motion Detection and Security Alert
  xTaskCreate(Task4, "Task4", 10000, NULL, 1, NULL); // User Interface (LCD Display)
  xTaskCreate(Task5, "Task5", 10000, NULL, 1, NULL); // Motor Control with PID
  xTaskCreate(Task6, "Task6", 10000, NULL, 3, NULL); // System Health Monitoring
}

void loop() {
  // Empty loop
}
