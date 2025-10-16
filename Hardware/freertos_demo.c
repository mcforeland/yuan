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

#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE   128
TaskHandle_t    start_task_handler;
void start_task( void * pvParameters );

static TimerHandle_t Swtmr1_Handle = NULL;/*软件定时器1句柄*/
static TimerHandle_t Swtmr2_Handle = NULL;/*软件定时器2句柄*/
/*
 * 在写应用程序时，可能需要用到的一些全局变量
 */
 
static uint32_t TmrCb_Count1 = 0;/*记录软件定时器1回调函数执行次数*/
static uint32_t TmrCb_Count2 = 0;/*记录软件定时器2回调函数执行次数*/

static void Swtmr1_Callback(void *parameter);
static void Swtmr2_Callback(void *parameter);

//vtask1
#define TASK1_STACK_SIZE  128
#define TASK1_PRIO 2
TaskHandle_t task1_handler;
void task1(void *parameters);

//vtask2
#define TASK2_STACK_SIZE  128
#define TASK2_PRIO 3
TaskHandle_t task2_handler;
void task2(void *parameters);

//vtask3
#define TASK3_STACK_SIZE  128
#define TASK3_PRIO 4
TaskHandle_t task3_handler;
void task3(void *parameters);


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
	/*
	 *TimerHandle_t xTimerCreate( const char * const pcTimerName, 
   *                                const TickType_t xTimerPeriodInTicks,
   *                                 const UBaseType_t uxAutoReload,
   *                                void * const pvTimerID,
   *                                TimerCallbackFunction_t pxCallbackFunction )
	 */
	Swtmr1_Handle = xTimerCreate("AutoReloadTimer",1000,pdTRUE,(void *)1,(TimerCallbackFunction_t)Swtmr1_Callback);
	if(Swtmr1_Handle!=NULL)
	{
			xTimerStart(Swtmr1_Handle,0);
	}
	Swtmr2_Handle = xTimerCreate("OneShotTimer",
																5000,
																pdFALSE,/*单次模式*/
																(void *)2,
																(TimerCallbackFunction_t)Swtmr2_Callback);
	if(Swtmr2_Handle!=NULL)
	{
			xTimerStart(Swtmr2_Handle,0);
	}
	//退出临界区
	vTaskDelete(NULL);
	taskEXIT_CRITICAL();
}

static void Swtmr1_Callback(void *parameter)
{
		TickType_t tick_num1;
	  TmrCb_Count1++;
	  tick_num1 = xTaskGetTickCount();
	  LED1_Turn();
	  printf("Swtmr1_Callback函数执行 %d 次 \r\n",TmrCb_Count1);
	  printf("滴答定时器数值=%d \r\n",tick_num1);

}
static void Swtmr2_Callback(void *parameter)
{
		TickType_t tick_num2;
	  TmrCb_Count2++;
	  tick_num2 = xTaskGetTickCount();
	  printf("Swtmr2_Callback函数执行 %d 次 \r\n",TmrCb_Count2);
	  printf("滴答定时器数值=%d \r\n",tick_num2);
}
