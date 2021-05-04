/*
 * my_serial.c
 *
 *  Created on: May 04, 2021
 *      Author: c3267533
 */


#include "my_main.h"
#include "main.h"
#include <stdio.h>// Added
#include <string.h>
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
	int8_t * pinRxBufTemp;
	int8_t * pinTxBufTemp;
//	stSERIAL_CHANNELTypeDef serial_channel;
	stSERIAL_CHANNELTypeDef *pserial_channel;// = &serial_channel;
//	stRX_SERIAL_CHANNELTypeDef * rx_channel;
//	stTX_SERIAL_CHANNELTypeDef * tx_channel;


	stRX_SERIAL_CHANNELTypeDef* rx_channel; //Create RX Serial Channel
	stTX_SERIAL_CHANNELTypeDef* tx_channel; //Create TX Serial Channel

	//Rx
	//Allocate buffers with size of appropriate buffer size
	pinRxBufTemp = (int8_t *)calloc(rx_Buffer_Size, sizeof(uint8_t));
	if(pinRxBufTemp == NULL){
		//Not enough Memory
		return (stSERIAL_CHANNELTypeDef * ) pinRxBufTemp;
	}

	//Tx
	//Allocate buffers with size of appropriate buffer size
	pinTxBufTemp = (int8_t *)calloc(tx_Buffer_Size, sizeof(uint8_t));
	if(pinTxBufTemp == NULL){
		//Not enough Memory
		return (stSERIAL_CHANNELTypeDef * ) pinTxBufTemp;
	}
	//Buffers have now been allocated

	//Allocate storage for main structures

	//Rx
	rx_channel = (stRX_SERIAL_CHANNELTypeDef*)calloc(1,sizeof(stRX_SERIAL_CHANNELTypeDef));
	if(rx_channel == NULL){
		return (stSERIAL_CHANNELTypeDef *) rx_channel;
	}

	//Tx
	tx_channel = (stTX_SERIAL_CHANNELTypeDef*)calloc(1,sizeof(stTX_SERIAL_CHANNELTypeDef));
	if(tx_channel == NULL){
		return (stSERIAL_CHANNELTypeDef *) rx_channel;
	}

	//initialize rx channel
	rx_channel->uinHead            = 0;
	rx_channel->uinTail            = 0;
	rx_channel->uinFree            = rx_Buffer_Size;
	rx_channel->uinUsed            = 0;
	rx_channel->uinBufSize         = rx_Buffer_Size;
	rx_channel->chCtrlSCtrlQ       = 0;
	rx_channel->boHysteresisActive = False;
	rx_channel->uinCtrlSThreshold  = RX_CTRLS_LEVEL;
	rx_channel->uinCtrlQThreshold  = RX_CTRLQ_LEVEL;
	rx_channel->boOverflowErr      = False;
	rx_channel->boParityErr        = False;
	rx_channel->pchSerialBuffer    = pinRxBufTemp;
	rx_channel->pstUartHALHandle   = pstHuart2;



	//initialize tx channel
	tx_channel->uinHead 		    = 0;
	tx_channel->uinTail 		    = 0;
	tx_channel->uinFree 		    = tx_Buffer_Size;
	tx_channel->uinUsed 		    = 0;
	tx_channel->uinBufSize 		    = tx_Buffer_Size;
	tx_channel->boTxUserCtrlS 	    = False;
	tx_channel->pchSerialBuffer     = pinTxBufTemp;
	tx_channel->pstUartHALHandle    = pstHuart2;


	//Allocate for actual serial channel structure
	pserial_channel = (stSERIAL_CHANNELTypeDef *)calloc(1, sizeof(stSERIAL_CHANNELTypeDef));
	if(pserial_channel == NULL){
		//Not enough Memory
		return pserial_channel;
	}

	pserial_channel->pstRxChannel         = rx_channel;
	pserial_channel->pstTxChannel         = tx_channel;
	pserial_channel->uinIRQn              = USART2_IRQn;
	pserial_channel->ulSerialErrorFlags   = 0U;
	pserial_channel->ulSerialErrorCodes   = 0U;

	//Turn on Red LED to indicate Rx Buffer overflow
	HAL_GPIO_WritePin(GPIOD, RED_LED, GPIO_PIN_RESET);

	//Turn on Orange LED to indicate Tx Buffer overflow
	HAL_GPIO_WritePin(GPIOD, ORANGE_LED, GPIO_PIN_RESET);


	return pserial_channel;

}
//function defines end

/*
* void fvdEnableSerialChInterrupts ( stSERIAL_CHANNELTypeDef * pstSerialCh )
* --------------------------------------------------------
*
* This function enables all of the interrupts for a serial
* channel -- i.e. it enables RX and TX for the particular
* interrupt , and globally enables interrupts in the NVIC .
*/

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

	//if is non blocking
	if(!boBlocking){
		//if rx used == 0
		if(pstSerialCh->pstRxChannel->uinUsed == 0){
			return 0xff;
		}
	}

	//while rx used == 0, do nothing and repeat until something is there
	while(pstSerialCh->pstRxChannel->uinUsed == 0){
		;
	}

	//critical section
	HAL_NVIC_DisableIRQ(pstSerialCh->uinIRQn);

	//grab the char from Rx Buffer Tail and put into a temp char
	tempChar = pstSerialCh->pstRxChannel->pchSerialBuffer[pstSerialCh->pstRxChannel->uinTail];
	//wrap Rx Buffer if needed tail+1 % bufsize is 0 when bufsize and tail + 1 are equal otherwise just tail+1
	pstSerialCh->pstRxChannel->uinTail = (pstSerialCh->pstRxChannel->uinTail + 1) % (pstSerialCh->pstRxChannel->uinBufSize);

	pstSerialCh->pstRxChannel->uinFree++;
	pstSerialCh->pstRxChannel->uinUsed++;

	//is hysteresis active and Rx Used <= Ctrl Q treshold?
	if(pstSerialCh->pstRxChannel->boHysteresisActive && (pstSerialCh->pstRxChannel->uinUsed) <= pstSerialCh->pstRxChannel->uinCtrlQThreshold){
		//CtrlS/Q loc = CTRLQ
		pstSerialCh->pstRxChannel->chCtrlSCtrlQ = CTRLQ;

		//Hysteresis Active = false
		pstSerialCh->pstRxChannel->boHysteresisActive = False;

		//Enable Tx Interrupts
		SET_BIT (( pstSerialCh->pstTxChannel -> pstUartHALHandle -> Instance -> CR1 ) ,USART_CR1_TXEIE );
	}

	HAL_NVIC_EnableIRQ(pstSerialCh->uinIRQn);

	return tempChar;
}

uint8_t fuinPutChar(stSERIAL_CHANNELTypeDef *pstSerialCh, char chChar, enum BOOL boBlocking)
{
	uint8_t uinFreeLoc;

	uinFreeLoc = pstSerialCh->pstTxChannel->uinFree;

	//is TxBuff.free == 0 and Blocking == false?
	if(uinFreeLoc == 0 && !boBlocking){
		//if yes
		return uinFreeLoc;
	}

	//else


	//is TxBuf.free == 0
	while(pstSerialCh->pstTxChannel->uinFree == 0){
		;//then do nothing
	}

	//txBuf.free not 0


	//START CRITICAL SECTION

	//disable NVIC UART Interrupts
	HAL_NVIC_DisableIRQ(pstSerialCh->uinIRQn);


	//TxBuf[head] = Char;
	pstSerialCh->pstTxChannel->pchSerialBuffer[pstSerialCh->pstTxChannel->uinHead] = chChar;

	//head++
	//check for wrap
	pstSerialCh->pstTxChannel->uinHead = (pstSerialCh->pstTxChannel->uinHead + 1) % (pstSerialCh->pstTxChannel->uinBufSize);

	//used++
	pstSerialCh->pstTxChannel->uinUsed++;
	//free--
	pstSerialCh->pstTxChannel->uinFree--;

	//is user CtrlS == True?
	if(!(pstSerialCh->pstTxChannel->boTxUserCtrlS)){
		//Enable Tx int
		pstSerialCh->pstTxChannel->pstUartHALHandle->Instance->CR1  |= ((0x1UL << (7U)));
	}

	HAL_NVIC_EnableIRQ(pstSerialCh->uinIRQn);


	return uinFreeLoc;
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
//			fvdRxInterruptHandler(pstSerialCh); //use this
			boInterrruptOccurred = True;
	    }
		//Check Tx Int Enabled and Tx Int
	    if (((srFlags & USART_SR_TXE) != 0U) && ((cr1its & USART_CR1_TXEIE) != 0U))
	    {
	    	//if yes
	    	//call Tx Int Handler
//	    	fvdTxInterrupthanler(pstSerialCh); //use this
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

void fvdTxInterruptHandler(stSERIAL_CHANNELTypeDef* pstSerialCh)
{
	//entry

	//send Ctrl S or Q?
	if((pstSerialCh->pstRxChannel->chCtrlSCtrlQ == CTRLS) || (pstSerialCh->pstRxChannel->chCtrlSCtrlQ == CTRLQ)){
		//if yes
			//txDR = CTRL S or CTRL Q
		pstSerialCh->pstTxChannel->pstUartHALHandle->Instance->DR = pstSerialCh->pstRxChannel->chCtrlSCtrlQ;

		//RESET CTRLS/Q loc = 0

		//ORANGE LED on for CTRLS and Off for CTRLQ
		if(pstSerialCh->pstRxChannel->chCtrlSCtrlQ == CTRLS){
			HAL_GPIO_WritePin(GPIOD, ORANGE_LED, GPIO_PIN_SET);
		}
		else if(pstSerialCh->pstRxChannel->chCtrlSCtrlQ == CTRLQ){
			HAL_GPIO_WritePin(GPIOD, ORANGE_LED, GPIO_PIN_RESET);
		}

		pstSerialCh->pstRxChannel->chCtrlSCtrlQ = 0;

		//return
		return;
	}
	//if no
		//is TxBuf Used == 0?
	if(pstSerialCh->pstTxChannel->uinUsed == 0){
			//if yes
				//disable Tx Int
//		DISABLE_TXE_INT(pstSerialCh->pstTxChannel);
		CLEAR_BIT (( pstSerialCh->pstTxChannel -> pstUartHALHandle -> Instance -> CR1 ) , USART_CR1_TXEIE );
		return;
	}
			//if no
				//is User CTRLS flag == true?
	if(pstSerialCh->pstTxChannel->boTxUserCtrlS){
					//if yes
						//disable Tx Int
		CLEAR_BIT (( pstSerialCh->pstTxChannel -> pstUartHALHandle -> Instance -> CR1 ) , USART_CR1_TXEIE );
		return;
	}
					//if no
						//TXDR <-- TBuf[tail];
	pstSerialCh->pstTxChannel->pstUartHALHandle->Instance->DR = (uint8_t)((pstSerialCh->pstTxChannel->pchSerialBuffer[pstSerialCh->pstTxChannel->uinTail]) & 0x7FU);
						//tail++
						//check for wrap
	pstSerialCh->pstTxChannel->uinTail = (pstSerialCh->pstTxChannel->uinTail + 1) % (pstSerialCh->pstTxChannel->uinBufSize);
						//free++
	pstSerialCh->pstTxChannel->uinFree++;
						//used--
	pstSerialCh->pstTxChannel->uinUsed--;
						//return
	return;
}

//returns true if successful and false if failed
enum BOOL fboPrintStr(stSERIAL_CHANNELTypeDef *pstSerialCh, char *pchString, enum BOOL boBlocking)
{
	uint16_t uinStringIndex = 0;

	//if non blocking
	if(boBlocking == NON_BLOCKING){
		//if the length of the string is less than or equal to the number of free space in the Tx Channel
		if(strlen(pchString) <= pstSerialCh->pstTxChannel->uinFree){
			while(pchString[uinStringIndex] != '\0'){
				fuinPutChar(pstSerialCh, pchString[uinStringIndex], NON_BLOCKING);
				uinStringIndex++;
			}
			return True;
		}
		else {
			return False;
		}
	}
	//if non Blocking
	else{
		return False;
	}
}

//returns the number of characters in the receive buffer
uint16_t fuinRecievedChars(stSERIAL_CHANNELTypeDef *pstSerialCh)
{
	return pstSerialCh->pstRxChannel->uinUsed;
}

//Returns the length of the string
uint16_t fuinGetAllChars(stSERIAL_CHANNELTypeDef *pstSerialCh, char *pchString, uint16_t uinMaxStringSize)
{
	uint16_t uinStringIndex = 0;

	while (uinStringIndex < uinMaxStringSize){
		pchString[uinStringIndex] = fchGetChar(pstSerialCh, NON_BLOCKING);
		if(pchString[uinStringIndex] == 255){
			pchString[uinStringIndex] = '\0';
			return uinStringIndex;
		}
		uinStringIndex++;
	}

	pchString[uinStringIndex] = '\0';

	return uinStringIndex;
}
//stSERIAL_CHANNELTypeDef *pstSerialChannel2;
