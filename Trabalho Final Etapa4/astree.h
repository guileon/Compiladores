#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "table.h"
#include "parser.tab.h"
#include "tokens.h"
#define SYMBOL_UNDEFINED 0
#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_FLOATING 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

#define TOKEN int

struct a_NODE{
	TOKEN token;
	struct a_NODE ** sons;
	struct HNODE * node;
	int lineNumber;
};

char *filename;


void a_setFile(char* file);

struct a_NODE * newNode(
	TOKEN _token,
	struct a_NODE * son1,
	struct a_NODE * son2,
	struct a_NODE * son3,
	struct a_NODE * son4,
	struct HNODE * value,
	int lineN);

void printNode(struct a_NODE * node_p);
int isBoolean(struct a_NODE *node);
int isInt(struct a_NODE *node);
int isPt(struct a_NODE *node);
