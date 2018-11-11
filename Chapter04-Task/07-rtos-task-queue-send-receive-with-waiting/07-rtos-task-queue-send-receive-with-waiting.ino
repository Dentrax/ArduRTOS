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

typedef enum
{
  eSender1,
  eSender2
} DataSource_t;

typedef struct
{
  uint8_t       ucValue;
  DataSource_t  eDataSource;
} Data_t;

static const Data_t xStructToSend[2]=
{
  {100, eSender1},
  {200, eSender2}
};

void setup() { 
  xQueue = xQueueCreate(3, sizeof(int32_t));

  if(xQueue != NULL){
    xTaskCreate(
      vTaskReceiver,
      (const portCHAR *) "vTaskReceiver",
      100,
      (void *)pcTextForTaskReceiver,
      1,
      NULL
    );
  
    xTaskCreate(
      vTaskSender,
      (const portCHAR *) "Sender-1",
      100,
      &(xStructToSend[0]),
      2,
      NULL
    );

    xTaskCreate(
      vTaskSender,
      (const portCHAR *) "Sender-2",
      100,
      &(xStructToSend[1]),
      2,
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

  const TickType_t xDelay100MS = pdMS_TO_TICKS(100);
  
  BaseType_t xStatus;

  Serial.begin(9600);
  Serial.println("Task[vTaskSender]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);

    xStatus = xQueueSendToBack(xQueue, pvParameters, xDelay100MS);
    //2nd. param: Struct's address that in Sending
    //3rd. param: Duration of the Task that in Blocked

    if(xStatus != pdPASS){
      Serial.println("Failed to send to Queue");
    }
  }
}

void vTaskReceiver(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "vTaskReceiver Ran!";

  Data_t xReceivedStructure;
  BaseType_t xStatus;
  
  Serial.begin(9600);
  Serial.println("Task[vTaskReceiver]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    
    if(uxQueueMessagesWaiting(xQueue) != 3){
      Serial.println("Queue must be filled");
    }
    
    xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);
    
    if(xStatus == pdPASS){
      if(xReceivedStructure.eDataSource == eSender1){
        Serial.print("From Sender-1: ");
        Serial.println(xReceivedStructure.ucValue );
      } else {
        Serial.print("From Sender-2: ");
        Serial.println(xReceivedStructure.ucValue );
      }
    } else {
      Serial.println("Failed to read from Queue");
    }
  }
}

