/*********************************************************
 * @file: UART_communication.c
 *
 * @brief: In this file UART is used to make communication
 * 	       possible between the STM32F4 board and a computer.
 * 	       With this code messages can be received and sent.
 * 	       This code is made with the assistance of an online
 * 	       guide from 'Controllerstech'.
 *
 * @authors: Skip Wijtman
 * @date: 3-5-2023
 * @version: 1.0 (Updates with every SWD branch)
*********************************************************/

//#include <library-header>

//#include "user-header"
#include "main.h"

//#define-statements

//external vars

//global vars

//user functies
void UART2_config(void);
void UART_sendChar(uint8_t c);
void UART_sendString(char *string);
uint8_t UART_getChar(void);

/*******************************************************
 * Function: UART2_config
 *
 * @brief: Function to enable all the necessary registers
 * 		   and operations to use UART.
 *
 * @param: Nothing
 *
 * @return: Nothing
*******************************************************/
void UART2_config(void)
{
	// 1. Clock enable
	RCC->APB1ENR |= (1<<17);	// Enables the UART2 clock
	RCC->AHB1ENR |= (1<<0);		// Enables the GPIOA clock

	// 2. Configure pins for UART
	GPIOA->MODER |=(2<<4);		// ALT function for pin PA2 enabled
	GPIOA->MODER |=(2<<6);		// ALT function for pin PA3 enabled
	GPIOA->OSPEEDR |= (3<<4);	// Setting pin PA2 on 'high speed' function
	GPIOA->OSPEEDR |= (3<<6);	// Setting pin PA3 on 'high speed' function
	GPIOA->AFR[0] |= (7<<8); 	// AFR[0] is for the enabling pins 0 to 7 and [1] is for pins 8 to 15. Here the pin PA2 is enabled as UART2 ALT function
	GPIOA->AFR[0] |= (7<<12);	// Pin PA2 is enabled as UART2 ALT function

	// 3. Enabling UART
	USART2->CR1 = 0;			// Resetting the register
	USART2->CR1 |= (1<<13);		// UE bit in register set to '1'

	// 4. Setting the word length
	USART2->CR1 |= (0<<12); 	// Setting the 12th bit to '0' for word length of 8 bits


	// 5. selecting BAUD rate for UART
	// The formula is as followed: BAUD = fck/(8*(2-OVER8)*USARTDIV)
	// OVER8 is for the oversampling, which is not used. So to calculate the BAUD, the peripheral clock frequency is divided by 16 times the USARTDIV
	// The USARTDIV is a number which can be coded in the BRR register.
	// So if a BAUD of 115200 is chosen it means the calculation is as followed: fck/(8*2*115200)=USARTDIV
	// So for the necessary value: 42000000/(8*2*115200)=22,7864583333 Refer to the manual for the Mantissa and Fraction values.
	// Mantissa = 22,7864583333=22=0x16		Fraction = 0,7864583333*16 = 12,5833=12=0xC		USARTDIV=0x16C

	USART2->BRR = 0x16C;		// Calculated value

	// 6. Enabling Tx and Rx
	USART2->CR1 |= (1<<3);		// Enables Tx for UART
	USART2->CR1 |= (1<<2);		// Enables Rx for UART
}

/*******************************************************
 * Function: UART_sendChar
 *
 * @brief: Function that sends char data to the connected terminal
 *
 * @param: Char data do be send
 *
 * @return: Nothing
*******************************************************/
void UART_sendChar(uint8_t c)
{
	while(!(USART2->SR & (1<<7)));		// Waits for the TXE bit to be low so that the previous, to be send, data is shifted into transmit register. When this is done new data can be send

	USART2->DR = c;						// Data to be send is written to a register which transmits to the connected UART terminal
}

/*******************************************************
 * Function: UART_sendString
 *
 * @brief: Function that sends a string to the connected terminal
 *
 * @param: String do be send
 *
 * @return: Nothing
*******************************************************/
void UART_sendString(char *string)
{
	while (*string) UART_sendChar(*string++);	// Loop the string letter after letter to send the whole to the terminal
}

/*******************************************************
 * Function: UART_getChar
 *
 * @brief: Function that receives data from the connected terminal
 *
 * @param: Nothing
 *
 * @return: Received data
*******************************************************/
uint8_t UART_getChar(void)
{
	uint8_t temp;

	while (!(USART2->SR & (1<<5)));  // wait for RXNE bit to set, this indicates that something was received via UART
	temp = USART2->DR;  // Read the data. This clears the RXNE also
	return temp;
}
