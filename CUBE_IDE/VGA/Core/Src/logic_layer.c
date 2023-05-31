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
char compare[5][12] = {{"lijn"}, {"rechthoek"}, {"clearscherm"}, {"tekst"}, {"bitmap"}};

/*****************************************************//**
 * @brief	Function that parses the command of the
 * 			received script
 *
 * @param	struct variable
 *
 * @return	Error code
*******************************************************/
int parse_cmd(UART data)
{
	for(uint8_t i = 0; i<12; i++)           // Loop to isolate the command
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

	for(int i = 0; i<5; i++)           		 // Loop to scearch for which command is given
	{
        if(strcmp(cmd, compare[i]) == 0)    // When a command is found, remember which iteration. Also no error
        {
        	found = i;
        	ERR = 55;
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
 * 			also get parsed further
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
 * @param	char of found command
 *
 * @return	Error code
*******************************************************/
int draw_options(char cmd, UART data)
{
	PARSE parsing;
	cahr ERR = NO_ERR;
	switch(cmd)				//////ALLES HIERONDER NOG EEN KEER DOOLOPEN OF HET KLOPT EN LOGISCH IS
	{
		case 0:
			int num_tracker = 0;
			int var_counter = 0;
			int num_checker = 0;
			int let_checker = 0;
			for(int i = LINE_LEN; i<STORAGE; i++)		// Start the loop after the command, to convert the rest of the script
			{
				if(data.receive[i] >= LB_ASCII_NUMBERS && data.receive[i] <= UB_ASCII_NUMBERS)		// When a number in ASCII values is found convert this to decimals
				{
					parsing.number_store[tracker] = number_converter(data.receive[i]);				// Converts and returns the number
					num_tracker++;														// Tracks how much numbers between two comma's are found so that these will be added together,   e.g.   ,100, in ASCII is '49' '48' '48' which will be converted to '1' '0' '0', but these numbers must be added together for the original '100'
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
					num_tracker = 0;
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

int number_converter(char ASCII)
{
	return num;
}

PARSE color_assign(UART data, int i)
{

}
