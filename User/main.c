#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "FreeRTOS.h"
#include "task.h"
#include "LED.h"
#include "FreeRTOSConfig.h"
#include "timers.h"
#include "freertos_demo.h"
#include "Key.h"
#include "queue.h"
uint8_t RxData;			//定义用于接收串口数据的变量


int main(void)
{

	LED_Init();
	Key_Init();
	/*串口初始化*/
	Serial_Init();		//串口初始化
	freertos_demo();

	return 0;

}
