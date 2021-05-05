/*
 * my_main.c
 *
 *  Created on: Apr 27, 2021
 *      Author: c3231308
 */
#include "my_main.h"

stSERIAL_CHANNELTypeDef *pstSerialChannel2;
uint8_t data[] = "Hello Cruel World\n";

void fvdMyMain(UART_HandleTypeDef *pstHuart2)
{
    char chRxChar;

    pstSerialChannel2 = pstCreateSerialChannel(pstHuart2, RX_BUFFER_SIZE, TX_BUFFER_SIZE);

    fvdEnableSerialChInterupts(pstSerialChannel2);
    //while(1) loop
    while(1){
        //region Figure 3 from Document
        //Read ISR and CR1
        chRxChar = fchGetChar(pstSerialChannel2, NON_BLOCKING);

        if((uint8_t)chRxChar != 255){
            fuinPutChar(pstSerialChannel2, chRxChar, BLOCKING);
        }
//    HAL_Delay(250);
//    HAL_GPIO_TogglePin(GPIOD, GREEN_LED);
    }

}
