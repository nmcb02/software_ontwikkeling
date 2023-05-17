/*******************************************************//**
 * @file    API_functions.h
 *
 * @brief  	Header file for API functions
 *
 * @authors Naomi Born
 * @date    17-05-2023
 * @version 1.0
*********************************************************/
#ifndef INC_API_FUNCTIONS_H_
#define INC_API_FUNCTIONS_H_

//#include <library-header>
#include <stdio.h>
#include <stdlib.h>

//#include other "user-header"
#include "stm32_ub_vga_screen.h"

//#define-statements
#define sgn(x) ((x<0)?-1:((x>0)?1:0)) // macro to return the sign of a number

// prototype user functions
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight);
int API_draw_rectangle (int x, int y, int width, int height, int color, int filled);

#endif /* INC_API_FUNCTIONS_H_ */
