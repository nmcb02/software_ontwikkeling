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

int Parser(UART data)
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

	for(int i = 0; i<5; i++)           	 // Loop to scearch for which command is given
	{
        if(strcmp(cmd, compare[i]) == 0)    // When a command is found, remember which iteration. Also no error
        {
        	found = i;
        	ERR = NO_ERR;
        	break;
        }

        else								// When no command is found, error
        	ERR = COMMAND_ERR;
	}

	if(found == NO_DATA)					// When no command, return error
		return ERR;

	return ERR;
}


