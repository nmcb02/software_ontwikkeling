/*******************************************************//**
 * @file    Template_doxygen.c
 * 
 * @brief   A test file for doxygen documentation
 * 
 * @authors Skip Wijtman
 * @date    19-4-2023
 * @version 1.0
*********************************************************/

//#include <library-header>
#include <stdio.h>

//#include other "user-header"
#include "main.h"   // possible other user header file

//struct definition
typedef struct test
{
    int testing;
}TEST, *PTEST;                  // Pointer-typedefs have to be the same name, but with a capital 'P'( typedef PERSON *PPERSON;)

//#define-statements
#define ERROR 69                // Defines and typedefs should all be in caps
                                
//external vars 
extern int test_1;

//prototype user functions
void Template(void);
