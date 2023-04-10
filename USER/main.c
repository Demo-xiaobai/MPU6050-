#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"  
#include "uart1.h"
#include "OLED.h"
#include "ANO.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "Motor_Encoder.h"
#include "PID.h"
#include "Motor.h"

extern  tPid pidMotor1Speed;  //pidMotor1Speed电机的目标速度
int main(void)
{


	float pitch,roll,yaw; //roll:横滚角  pitch  yaw�������
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 
	uart_init(115200);	 	
	delay_init();			  			
	MPU_Init();	
	OLED_Init();
	UART2_Init();
	while(mpu_dmp_init())		//返回0 初始化成功  返回其他值初始化失败
	{
		delay_ms(20);
	}

	while(1)
	{
		delay_ms(2);
		//当得出dmp计算的结果后，  我们获取芯片的温度值，
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)	//得出dmp计算的结果   返回0正常  返回其它值失败
		{
			temp=MPU_Get_Temperature();	//获取芯片的温度
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
		}
		Send03((int)(pitch*100),(int)(roll*100),(int)(yaw*100),1);
		
		OLED_ShowString(2,2,"Pitch:");
		OLED_ShowString(3,2,"Roll");
		OLED_ShowString(4,2,"yaw");
		
		OLED_ShowSignedNum(2,9,pitch,5);
		OLED_ShowSignedNum(3,9,roll,5);
		OLED_ShowSignedNum(4,9,yaw,5);
	} 		

	//Motor_Init();
	//SetSpeed(10000);
	

}



