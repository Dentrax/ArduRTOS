// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

const TickType_t xDelay100MS = pdMS_TO_TICKS(100UL);

static const char *pcTextForTask1 = "Task1 Ran!";
static const char *pcTextForTask2 = "Task2 Ran!";

TaskHandle_t xTask2Handle = NULL;

void vTask1(void *pvParamethers);
void vTask2(void *pvParamethers);

void setup() { 
  xTaskCreate(
    vTask1,
    (const portCHAR *) "Task1",
    100,
    (void *)pcTextForTask1,
    1,
    NULL
  );
  
  xTaskCreate(
    vTask2,
    (const portCHAR *) "Task2",
    100,
    (void *)pcTextForTask1,
    2,
    &xTask2Handle
  );  
  
  vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTask1(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task1 Ran!";

  Serial.begin(9600);
  Serial.println("Task[vTask1]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);

    vTaskDelay(xDelay100MS);
  }
}

void vTask2(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task2 Ran!";
  
  Serial.begin(9600);
  Serial.println("Task[vTask2]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    vTaskDelay(xDelay100MS);
    vTaskDelete(NULL);
    Serial.println("...DETELED...");
  }
}

