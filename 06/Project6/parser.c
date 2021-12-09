// Andrew Hepworth

#include "parser.h"
#include "error.h"
#include "symtable.h"

int parse(FILE * file, instruction *instructions) {
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	instruction instr;

	add_predefined_symbols();

	while(fgets(line, sizeof(line), file)){
		line_num += 1;
		if (instr_num > MAX_INSTRUCTIONS) {
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS);
		}

		strip(line);
		if(!*line) {
			continue;
		}

		char inst_type;
		if (is_Atype(line)) {
			inst_type = 'A';
			if (!parse_A_instruction(line, &instr.a_or_c.a_ins)){
    				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
 			}
			instr.a_c_type = Atype;
		}
		else if (is_label(line)) {
			inst_type = 'L';
			char out[MAX_LABEL_LENGTH];
			strcpy(line, extract_label(line, out));
			if (!isalpha(line[0])) {
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}
			if (symtable_find(line)) {
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			symtable_insert(line, instr_num);
			continue;
		}
		else if (is_Ctype(line)) {
			inst_type = 'C';
			char tmp_line[MAX_LINE_LENGTH];
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.a_or_c.c_ins);

			if (instr.a_or_c.c_ins.dest == -1) {
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			if (instr.a_or_c.c_ins.comp == -1) {
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}
			if (instr.a_or_c.c_ins.jump == -1) {
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
			instr.a_c_type = Ctype;

		}

		printf("%c  %s\n", inst_type, line);
		instr_num += 1;
		instructions[instr_num++] = instr;
	}
	return instr_num;
}

char *strip(char *s) {
	char s_new[strlen(s) + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) {
		if(*s2 == '/' && *(s2 + 1) == '/') {
			break;
		}
		else if(!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}

	s_new[i] = '\0';
	strcpy(s, s_new);
	return s;
}

bool is_Atype(const char *line) {
	if (line[0] == '@') {
		return true;
	}
	
	return false;
}

bool is_label(const char *line) {
	if (line[0] == '(' && line[strlen(line) - 1] == ')'){
		return true;
	}

	return false;
}

bool is_Ctype(const char *line) {
	if (!(is_Atype(line) && is_label(line))){
		return true;
	}

	return false;
}

char *extract_label(const char *line, char* label){
	strcpy(label, line);
	label++;
	label[strlen(label) - 1] = 0;
	return label;
}

void add_predefined_symbols() {
	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
		predefined_symbol symbol = predefined_symbols[i];
		symtable_insert(symbol.name, symbol.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr){
	char *s;
	s = (char*) malloc(strlen(line));
	strcpy(s, line+1);
	char *s_end = NULL;
	long result = strtol(s, &s_end, 10);
	if (strcmp(s, s_end) == 0) {
		instr->add_or_label.label = (char*) malloc(strlen(line));
	}
	else if (*s_end != 0){
		return false;
	}
	else {
		instr->add_or_label.address = result;
		instr->is_addr = true;
	}
	return true;
}

void parse_C_instruction(char *line, c_instruction *instr) {
	char *temp = strtok(line, ";");
	char *jump = strtok(NULL, ";");
	char *dest = strtok(temp, "=");
	char *comp = strtok(NULL, "=");
	int a;

	instr->jump = str_to_jumpid(jump);
	if (!comp) {	
		instr->dest = str_to_destid(comp);
		instr->comp = str_to_compid(dest, &a);
	}
	else {
		instr->dest = str_to_destid(dest);
		instr->comp = str_to_compid(comp, &a);
	}
	instr->a = a == 0 ? 0 : 1;
}

void assemble(const char * file_name, instruction* instructions, int num_instructions) {
        FILE * file;
        char out_file_name[80];
        strcpy(out_file_name, file_name);
        strcat(out_file_name, ".hack");

        file = fopen(out_file_name, "w+");

        for (int i = 0; i < num_instructions; i++) {
                opcode opcode;
		int symtable_index = 16;
                if (instructions[i].a_c_type == Atype) {
                        // I am an A-Type instruction...
                        a_instruction instruction = instructions[i].a_or_c.a_ins;
                        if (instruction.is_addr) {
                                // that holds an address.
                                opcode = instruction.add_or_label.address;
                        }
                        else {
                                struct Symbol * label = symtable_find(instruction.add_or_label.label);
                                // that holds a label...
                                if (!label) {
                                        // that exists.
                                        opcode = label->addr;
                                }
                                else {
                                        symtable_insert(instruction.add_or_label.label, symtable_index);
                                        opcode = symtable_find(instruction.add_or_label.label)->addr;
                                        symtable_index++;
                                }
                        }
                }
                else {
                        c_instruction instruction = instructions[i].a_or_c.c_ins;
                        opcode = instruction_to_opcode(instruction);
                }
		printf("%d\n",opcode);
        }
        fclose(file);
}

opcode instruction_to_opcode(c_instruction instr) {
        opcode op = 0;
        op |= (7 << 13);
        op |= (instr.a << 12);
        op |= (instr.comp << 6);
        op |= (instr.dest << 3);
        op |= instr.jump;
        return op;
}

