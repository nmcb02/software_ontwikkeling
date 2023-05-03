/*********************************************************
 * @file: UART_communication.h
 *
 * @brief: This file contains the functions which are used
 * 		   in the source file 'UART_communication.c'.
 *
 * @authors: Skip Wijtman
 * @date: 3-5-2023
 * @version: 1.0 (Updates with every SWD branch)
*********************************************************/

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

//#include <library-header>

//#include "user-header"

//#define-statements

//external vars

//user functies
void UART2_config(void);
void UART_sendChar(uint8_t c);
void UART_sendString(char *string);
uint8_t UART_getChar(void);

#endif /* INC_UART_COMMUNICATION_H_ */
