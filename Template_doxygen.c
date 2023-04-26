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
#define ERROR 69                // Defines en typedefs worden gegeven in caps
                                // Pointer-typedefs houden dezelfde naam, maar beginnen met hoofdletter 'P' ( typedef PERSON *PPERSON;)
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
void Template(void)                 // Comments worden gegeven op een afstand van een statement en beschrijft wat er in ene statement wordt gedaan
{                                   // Acolades boven en onder op deze manier
    int x;                          // De code tussen accolades heeft standaard een insprong van 4 spaties/1 tab
    x = ERROR;
    if(x == ERROR)                  // Statements met enkele uitvoeringen zonder accolades
        printf("x is %d", x);
}                                   // Accolades boven en onder op deze manier

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
