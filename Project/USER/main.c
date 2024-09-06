#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"


uint32_t flag1;
uint32_t flag2;
extern List_t pxReadyTasksLists[configMAX_PRIORITIES];

TaskHandle_t Task1_Handle;
#define TASK1_STACK_SIZE            128
StackType_t Task1Stack[TASK1_STACK_SIZE];
TCB_t Task1TCB;

TaskHandle_t Task2_Handle;
#define TASK2_STACK_SIZE            128
StackType_t Task2Stack[TASK2_STACK_SIZE];
TCB_t Task2TCB;


void Task1_Entry(void *p_arg);
void Task2_Entry(void *p_arg);
int main(void)
{	
    delay_init();	    //延时函数初始化	  
    LED_Init();		  	//初始化与LED连接的硬件接口
    LED0 = 0;
    Task1_Handle = xTaskCreateStatic((TaskFunction_t)Task1_Entry,
                                     (char *)"Task1",
                                     (uint32_t)TASK1_STACK_SIZE,
                                     (void *)NULL,
                                        3,
                                     (StackType_t *)Task1Stack,
                                     (TCB_t *)&Task1TCB);
    vListInsertEnd((&pxReadyTasksLists[1]),
                   &(((TCB_t *)(&Task1TCB))->xStateListItem ));
                   
                   
    Task2_Handle = xTaskCreateStatic((TaskFunction_t)Task2_Entry,
                                     (char *)"Task2",
                                     (uint32_t)TASK2_STACK_SIZE,
                                     (void *)NULL,
                                        3,
                                     (StackType_t *)Task2Stack,
                                     (TCB_t *)&Task2TCB);
    vListInsertEnd((&pxReadyTasksLists[2]),
                   &(((TCB_t *)(&Task2TCB))->xStateListItem ));
    
    vTaskStartScheduler();
    
    while(1)
    {
        
    }
}

void Task1_Entry(void *p_arg)
{
    for(;;)
    {
        flag1 = 1;
        LED0 = 1;
        delay_ms(500);
        flag1 = 0;
        LED0 = 0;
        delay_ms(500);
        taskYIELD();
    }
    
}

void Task2_Entry(void *p_arg)
{
    for(;;)
    {
        flag2 = 1;
        LED1 = 1;
        delay_ms(500);
        flag2 = 0;
        LED1 = 0;
        delay_ms(500);
        taskYIELD();
    }
}
