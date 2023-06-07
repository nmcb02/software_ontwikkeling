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
#include <math.h>

//#include "user-header"
#include "main.h"
#include "stm32_ub_vga_screen.h"
#include "UART_communication.h"
#include "API_functions.h"
#include "logic_layer.h"
#include "error.h"

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
int val = 0;

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


	UB_VGA_FillScreen(VGA_COL_WHITE);	// Start with a white screen

  while(1)		// Infinite loop
  {
	  UART test;
	  int err = NO_ERR;

	  test = UART_receiver();


	  if(test.receive[0] != 0)		// When data received, parse
	  {
		  val = parse_cmd(test);
		  err = draw_options(val, test);
	  }

	  else
		  val = NO_DATA;

	  if(err != NO_ERR)
	  {
		  UART_errorHandling(err);
	  }
  }
}

