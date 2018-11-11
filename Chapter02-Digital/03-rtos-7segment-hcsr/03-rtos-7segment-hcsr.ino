// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>
#include "LedControl.h"

#define PIN_HCSR04_TRIG 7
#define PIN_HCSR04_ECHO 8

#define RANGE_HCSR04_MAX 200
#define RANGE_HCSR04_MIN 3
#define RANGE_HCSR04_NO_ECHO -1

LedControl lc = LedControl(10, 12, 11, 1);

void vTask7SGMNT(void *pvParameters);
void vTaskHCSR04(void *pvParameters);

void setup() {
  pinMode(PIN_HCSR04_ECHO, INPUT);
  pinMode(PIN_HCSR04_TRIG, OUTPUT);

  //Clear LCD module
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  //Task for 7-Segment-Display 
  //Priority: 1
  xTaskCreate(
    vTask7SGMNT,
    (const portCHAR *) "Task - 7Segment",
    100,
    NULL,
    1,
    NULL
  );

  //Task for HCSR04 sensor 
  //Priority: 1
  xTaskCreate(
    vTaskHCSR04,
    (const portCHAR *) "Task - HCSR04",
    100,
    NULL,
    1,
    NULL
  );
     
  vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTaskHCSR04(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task: ";

  Serial.begin(9600);
  Serial.println("Task[vTaskHCSR04]::Initialized!");

  volatile uint32_t lDuration = 0;
  volatile uint32_t lDistance = 0;

  for(;;){
    Serial.print(pcTaskName);
    Serial.println(lDistance);

    taskDISABLE_INTERRUPTS();
    
    digitalWrite(PIN_HCSR04_TRIG, LOW);
    vTaskDelay(2 / portTICK_PERIOD_MS);
  
    digitalWrite(PIN_HCSR04_TRIG, HIGH);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    digitalWrite(PIN_HCSR04_TRIG, LOW);

    taskENABLE_INTERRUPTS();

    lDuration = pulseIn(PIN_HCSR04_ECHO, HIGH);
    lDistance = lDuration / 29.1 / 2;

    if(lDistance > RANGE_HCSR04_MAX){
      lDistance = RANGE_HCSR04_NO_ECHO;
    } else {
      lDistance = constrain(lDistance, RANGE_HCSR04_MIN, RANGE_HCSR04_MAX);
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void vTask7SGMNT(void *pvParameters) {
  (void) pvParameters;
  const char *pcTaskName = "Task: ";

  Serial.begin(9600);
  Serial.println("Task[vTask7SGMNT]::Initialized!");

  byte current = 0;

  for(;;) {
      Serial.print(pcTaskName);
      Serial.println(current);
      
      if(current % 10 == 0) current = 0;
      
      lc.setDigit(0, 3, 9 - current, false);
      
      current++;
      
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }  
}

