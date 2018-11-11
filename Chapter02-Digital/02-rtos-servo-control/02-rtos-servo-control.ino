// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>
#include <Servo.h>

#define PIN_SERVO_1 8
#define PIN_SERVO_2 9

Servo SERVO_1;
Servo SERVO_2;

void vTaskForward(void *pvParamethers);
void vTaskBackward(void *pvParamethers);

void setup() {
  SERVO_1.attach(PIN_SERVO_1);
  SERVO_2.attach(PIN_SERVO_2);
  
  xTaskCreate(
    vTaskForward,
    (const portCHAR *) "vTaskForward",
    100,
    NULL,
    1,
    NULL
    );

  xTaskCreate(
    vTaskBackward,
    (const portCHAR *) "vTaskBackward",
    100,
    NULL,
    2,
    NULL
  );
     
  vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTaskForward(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task: ";

  Serial.begin(9600);
  Serial.println("Task[vTaskForward]::Initialized!");

  for(;;){
      Serial.println(pcTaskName);
      SERVO_1.write(180);
      SERVO_2.write(180);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTaskBackward(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task: ";

  Serial.begin(9600);
  Serial.println("Task[vTaskBackward]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    SERVO_1.write(90);
    SERVO_2.write(90);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

