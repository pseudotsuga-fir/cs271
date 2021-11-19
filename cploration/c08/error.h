#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum exitcode {

	/*
 	* Error code 1 represents that given file does not exist.
	*/
	EXIT_INCORRECT_ARGUMENTS = 1,

	/*
 	* Error code 2 represents that given file cannot be opened.
	*/
	EXIT_CANNOT_OPEN_FILE = 2,

	/*
	* Error code 3 represents that the instruction limit has been reached.
	*/
	EXIT_TOO_MANY_INSTRUCTIONS = 3,

	/*
	* Error code 4 represents that the label violates syntax.
	*/
	EXIT_INVALID_LABEL = 4,
	
	/*
        * Error code 5 represents that the label does not exist.
        */
        EXIT_SYMBOL_ALREADY_EXISTS = 5,


};

void exit_program(enum exitcode code, ...);

#endif
