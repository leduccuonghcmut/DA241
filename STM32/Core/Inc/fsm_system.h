/*
 * fsm_system.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Duy
 */
#include "sofware_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "dht20.h"
#include "I2C-LCD.h"
#ifndef INC_FSM_SYSTEM_H_
#define INC_FSM_SYSTEM_H_
#define INIT 1
#define LED_RED 2
#define LED_GREEN 3
#define LED_YELLOW 4
extern int tempInt;
extern int humidInt;
extern int status;
extern int temp1;
void fsm_system();
void init_variables();

#endif /* INC_FSM_SYSTEM_H_ */
