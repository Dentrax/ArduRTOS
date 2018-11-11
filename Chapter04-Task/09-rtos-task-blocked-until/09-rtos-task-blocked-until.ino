// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

const TickType_t xDelayMS250  = pdMS_TO_TICKS(250);
const TickType_t xDelayMS500  = pdMS_TO_TICKS(500);
const TickType_t xDelayMS1000 = pdMS_TO_TICKS(1000);

void vTask1(void *pvParamethers);
void vTask2(void *pvParamethers);

void setup() { 
  xTaskCreate(
    vTask1,
    (const portCHAR *) "vTask1",
    100,
    NULL,
    1,
    NULL
    );

  xTaskCreate(
    vTask2,
    (const portCHAR *) "vTask2",
    100,
    NULL,
    3,
    NULL
  );
     
  vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTask1(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task1 Ran!";

  TickType_t xLastWakeTime = xTaskGetTickCount();

  Serial.begin(9600);
  Serial.println("Task[vTask1]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(250));
  }
}

void vTask2(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task2 Ran!";

  TickType_t xLastWakeTime = xTaskGetTickCount();

  Serial.begin(9600);
  Serial.println("Task[vTask2]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(250));
  }
}

