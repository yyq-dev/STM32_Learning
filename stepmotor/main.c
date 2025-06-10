#include <stm32f10x.h>                  
#include <Delay.h>
#include <key.h>
#include <stmotor.h>

extern uint8_t step;
uint8_t s;

int main(void)
{
	StMotor_Init();  
	KEY_Init();   //步进电机和按键初始化
	
	while (1)
	{
		s = Key_GetNum();

		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 1 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)	
		//当键盘锁开锁且正转开关闭合时，步进电机按设定步数正转	
		{
			StMotor_For(s);
			step = 0;	
		}

		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 1 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == 0)	
		//当键盘锁开锁且反转开关闭合时，步进电机按设定步数反转
		{
			StMotor_Rev(s);	
			step = 0;
		}
	}
	
}
