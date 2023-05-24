/*******************************************************//**
 * @file    Template_doxygen.h
 *
 * @brief   This file contains the functions which are used
 * 		   	in the source file 'Template_doxygen.c'.
 *
 * @authors Skip Wijtman
 * @date    24-5-2023
 * @version 1.0
*********************************************************/
#ifndef INC_LOGIC_LAYER_H_
#define INC_LOGIC_LAYER_H_

//#include <library-header>


//#include other "user-header"
#include "UART_communication.h"


//struct definition


//#define-statements
enum ERROR
{
	NO_ERR = 0,
	COMMAND_ERR
};


//external vars


//prototype user functions
int Parser(UART data);


#endif /* INC_LOGIC_LAYER_H_ */
