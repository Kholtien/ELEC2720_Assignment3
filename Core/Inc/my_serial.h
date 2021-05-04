/*
 * my_serial.h
 *
 *  Created on: May 04, 2021
 *      Author: c3267533
 */

#ifndef INC_MY_SERIAL_H_
#define INC_MY_SERIAL_H_

#include <stdio.h>// Added
#include "stm32f4xx_hal.h" //added
#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"


// Set up the buffer sizes
# define TX_BUFFER_SIZE 40
# define RX_BUFFER_SIZE 40
// Set up the level to generate Ctrl S and Ctrl Q for Rx buffer
# define RX_CTRLS_LEVEL RX_BUFFER_SIZE * 0.3
# define RX_CTRLQ_LEVEL RX_BUFFER_SIZE * 0.0

/*
* Define specific error codes for this serial handler
*/
# define INTERRUPT_GEN_ERROR ((0x01U )) // The interrupt generated an error
# define RX_BUFFER_FULL ((0x01U ) << 1) // Rx buffer is full upon receive interrupt
enum BOOL { False , True };
// USART interrupt enable and disable macros
// enable the RX interrupt
# define ENABLE_RXNE_INT (RX_CHANNEL) SET_BIT( (RX_CHANNEL->pstUartHALHandle->Instance->CR1), USART_CR1_RXNEIE )
// enable the TX interrupt
# define ENABLE_TXE_INT ( TX_CHANNEL ) SET_BIT (( TX_CHANNEL -> pstUartHALHandle -> Instance -> CR1 ) ,USART_CR1_TXEIE )
// disable the RX interrupt
# define DISABLE_RXNE_INT ( RX_CHANNEL ) CLEAR_BIT (( RX_CHANNEL -> pstUartHALHandle -> Instance -> CR1 ) , USART_CR1_RXNEIE )
// disable the TX interrupt
# define DISABLE_TXE_INT ( TX_CHANNEL ) CLEAR_BIT (( TX_CHANNEL -> pstUartHALHandle -> Instance -> CR1 ) , USART_CR1_TXEIE )
# define CTRLS 0x13 // The Control S ascii character -- STOP transmission
# define CTRLQ 0x11 // The Control Q ascii character -- START transmission
# define NULL_CHAR '\0' // Used to indicate the end of strings .
# define BLOCKING True // Blocking call to serial routine
# define NON_BLOCKING False // Non - blocking call to serial routine
// Set up the bits used to check for serial transmission errors
// Actually defined in the auto generated HAL code
# define UART_OVERRUN_ERR ((0x01U ) << 3) // The bit that indicates an overrun error .
# define UART_NOISE_ERR ((0x01U ) << 2) // Noise glitch detected error .
# define UART_FRAMING_ERR ((0x01U ) << 1) // Framing error .
# define UART_PARITY_ERR ((0x01U ) << 0) // Parity error




//struct define begin
//typedef struct stRX_SERIAL_CHANNELTypeDef stRX_SERIAL_CHANNELTypeDef;
//typedef struct stTX_SERIAL_CHANNELTypeDef stTX_SERIAL_CHANNELTypeDef;
//typedef struct stSERIAL_CHANNELTypeDef stSERIAL_CHANNELTypeDef;
//struct create begin
typedef struct
{
	UART_HandleTypeDef * pstUartHALHandle ; 	// Pointer to the HAL USART Structure .
	uint16_t uinHead ; 							// The buffer head index .
	uint16_t uinTail ; 							// The buffer tail index .
	uint16_t uinFree ; 							// Number of free buffer locs .
	uint16_t uinUsed ; 							// Number of unused buffer locs .
	uint16_t uinBufSize ; 						// The size of the buffer .
	int8_t chCtrlSCtrlQ ; 						// Set to ctrl S or Q if this should be
												// sent immediately out of the Tx , else a 0
												// This CtrlS /Q is related to the Rx buffer state .
	enum BOOL boHysteresisActive ; 				// True if waiting for CtrlQ threshold .
	uint16_t uinCtrlSThreshold ; 				// The number of free locations where
												// a Ctrl S has been sent .
	uint16_t uinCtrlQThreshold ; 				// The number of free locations when
												// a Ctrl Q should be sent .
	enum BOOL boOverflowErr ; 					// Overflow error flag .
	enum BOOL boParityErr ; 					// Parity error flag .
	int8_t * pchSerialBuffer ; 						// Pointer to the serial buffer
} stRX_SERIAL_CHANNELTypeDef ;


typedef struct
{
	UART_HandleTypeDef * pstUartHALHandle ; 	// Pointer to the HAL USART Structure .
	uint16_t uinHead ; 							// The buffer head index .
	uint16_t uinTail ; 							// The buffer tail index .
	uint16_t uinFree ; 							// Number of free buffer locs .
	uint16_t uinUsed ; 							// Number of unused buffer locs .
	uint16_t uinBufSize ; 						// The size of the buffer .
	enum BOOL boTxUserCtrlS ; 					// True if the user requests stop of Tx.
	int8_t * pchSerialBuffer ; 					// Pointer to the serial buffer
} stTX_SERIAL_CHANNELTypeDef;

typedef struct
{
	stRX_SERIAL_CHANNELTypeDef * pstRxChannel ; // Pointer to the RX data structure
	stTX_SERIAL_CHANNELTypeDef * pstTxChannel ; // Pointer to the TX data structure
	uint8_t uinIRQn ; 							// The interrupt number for the UART
	uint32_t ulSerialErrorFlags ; 				// To store the error flags
	uint32_t ulSerialErrorCodes ; 				// TO store error codes serial channel
} stSERIAL_CHANNELTypeDef;
//struct create end
//struct define end

stSERIAL_CHANNELTypeDef * pstCreateSerialChannel(UART_HandleTypeDef *pstHuart2, uint16_t rx_Buffer_Size, uint16_t tx_Buffer_Size);//done

void fvdEnableSerialChInterupts(stSERIAL_CHANNELTypeDef * pstSERIAL_CHANNEL); //done
char fchGetChar(stSERIAL_CHANNELTypeDef *pstSerialCh, enum BOOL boBlocking);//done
uint8_t fuinPutChar(stSERIAL_CHANNELTypeDef *pstSerialCh, char chChar, enum BOOL boBlocking);//done
void fvdSerialChannelISR(stSERIAL_CHANNELTypeDef * pstSerialCh);//done
void fvdTxInterruptHandler(stSERIAL_CHANNELTypeDef* pstSerialCh);//done


enum BOOL fboPrintStr(stSERIAL_CHANNELTypeDef *pstSerialCh, char *pchString, enum BOOL boBlocking);//done

uint16_t fuinRecievedChars(stSERIAL_CHANNELTypeDef *pstSerialCh);//done

uint16_t fuinGetAllChars(stSERIAL_CHANNELTypeDef *pstSerialCh, char *pchString, uint16_t uinMaxStringSize);

void fvdRxInterruptHandler(stSERIAL_CHANNELTypeDef* pstSerialCh);//TODO

uint16_t fuinGetAllChars(stSERIAL_CHANNELTypeDef *pstSerialCh, char *pchString, uint16_t uinMaxStringSize);//TODO

uint16_t fuinReceivedChars(stSERIAL_CHANNELTypeDef* pstSerialCh);//TODO

enum BOOL fboPrintString(stSERIAL_CHANNELTypeDef *pstSerialCh, char *pchString, enum BOOL boBlocking);//TODO

#endif /* INC_MY_SERIAL_H_ */
