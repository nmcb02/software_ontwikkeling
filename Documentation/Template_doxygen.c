/*******************************************************//**
 * @file    Template_doxygen.c
 * 
 * @brief   A test file for doxygen documentation
 * 
 * @authors Skip Wijtman
 * @date    19-4-2023
 * @version 1.0
*********************************************************/

//#include "user-header"
#include "Template_doxygen.h"   // Corresponding user header file

//struct declaration
TEST str;

//global vars
int test_2;

/*****************************************************//**
 * @brief   Template function that points out how a 
 *          function header should look.
 * 
 * @param   Nothing
 * 
 * @return  Nothing
*******************************************************/
void Template(void)                 // Comments are to be given at an appropiate distance and should discribe the statement
{                                   // Braces at the top and bottem of a function and statement should be like this
    int x;                          // Code between braces should have a indent of 4 spaces/1 tab
    x = ERROR;
    if(x == ERROR)                  // Statements with single execusions are used WITHOUT braces
        printf("x is %d", x);
}                                   // Braces at the top and bottom of a function and statement should be like this

/****************************************************//**
 * @brief   main header
 * 
 * @param   Nothing
 * 
 * @return  Nothing
******************************************************/
void main()
{
    Template();                     // Calls function
}
