/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * ???t??  ¡êomain.c
 * ?¨¨¨º?    ¡êoGPIOC8?¨®3?¨¦¨´2¡§?¡ê?¨¦¦Ì?TRIG¡ê?GPIOC9?¨®3?¨¦¨´?¡ê?¨¦¦Ì?ECHO¡ê?
             ????¡ä??¨²??(?¡À¨¢?¡ä??¨²??)2??¨²¡ã?¡Á¨®COM1?¨²¨¦?,2¡é¡ä¨°?a3???
			 ?????¨°¡ä??¨²?¨²¨º?¡ê?????2¡§¨¬??¨º115200¡ê?8??¡ê?¨°???¨ª¡ê?1??¡ê?
			 ?TD¡ê?¨¦???¡ê?¡§¨º¡À?¨°PC¡¤¡é?¨ª2a¦Ì?¦Ì??¨¤¨¤?         
 * ¨º¦Ì?¨¦??¨¬¡§¡êo¨°¡ã?eSTM32?a¡¤¡é¡ã?
 * ?a¡ã?¡À?  ¡êoST3.5.0
 *
 * ¡Á¡Â??    ¡êowildfire team 
 * ??¨¬3    ¡êohttp://www.amobbs.com/forum-1008-1.html
 * ¨¬?¡À|    ¡êohttp://firestm32.taobao.com
*********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "TIM4.h"
#include "UltrasonicWave.h"
#include "interface.h"
#include "motor.h"
#include "pwm.h"

/*
 * o¡¥¨ºy??¡êoDelayTime_ms
 * ?¨¨¨º?  ¡êoTime   	?¨®¨º¡À¦Ì?¨º¡À?? MS
 * ¨º?¨¨?  ¡êo?T
 * ¨º?3?  ¡êo?T
 */
 
char ctrl_comm_m1 = 'N';//??????¨¢?
char ctrl_comm_m2 = 'N';//??????¨¢?
char ctrl_comm_l = 'N';//??????¨¢?
char ctrl_comm_r = 'N';//??????¨¢?

char ctrl_comm_a = 'N';//??????¨¢?

char pctrl_comm_m1[10];//??????¨¢?
char pctrl_comm_m2[10];//??????¨¢?
char pctrl_comm_l[10];//??????¨¢?
char pctrl_comm_r[10];//??????¨¢?
int num=0,num1=0,num2=0;

//unsigned char continue_time1=0;

//?-?¡ê¡ê?¨ª¡§1y?D??¨¨y??1a¦Ì???1¨¹¦Ì?¡Á¡ä¨¬?¨¤¡ä????D?3¦Ì???¡¥
void SearchRun(void)
{
	
	pctrl_comm_m1[num%10] = ctrl_comm_m1;//??????¨¢?
	pctrl_comm_m2[num%10] = ctrl_comm_m2;//??????¨¢?
	pctrl_comm_l[num%10] = ctrl_comm_l;//??????¨¢?
	pctrl_comm_r[num%10] =  ctrl_comm_r;//??????¨¢?
	num++;
	
	//¨¨y?¡¤???¨¬2a¦Ì?
	if(SEARCH_M1_IO == BLACK_AREA)
	{
		ctrl_comm_m1 = 'W';
	}
	else if(SEARCH_M1_IO == WHITE_AREA)//?D
	{
		ctrl_comm_m1 = 'B';
	}
	
	if(SEARCH_M2_IO == BLACK_AREA)
	{
		ctrl_comm_m2 = 'W';
	}
	else if(SEARCH_M2_IO == WHITE_AREA)//?D
	{
		ctrl_comm_m2 = 'B';
	}
	
	if(SEARCH_R_IO == BLACK_AREA)
	{
		ctrl_comm_r = 'W';
	}
	else if(SEARCH_R_IO == WHITE_AREA)//?D
	{
		ctrl_comm_r = 'B';
	}
	
	if(SEARCH_L_IO == BLACK_AREA)
	{
		ctrl_comm_l = 'W';
	}
	else if(SEARCH_L_IO == WHITE_AREA)//?D
	{
		ctrl_comm_l = 'B';
	}
	
	if(SEARCH_A_IO == BLACK_AREA)
	{
		ctrl_comm_a = 'W';
	}
	else if(SEARCH_A_IO == WHITE_AREA)//?D
	{
		ctrl_comm_a = 'B';
	}
	
	
}


void DelayTime_ms(int Time)      //1us?¨®¨º¡Ào¡¥¨ºy
{
   unsigned int i;
   for ( ; Time>0; Time--)
     for ( i = 0; i <720; i++ );
}

/*
 * o¡¥¨ºy??¡êomain
 * ?¨¨¨º?  ¡êo?¡Âo¡¥¨ºy
 * ¨º?¨¨?  ¡êo?T
 * ¨º?3?  ¡êo?T
 */
int main(void)
{	
    /* ?????¦Ì¨ª3¨º¡À?¨®?a 72M */ 
	double duty_cycle = 0.6; 
	int arr = 899;
	SystemInit();
	/* USART1 config 115200 8-N-1 */
	USART1_Config();
	NVIC_Configuration();
	
	TIM4_Configuration();
	UltrasonicWave_Configuration();
	delay_init();
	RedRayInit();
	

	TIM2_PWM_Init(arr,10);
	TIM3_PWM_Init(arr,10);

	while(1)
	{
	
	  UltrasonicWave_StartMeasure();
	  DelayTime_ms(50);	
		
		SearchRun();
	
		/*if (0==num1)
		{
			//DelayTime_ms(200);
			right(arr*0.2,arr*1);
			if (num2++==0) DelayTime_ms(25000);
			if (ctrl_comm_m2 == 'B')
			{
				num1 = 1;
				//right(arr*0.2,arr*1);
				//DelayTime_ms(10000);
			}
			continue;
		}*/
		
		/*if (ctrl_comm_l == 'W' && ctrl_comm_r == 'B' && ctrl_comm_m1 == 'W' && ctrl_comm_m2 == 'W')
			left(arr*0.8,arr*0.3);
		else if(ctrl_comm_l == 'W' && ctrl_comm_r == 'W' && ctrl_comm_m1 == 'B' && ctrl_comm_m2 == 'W')
			right(arr*0.3,arr*0.8);
		else */if(ctrl_comm_l == 'B' && ctrl_comm_r == 'W' && ctrl_comm_m1 == 'W' && ctrl_comm_m2 == 'W')
			right(arr*0.7,arr*0.35);
		else if(ctrl_comm_l == 'W' && ctrl_comm_r == 'W' && ctrl_comm_m1 == 'W' && ctrl_comm_m2 == 'B')
			left(arr*0.35,arr*0.7);
		else if (ctrl_comm_l == 'B' && ctrl_comm_r == 'B' && ctrl_comm_m1 == 'B' && ctrl_comm_m2 == 'B' )
			back(arr*0.36);
		else if (ctrl_comm_l == 'W' && ctrl_comm_r == 'B' && ctrl_comm_m1 == 'B' && ctrl_comm_m2 == 'W')
			back(arr*0.36);
		else if (ctrl_comm_l == 'W' && ctrl_comm_r == 'W' && ctrl_comm_m1 == 'W' && ctrl_comm_m2 == 'W')
		{
			if (pctrl_comm_l[num%10] == 'W' && pctrl_comm_r[num%10] == 'W' && pctrl_comm_m1[num%10] == 'W' && pctrl_comm_m2[num%10] == 'B')
				left(arr*0.3,arr*0.76);
			else if (pctrl_comm_l[num%10] == 'B' && pctrl_comm_r[num%10] == 'W' && pctrl_comm_m1[num%10] == 'W' && pctrl_comm_m2[num%10] == 'W')
				right(arr*0.76,arr*0.3);
			/*else if (pctrl_comm_l[num%10] == 'W' && pctrl_comm_r[num%10] == 'W' && pctrl_comm_m1[num%10] == 'B' && pctrl_comm_m2[num%10] == 'W')
				right(arr*0.5,arr*0.8);
			else if (pctrl_comm_l[num%10] == 'W' && pctrl_comm_r[num%10] == 'B' && pctrl_comm_m1[num%10] == 'W' && pctrl_comm_m2[num%10] == 'W')
				left(arr*0.8,arr*0.5);*/
			/*else if (pctrl_comm_l[num%10] == 'W' && pctrl_comm_r[num%10] == 'W' && pctrl_comm_m1[num%10] == 'B' && pctrl_comm_m2[num%10] == 'B')
				right(arr*0.2,arr*0.8);
			else if (pctrl_comm_l[num%10] == 'B' && pctrl_comm_r[num%10] == 'B' && pctrl_comm_m1[num%10] == 'W' && pctrl_comm_m2[num%10] == 'W')
				left(arr*0.8,arr*0.2);*/
		}
		else back(arr*0.2);

	}
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

