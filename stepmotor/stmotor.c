#include "stm32f10x.h"
#include "stdint.h"
#include "Delay.h"
#define A 50

u16 FRot[4]={0x0008,0x0004,0x0002,0x0001};    //正转控制字
u16 RRot[4]={0x0001,0x0002,0x0004,0x0008};    //反转控制字
int i,j;

void StMotor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
}

void StMotor_For(uint8_t step)      //步进电机正转
{
    for(j=0;j<step;j++)
	{
		for(i=0;i<4;i++)
		{
			GPIO_Write(GPIOA, FRot[i]);
			Delay_ms(A);
		}
	}
	GPIO_Write(GPIOA,0x0000);
}

void StMotor_Rev(uint8_t step)      //步进电机反转
{
    for(j=0;j<step;j++)
	{
		for(i=0;i<4;i++)
		{
			GPIO_Write(GPIOA, RRot[i]);
			Delay_ms(A);
		}
	}
	GPIO_Write(GPIOA,0x0000);
}
