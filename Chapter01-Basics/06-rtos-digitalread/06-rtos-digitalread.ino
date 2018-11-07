// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

#define PIN_BUTTON_1 10

void vTask1(void *pvParamethers);

void setup() {
  pinMode(PIN_BUTTON_1, INPUT);
  
  xTaskCreate(
       vTask,
       (const portCHAR *) "Task",
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

void vTask(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task: ";

  Serial.begin(9600);
  Serial.println("Task[vTask]::Initialized!");

  int stateButton = LOW;
  
  for(;;){
      Serial.println(pcTaskName);

      stateButton = digitalRead(PIN_BUTTON_1);
      Serial.println(stateButton);
      
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
