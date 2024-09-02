// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

// Define the pins
#define LED1_PIN 4
#define LDR_PIN 14
#define PIR_PIN 13
#define BUZZER_PIN 12
#define DHT_PIN 15
#define DIRECTION_PIN 26
#define STEP_PIN 25
#define LED_PIN 2

// Shared variables
extern DHT dht;
extern LiquidCrystal_I2C lcd;

// Mutexes
extern SemaphoreHandle_t dhtMutex;
extern SemaphoreHandle_t lcdMutex;
extern SemaphoreHandle_t motorMutex;

// PID constants
extern float Kp;
extern float Ki;
extern float Kd;
extern float setpoint;
extern float previousError;
extern float integral;

#endif // GLOBALS_H
