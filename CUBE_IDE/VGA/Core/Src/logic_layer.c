/*******************************************************//**
 * @file    Template_doxygen.c
 *
 * @brief   Here commands will be processed and executed
 *
 * @authors Skip Wijtman
 * @date    24-5-2023
 * @version 1.2
*********************************************************/

//#include "user-header"
#include "logic_layer.h"   // Corresponding user header file

//struct declaration


//global vars
char cmd[12] = {0};

char compare_cmd[5][12] = {	{"lijn"}, 
							{"rechthoek"}, 
							{"clearscherm"}, 
							{"tekst"}, 
							{"bitmap"}};

char compare_col[15][12] = {{"zwart"}, 
							{"blauw"}, 
							{"lichtblauw"}, 
							{"groen"}, 
							{"lichtgroen"}, 
							{"cyaan"}, 
							{"lichtcyaan"}, 
							{"rood"}, 
							{"lichtrood"}, 
							{"magenta"}, 
							{"lichtmagenta"}, 
							{"bruin"}, 
							{"geel"}, 
							{"grijs"}, 
							{"wit"}};

/*****************************************************//**
 * @brief	Function that parses the command of the
 * 			received script
 *
 * @param	data is a struct variable with the received script
 *
 * @return	Error code
*******************************************************/
int parse_cmd(UART data)
{
	for(uint8_t i = 0; i<MAX_CMD_LEN; i++)           // Loop to isolate the command
	{
		if(data.receive[i] == ',')          // Stop the loop when a comma is found, command is isloated
		{
			cmd[i] = '\0';                  // Add a string terminator
			break;
		}

		cmd[i] = data.receive[i];           // Store the command in array
	}

    char found = NO_DATA;
    char ERR = NO_ERR;

	for(int i = 0; i<5; i++)           		 // Loop to scearch for which command is given ///try: i<(sizeof(compare_cmd)/sizeof(compare[0])) 
	{
        if(strcmp(cmd, compare_cmd[i]) == 0)    // When a command is found, remember which iteration. Also no error
        {
        	found = i;
        	ERR = NO_ERR;
        	break;
        }

        else								// When no command is found, error
        	ERR = COMMAND_ERR;
	}

	return found;
}

/*****************************************************//**
 * @brief	Function that determines with the command
 * 			which function should be used, Here the script
 * 			also get parsed further and decodes ASCII to
 * 			useful data
 *
 * 			Here a switch-case is used to determine the
 * 			received command, Cases 0 to 4 are numbered as
 * 			followed:
 *
 * 			-# lijn
 * 			-# rechthoek
 * 			-# clearscherm
 * 			-# tekst
 * 			-# bitmap
 *
 * @param	cmd is a interger of the found command
 * @param 	data is a struct variable with the received script
 *
 * @return	Error code
*******************************************************/
int draw_options(char cmd, UART data)
{
	PARSE parsing;
	char ERR = NO_ERR;
	switch(cmd)				//////ALLES HIERONDER NOG EEN KEER DOOLOPEN OF HET KLOPT EN LOGISCH IS
	{
		case 0:
			int var_counter = 0;
			int num_checker = 0;
			int let_checker = 0;
			for(int i = LINE_LEN; i<STORAGE; i++)		// Start the loop after the command, to convert the rest of the script
			{
				if(data.receive[i] >= LB_ASCII_NUMBERS && data.receive[i] <= UB_ASCII_NUMBERS)		// When a number in ASCII values is found convert this to decimals
				{
					parsing.number_store[0] = parsing.number_store[1];					// Shifting the found numbers to correct possition to add them for the supposed value
					parsing.number_store[1] = parsing.number_store[2];

					parsing.number_store[2] = number_converter(data.receive[i]);				// Converts and returns the number
					num_checker = TRUE;													// Signals that ASCII number is found
				}

				else if(data.receive[i] >= LB_ASCII_LETTERS && data.receive[i] <= UB_ASCII_LETTERS)		// When a letter is found convert the found text to a color
				{
					parsing = color_assign(data, i);				// Reads the wanted color and matches this, also tracks the loop iterator to skip the rest of the letters
					i = parsing.loop_iterator;						// Change 'i' to skip remaining letters of the same supposed color
					let_checker = TRUE;								// Signals that ASCII letter is found
				}

				else						// Error data not usable
					return ERR = DATA_ERR;

				if(data.receive[i] == ',')	// Reset the trackers when a comma is found, to start new character conversion, also stores data to use when complete
				{
					if(num_checker)			// When the data was in numbers
						parsing.var_store[var_counter] = (parsing.number_store[0] * 100) + (parsing.number_store[1] * 10) + parsing.number_store[2];

					if(let_checker)			// When the data was in letters
						parsing.var_store[var_counter] = parsing.color;

					for(int j = 0; j<sizeof(parsing.number_store); j++)		// Empties the numbers stored
						parsing.number_store[j] = 0;

					let_checker = 0;				// Reset signals
					num_checker = 0;
				}



			}
			break;

		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		case 4:

			break;

		default:
			return NO_ERR;		// Different error, but which one?
	}
	return NO_ERR;
}

/*****************************************************//**
 * @brief	Function that converts ASCII numbers to decimals
 *
 * @param	ASCII is character of a ASCII number
 *
 * @return	decimal number
*******************************************************/
int number_converter(char ASCII)
{
	return ASCII - '0';
}

/*****************************************************//**
 * @brief	Function that reads received script text and 
 * 			when possible converts this to the correspondiong color 
 *
 * @param	data is a struct variable with the received script
 * @param 	i is the variable for the loop iterator
 *
 * @return	parsing is a struct variable with data info 
 * 			which are retrieved from the script
*******************************************************/
PARSE color_assign(UART data, int i)
{
	PARSE parsing;
	char color[MAX_COL_LEN];

	for(i; i<(i+MAX_COL_LEN); i++)           // Loop to isolate the color
	{
		if(data.receive[i] == ',')          // Stop the loop when a comma is found, color is isloated
		{
			color[i] = '\0';                  // Add a string terminator
			break;
		}

		color[i] = data.receive[i];           // Store the color in array
	}

	parsing.iterator = i;					  // Storing i, which stopped on a comma, for the loop in 'draw_options' to continue

	int j;
	for(j = 0; j<(sizeof(compare_col)/sizeof(compare_col[0])); j++)		// Loop to find the color, iterator tracks which color
	{
		if(strcmp(color, compare_col[j]) == 0)		// When correct color is found
		{
			parsing.err_code = NO_ERR;
			break;
		}
			
		else
			parsing.err_code = COLOR_ERR;
	}

	switch(j)					// Give the correct color value to the struct
	{
		case 0:
			parsing.color = VGA_COL_BLACK;
			break;

		case 1:
			parsing.color = VGA_COL_BLUE;
			break;

		case 2:
			parsing.color = VGA_COL_LIGHTBLUE;
			break;

		case 3:
			parsing.color = VGA_COL_GREEN;
			break;

		case 4:
			parsing.color = VGA_COL_LIGHTGREEN;
			break;

		case 5:
			parsing.color = VGA_COL_CYAN;
			break;

		case 6:
			parsing.color = VGA_COL_LIGHTCYAN;
			break;

		case 7:
			parsing.color = VGA_COL_RED;
			break;

		case 8:
			parsing.color = VGA_COL_LIGHTRED;
			break;

		case 9:
			parsing.color = VGA_COL_MAGENTA;
			break;

		case 10:
			parsing.color = VGA_COL_LIGHTMAGENTA;
			break;

		case 11:
			parsing.color = VGA_COL_BROWN;
			break;

		case 12:
			parsing.color = VGA_COL_YELLOW;
			break;

		case 13:
			parsing.color = VGA_COL_GRAY;
			break;

		case 14:
			parsing.color = VGA_COL_WHITE;
			break;

		default:
			parsing.err_code = COLOR_ERR;	//???
			break;
	}

	return parsing;
}
