/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "los_base.h"
#include "los_task.h"

#include "./usart/bsp_usart.h"	
#include "./lcd/bsp_ili9341_lcd.h"
#include "./flash/bsp_spi_flash.h"

static UINT32 s_uwTskID1,s_uwTskID2;


VOID task1(void)
{
    UINT32 uwRet = LOS_OK;
    
    while(1)
    {
        printf("HUAWEI lite_os UART test\n");
        uwRet = LOS_TaskDelay(1000);//操作系统延时
        if(uwRet !=LOS_OK)
        return;
    }
}

VOID task2(void)
{
    UINT32 uwRet = LOS_OK;
    
    while(1)
    {
        ILI9341_DispStringLine_EN_CH(LINE(1),"HUAWEI LiteOS task2");
        uwRet = LOS_TaskDelay(1000);//操作系统延时
        if(uwRet !=LOS_OK)
        return;
    }
}

UINT32 create_task1(void)
{
    UINT32 uwRet = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;
    task_init_param.usTaskPrio = 1;//任务优先级
    task_init_param.pcName = "task1";//任务名
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task1;//指定任务入口函数
    task_init_param.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;//设置任务堆栈大小
    uwRet = LOS_TaskCreate(&s_uwTskID1,&task_init_param);//调用任务创建函数
    if(uwRet !=LOS_OK)
    {
        return uwRet;
    }
    return uwRet;
}

UINT32 create_task2(void)
{
    UINT32 uwRet = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;
    task_init_param.usTaskPrio = 1;//任务优先级
    task_init_param.pcName = "task2";//任务名
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task2;//指定任务入口函数
    task_init_param.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;//设置任务堆栈大小
    uwRet = LOS_TaskCreate(&s_uwTskID2,&task_init_param);//调用任务创建函数
    if(uwRet !=LOS_OK)
    {
        return uwRet;
    }
    return uwRet;
}

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
//  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/.
	ILI9341_Init ();         
  USART_Config();
	ILI9341_GramScan ( 6 );
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	ILI9341_DispStringLine_EN_CH(LINE(0),"HUAWEI LiteOS");
//	
//	/* 发送一个字符串 */
//	Usart_SendString( DEBUG_USARTx,"这是一个串口中断接收回显实验\n");
	printf("Stm32F103 Power By HUAWEI Lite_OS");
	if (LOS_OK != LOS_KernelInit())
	{
			return LOS_NOK;
	}
	if (LOS_OK != create_task1())
	{
			return LOS_NOK;
	}
	if (LOS_OK != create_task2())
	{
			return LOS_NOK;
	}
	
	LOS_Start();
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/
