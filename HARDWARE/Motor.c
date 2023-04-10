#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "PWM.h"

int   Dead_Zone=4250;    //电机死区

	/*正转
		ANI1 = PWM(PA7)	 	AIN2 = 0(PA3)
		BIN1 = PWM(PA6)   	BIN2 = 0(PA4)
	反转
		AIN1 = 1    AIN2 = PWM
		BIN1 = 1    BIN2 = PWM
		
		PWM的频率一般选在5k~20kHz。
	*/
void Motor_Init()
{
	//PA7--AIN1  PA3----AIN2  PA6---BIN1   PA4----BIN2
	GPIO_InitTypeDef GPIO_InitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructer.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructer);
	TIM3_Init();
	
}
void SetSpeed(uint8_t speed)
{
	if(speed>=0)
	{
		ZCroll(speed);
	}	
}
//正转
void ZCroll(uint8_t speed)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_3,Bit_RESET);	//AIN2 = 0
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);	//BIN2 = 0
	PWM_SetCompare1(speed+Dead_Zone);
	PWM_SetCompare2(speed+Dead_Zone);	
}

//反转
void ReviseRoll(uint8_t speed)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_3);	//AIN2 = 1
	GPIO_SetBits(GPIOA, GPIO_Pin_4);    //BIN2 = 1
	
}
