/*******************************************************//**
 * @file    Template_doxygen.h
 *
 * @brief   This file contains the functions which are used
 * 		   	in the source file 'Template_doxygen.c'.
 *
 * @authors Skip Wijtman
 * @date    24-5-2023
 * @version 1.2
*********************************************************/
#ifndef INC_LOGIC_LAYER_H_
#define INC_LOGIC_LAYER_H_

//#include <library-header>


//#include other "user-header"
#include "UART_communication.h"
#include "stm32_ub_vga_screen.h"
#include "API_functions.h"


//struct definition
typedef struct PARSE_STORAGE
{
	int number_store[3];
	int color;
	int loop_iterator;
	int var_store[6];
	int err_code;
}PARSE, *PPARSE;

//#define-statements
enum ERROR
{
	NO_ERR = 0,		// All errors listed
	COMMAND_ERR,
	DATA_ERR,
	COLOR_ERR
};

#define MAX_CMD_LEN 		12
#define MAX_COL_LEN			13

#define LINE_LEN 			5		// Defines to skip the command in the received array
#define RECTANGLE_LEN 		10
#define CLEAR_LEN 			12
#define TEXT_LEN 			6
#define BITMAP_LEN 			7

#define LB_ASCII_NUMBERS	48		// Defines to mark the lower and upper bounds of the ASCII numbers
#define UB_ASCII_NUMBERS	57

#define LB_ASCII_LETTERS	97		// Defines to mark the lower and upper bounds of the ASCII lowercase letters
#define UB_ASCII_LETTERS	122

#define TRUE 				1
#define FALSE				0

//external vars


//prototype user functions
int parse_cmd(UART data);
int draw_options(char cmd, UART data);
int number_converter(char ASCII);
PARSE color_assign(UART data, int i, PARSE parsing);

#endif /* INC_LOGIC_LAYER_H_ */
