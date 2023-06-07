/*******************************************************//**
 * @file    error.h
 *
 * @brief   This file contains the error ENUMs for the
 * 			global error handling.
 *
 * @authors Skip Wijtman
 * @date    6-6-2023
 * @version 1.0
*********************************************************/

#ifndef INC_ERROR_H_
#define INC_ERROR_H_

enum ERROR
{
	NO_ERR = 0,		// All errors listed
	COMMAND_ERR,	// Command errors such as 'lijn' and 'rechthoek'
	DATA_ERR,		// Data error means something in the data is wrong, such as characters which are not usable: '/', '[', '(' or '@' are some examples
	OOB_ERR,		// OOB, aka 'out of bounds', is an error which is given when pixels are outside the maximum ranges
	COLOR_ERR		// Color error means a color which is not usable, was submitted
};

#endif /* INC_ERROR_H_ */
