/*
 * sofware_timer.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Duy
 */
#include "sofware_timer.h"

#define timer_cycle 10

int timer_counter=0;
int timer_flag=0;

void setTimer(int duration)
{
	timer_counter = duration/timer_cycle;
	timer_flag = 0;
}

void timeRun()
{
	if(timer_counter > 0){
		timer_counter--;
		if(timer_counter <= 0){
			timer_flag = 1;
		}
	}
}
