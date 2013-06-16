#include "tac.h"

tac * newTac(int type_, hashNode * target_, hashNode * op1_, hashNode * op2_, tac * prev_)
{
	tac * new = (tac*)calloc(1,sizeof(tac));
	new->type = type_;
	new->target = target_;
	new->op1 = op1_;
	new->op2 = op2_;
	new->prev = prev_;\
	return new;
}
tac * appendTac(tac * tac1, tac* tac2)
{
	tac * aux;
	if(tac1 == NULL)
        return tac2;
    if(tac2 == NULL)
        return tac1;
	for(aux = tac2 ; aux->prev ; aux = aux->prev);
        aux->prev = tac1;
	return tac2;
}

tac * generateTac(struct a_NODE * astree)
{
	if(astree){
	tac * retvalue;
	tac * aux[4];
	tac * auxResult;
	struct HNODE * auxNode;
	int i;
	switch(astree->token)
	{
		case LIT_INTEGER:
			printf("LIT_INTEGER: %s\n",astree->node->value);
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		case '+':
			printf("+\n");
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('+',auxNode,aux[0]->target,aux[1]->target,auxResult);
			break;
        case '-':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('-',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
        case '*':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('*',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
        case '/':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('/',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
		default:
			
			for(i=0 ; i<4 ; i++)
				generateTac(astree->sons[i]);
			retvalue = appendTac(generateTac(astree->sons[0]),appendTac(generateTac(astree->sons[1]),appendTac(generateTac(astree->sons[2]),generateTac(astree->sons[3]))));
			break;
	}
		return retvalue;
	}
}


void printTac(tac * tac1)
{
	if(tac1)
	{
		printTac(tac1->prev);
		printf("Tipo: %d, Target: %s, Op1: %s, Op2: %s\n",tac1->type, tac1->target->value, tac1->op1->value, tac1->op2->value);
	}
}

