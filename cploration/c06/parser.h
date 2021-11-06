#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2

typedef int16_t hack_addr;
typedef int16_t opcode;
enum instr_type{Invalid = -1, Atype, Ctype};
typedef struct c_instruction {
	opcode a:1;
	opcode comp:6;
	opcode dest:3;
	opcode jump:3;
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
void parse(FILE *);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

char *extract_label(const char *line, char* label);
