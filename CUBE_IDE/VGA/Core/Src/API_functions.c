/*
 * API_functions.c
 *
 *  Created on: May 17, 2023
 *      Author: naomi
 */

#include "API_functions.h"
#include "stm32_ub_vga_screen.h"


#define sgn(x) ((x<0)?-1:((x>0)?1:0)) // macro to return the sign of a number

int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	int dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

	dx = x_2 - x_1;	//calculate deltas of x and y
	dy = y_2 - y_1;

	dxabs = abs(dx); // absolute val so no negative values exist
	dyabs = abs(dy);

	sdx = sgn(dx);
	sdy = sgn(dy);

	x = dyabs>>1; // bit shift to right aka dyabs/2
	y = dxabs>>1; // bit shift to right aka dxabs/2

	px = x_1;
	py = y_1;


	if (dxabs>=dyabs)	// Delta x is bigger than delta y
	{
		for (int i = 0; i < dxabs; i++) // Loop for a line < delta x
		{
			y += dyabs;

			if (y >= dxabs)
			{
				y -= dxabs;
				py += sdy;
			}

			px += sdx;
			UB_VGA_SetPixel(px, py, VGA_COL_GREEN);
		}
	}

	else
	{
		for (int i = 0; i < dyabs; i++) // Loop for a line < delta x
		{
			x += dxabs;

			if (x >= dyabs)
			{
				x -= dyabs;
				px += sdx;
			}
			py += sdy;
			UB_VGA_SetPixel(px, py, VGA_COL_GREEN);
		}
	}
//		for (short y = y_1; y <= y_1 + weight; y++)
//		{
//			for(short x = x_1; x <= x_2; x++)
//			{
//				UB_VGA_SetPixel(x, y, VGA_COL_GREEN);
//			}
//		}

	return 1;
}

