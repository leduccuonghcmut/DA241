#include "sofware_timer.h"

#define timer_cycle 10

int timer_counter=0;
int timer_flag=0;
int timer_counter_fan=0;
int timer_flag_fan=0;
void setTimer(int duration)
{
	timer_counter = duration/timer_cycle;
	timer_flag = 0;
}
void setTimer_fan(int duration)
{
	timer_counter_fan = duration/timer_cycle;
	timer_flag_fan = 0;
}
void timeRun()
{
	if(timer_counter > 0){
		timer_counter--;
		if(timer_counter <= 0){
			timer_flag = 1;
		}
	}
	if(timer_counter_fan > 0){
		timer_counter_fan--;
		if(timer_counter_fan <= 0){
			timer_flag_fan = 1;
		}
	}
}
