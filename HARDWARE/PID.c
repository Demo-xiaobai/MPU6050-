#include "PID.h"


tPid pidMotor1Speed;
tPid pid_Location;	//位置PID
tPid pid_Speed;		//速度PID
/*返回值是pwm
速度控制
*/
void PID_Init(){
	pidMotor1Speed.actual_val = 0.0;
	pidMotor1Speed.err = 0.0;
	pidMotor1Speed.err_last = 0.0;
	pidMotor1Speed.err_sum = 0.0;
	pidMotor1Speed.err_last_last = 0.0;
	pidMotor1Speed.Kd = 0;
	pidMotor1Speed.Ki = 0;
	pidMotor1Speed.Kp = 0;
	pidMotor1Speed.target_val = 0.0;
}
float P_realize(tPid* pid,float actual_val)
{	
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->actual_val = pid->Kp*pid->err;
	return pid->actual_val;
}

float PI_realize(tPid* pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->err_sum+=pid->err;
	pid->actual_val = pid->Kp*pid->err+pid->Ki*pid->err_sum;
	return pid->actual_val;
}


//位置式PID
float PID_realize(tPid* pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;
	pid->err_sum+=pid->err;
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err-pid->err_last);
	pid->err_last = pid->err;
	return pid->actual_val;
}
//增量式PID
float PID_realize_add(tPid* pid,float actual_val)
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;	//当前误差
	
	pid->actual_val = pid->Kp*(pid->err-pid->err_last)
					+ pid->Ki*(pid->err)
					+ pid->Kd*(pid->err + pid->err_last_last - 2*pid->err_last);
	
	pid->err_last_last = pid->err_last;
	pid->err_last = pid->err;
	return pid->actual_val;
}
//速度环
/*************速度环和直立环串联PID*********/
void Pid_Param_Init()
{
	//直立环  由mpu6050测出
	pid_Location.actual_val = 0.0;
	pid_Location.err = 0.0;
	pid_Location.err_last = 0.0;
	pid_Location.err_sum = 0.0;
	pid_Location.err_last_last = 0.0;
	pid_Location.Kd = 0;
	pid_Location.Ki = 0;
	pid_Location.Kp = 0;
	pid_Location.target_val = 0.0;
	
	//速度环  由编码器测出
	pid_Speed.actual_val = 0.0;
	pid_Speed.err = 0.0;
	pid_Speed.err_last = 0.0;
	pid_Speed.err_sum = 0.0;
	pid_Speed.err_last_last = 0.0;
	pid_Speed.Kd = 0;
	pid_Speed.Ki = 0;
	pid_Speed.Kp = 0;
	pid_Speed.target_val = 0.0;
	
}



