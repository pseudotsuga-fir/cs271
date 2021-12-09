// Andrew Hepworth

#include "parser.h"
#include "error.h"

#define MAX_INSTRUCTION_COUNT 300000

int main(int argc, const char *argv[]) {
    if (argc != 2) {
    	// incorrect number of arguments
	exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);        
    }

    FILE *fin = fopen( argv[1], "r" );

    if(!fin) {
	exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));
    int num_instructions = parse(fin, instructions);
    fclose(fin);
    
    assemble(argv[1], instructions, num_instructions);

    free(instructions);
    
    return 0;
}

