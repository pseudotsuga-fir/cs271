#include <stdio.h>
#include <stdlib.h>

#define SYMBOL_TABLE_SIZE 100

typedef int16_t hack_addr;
struct Symbol {
	char *name;
	hack_addr addr;
};

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str);
struct Symbol *find(char * key);
void insert(char* key, hack_addr addr);
void display_table();
