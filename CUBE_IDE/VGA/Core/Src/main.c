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


	UB_VGA_FillScreen(VGA_COL_WHITE);

  while(1)		// Infinite loop
  {
	  UART test;
	  int err=0;

//	  test = UART_receiver();
//
////	  for(j = 0; j<STORAGE; j++)		// Copies received data
////		  arr[j] = test.receive[j];
//
//
//	  if(test.receive[0] != 0)		// When data received, parse
//	  {
//		  val = parse_cmd(test);
//
//	  }
//
//	  else
//		  val = NO_DATA;

	  test.receive[0] = 'l';
	  test.receive[1] = 'i';
	  test.receive[2] = 'j';
	  test.receive[3] = 'n';
	  test.receive[4] = ',';
	  test.receive[5] = '1';
	  test.receive[6] = ',';
	  test.receive[7] = '1';
	  test.receive[8] = ',';
	  test.receive[9] = '1';
	  test.receive[10] = '0';
	  test.receive[11] = '0';
	  test.receive[12] = ',';
	  test.receive[13] = '1';
	  test.receive[14] = '0';
	  test.receive[15] = '0';
	  test.receive[16] = ',';
	  test.receive[17] = 'r';
	  test.receive[18] = 'o';
	  test.receive[19] = 'o';
	  test.receive[20] = 'd';
	  test.receive[21] = ',';
	  test.receive[22] = '4';
	  test.receive[23] = '\n';

	  err = draw_options(val, test);

  }
}

