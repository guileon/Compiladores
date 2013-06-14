#include "tac.h"

tac * newTac(int type_, hashNode * target_, hashNode * op1_, hashNode op2_, tac_s * prev_)
{
	tac * new = (tac*)calloc(1,sizeof(tac));
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
	if(astree){
	tac * aux[4];
	tac * auxResult;
	switch(astree->token)
	{
		case LITERAL: 
			return newTac(LITERAL, astree->node, 0, 0, 0);
			break;
		case '+': 
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			return newTac('+',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
		default:
			break;
	}
	}
}