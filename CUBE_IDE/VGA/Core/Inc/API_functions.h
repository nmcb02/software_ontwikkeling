/*
 * API_functions.h
 *
 *  Created on: May 17, 2023
 *      Author: naomi
 */

#ifndef INC_API_FUNCTIONS_H_
#define INC_API_FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include "stm32_ub_vga_screen.h"

// prototype user functions
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight);

#endif /* INC_API_FUNCTIONS_H_ */
