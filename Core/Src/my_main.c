/*
 * my_main.c
 *
 *  Created on: Apr 27, 2021
 *      Author: c3231308
 */

#include "my_main.h"
#include "main.h"
#include <stdio.h>// Added
#include <stdlib.h>








//function defines begin
//stRX_SERIAL_CHANNELTypeDef * pstCreatestRX_SERIAL_CHANNELTypeDef(UART_HandleTypeDef* pstHuart2,uint16_t rx_Buffer_Size)
//{
//	stRX_SERIAL_CHANNELTypeDef * rx_channel;
//	int8_t * pchSerialBuffer = malloc(rx_Buffer_Size);
//
//	for(int i = 0; i <= rx_Buffer_Size; i++){
//		pchSerialBuffer[i] = 0;
//	}
//
//	rx_channel->pstUartHALHandle   = pstHuart2;
//	rx_channel->uinHead            = 0;
//	rx_channel->uinTail            = 0;
//	rx_channel->uinFree            = rx_Buffer_Size;
//	rx_channel->uinUsed            = 0;
//	rx_channel->uinBufSize         = rx_Buffer_Size;
//	rx_channel->chCtrlSCtrlQ       = 0;
//	rx_channel->boHysteresisActive = False;
//	rx_channel->uinCtrlSThreshold  = 0;
//	rx_channel->uinCtrlQThreshold  = 0;
//	rx_channel->boOverflowErr      = 0;
//	rx_channel->boParityErr        = 0;
//	rx_channel->pchSerialBuffer    = pchSerialBuffer;
//
//	return rx_channel;
//}

//stTX_SERIAL_CHANNELTypeDef * pstCreatestTX_SERIAL_CHANNELTypeDef(UART_HandleTypeDef *pstHuart2, uint16_t tx_Buffer_Size)
//{
//	stTX_SERIAL_CHANNELTypeDef * tx_channel;
//	int8_t *pchSerialBuffer = malloc(tx_Buffer_Size);
//	for(int i = 0; i <= tx_Buffer_Size; i++){
//		pchSerialBuffer[i] = 0;
//	}
//
//	tx_channel->pstUartHALHandle 	= pstHuart2;
//	tx_channel->uinHead 			= 0;
//	tx_channel->uinTail 			= 0;
//	tx_channel->uinFree 			= tx_Buffer_Size;
//	tx_channel->uinUsed 			= 0;
//	tx_channel->uinBufSize 			= tx_Buffer_Size;
//	tx_channel->boTxUserCtrlS 		= False;
//	tx_channel->pchSerialBuffer 	= pchSerialBuffer;
//
//	return tx_channel;
//}


stSERIAL_CHANNELTypeDef * pstCreateSerialChannel(UART_HandleTypeDef *pstHuart2, uint16_t rx_Buffer_Size, uint16_t tx_Buffer_Size)
{
	stSERIAL_CHANNELTypeDef serial_channel;
	stSERIAL_CHANNELTypeDef *pserial_channel = &serial_channel;
//	stRX_SERIAL_CHANNELTypeDef * rx_channel;
//	stTX_SERIAL_CHANNELTypeDef * tx_channel;


	stRX_SERIAL_CHANNELTypeDef rx_channel; //Create RX Serial Channel
	stTX_SERIAL_CHANNELTypeDef tx_channel; //Create TX Serial Channel
	int8_t * pchSerialBufferRX = malloc(rx_Buffer_Size);
	int8_t * pchSerialBufferTX = malloc(tx_Buffer_Size);

	for(int i = 0; i <= rx_Buffer_Size; i++){
		pchSerialBufferRX[i] = 0;
	}
	for(int i = 0; i <= tx_Buffer_Size; i++){
		pchSerialBufferTX[i] = 0;
	}

	//initialize rx channel
	rx_channel.uinHead            = 0;
	rx_channel.uinTail            = 0;
	rx_channel.uinFree            = rx_Buffer_Size;
	rx_channel.uinUsed            = 0;
	rx_channel.uinBufSize         = rx_Buffer_Size;
	rx_channel.chCtrlSCtrlQ       = 0;
	rx_channel.boHysteresisActive = False;
	rx_channel.uinCtrlSThreshold  = 0;
	rx_channel.uinCtrlQThreshold  = 0;
	rx_channel.boOverflowErr      = 0;
	rx_channel.boParityErr        = 0;
	rx_channel.pchSerialBuffer    = pchSerialBufferRX;
	rx_channel.pstUartHALHandle   = pstHuart2;



	//initialize tx channel
	tx_channel.uinHead 		    = 0;
	tx_channel.uinTail 		    = 0;
	tx_channel.uinFree 		    = tx_Buffer_Size;
	tx_channel.uinUsed 		    = 0;
	tx_channel.uinBufSize 		    = tx_Buffer_Size;
	tx_channel.boTxUserCtrlS 	    = False;
	tx_channel.pchSerialBuffer     = pchSerialBufferTX;
	tx_channel.pstUartHALHandle    = pstHuart2;

//	rx_channel = pstCreatestRX_SERIAL_CHANNELTypeDef(&pstHuart2, rx_Buffer_Size);
//	tx_channel = pstCreatestTX_SERIAL_CHANNELTypeDef(&pstHuart2, tx_Buffer_Size);

	serial_channel.pstRxChannel         = &rx_channel;
	serial_channel.pstTxChannel         = &tx_channel;
	serial_channel.uinIRQn              = 0;
	serial_channel.ulSerialErrorFlags   = 0;
	serial_channel.ulSerialErrorCodes   = 0;

	return pserial_channel;

}
//function defines end


void fvdEnableSerialChInterupts(stSERIAL_CHANNELTypeDef * pstSERIAL_CHANNEL)
{
	//Enable Rx Not Empty Interrupt
//	ENABLE_RXNE_INT(pstSERIAL_CHANNEL->pstRxChannel);
	SET_BIT( (pstSERIAL_CHANNEL->pstRxChannel->pstUartHALHandle->Instance->CR1), USART_CR1_RXNEIE );
	// Enable TX empty interrupt
	// SET_BIT ( pstSerialCh -> pstTxChannel - > pstUartHALHandle -> Instance - >CR1 , USART_CR1_TXEIE );
	// ENABLE_TXE_INT ( pstSerialCh -> pstTxChannel -> pstUartHALHandle -> Instance -> CR1);
	// Globally enable interrupts for this USART
	HAL_NVIC_EnableIRQ ( pstSERIAL_CHANNEL -> uinIRQn );

}

char fchGetChar(stSERIAL_CHANNELTypeDef *pstSerialCh, enum BOOL boBlocking)
{
	char tempChar;

	if(!boBlocking){
		if(pstSerialCh->pstRxChannel->uinUsed == 0){
			return 0xff;
		}
	}

	while(pstSerialCh->pstRxChannel->uinUsed == 0){
		;
	}

	//critical section
	HAL_NVIC_DisableIRQ(pstSerialCh->uinIRQn);

	tempChar = pstSerialCh->pstRxChannel->pchSerialBuffer[pstSerialCh->pstRxChannel->uinTail];
	pstSerialCh->pstRxChannel->uinTail ++;


}

void fvdSerialChannelISR(stSERIAL_CHANNELTypeDef * pstSerialCh)
{
	//read ISR and CR1
	uint32_t srFlags = READ_REG(pstSerialCh->pstRxChannel->pstUartHALHandle->Instance->SR);
	uint32_t cr1its = READ_REG(pstSerialCh->pstRxChannel->pstUartHALHandle->Instance->CR1);
	uint32_t errorflags = 0x00U;
	enum BOOL boInterrruptOccurred = False;


	errorflags = (srFlags & (uint32_t)(USART_SR_PE | USART_SR_FE | USART_SR_ORE | USART_SR_NE));

	//Has a comm error occured?
	//if no
	if (errorflags == 0U)
	{
		//Check Rx Int Enabled and Rx Int?
			//if yes
				//call Rx Int Handler function
	    if (((srFlags & USART_SR_RXNE) != 0U) && ((cr1its & USART_CR1_RXNEIE) != 0U)){
			fvdRxInterruptHandler(pstSerialCh);
			boInterrruptOccurred = True;
	    }
		//Check Tx Int Enabled and Tx Int
	    if (((srFlags & USART_SR_TXE) != 0U) && ((cr1its & USART_CR1_TXEIE) != 0U))
	    {
	    	//if yes
	    	//call Tx Int Handler
	    	fvdTxInterrupthanler(pstSerialCh);
	    	boInterrruptOccurred = True;
//	      UART_Transmit_IT(huart);
	      return;
	    }
	    //if no
	    	//save the error flags for later handling
	    pstSerialCh->ulSerialErrorFlags = errorflags;

	//has an interrupt occured

	    if(!boInterrruptOccurred){
	    	//if no
	    	pstSerialCh->ulSerialErrorCodes |= INTERRUPT_GEN_ERROR;
	    	HAL_NVIC_ClearPendingIRQ(pstSerialCh->uinIRQn);
	    }


						//set error flag clear pending uart interrupt
			//if yes

		//return
	}
	//if yes
		//save the error flags later for handling
	pstSerialCh->ulSerialErrorFlags = errorflags;



}



//stSERIAL_CHANNELTypeDef *pstSerialChannel2;


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
