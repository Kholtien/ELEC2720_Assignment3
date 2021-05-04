/*
 * my_main.c
 *
 *  Created on: Apr 27, 2021
 *      Author: c3231308
 */
#include "my_main.h"


void fvdMyMain(UART_HandleTypeDef *pstHuart2)
{
    char chRxChar;
    stSERIAL_CHANNELTypeDef *pstSerialChannel2;
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

    }

}
