#include "freertos_demo.h"
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LED.h"
#include "FreeRTOSConfig.h"
#include "timers.h"
#include "stdio.h"
#include "Key.h"
#include "queue.h"
#include "semphr.h"

#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE   128
TaskHandle_t    start_task_handler;
void start_task( void * pvParameters );

//vtask1 实现入队
#define TASK1_STACK_SIZE  128
#define TASK1_PRIO 2
TaskHandle_t task1_handler;
void task1(void *parameters);

//vtask2 实现小数据出队
#define TASK2_STACK_SIZE  128
#define TASK2_PRIO 3
TaskHandle_t task2_handler;
void task2(void *parameters);

//vtask3 实现大数据出队
#define TASK3_STACK_SIZE  128
#define TASK3_PRIO 4
TaskHandle_t task3_handler;
void task3(void *parameters);


//	ctreate queue
QueueSetHandle_t queueset_Handle;
QueueHandle_t queue_key;/*小数据*/
QueueHandle_t semphr_handle;/*大数据*/

char buf[100] = "这是一个大数组，12345n";
void freertos_demo(void)
{
		
		xTaskCreate((TaskFunction_t         )   start_task,
                (char *                 )   "start_task",
                (configSTACK_DEPTH_TYPE )   START_TASK_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   START_TASK_PRIO,
                (TaskHandle_t *         )   &start_task_handler );
    vTaskStartScheduler();
}

void start_task(void *parameters)
{
	//进入临界区
	taskENTER_CRITICAL();
	queueset_Handle = xQueueCreateSet(2);
	if(queueset_Handle!=NULL)
	{
			printf("创建queueset_Handle队列集成功！\r\n");
	}
	
	queue_key = xQueueCreate(2,sizeof(uint8_t));
	if(queue_key!=NULL)
	{
			printf("创建queue_key队列成功！ \r\n");
	}
	
	semphr_handle = xSemaphoreCreateBinary();
	if(semphr_handle != NULL)
	{
			printf("创建semphr_handle队列成功！ \r\n");
	}
	
	//添加队列和信号量到队列集
	xQueueAddToSet(queue_key,queueset_Handle);
	xQueueAddToSet(semphr_handle,queueset_Handle);
	
	
	xTaskCreate((TaskFunction_t         )   task1,
                (char *                 )   "task1",
                (configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK1_PRIO,
                (TaskHandle_t *         )   &task1_handler );
	xTaskCreate((TaskFunction_t         )   task2,
                (char *                 )   "task2",
                (configSTACK_DEPTH_TYPE )   TASK2_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK2_PRIO,
                (TaskHandle_t *         )   &task2_handler );

	//退出临界区
	vTaskDelete(NULL);
	taskEXIT_CRITICAL();
}

void task1(void *parameters)
{
	 uint16_t key = 0;
	 BaseType_t rev = 0;
	 
	 for(;;)
	 {
		    key = Key_GetNum();
				if(key == 1)
				{
					printf("Key1按下,键值为%d\r\n",key);
					rev = xQueueSend(queue_key, &key, portMAX_DELAY);
					if(rev == pdTRUE)
					{
							printf("queue_key写入队列成功！ \r\n");
					}
					LED1_Turn();
				}
				else if(key == 2)
				{
						printf("Key11按下,键值为%d\r\n",key);
					rev = xSemaphoreGive(semphr_handle);
					if(rev == pdTRUE)
					{
							printf("信号量释放成功！ \r\n");
					}
					LED2_Turn();
				}
	 }
	 vTaskDelay(10);
}

void task2(void *parameters)
{
	  BaseType_t rev = 0;
	  uint8_t key_val = 0;
	  QueueSetMemberHandle_t  member_handle;
	  for(;;)
		{
			 member_handle = xQueueSelectFromSet(queueset_Handle,portMAX_DELAY );
			 if(member_handle == queue_key)
			 {
				    xQueueReceive(member_handle,&key_val,portMAX_DELAY);
						printf("接收数据:%d\r\n",key_val);
			 }
			 else if(member_handle == semphr_handle)
			 {
						xQueueReceive(member_handle,&key_val,portMAX_DELAY);
						printf("二值信号量接收成功 \r\n");
			 }
		}
}


