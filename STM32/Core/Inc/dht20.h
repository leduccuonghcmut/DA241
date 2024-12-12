/*
 * dht20.h
 *
 *  Created on: Oct 31, 2024
 *      Author: Duy
 */

#ifndef INC_DHT20_H_
#define INC_DHT20_H_
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "I2C-LCD.h"
#include "main.h"
#include "dht20.h"
#include "sofware_timer.h"
extern uint16_t value_x10[2];
extern char temp[20],humid[20];
void dht20_init();

void dht20_reset(uint8_t);

void dht20_read(uint16_t*);

void dht20_start();

void dht20_output();

#endif /* INC_DHT20_H_ */
