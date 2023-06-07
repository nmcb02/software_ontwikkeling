/*******************************************************//**
 * @file    logic_layer.c
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
char cmd[MAX_CMD_LEN] = {0};

char compare_cmd[4][MAX_CMD_LEN] = {	{"lijn"},
										{"rechthoek"},
										{"clearscherm"},
										{"bitmap"}};

char compare_col[16][MAX_COL_LEN] = {	{"zwart"},
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
										{"roze"},
										{"wit"}};

/*****************************************************//**
 * @brief	Function that parses the command of the
 * 			received script
 *
 * @param	data is a struct variable with the received script
 *
 * @return	Error code or the current index of found
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
    int counter = 0;

	for(int i = 0; i<5; i++)           		 // Loop to scearch for which command is given ///try: i<(sizeof(compare_cmd)/sizeof(compare[0])) 
	{
		counter++;
        if(strcmp(cmd, compare_cmd[i]) == 0)    // When a command is found, remember which iteration. Also no error
        {
        	found = i;
        	break;
        }

        else if (counter == 4)								// When no command is found, error
        	return COMMAND_ERR;
	}

	return found + ERROR_OFF;
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

	for(int j = 0; j < (sizeof(parsing.number_store)/sizeof(parsing.number_store[0])); j++)		// Empties the array
		parsing.number_store[j] = 0;
	for(int j = 0; j < (sizeof(parsing.var_store)/sizeof(parsing.var_store[0])); j++)
		parsing.var_store[j] = 0;

	parsing.err_code = 0;				// Removing junk values

	int error_return = NO_ERR;
	int var_counter = 0;
	int num_counter = 0;
	int num_checker = 0;
	int let_checker = 0;

	switch(cmd)				// Chooses the corresponding function with the found command
	{						// In the case the data is parsed and used, also searches for errors and stop the function execution when one is found
		case 5:
			parsing = parse_data(parsing, data, LINE_LEN, var_counter, num_checker, let_checker, num_counter);

				if(parsing.err_code != NO_ERR)
							return parsing.err_code;

			error_return = API_draw_line(parsing.var_store[0], parsing.var_store[1], parsing.var_store[2], parsing.var_store[3], parsing.var_store[4], parsing.var_store[5]);
			return error_return;

		case 6:
			parsing = parse_data(parsing, data, RECTANGLE_LEN, var_counter, num_checker, let_checker, num_counter);

			if(parsing.err_code != NO_ERR)
				return parsing.err_code;

			error_return = API_draw_rectangle(parsing.var_store[0], parsing.var_store[1], parsing.var_store[2], parsing.var_store[3], parsing.var_store[4], parsing.var_store[5]);
			return error_return;

		case 7:
			parsing = parse_data(parsing, data, CLEAR_LEN, var_counter, num_checker, let_checker, num_counter);

			if(parsing.err_code != NO_ERR)
				return parsing.err_code;

			error_return = API_clearscreen(parsing.var_store[0]);
			return error_return;

		case 8:
			parsing = parse_data(parsing, data, BITMAP_LEN, var_counter, num_checker, let_checker, num_counter);

			if(parsing.err_code != NO_ERR)
				return parsing.err_code;

			error_return = API_draw_bitmap(parsing.var_store[0], parsing.var_store[1], parsing.var_store[2]);
			return error_return;

		default:
			return cmd;		// ERROR found in 'parse_cmd' returning found error
	}
}

/*****************************************************//**
 * @brief	This function is used for parsing data and 
 * 			converts ASCII to decimals
 * 
 * @param	parsing is a struct variable that stores all needed data for functions
 * @param 	data is a struct variable with the received script
 * @param	LEN is the length of the command + the comma to skip these is the parser
 * @param 	var_counter is an index of an array to store the data in from the script
 * @param 	num_checker is a variable to confirm a ASCII number is found and ensures 
 * 						that no junk color values are stored in the data array
 * @param	let_checker is a variable to confirm a letter is found and ensures 
 * 						that no junk number values are stored in the data array
 * @param	num_counter is a variable which counts the amount of ASCII numbers between two commas
 *
 * @return	Error code
*******************************************************/
PARSE parse_data(PARSE parsing, UART data, int LEN, int var_counter, int num_checker, int let_checker, int num_counter)
{
	for(int i = LEN; i<STORAGE; i++)		// Start the loop after the command, to convert the rest of the script
	{
		if(data.receive[i] >= LB_ASCII_NUMBERS && data.receive[i] <= UB_ASCII_NUMBERS)		// When a number in ASCII values is found convert this to decimals
		{
			parsing.number_store[0] = parsing.number_store[1];					// Shifting the found numbers to correct possition to add them for the supposed value
			parsing.number_store[1] = parsing.number_store[2];

			parsing.number_store[2] = number_converter(data.receive[i]);				// Converts and returns the number
			num_counter++;
			num_checker = TRUE;													// Signals that ASCII number is found
			let_checker = FALSE;
		}

		else if(data.receive[i] >= LB_ASCII_LETTERS && data.receive[i] <= UB_ASCII_LETTERS)		// When a letter is found convert the found text to a color
		{
			parsing = color_assign(data, i, parsing);				// Reads the wanted color and matches this, also tracks the loop iterator to skip the rest of the letters
			i = parsing.loop_iterator;						// Change 'i' to skip remaining letters of the same supposed color
			let_checker = TRUE;								// Signals that ASCII letter is found
			num_checker = FALSE;
		}


		else if(data.receive[i] == ',' || data.receive[i] == '\n')	// Reset the trackers when a comma is found, to start new character conversion, also stores data to use when complete
		{
			if(num_checker)			// When the data was in numbers
				parsing.var_store[var_counter] = (parsing.number_store[0] * 100) + (parsing.number_store[1] * 10) + parsing.number_store[2];

			if(let_checker)			// When the data was in letters
				parsing.var_store[var_counter] = parsing.color;

			for(int j = 0; j<(sizeof(parsing.number_store)/sizeof(parsing.number_store[0])); j++)		// Empties the numbers stored
				parsing.number_store[j] = 0;

			if(data.receive[i] == '\n')			// When a '\n'is found the data parsing is complete
				break;

			if(num_counter >= 4)				// When more than 3 digits, between 2 comma's, are found in the data, ERROR
			{
				parsing.err_code = OOB_ERR;
				return parsing;
			}

			num_counter = 0;
			let_checker = FALSE;				// Reset signals
			num_checker = FALSE;
			var_counter++;
		}

		else						// Error data not usable
		{
			parsing.err_code = DATA_ERR;
			return parsing;
		}
	}

	return parsing;
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
 * @param 	parsing is a struct variable that stores all needed data for functions
 *
 * @return	parsing is a struct variable with data info 
 * 			which are retrieved from the script
*******************************************************/
PARSE color_assign(UART data, int i, PARSE parsing)
{
	char color[MAX_COL_LEN];
	for(int j = 0; j<MAX_COL_LEN; j++)		// Empties the array
		color[j] = 0;

	int j = 0;
	for(i=i; i<(i+MAX_COL_LEN); i++)           // Loop to isolate the color
	{
		if(data.receive[i] == ',' || data.receive[i] == '\n')          // Stop the loop when a comma is found, color is isloated
		{
			color[j] = '\0';                  // Add a string terminator
			break;
		}

		color[j] = data.receive[i];           // Store the color in array
		j++;
	}

	parsing.loop_iterator = i-1;					  // Storing i, the iterator is now set right before the comma so that the loop in the parser can continue properly

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
			parsing.color = VGA_COL_PINK;
			break;

		case 15:
			parsing.color = VGA_COL_WHITE;
			break;

		default:
			parsing.err_code = COLOR_ERR;	//???
			break;
	}

	return parsing;
}
