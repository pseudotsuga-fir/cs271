#include "parser.h"

void parse(FILE * file) {
	char line[MAX_LINE_LENGTH] = {0};

	while(fgets(line, sizeof(line), file)){
		strip(line);
		if(!*line) {
			continue;
		}

		char inst_type;
		if (is_Atype(line)) {
			inst_type = 'A';
		}
		else if (is_label(line)) {
			inst_type = 'L';
			char out[MAX_LABEL_LENGTH];
			strcpy(line, extract_label(line, out));
		}
		else if (is_Ctype(line)) {
			inst_type = 'C';
		}

		printf("%c  %s\n", inst_type, line);
    }

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
