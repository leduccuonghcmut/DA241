#include "fsm_system.h"

int status=INIT;
int status_fan=0;
int tempInt;
int humidInt;
int temp1=0;
void init_variables() {
	tempInt=atoi(temp);
	humidInt=atoi(humid);

}
TIM_HandleTypeDef htim1;
void fsm_system() {
    switch (status) {
        case INIT:
        	dht20_output();
            status = LED_YELLOW;
            break;

        case LED_RED:
            if (timer_flag == 1) {
            	dht20_output();
                if (0 < tempInt && tempInt < 27) {
                    status = LED_GREEN;
                } else if (27 <= tempInt && tempInt < 28) {
                    status = LED_YELLOW;
                }
                // LED_RED sáng
        		if(timer_flag_fan==1)
        		{
       		     __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,999);
       		     HAL_Delay(2);
        		}
                HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, SET);
                HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, SET);
                setTimer(500);
            }
            break;

        case LED_GREEN:
            if (timer_flag == 1) {
            	dht20_output();
                if (tempInt >= 28) {
                    status = LED_RED;
                } else if (27 <= tempInt && tempInt < 28) {
                    status = LED_YELLOW;
                }
        		if(timer_flag_fan==1)
        		{
       		     __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
       		     HAL_Delay(2);
        		}
                HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, SET);
                HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, RESET);
                setTimer(500);
            }
            break;

        case LED_YELLOW:
            if (timer_flag == 1) {
            	dht20_output();
                if (0 < tempInt && tempInt < 27) {
                    status = LED_GREEN;
                } else if (tempInt >= 28) {
                    status = LED_RED;
                }
        		if(timer_flag_fan==1)
        		{
       		     __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,499);
       		     HAL_Delay(2);
        		}
                HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, RESET);
                HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, SET);
                setTimer(500);

            }
            break;
        default:
        	break;
    }
}

