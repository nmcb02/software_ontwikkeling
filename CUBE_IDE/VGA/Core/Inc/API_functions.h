/*******************************************************//**
 * @file    API_functions.h
 *
 * @brief  	Header file for API functions
 *
 * @authors Naomi Born
 * @date    17-05-2023
 * @version 1.1
*********************************************************/
#ifndef INC_API_FUNCTIONS_H_
#define INC_API_FUNCTIONS_H_

//#include <library-header>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include other "user-header"
#include "stm32_ub_vga_screen.h"
#include "error.h"

//#define-statements
#define sgn(x) ((x<0)?-1:((x>0)?1:0)) // macro to return the sign of a number

#define BITMAP_HEIGHT 77	// Defines for drawing bitmaps
#define BITMAP_WIDTH 120
#define BITMAP_SIZE 9240

#define BM_ARROW_UP				1	// Define for bitmap options
#define BM_ARROW_down			2
#define BM_ARROW_left			3
#define BM_ARROW_right			4
#define BM_SMILEY_ANGERY		5
#define BM_SMILEY_ANGERY_COL	6
#define BM_SMILEY_HAPPY			7
#define BM_SMILEY_HAPPY_COL		8
#define BM_SMILEY_SAD			9
#define BM_SMILEY_SAD_COL		10

#define BLACK	0 			// Defines for matching array colors with VGA colors
#define BLUE	23
#define YELLOW	252
#define RED		224
#define PINK	247
#define WHITE	255

// prototype user functions
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight);
int API_clearscreen(int color);
int API_draw_rectangle(int x, int y, int width, int height, int color, int filled);
int API_draw_bitmap(int bm_nr, int x_lup, int y_lup);

#endif /* INC_API_FUNCTIONS_H_ */
