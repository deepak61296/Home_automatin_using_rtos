Here’s an updated documentation for your project, including design choices, task priorities, usage of RTOS features, PID control implementation, and instructions on how to run and test the project on Wokwi.

---

# **Smart Home Automation System Documentation**

## **Project Overview**

The Smart Home Automation System integrates multiple functionalities, including temperature monitoring, lighting control, motion detection, user interface management, motor control with PID, and system health monitoring. This project uses FreeRTOS to handle multiple concurrent tasks effectively.

## **Design Choices and Task Priorities**

### **1. Task Descriptions**

- **`Task1: Temperature Monitoring`**
  - **File:** `task1_temperature_monitoring.ino`
  - **Function:** Monitors temperature and humidity using a DHT22 sensor. It reads the temperature and humidity every 2 seconds and prints the values to the Serial Monitor.
  - **Priority:** 1 (Low)

- **`Task2: Lighting Control`**
  - **File:** `task2_lighting_control.ino`
  - **Function:** Controls an LED based on the light level detected by an LDR. The LED is turned on when the light level is low (i.e., it's dark) and turned off when the light level is high (i.e., it's bright).
  - **Priority:** 1 (Low)

- **`Task3: Motion Detection`**
  - **File:** `task3_motion_detection.ino`
  - **Function:** Monitors a PIR sensor to detect motion. If motion is detected, a buzzer is turned on to alert the user. Otherwise, the buzzer remains off.
  - **Priority:** 2 (Medium)

- **`Task4: User Interface`**
  - **File:** `task4_user_interface.ino`
  - **Function:** Updates an LCD display with the current temperature read from the DHT22 sensor. This task runs every 2 seconds.
  - **Priority:** 1 (Low)

- **`Task5: Motor Control with PID`**
  - **File:** `task5_motor_control.ino`
  - **Function:** Controls a stepper motor using PID control based on the temperature. The motor direction is adjusted based on the temperature, and the motor steps are adjusted accordingly.
  - **Priority:** 1 (Low)

- **`Task6: System Health Monitoring`**
  - **File:** `task6_system_health.ino`
  - **Function:** Periodically prints system health information to the Serial Monitor every 5 seconds.
  - **Priority:** 3 (High)

### **2. RTOS Features**

- **Semaphores/Mutexes:**
  - **DHT Mutex (`dhtMutex`):** Ensures that only one task accesses the DHT sensor at a time to prevent data corruption.
  - **LCD Mutex (`lcdMutex`):** Manages access to the LCD to avoid conflicts between tasks trying to update the display.
  - **Motor Mutex (`motorMutex`):** Coordinates access to the stepper motor to ensure proper operation without conflicts.

  Mutexes are used to protect shared resources and avoid race conditions, ensuring that critical sections of the code are accessed by only one task at a time.

## **PID Control Implementation**

The PID control is implemented in `Task5` to manage a stepper motor based on temperature readings:
- **Proportional (P):** Reacts to the current error.
- **Integral (I):** Accounts for past errors by summing them over time.
- **Derivative (D):** Predicts future errors based on the rate of change.

The PID constants (Kp, Ki, Kd) are used to adjust the control response. The motor's direction is set based on temperature thresholds, and the number of steps is adjusted according to the PID output.

## **Instructions for Running and Testing in Wokwi**

1. **Access the Project:**
   - Open your Wokwi project using the following link: [Wokwi Project](https://wokwi.com/projects/407931795033906177).

2. **Upload the Code:**
   - Ensure that all `.ino` files are correctly included in your Wokwi project. The `main.ino` file should be the primary file that initializes and manages the tasks.

3. **Compile and Upload:**
   - Use the Wokwi IDE to compile the code. Fix any issues reported during the compilation if necessary.
   - Upload the code to the virtual Arduino board.

4. **Monitor Outputs:**
   - Open the Serial Monitor in Wokwi to view output from `Task1` (temperature and humidity readings) and `Task6` (system health information).

5. **Test Functionalities:**
   - **Temperature Monitoring:** Verify that temperature and humidity readings are correctly displayed on the Serial Monitor.
   - **Lighting Control:** Test by changing light levels to observe the LED behavior.
   - **Motion Detection:** Simulate motion to check if the buzzer responds appropriately.
   - **User Interface:** Confirm that the LCD displays the correct temperature readings.
   - **Motor Control:** Observe the stepper motor's behavior and ensure it adjusts based on temperature readings.

6. **Debugging:**
   - Use the Serial Monitor for debugging and to view outputs from various tasks.
   - Adjust task priorities and PID constants if needed based on the observed behavior.

---

Feel free to adjust the details based on any specific observations or additional functionality you might have in your implementation.
