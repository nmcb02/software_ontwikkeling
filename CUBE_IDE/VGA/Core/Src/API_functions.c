/*******************************************************//**
 * @file    API_functions.c
 *
 * @brief  	All API functions are created in this file
 *
 * @authors Naomi Born
 * @date    17-05-2023
 * @version 1.0
*********************************************************/
//#include other "user-header"
#include "API_functions.h"
#include "bitmap_arrows.h"
#include "bitmap_smileys.h"

/*****************************************************//**
 * @brief   This function gives the user the ability to draw lines on a VGA screen
 *
 * @param   x_1 Starting point coördinate of x
 * @param   x_2 Ending point coördinate of x
 * @param   y_1 Starting point coördinate of y
 * @param   y_2 Ending point coördinate of y
 * @param   color Color of the line
 * @param   weight Width of the line
 *
 * @return  Error code if error or no error occurs
*******************************************************/
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight)
{
	int dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;

	dx = x_2 - x_1;	// Calculate deltas of x and y
	dy = y_2 - y_1;

	dxabs = abs(dx); // Absolute val so no negative values exist
	dyabs = abs(dy);

	sdx = sgn(dx);
	sdy = sgn(dy);

	x = dyabs>>1; // Bit shift to right aka dyabs/2
	y = dxabs>>1; // Bit shift to right aka dxabs/2

	px = x_1;
	py = y_1;

	if (dy == 0)	// Horizontal line
	{
		for (int y = y_1; y <= y_1 + weight; y++)
		{
			for(int x = x_1; x <= x_2; x++)
			{
				UB_VGA_SetPixel(x, y, color);
			}
		}
	}

	else if (dx == 0) // vertical line
	{
		for (int x = x_1; x <= x_1 + weight; x++)
		{
			for(int y = y_1; y <= y_2; y++)
			{
				UB_VGA_SetPixel(x, y, color);
			}
		}
	}

	else if (dxabs>=dyabs)	// Delta x is bigger than delta y
	{
		for(int j = 0; j < weight; j++)
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
				UB_VGA_SetPixel(px+j, py, color);
			}
			px = x_1;
			py = y_1;
		}
	}

	else
	{
		for(int j = 0; j < weight; j++)
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
				UB_VGA_SetPixel(px+j, py, color);
			}
			px = x_1;
			py = y_1;
		}
	}
	return 0;
}

/*****************************************************//**
 * @brief   This function gives the user the ability to clear the screen to a certain color
 *
 * @param   color Color of the screen
 *
 * @return  Error code if error occurs
*******************************************************/
int API_clearscreen (int color)
{
	UB_VGA_FillScreen(color);

	return 0;
}
/*****************************************************//**
 * @brief   This function gives the user the ability to clear the screen to a certain color
 *
 * @param   color Color of the screen
 *
 * @return  Error code if error or no error occurs
*******************************************************/
int API_draw_rectangle (int x_1, int y_1, int width, int height, int color, int filled)
{
	UB_VGA_FillScreen(color);

	return 0;
}

/*****************************************************//**
 * @brief   This function gives the user the ability to put a bitmap on the VGA screen
 *
 * @param   x_lup X coordinate of x left up
 * 			y_lup Y coordinate of y left up
 * 			bm_nr Number of the bitmap
 *
 * @return  Error code if error or no error occurs
*******************************************************/
int API_draw_bitmap (int x_lup, int y_lup, int bm_nr)
{
	int index_x = 0;
	int bitmap[BITMAP_SIZE];

	switch(bm_nr)
	{
		case 1:
			memcpy(bitmap, arrow_up, sizeof bitmap);
			break;
		case 2:
			memcpy(bitmap, arrow_down, sizeof bitmap);
			break;
		case 3:
			memcpy(bitmap, arrow_left, sizeof bitmap);
			break;
		case 4:
			memcpy(bitmap, arrow_right, sizeof bitmap);
			break;
		case 5:
			memcpy(bitmap, smiley_angry, sizeof bitmap);
			break;
		case 6:
			memcpy(bitmap, smiley_angry_col, sizeof bitmap);
			break;
		case 7:
			memcpy(bitmap, smiley_happy, sizeof bitmap);
			break;
		case 8:
			memcpy(bitmap, smiley_happy_col, sizeof bitmap);
			break;
		case 9:
			memcpy(bitmap, smiley_sad, sizeof bitmap);
			break;
		case 10:
			memcpy(bitmap, smiley_sad_col, sizeof bitmap);
			break;
		default:
			return 1; //error no existing bitmap number given
	}


	for(int y = y_lup; y < y_lup + BITMAP_HEIGHT; y++)
	{
		for(int x = x_lup; x < x_lup + BITMAP_WIDTH; x++)
		{
			index_x++;
			if (index_x == BITMAP_SIZE)
				break;

			else if (bitmap[index_x] == 0)
				UB_VGA_SetPixel(x, y, VGA_COL_BLACK);
			else if (bitmap[index_x] == 23)
				UB_VGA_SetPixel(x, y, VGA_COL_BLUE);
			else if (bitmap[index_x] == 252)
				UB_VGA_SetPixel(x, y, VGA_COL_YELLOW);
			else if (bitmap[index_x] == 224)
				UB_VGA_SetPixel(x, y, VGA_COL_RED);
			else if (bitmap[index_x] == 247)
				UB_VGA_SetPixel(x, y, VGA_COL_PINK);
			else if (bitmap[index_x] == 255)
				UB_VGA_SetPixel(x, y, VGA_COL_WHITE);

		}
	}

	return 0;
}
