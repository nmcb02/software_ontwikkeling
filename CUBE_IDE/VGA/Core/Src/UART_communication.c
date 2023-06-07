/*******************************************************//**
 * @file	UART_communication.c
 *
 * @brief	In this file UART is used to make communication
 * 	       	possible between the STM32F4 board and a computer.
 * 	       	With this code messages can be received and sent.
 * 	       	This code is made with the assistance of an online
 * 	       	guide from 'Controllerstech'.
 *
 * @authors	Skip Wijtman
 * @date	3-5-2023
 * @version	1.3
*********************************************************/

//#include "user-header"
#include "UART_communication.h"

//struct declaration


//global vars


/*****************************************************//**
 * @brief	Function to enable all the necessary registers
 * 		   	and operations to use UART.
 *
 * @param	Nothing
 *
 * @return	Nothing
*******************************************************/
void UART2_config(void)
{
	// 1. Clock enable
	RCC->APB1ENR |= (1<<17);	// Enables the UART2 clock
	RCC->AHB1ENR |= (1<<0);		// Enables the GPIOA clock

	// 2. Configure pins for UART
	GPIOA->MODER |= (2<<4);		// ALT function for pin PA2 enabled
	GPIOA->MODER |= (2<<6);		// ALT function for pin PA3 enabled
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

/*****************************************************//**
 * @brief	Function that sends char data to the connected terminal
 *
 * @param	Char data do be send
 *
 * @return	Nothing
*******************************************************/
void UART_sendChar(uint8_t c)
{
	while(!(USART2->SR & (1<<7)));		// Waits for the TXE bit to be low so that the previous, to be send, data is shifted into transmit register. When this is done new data can be send

	USART2->DR = c;						// Data to be send is written to a register which transmits to the connected UART terminal
}

/*****************************************************//**
 * @brief	Function that sends a string to the connected terminal
 *
 * @param	String do be send
 *
 * @return	Nothing
*******************************************************/
void UART_sendString(char *string)
{
	while (*string) UART_sendChar(*string++);	// Loop the string letter after letter to send the whole to the terminal
}

/*****************************************************//**
 * @brief	Function that receives data from the connected terminal
 *
 * @param	Nothing
 *
 * @return	Received data
*******************************************************/
uint8_t UART_getChar(void)
{
	uint8_t temp = NO_DATA;
	unsigned int i = 0;

	while(!(USART2->SR & (1<<5)))		// wait for RXNE bit to set, this indicates that something was received via UART
		{
			if(i==WAIT_FOR_DATA)
			{
				i = 0;
				temp = NO_DATA;
				return temp;
			}
			i++;
		}
	temp = USART2->DR;  // Read the data. This clears the RXNE also
	return temp;
}

/*****************************************************//**
 * @brief	Function that read a single line and stores the data
 *
 * @param	Nothing
 *
 * @return	struct variable
*******************************************************/
UART UART_receiver(void)
{
	UART data;
	uint8_t temp=0;
	uint8_t i = 0;

	for(unsigned char j = 0; j < STORAGE; j++)		// Empties the array
		data.receive[j] = 0;

	while(1)
	{
		temp = UART_getChar();

		 if(temp == '\r' || temp == ' ')	// Skip CR and space ASCII symbols
			 continue;

		 if(temp == '\n' || temp == NO_DATA)		// When a LN is found stop the data receiving
		 {
			 if(temp == '\n')
				 data.receive[i] = temp;

			 i = 0;
			 break;
		 }

		 data.receive[i] = temp;	// Stores received data in array
		 i++;
	}
	return data;
}

/*****************************************************//**
 * @brief	Function that handles the occuring errors to the terminal
 *
 * @param	err error that is supposed to be shown
 *
 * @return	nothing
*******************************************************/
void UART_errorHandling(int err)
{
	switch(err)
	{
		case COMMAND_ERR:
			UART_sendString("COMMAND ERROR: er is een commando gegeven wat niet herkent wordt.\n"
							"Ondersteunde commando's zijn: 'lijn', 'rechthoek', 'clearscherm' en 'bitmap'.\n\n");
			break;

		case DATA_ERR:
			UART_sendString("DATA ERROR: er is iets onbekends in de data reeks in gevuld.\n"
							"De data wat herkent wordt zijn cijfers en letters, als er iets anders is ingevuld, zoals een '/'\n"
							"dan wordt dit niet herkent.\n\n");
			break;

		case OOB_ERR:
			UART_sendString("OUT OF BOUNDS ERROR: er is een co-ordinaat gegeven wat zich buiten het scherm bevind.\n"
							"De beschikbare co-ordinaten voor de X-as zijn 0 t/m 319, voor de Y-as 0 t/m 239.\n\n");
			break;

		case COLOR_ERR:
			UART_sendString("COLOR ERROR: er is een kleur opgegeven welke niet herkent wordt.\n"
							"De beschikbare kleuren zijn: zwart, blauw, lichtblauw, groen, lichtgroen, cyaan, \n"
							"lichtcyaan, rood, lichtrood, magenta, lichtmagenta, bruin, geel, grijs, wit en roze.\n\n");
			break;

		case BITMAP_ERR:
			UART_sendString("BITMAP ERROR: er is een ongeldigde bitmap nummer ingevuld.\n"
							"Mogelijke bitmap nummers zijn: 1, 2, 3, 4, 5, 6, 7, 8, 9 en 10\n\n");
			break;

		default:
			break;
	}
}
