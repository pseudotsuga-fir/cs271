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

	/*
        * Error code 6 represents that the label does not exist.
        */
        EXIT_INVALID_A_INSTR = 6,

	/*
        * Error code 7 represents that the label does not exist.
        */
        EXIT_INVALID_C_DEST = 7,
	
	/*
        * Error code 8 represents that the label does not exist.
        */
        EXIT_INVALID_C_COMP = 8,

	/*
        * Error code 9 represents that the label does not exist.
        */
        EXIT_INVALID_C_JUMP = 9,

};

void exit_program(enum exitcode code, ...);

#endif
