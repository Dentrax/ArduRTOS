// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

void vTaskContinuous(void *pvParamethers);
void vTaskPeriodic(void *pvParamethers);

void setup() { 
  xTaskCreate(
    vTaskContinuous,
    (const portCHAR *) "vTaskContinuous1",
    100,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    vTaskContinuous,
    (const portCHAR *) "vTaskContinuous2",
    100,
    NULL,
    2,
    NULL
  );

  xTaskCreate(
    vTaskPeriodic,
    (const portCHAR *) "vTaskPeriodic",
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

void vTaskContinuous(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task1 Ran!";

  const TickType_t xDelay10ms = pdMS_TO_TICKS(1000);

  TickType_t xLastWakeTime;

  Serial.begin(9600);
  Serial.println("Task[vTaskContinuous]::Initialized!");

  for(;;){
    //vTaskDelay(xDelay10ms);  
    //xLastWakeTime=xTaskGetTickCount();
    Serial.print(xLastWakeTime);
    Serial.println(pcTaskName);
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

