#ifndef __ANO_H__
#define __ANO_H__

//自定义帧
void SendF1(s16 _a,s16 _b ,s32 _c);

//飞控姿态的帧
void Send03(s16 ROL,s16 PIT,s16 YAW,u8 FUSION_STA);

void SendF2(uint8_t speed);

#endif