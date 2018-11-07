// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

#define PIN_LED_1 9

#define PIN_BUTTON_1 2

void vTask(void *pvParamethers);

void setup() {
  pinMode(PIN_LED_1,    OUTPUT);
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
      
      if (stateButton == HIGH) {
        digitalWrite(PIN_LED_1, HIGH);
      } else {
        digitalWrite(PIN_LED_1, LOW);
      }
      
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
