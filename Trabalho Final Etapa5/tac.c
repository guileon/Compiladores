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
    tac * childTac[4];
	if(astree){
	tac * retvalue;
	tac * aux[4];
	tac * auxResult;
	struct HNODE * auxNode;
	int i;
	switch(astree->token)
	{
		// LITERALS + IDENTIFIER
		case LIT_INTEGER:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		case LIT_CHAR:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		case LIT_TRUE:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		case LIT_FALSE:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		case TK_IDENTIFIER:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		case LIT_STRING:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		// EXPRESSIONS
		case '=':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('=',aux[0]->target,aux[1]->target,0,auxResult);
		case '+':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			//auxNode = newTemp(TEMP);
			retvalue = newTac('+',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			//printTac(retvalue);
			break;
        case '-':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('-',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
        case '*':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('*',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
        case '/':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('/',newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
        case OR:
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac(OR,newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
        case AND:
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac(AND,newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
		// DECLARATIONS
		case DECLARATION:
			aux[0] = generateTac(astree->sons[1]);
			aux[1] = generateTac(astree->sons[2]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('=',aux[0]->target,aux[1]->target,0,auxResult);
			break;
		// FLOW CONTROL
		// ATTRIBUTION
		// ETC
		default:
			for(i=0 ; i<4 ; i++)
				childTac[i] = generateTac(astree->sons[i]);
			//retvalue = appendTac(generateTac(astree->sons[0]),appendTac(generateTac(astree->sons[1]),appendTac(generateTac(astree->sons[2]),generateTac(astree->sons[3]))));
			retvalue = appendTac(childTac[0], appendTac(childTac[1], appendTac(childTac[2], childTac[3])));

			break;
	}
		return retvalue;
	}
	return NULL;
}


void printTac(tac * tac1)
{
	if(tac1)
	{
		printTac(tac1->prev);
		fprintf(stderr,"Tipo: %c |",tac1->type);
		if(tac1->target)
            fprintf(stderr,"Target: %s |",tac1->target->value);
		if(tac1->op1)
			fprintf(stderr,"OP1: %s |",tac1->op1->value);
		if(tac1->op2)
			fprintf(stderr,"OP2: %s |",tac1->op2->value);
		printf("\n");
	}
}

