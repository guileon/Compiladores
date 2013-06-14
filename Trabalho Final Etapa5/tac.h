#include <stdio.h>
#icnlude <stdlib.h>
#include "astree.h"
#include "table.h"





struct tac_s{
	int type;
	struct HNODE * target;
	struct HNODE * op1;
	struct HNODE * op2;
	struct tac_s * prev;
};

typedef struct tac_s tac;

tac * newTac(int type_, hashNode * target_, hashNode * op1_, hashNode op2_, tac_s * prev_);
tac * appendTac(tac * tac1, tac* tac2);
tac * generateTac(struct a_NODE * astree);