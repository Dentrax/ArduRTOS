// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

#define PIN_SENSOR A0
#define PIN_BUTTON 2

void vTask(void *pvParamethers);

void setup() {
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_BUTTON, INPUT);
  
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

  int16_t sStateButton = LOW;
  int16_t sValueSensor = 0;
  
  for(;;){
      Serial.println(pcTaskName);

      sStateButton = digitalRead(PIN_BUTTON);
      sValueSensor = analogRead(PIN_SENSOR);
      
      if (sStateButton == HIGH) {
        Serial.print("Analog Read:");
        Serial.println(sValueSensor);
      }
      
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
  vTaskDelete(NULL);
  //Delete task if for-loop breaked
}
