#include "motor.h"



void forward(int low_level_length )//move forward
{
	 TIM_SetCompare1(TIM3,low_level_length);  //represent how long low_level_length is in a cycle
	 TIM_SetCompare3(TIM3,low_level_length);
	 TIM_SetCompare1(TIM2,low_level_length);
	 TIM_SetCompare3(TIM2,low_level_length);
	 set_zero();
}

void back(int low_level_length)//move back
{
	TIM_SetCompare2(TIM3,low_level_length);
	TIM_SetCompare4(TIM3,low_level_length);
	TIM_SetCompare2(TIM2,low_level_length);
	TIM_SetCompare4(TIM2,low_level_length);
	set_zero_back();
}


void left(int left_front_low_level_length, int right_front_low_level_length)//change the direction need to change the duty cycle
{
	 TIM_SetCompare1(TIM3,left_front_low_level_length);
	 TIM_SetCompare3(TIM3,left_front_low_level_length);
	 TIM_SetCompare1(TIM2,right_front_low_level_length);
	 TIM_SetCompare3(TIM2,right_front_low_level_length);
	 set_zero();
}

void right(int left_front_low_level_length, int right_front_low_level_length)
{
	 TIM_SetCompare1(TIM3,left_front_low_level_length);
	 TIM_SetCompare3(TIM3,left_front_low_level_length);
	 TIM_SetCompare1(TIM2,right_front_low_level_length);
	 TIM_SetCompare3(TIM2,right_front_low_level_length);
	 set_zero();
}

void fleft(int left_front_low_level_length, int right_front_low_level_length)//change the direction need to change the duty cycle
{
	 TIM_SetCompare2(TIM3,left_front_low_level_length);
	 TIM_SetCompare4(TIM3,left_front_low_level_length);
	 TIM_SetCompare2(TIM2,right_front_low_level_length);
	 TIM_SetCompare4(TIM2,right_front_low_level_length);
	 set_zero_back();
}

void fright(int left_front_low_level_length, int right_front_low_level_length)
{
	 TIM_SetCompare2(TIM3,left_front_low_level_length);
	 TIM_SetCompare4(TIM3,left_front_low_level_length);
	 TIM_SetCompare2(TIM2,right_front_low_level_length);
	 TIM_SetCompare4(TIM2,right_front_low_level_length);
	 set_zero_back();
}

void set_zero()//move ,the other four channels set zero
{
	TIM_SetCompare2(TIM3,900);
	TIM_SetCompare4(TIM3,900);
	TIM_SetCompare2(TIM2,900);
	TIM_SetCompare4(TIM2,900);
}
void set_zero_back()//move ,the other four channels set zero
{
	TIM_SetCompare1(TIM3,900);
	TIM_SetCompare3(TIM3,900);
	TIM_SetCompare1(TIM2,900);
	TIM_SetCompare3(TIM2,900);
}


