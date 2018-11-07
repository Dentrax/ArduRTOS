// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

#define PIN_LED_1 9 //PWM Pin
#define PIN_LED_2 10

void vTask1(void *pvParamethers);
void vTask2(void *pvParamethers);

void setup() {
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  
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
       1,
       NULL);
          
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

  int brightness = 0;
  int fadeAmount = 5;
  
  for(;;){
      Serial.println(pcTaskName);

      analogWrite(PIN_LED_1, brightness);
      
      brightness = brightness + fadeAmount;
      
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
      
      vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}

void vTask2(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "Task-2: ";

  Serial.begin(9600);
  Serial.println("Task[vTask2]::Initialized!");

  int brightness = 0;
  int fadeAmount = 5;

  for(;;){
      Serial.println(pcTaskName);

      analogWrite(PIN_LED_2, brightness);
      
      brightness = brightness + fadeAmount;
      
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }

      vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}
