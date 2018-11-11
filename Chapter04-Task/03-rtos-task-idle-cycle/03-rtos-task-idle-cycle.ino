// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

static const char *pcTextForTask = "Task Ran!";

volatile uint32_t ulIdleCycleCount = 0ul;

void vTask(void *pvParamethers);

void setup() { 
  xTaskCreate(
    vTask,
    (const portCHAR *) "Task",
    100,
    (void *)pcTextForTask,
    1,
    NULL
  );
  
  vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vApplicationIdleHook(void){
  ulIdleCycleCount++;
}

void vTask(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task1 Ran!";

  const TickType_t xDelay250MS = pdMS_TO_TICKS(250);

  Serial.begin(9600);
  Serial.println("Task[vTask]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    Serial.println(ulIdleCycleCount);
    //vPrintStringAndNumber(pcTaskName, ulIdleCycleCount);
    vTaskDelay(xDelay250MS);
  }
}

void vTaskPeriodic(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task2 Ran!";

  const TickType_t xDelay3ms = pdMS_TO_TICKS(1000);

  TickType_t xLastWakeTime = xTaskGetTickCount();
  
  Serial.begin(9600);
  Serial.println("Task[vTaskPeriodic]::Initialized!");

  for(;;){
    vTaskDelayUntil(&xLastWakeTime, xDelay3ms);  

    Serial.print(xLastWakeTime);
    Serial.println(pcTaskName);
  }
}

