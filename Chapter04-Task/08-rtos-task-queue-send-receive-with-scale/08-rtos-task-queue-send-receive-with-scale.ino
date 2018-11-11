// ====================================================
// ArduRTOS Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

#include <Arduino_FreeRTOS.h>
#include <frt.h>

static QueueHandle_t xQueue1 = NULL;
static QueueHandle_t xQueue2 = NULL;

static QueueSetHandle_t xQueueSet = NULL;

void vTaskSender1(void *pvParamethers);
void vTaskSender2(void *pvParamethers);
void vTaskReceiver(void *pvParamethers);

void setup() { 
  xQueue1 = xQueueCreate(1, sizeof(char *));
  xQueue2 = xQueueCreate(1, sizeof(char *));

  xQueueSet = xQueueCreateSet(1 * 2);

  xQueueAddToSet(xQueue1, xQueueSet);
  xQueueAddToSet(xQueue2, xQueueSet);

  xTaskCreate(
    vTaskSender1,
    (const portCHAR *) "Sender-1",
    100,
    NULL,
    1,
    NULL
  );
  
  xTaskCreate(
    vTaskSender2,
    (const portCHAR *) "Sender-2",
    100,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    vTaskReceiver,
    (const portCHAR *) "Receiver",
    100,
    NULL,
    2,
    NULL
  );
    
  vTaskStartScheduler();
}

void loop() {
  // Must be empty to run Tasks correctly
}

void vTaskSender1(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "vTaskSender1 Ran!";

  const TickType_t xDelay100MS = pdMS_TO_TICKS(100);
  const char * const pcMessage = "Message from vSenderTask1\r\n";

  for(;;){
    vTaskDelay(xDelay100MS);
    xQueueSend(xQueue1, &pcMessage, 0);
  }
}

void vTaskSender2(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "vTaskSender1 Ran!";

  const TickType_t xDelay200MS = pdMS_TO_TICKS(200);
  const char * const pcMessage = "Message from vSenderTask1\r\n";
  
  for(;;){
    vTaskDelay(xDelay200MS);
    xQueueSend(xQueue2, &pcMessage, 0);
  }
}

void vTaskReceiver(void *pvParameters){
  (void) pvParameters;
  const char *pcTaskName = "vTaskReceiver Ran!";

  QueueHandle_t xQueueThatContainsData;
  char *pcReceivedString;
  
  Serial.begin(9600);
  Serial.println("Task[vTaskReceiver]::Initialized!");

  for(;;){
    Serial.println(pcTaskName);
    
    xQueueThatContainsData = (QueueHandle_t) xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
    xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0);
    
    Serial.println(pcReceivedString);
  }
}

