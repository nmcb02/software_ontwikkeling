/*******************************************************//**
 * @file    logic_layer.h
 *
 * @brief   This file contains the functions which are used
 * 		   	in the source file 'logic_layer.c'.
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
#include "error.h"


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
#define MAX_CMD_LEN 		12		// Defines for loops
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

#define ERROR_OFF 			5

//external vars

//prototype user functions
int parse_cmd(UART data);
int draw_options(char cmd, UART data);
int number_converter(char ASCII);
PARSE color_assign(UART data, int i, PARSE parsing);
PARSE parse_data(PARSE parsing, UART data, int LEN , int var_counter, int num_checker, int let_checker);

#endif /* INC_LOGIC_LAYER_H_ */
