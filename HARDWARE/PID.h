#ifndef __PID_H__
#define __PID_H__

typedef struct{
	float target_val;	//目标值
	float actual_val;	//实际值
	float err;		//当前误差
	float err_last;	//上一次的误差
	float err_sum;	//累计误差
	float Kp,Ki,Kd;	//	比例  积分  微分
	float err_last_last;

}tPid;

float P_realize(tPid* pid,float actual_val);	//P调节
void PID_Init();
float PI_realize(tPid* pid,float actual_val);	//I调节
float PID_realize(tPid* pid,float actual_val);	//D调节
#endif