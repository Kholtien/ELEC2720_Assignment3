/*
 * my_main.h
 *
 *  Created on: Apr 27, 2021
 *      Author: c3231308
 */

#ifndef INC_MY_MAIN_H_
#define INC_MY_MAIN_H_

#include "main.h"
#include "my_serial.h"

#define GREEN_LED   LD4_Pin
#define ORANGE_LED 	LD3_Pin
#define RED_LED     LD5_Pin
#define BLUE_LED    LD6_Pin

//void fvdWrapBuffer()

void fvdMyMain(UART_HandleTypeDef *pstHuart2);

#endif /* INC_MY_MAIN_H_ */
