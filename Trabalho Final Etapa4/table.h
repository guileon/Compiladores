#ifndef TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_UNDEFINED 0


#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_FLOATING 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

#define TRUE 1
#define FALSE 0

#define HASH_SIZE 997

struct intList;
struct intList
{
	int v;
	struct intList * next;
}

struct HNODE;
struct HNODE
{
int type;
char * value;
int dataType;
struct HNODE *next;
struct intList * args;
} ;

struct HNODE*table[HASH_SIZE];

void table_start(void);
int table_address(char *text);
struct HNODE*table_insertTable(char *text, int type);
struct HNODE*table_find(char * text);
int table_isInTable(char *text);
void table_print(void);
struct intList * insertInIntList(int value, struct intList * oldList);
#define TABLE
#endif