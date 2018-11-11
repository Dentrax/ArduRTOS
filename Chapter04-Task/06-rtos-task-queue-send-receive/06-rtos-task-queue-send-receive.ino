// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>
#include <frt.h>

static const char *pcTextForTaskSender    = "Task::Sender Ran!";
static const char *pcTextForTaskReceiver  = "Task::Receiver Ran!";

QueueHandle_t xQueue;

void vTaskSender(void *pvParamethers);
void vTaskReceiver(void *pvParamethers);

void setup() { 
  xQueue = xQueueCreate(5, sizeof(int32_t));

  if(xQueue != NULL){
    xTaskCreate(
      vTaskReceiver,
      (const portCHAR *) "vTaskReceiver",
      100,
      (void *)pcTextForTaskReceiver,
      2,
      NULL
    );
  
    xTaskCreate(
      vTaskSender,
      (const portCHAR *) "Sender-1",
      100,
      (void *)100,
      1,
      NULL
    );

    xTaskCreate(
      vTaskSender,
      (const portCHAR *) "Sender-2",
      100,
      (void *)150,
      1,
      NULL
    );
    
    xTaskCreate(
      vTaskSender,
      (const portCHAR *) "Sender-3",
      100,
      (void *)200,
      1,
      NULL
    );
    
    xTaskCreate(
      vTaskSender,
      (const portCHAR *) "Sender-4",
      100,
      (void *)250,
      1,
      NULL
    );
    
    vTaskStartScheduler();
  } else {
    Serial.begin(9600);
    Serial.println("Setup::Queue allocition failed!");
  }

}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTaskSender(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "vTaskSender Ran!";

  int32_t lValueToSend = (int32_t)pvParameters;
  BaseType_t xStatus;

  Serial.begin(9600);
  Serial.println("Task[vTaskSender]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);

    xStatus = xQueueSendToBack(xQueue, &lValueToSend, 0);

    if(xStatus != pdPASS){
      Serial.println("Failed to send to Queue");
    }
  }
}

void vTaskReceiver(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "vTaskReceiver Ran!";

  const TickType_t xDelay100MS = pdMS_TO_TICKS(100);

  int32_t lValueReceived;
  BaseType_t xStatus;
  
  Serial.begin(9600);
  Serial.println("Task[vTaskReceiver]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    
    if(uxQueueMessagesWaiting(xQueue) != 0){
      Serial.println("Queue must be empty");
    }
    
    xStatus = xQueueReceive(xQueue, &lValueReceived, xDelay100MS);
    
    if(xStatus == pdPASS){
      Serial.println("Received value: ");
      Serial.println(lValueReceived);
    } else {
      Serial.println("Failed to receive from Queue");
    }
  }
}

