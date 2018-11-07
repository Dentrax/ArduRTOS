// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

void vTask(void *pvParameters);

void setup() {
  //xTaskCreate(
  //            vTask,            /* Task function */
  //            "TaskOne",        /* String with name of Task */
  //            10000,            /* Stack size in words */
  //            NULL,             /* Parameter passed as input of the Task */
  //            1,                /* Priority of the Task */
  //            NULL);            /* Task handle */
  
  //vTaskDelete(NULL);            /* Delete task */
  
  //vTaskStartScheduler();        /* Start tasks */
}
void loop(){
 // ust be empty to run Tasks correctly
}

void vTask(void *pvParameters) {
  (void) pvParameters;
  const char *pcTaskName = "Task";
  Serial.begin(9600);

  for(;;) {
    Serial.println(pcTaskName);
    /*
     * Codes
     */
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
