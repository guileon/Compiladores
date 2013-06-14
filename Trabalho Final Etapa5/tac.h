#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "table.h"
#include "tokens.h"
#include "parser.tab.h"
#include "parser.tab.h"




struct tac_s{
	int type;
	hashNode * target;
	hashNode * op1;
	hashNode * op2;
	struct tac_s * prev;
};

typedef struct tac_s tac;

tac * newTac(int type_, hashNode * target_, hashNode * op1_, hashNode * op2_, tac * prev_);
tac * appendTac(tac * tac1, tac* tac2);
tac * generateTac(struct a_NODE * astree);
void printTac(tac * tac1);