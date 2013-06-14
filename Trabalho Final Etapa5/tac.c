#include "tac.h"

tac * newTac(int type_, hashNode * target_, hashNode * op1_, hashNode op2_, tac_s * prev_)
{
	tac * new = calloc(1,sizeof(tac));
	new->type = type_;
	new->target = target_;
	new->op1 = op1_;
	new->op2 = op2_;
	new->prev = prev_;
	return new;
}
tac * appendTac(tac * tac1, tac* tac2)
{
	tac * aux;
	for(aux = tac2 ; aux->prev ; aux = aux->prev);
	aux->prev = tac1;
	return tac2;
}

tac * generateTac(struct a_NODE * astree)
{
}