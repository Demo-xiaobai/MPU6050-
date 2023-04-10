#include "stm32f10x.h"                  // Device header
#include "Motor_Encoder.h"
//编码电机的读取
//编码器接口测速

void Motor_Encoder_Init()
{
	GPIO_InitTypeDef GPIO_InitStructer;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;
	TIM_ICInitTypeDef TIM_ICInitStructer;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入模式
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	//GPIO_Init(GPIOB,&GPIO_InitStructer);
	
//	TIM_InternalClockConfig(TIM2); 编码器接口会托管时钟，就不需要这行了
	//时基单元配置
	TIM_TimeBaseInitStructer.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructer.TIM_Period = 65536-1;
	TIM_TimeBaseInitStructer.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseInitStructer.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructer);
	
	
	
	//输入捕获单元配置 没有全部使用到
	TIM_ICStructInit(&TIM_ICInitStructer);
	TIM_ICInitStructer.TIM_Channel = TIM_Channel_1;	//通道为1
	TIM_ICInitStructer.TIM_ICFilter = 0xF;			//滤波器为0xF
	//TIM_ICInitStructer.TIM_ICPolarity = TIM_ICPolarity_Rising;	//电平极性为上升沿，代表高低电平极性不反转，不反相
	TIM_ICInit(TIM2,&TIM_ICInitStructer);
	
	TIM_ICInitStructer.TIM_Channel = TIM_Channel_2;	//通道为2
	TIM_ICInitStructer.TIM_ICFilter = 0xF;			//滤波器为0xF
	//TIM_ICInitStructer.TIM_ICPolarity = TIM_ICPolarity_Rising;	//电平极性为上升沿，代表高低电平极性不反转，不反相
	TIM_ICInit(TIM2,&TIM_ICInitStructer);
	
	//配置编码器接口
	/*
	TIM_EncoderMode_TI12:  TI1 TI2都计数
	TIM_ICPolarity_Rising: 反不反相
	参数3和4可以控制 反向和正向
	
	*/
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Falling);
	
	TIM_Cmd(TIM2,ENABLE);
}

int16_t Get_Encoder()	//得到速度 有符号
{
	int16_t temp;
	temp = TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2,0);	//CNT清0
	return temp;//获取计数器CNT的值
}

int16_t Encoder_loaction()		// 得到位置
{
	return TIM_GetCounter(TIM2);
}