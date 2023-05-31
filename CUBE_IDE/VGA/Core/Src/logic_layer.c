/*******************************************************//**
 * @file    Template_doxygen.c
 *
 * @brief   Here commands will be processed and executed
 *
 * @authors Skip Wijtman
 * @date    24-5-2023
 * @version 1.0
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
 * 			received command, Cases 1 to 5 are numbered as
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
	char cmd_length;

	switch(cmd)				//////Voor cijfers kan er een array van 3 lang gebruikt worden om deze een voor een in te zetten, na vertalen van ASCII, en wanneer er een comma weer is gevondendeze getallen goed bijelkaar optellen
	{						///// dit hier boven is goed, maar dat moet dan waarschijnlijk ook weer in een struct, dus de vraag is of hier ook een struct voor gemaakt wordt of dat de 'UART' struct algemeen wordt.
		case 0:
		{
			char tracker = 0;
			cmd_length = LINE_LEN;			// The cmd length to skip it in the script tekst
			for(int i = cmd_length; i<LINE_STORAGE; i++)		// Start the loop after the command, to convert the rest of the script
			{
				if(data.receive[i] >= 48 && data.receive[i] <= 57)		// When a numberin ASCII values is found convert this to decimals
				{
					tracker++;											// Tracks how much numbers between two comma's are found so that these will be added together,   e.g.   ,100, in ASCII is '49' '48' '48' which will be converted to '1' '0' '0', but these numbers must be added together for the original '100'
					number_converter(tracker, data.receive[i]);
				}

			}
			break;
		}

		case 1:
		{
			break;
		}

		case 2:
		{
			break;
		}

		case 3:
		{
			break;
		}

		case 4:
		{
			break;
		}

		default:
			return COMMAND_ERR;
	}
	return NO_ERR;
}

void number_converter(char tracker, char ASCII)
{

}
