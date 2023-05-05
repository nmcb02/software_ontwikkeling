/*********************************************************
 * @file: main.c
 *
 * @brief: The file that gets executed and is used for operating
 * 		   a screen via VGA with external functions.<br>
 *
 * 		   **Extra infromation:**
 * 		   # CPU      : STM32F4
 * 		   # IDE      : CooCox CoIDE 1.7.x
 * 		   # Module   : CMSIS_BOOT, M4_CMSIS_CORE
 * 		   # Function : VGA_core DMA LIB 320x240, 8bit color
 *
 * @authors: UB, J.F van der Bent, Skip Wijtman
 * @date: 3-5-2023
 * @version: 1.0 (Updates with every SWD branch)
*********************************************************/

//#include <library-header>
#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>

//#include "user-header"

//#define-statements

//external vars

//global vars
uint8_t data;
uint8_t save[8];
uint8_t i=0;

/*******************************************************
 * Function: main
 *
 * @brief: Program start.
 *
 * @param: Nothing
 *
 * @return: integer val
*******************************************************/
int main(void)
{
	SystemInit(); 			// System speed to 168MHz
	UART2_config();			// Init UART
	UB_VGA_Screen_Init(); 	// Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_BLUE);

	for(short x=160; x<(160+10); x++)
	{
		UB_VGA_SetPixel(x, 120, VGA_COL_BLACK);

		for(short y=120; y<(120+10); y++)
		{
			UB_VGA_SetPixel(160, y, VGA_COL_GREEN);
		}
	}

//	UART_sendChar('g');
//	UART_sendChar('o');
//	UART_sendChar('e');
//	UART_sendChar('d');
//	UART_sendChar('\n');
//	UART_sendChar('!');

//	UART_sendString("goed!");


  while(1)		// Infinite loop
  {
	  data = UART_getChar();
	  if(data != 0)
	  {
		  save[i] = data;
		  i++;
		  if(data == ' ')
			  i = 0;
	  }
//	  UART_sendChar(data);

//	  UART_sendChar('g');
//  	  UART_sendChar('o');
//	  UART_sendChar('e');
//	  UART_sendChar('d');
//	  UART_sendChar('!');

  }
}

