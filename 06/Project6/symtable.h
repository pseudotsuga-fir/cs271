#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SYMBOL_TABLE_SIZE 50000

typedef int16_t hack_addr;
struct Symbol {
	char *name;
	hack_addr addr;
};

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str);
struct Symbol *symtable_find(char * key);
void symtable_insert(char* key, hack_addr addr);
void symtable_display_table();

#endif
