/*
 * fsm_system.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Duy
 */

#include "fsm_system.h"

int status=0;
int tempInt;    // Biến toàn cục không khởi tạo
int humidInt;

void init_variables() {
    tempInt = atoi(temp);  // Khởi tạo giá trị trong hàm
    humidInt = atoi(humid);
}


void fsm_system() {
    switch (status) {
        case INIT:
            status = LED_RED;
            break;

        case LED_RED:
            if (timer_flag == 1) {
                if ((0 < tempInt && tempInt < 10) || (0 < humidInt && humidInt < 40)) {
                    status = LED_YELLOW;
                    setTimer(200);
                } else if ((10 < tempInt && tempInt < 30) || (40 < humidInt && humidInt < 80)) {
                    status = LED_GREEN;
                    setTimer(200);
                }
                // LED_RED sáng
            }
            break;

        case LED_YELLOW:
            if (timer_flag == 1) {
                if (tempInt >= 30 || humidInt >= 70) {
                    status = LED_RED;
                    setTimer(200);
                } else if ((10 < tempInt && tempInt < 30) || (40 < humidInt && humidInt < 80)) {
                    status = LED_GREEN;
                    setTimer(200);
                }
                // LED_YELLOW sáng
            }
            break;

        case LED_GREEN:
            if (timer_flag == 1) {
                if ((0 < tempInt && tempInt < 10) || (0 < humidInt && humidInt < 40)) {
                    status = LED_YELLOW;
                    setTimer(200);
                } else if ((10 < tempInt && tempInt < 30) || (40 < humidInt && humidInt < 80)) {
                    status = LED_GREEN;
                    setTimer(200);
                }
                // LED_GREEN sáng
            }
            break;
    }
}
