/*********************************************************
 * @file: UART_communication.h
 *
 * @brief: This file contains the functions which are used
 * 		   in the source file 'UART_communication.c'.
 *
 * @authors: Skip Wijtman
 * @date: 3-5-2023
 * @version: 1.1 (Updates with every SWD branch)
*********************************************************/

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

//#include <library-header>
#include <stdio.h>
#include <string.h>

//#include other "user-header"


//struct definition
typedef struct UART_Communication
{
	uint8_t receive[100];
	uint8_t buffer[100];	// misschien de receive functie als struct maken zodatde functie de data van de struct meteen kan mee geven en dus de gehele array met het ingelezen bericht.
}UART, *PUART;

//#define-statements


//external vars


//user functies
void UART2_config(void);
void UART_sendChar(uint8_t c);
void UART_sendString(char *string);
uint8_t UART_getChar(void);
UART UART_receiver(void);

#endif /* INC_UART_COMMUNICATION_H_ */
