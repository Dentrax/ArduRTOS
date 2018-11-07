// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>

void vTask(void *pvParameters);

void setup() {
  //Create and Start RTOS-spesific Tasks
}

void loop(){
  //Must be empty to run RTOS-Tasks correctly 
}

void vTask(void *pvParameters) {
  //TASK-spesific codes
}
