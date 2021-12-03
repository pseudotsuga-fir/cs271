// Andrew Hepworth

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#include "hack.h"

#define MAX_LINE_LENGTH  300
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;
enum instr_type{Invalid = -1, Atype, Ctype};
typedef struct c_instruction {
	opcode a:1;
	opcode comp:7;
	opcode dest:4;
	opcode jump:4;
} c_instruction;
typedef struct a_instruction {
	union add_or_label {
		hack_addr address;
		char *label;
	} add_or_label;
	bool is_addr;
} a_instruction;
typedef struct instruction {
	union a_or_c {
		a_instruction a_ins;
		c_instruction c_ins;
	} a_or_c;
	enum instr_type a_c_type;
} instruction;

char *strip(char *);
int parse(FILE * file, instruction *instructions);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);

void add_predefined_symbols();

bool parse_A_instruction(const char *line, a_instruction *instr);

void parse_C_instruction(char *line, c_instruction *instr);

#endif
