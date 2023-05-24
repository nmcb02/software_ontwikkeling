/*****************************************************//**
 * @file 	main.c
 *
 * @brief 	The file that gets executed and is used for operating
 * 		  	a screen via VGA with external functions.
 *
 * 		   	**Extra infromation:**
 * 		  	-# CPU      : STM32F4
 * 		   	-# IDE      : CooCox CoIDE 1.7.x
 * 		   	-# Module   : CMSIS_BOOT, M4_CMSIS_CORE
 * 		   	-# Function : VGA_core DMA LIB 320x240, 8bit color
 *
 * @authors UB, J.F van der Bent, Skip Wijtman
 * @date 	3-5-2023
 * @version 1.0 (Updates with every SWD branch)
*********************************************************/

//#include <library-header>
#include "API_functions.h"
#include <math.h>

//#include "user-header"
#include "main.h"
#include "stm32_ub_vga_screen.h"
#include "UART_communication.h"

//#define-statements

//external vars

//global vars
uint8_t data;
char save[100];
char save2[100];
uint8_t arr[100];
uint8_t i=0;
//int some = 1; // Variable for clear screen test
int x = 0;
unsigned char j;
/*****************************************************//**
 * @brief	Program start.
 *
 * @param	Nothing
 *
 * @return	integer val
*******************************************************/
int main(void)
{
	SystemInit(); 			// System speed to 168MHz
	UART2_config();			// Init UART
	UB_VGA_Screen_Init(); 	// Init VGA-Screen


//		UB_VGA_FillScreen(VGA_COL_WHITE);

/*  LINE drawing test */

//	API_draw_line(10, 30, 50, 30, VGA_COL_GREEN, 10);
//	API_draw_line(50, 30, 50, 60, VGA_COL_GREEN, 10);
//	API_draw_line(110, 10, 140, 60, VGA_COL_GREEN, 5);
//	API_draw_line(110, 60, 140, 10, VGA_COL_GREEN, 5);

/* CLEARSCREEN test, don't forget to uncomment the "some" variable */

//	while (some == 1)
//	{
//		UB_VGA_FillScreen(VGA_COL_BLACK);
//		API_draw_line(100, 120, 200, 120, VGA_COL_MAGENTA, 4);
//		some = 0;
//	}
//
//	while (!some)
//		API_clearscreen(VGA_COL_WHITE);


/*	UART testing

	UART_sendChar('g');
	UART_sendChar('o');
	UART_sendChar('e');
	UART_sendChar('d');
	UART_sendChar('\n');
	UART_sendChar('!');

	UART_sendString("goed!");
*/

//  while(1)		// Infinite loop
//  {
//	  data = UART_getChar();	// Stores received data in variable
//	  if(data != 0)				// If data is received
//	  {
//		  save[i] = data;		// Stores received data for later usage and better readability
//		  i++;
//		  if(data == ' ')		// still testing // When a space is found start anew for data receiving
//			  i = 0;
//	  }

	  UART test;

	  test = UART_receiver();

	  for(j = 0; j<LINE_STORAGE; j++)		// Copies received data
		  arr[j] = test.receive[j];


//  }
}

