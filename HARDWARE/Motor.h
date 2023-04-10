#ifndef __MOTOR_H__
#define __MOTOR_H__
void Motor_Init();
void SetSpeed(uint8_t speed);
void ZCroll(uint8_t speed);//正转
void ReviseRoll(uint8_t speed);
#endif