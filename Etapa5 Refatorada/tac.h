#ifndef TAC
#define TAC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "hash.h"
#include "test.h"

struct tac_s;
struct tac_s{
	int type;
	hashNode * target;
	hashNode * op1;
	hashNode * op2;
	struct tac_s * prev;
};

typedef struct tac_s tac;

void printTac(tac * tacToBePrinted);
tac * generateTac(astreeNode * node);




#endif