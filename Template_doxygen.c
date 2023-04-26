/*********************************************************
 * @file: Template_doxygen.c
 * 
 * @brief: A test file for doxygen documentation
 * 
 * @authors: Skip Wijtman
 * @date: 19-4-2023
 * @version: 1.0
*********************************************************/

//#include <library-header>
#include <stdio.h>

//#include "user-header"
#include "test.h"

//#define-statements
#define ERROR 69                // Defines and typedefs should all be in caps
                                // Pointer-typedefs have to be the same name, but with a capital 'P'( typedef PERSON *PPERSON;)
//external vars 
extern int test_1;

//global vars
int test_2;

//user functies 
void Template(void);

/*******************************************************
 * Function: Template
 * 
 * @brief: Template function that points out how a 
 *         function header should look.
 * 
 * @param: Nothing
 * 
 * @return: Nothing
*******************************************************/
void Template(void)                 // Comments are to be geven at a appropiate distance and should discribe the statement
{                                   // Braces at the top and bottem of a function and statement should be like this
    int x;                          // Code between braces should have a indent of 4 spaces/1 tab
    x = ERROR;
    if(x == ERROR)                  // Statements with single execusions are used WITHOUT braces
        printf("x is %d", x);
}                                   // Braces at the top and bottem of a function and statement should be like this

/******************************************************
 * Function: Main
 * 
 * @brief: main header
 * 
 * @param: Nothing
 * 
 * @return: Nothing
******************************************************/
void main()
{
    Template();
}
