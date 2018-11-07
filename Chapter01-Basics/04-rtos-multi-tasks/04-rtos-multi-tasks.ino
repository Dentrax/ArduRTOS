// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

void vTask1(void *pvParamethers);
void vTask2(void *pvParamethers);
void vTask3(void *pvParamethers);
void vTask4(void *pvParamethers);

void setup() {
  xTaskCreate(
       vTask1,
       (const portCHAR *) "Task-1",
       100,
       NULL,
       1,
       NULL
     );
  
   xTaskCreate(
       vTask2,
       (const portCHAR *) "Task-2",
       100,
       NULL,
       2,
       NULL);
       
  xTaskCreate(
       vTask3,
       (const portCHAR *) "Task-3",
       100,
       NULL,
       3,
       NULL
     );
     
  xTaskCreate(
       vTask4,
       (const portCHAR *) "Task-4",
       100,
       NULL,
       4,
       NULL
     );
     
   vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTask1(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task-1: ";

  Serial.begin(9600);
  Serial.println("Task[vTask1]::Initialized!");
  
  for(;;){
      Serial.println(pcTaskName);
      /* 
       *  Codes
       */
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTask2(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task-2: ";

  Serial.begin(9600);
  Serial.println("Task[vTask2]::Initialized!");

  for(;;){
      Serial.println(pcTaskName);
      /*
       * Codes
       */
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTask3(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task-3: ";

  Serial.begin(9600);
  Serial.println("Task[vTask3]::Initialized!");

  for(;;){
      Serial.println(pcTaskName);
      /*
       * Codes
       */
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void vTask4(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task-4: ";

  Serial.begin(9600);
  Serial.println("Task[vTask4]::Initialized!");

  for(;;){
      Serial.println(pcTaskName);
      /*
       * Codes
       */
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
