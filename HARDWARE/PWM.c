#include "stm32f10x.h"                  // Device header
#include "PWM.h"

//PA6 7 TIM3 CH1 2
void TIM3_Init()
{
	GPIO_InitTypeDef GPIO_InitStructer;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStructer;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	
//	配置时基单元
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 8000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

	//	配置输出比较单元
	//初始化输出比较单元 
	
//结构体变量有些成员未赋值，可能会出错，故需要给结构体全部成员赋予一个初始值
	TIM_OCStructInit(&TIM_OCInitStructer);
	TIM_OCInitStructer.TIM_OCMode = TIM_OCMode_PWM1;//设置输出比较的模式
	TIM_OCInitStructer.TIM_OCPolarity = TIM_OCPolarity_High;//设置输出比较的极性
	TIM_OCInitStructer.TIM_OutputState = TIM_OutputState_Enable;//设置输出使能
	TIM_OCInitStructer.TIM_Pulse = 0;//设置CCR
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructer);
	TIM_OC2Init(TIM3,&TIM_OCInitStructer);

//使能预装载器
//	TIM_OC1PolarityConfig(TIM3, TIM_OutputState_Enable);
//	TIM_OC2PolarityConfig(TIM3, TIM_OutputState_Enable);

	TIM_Cmd(TIM3,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3, Compare);
}
