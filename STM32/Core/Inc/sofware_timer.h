/*
 * sofware_timer.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Duy
 */

#ifndef INC_SOFWARE_TIMER_H_
#define INC_SOFWARE_TIMER_H_
#define timer_cycle 10
extern int timer_counter;
extern int timer_flag;
extern int timer_counter_fan;
extern int timer_flag_fan;
void setTimer_fan(int duration);
void timeRun();
void setTimer(int duration);

#endif /* INC_SOFWARE_TIMER_H_ */
