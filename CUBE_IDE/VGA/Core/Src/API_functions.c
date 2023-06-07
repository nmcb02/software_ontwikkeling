/*******************************************************//**
 * @file    API_functions.c
 *
 * @brief  	All API functions are created in this file
 *
 * @authors Naomi Born
 * @date    17-05-2023
 * @version 1.1
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

	if ((0 > x_1) || (x_1 > VGA_DISPLAY_X) || (0 > x_2) || (x_2 > VGA_DISPLAY_X))
		return OOB_ERR; // ERROR:	Invalid value

	else if ((0 > y_1) || (y_1 > VGA_DISPLAY_Y) || (0 > y_2) || (y_2 > VGA_DISPLAY_Y))
		return OOB_ERR; // ERROR:	Invalid value

	else if ((0 > weight) || (weight > VGA_DISPLAY_X) || (0 > weight) || (weight > VGA_DISPLAY_Y))
		return OOB_ERR; // ERROR:	Invalid value

	else
	{
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
				for (int x = x_1; x <= x_2; x++)
					UB_VGA_SetPixel(x, y, color);
			}
		}

		else if (dx == 0) // vertical line
		{
			for (int x = x_1; x <= x_1 + weight; x++)
			{
				for(int y = y_1; y <= y_2; y++)
					UB_VGA_SetPixel(x, y, color);
			}
		}

		else if (dxabs>=dyabs)	// Delta x is bigger than delta y
		{
			for (int j = 0; j < weight; j++)
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
			for (int j = 0; j < weight; j++)
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
		return NO_ERR;
	}
}

/*****************************************************//**
 * @brief   This function gives the user the ability to clear the screen to a certain color
 *
 * @param   color Color of the screen
 *
 * @return  Error code if error occurs
*******************************************************/
int API_clearscreen(int color)
{
	UB_VGA_FillScreen(color);

	return NO_ERR;
}

/*****************************************************//**
 * @brief   This function gives the user the ability to draw a rectangle on a VGA screen
 *
 * @param   x_1 Starting point coördinate of x
 * @param   y_1 Starting point coördinate of y
 * @param   width Width of the rectangle max. 320
 * @param   height Height of the rectangle max. 240
 * @param   color Color of the rectangle/borders
 * @param   filled 1 is filled rectangle 0 is just borders
 *
 * @return  Error code if error occurs
*******************************************************/
int API_draw_rectangle(int x_1, int y_1, int width, int height, int color, int filled)
{
	int x_2, y_2;

	if ((0 > x_1) || (x_1 > VGA_DISPLAY_X) || (0 > width) || (width > VGA_DISPLAY_X))
		return OOB_ERR; // ERROR:	Invalid value

	else if ((0 > y_1) || (y_1 > VGA_DISPLAY_Y) || (0 > height) || (height > VGA_DISPLAY_Y))
		return OOB_ERR; // ERROR:	Invalid value

	else
	{
		x_2 = x_1 + width;
		y_2 = y_1 + height;

		if (filled)	//Drawing a filled rectangle
		{
			for (int y = y_1; y <= y_2; y++)
			{
				for (int x = x_1; x <= x_2; x++)
					UB_VGA_SetPixel(x, y, color);
			}
		}

		else if (!filled)
		{
			for (int x = x_1; x <= x_2; x++)	// Draw top line
				UB_VGA_SetPixel(x, y_1, color);

			for (int y = y_1; y <= y_2; y++)	// Draw left line
				UB_VGA_SetPixel(x_1, y, color);

			for (int y = y_1; y <= y_2; y++)	// Draw right line
				UB_VGA_SetPixel(x_2, y, color);

			for (int x = x_1; x <= x_2; x++)	// Draw bottom line
				UB_VGA_SetPixel(x, y_2, color);
		}

		else
			return DATA_ERR; // ERROR:	Invalid value

		return NO_ERR;
	}
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
int API_draw_bitmap(int bm_nr, int x_lup, int y_lup)
{
	int index_x = 0;
	int bitmap[BITMAP_SIZE];

	switch(bm_nr)	// Switch case to decide which bitmap needs to be shown
	{
		case BM_ARROW_UP:
			memcpy(bitmap, arrow_up, sizeof bitmap);
			break;
		case BM_ARROW_down:
			memcpy(bitmap, arrow_down, sizeof bitmap);
			break;
		case BM_ARROW_left:
			memcpy(bitmap, arrow_left, sizeof bitmap);
			break;
		case BM_ARROW_right:
			memcpy(bitmap, arrow_right, sizeof bitmap);
			break;
		case BM_SMILEY_ANGERY:
			memcpy(bitmap, smiley_angry, sizeof bitmap);
			break;
		case BM_SMILEY_ANGERY_COL:
			memcpy(bitmap, smiley_angry_col, sizeof bitmap);
			break;
		case BM_SMILEY_HAPPY:
			memcpy(bitmap, smiley_happy, sizeof bitmap);
			break;
		case BM_SMILEY_HAPPY_COL:
			memcpy(bitmap, smiley_happy_col, sizeof bitmap);
			break;
		case BM_SMILEY_SAD:
			memcpy(bitmap, smiley_sad, sizeof bitmap);
			break;
		case BM_SMILEY_SAD_COL:
			memcpy(bitmap, smiley_sad_col, sizeof bitmap);
			break;
		default:
			return BITMAP_ERR; //ERROR: no existing bitmap number given
	}

	for (int y = y_lup; y < y_lup + BITMAP_HEIGHT; y++)		// For loop to get the y-coordinate
	{
		for (int x = x_lup; x < x_lup + BITMAP_WIDTH; x++)	// For loop to get the x-coordinate
		{
			index_x++;
			if (index_x == BITMAP_SIZE)	// If index is equal to the array size quit the loop
				break;

			// If statements for various colors from the bitmaps
			else if (bitmap[index_x] == BLACK)
				UB_VGA_SetPixel(x, y, VGA_COL_BLACK);
			else if (bitmap[index_x] == BLUE)
				UB_VGA_SetPixel(x, y, VGA_COL_BLUE);
			else if (bitmap[index_x] == YELLOW)
				UB_VGA_SetPixel(x, y, VGA_COL_YELLOW);
			else if (bitmap[index_x] == RED)
				UB_VGA_SetPixel(x, y, VGA_COL_RED);
			else if (bitmap[index_x] == PINK)
				UB_VGA_SetPixel(x, y, VGA_COL_PINK);
			else if (bitmap[index_x] == WHITE)
				UB_VGA_SetPixel(x, y, VGA_COL_WHITE);
		}
	}
	return NO_ERR;
}
