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
	    case OUTPUT:
            retvalue = appendTac(generateTac(astree->sons[0]), newTac(KW_OUTPUT, NULL, NULL, NULL, NULL));
            break;
        case INPUT:
            retvalue = newTac(KW_INPUT,astree->sons[0]->node, NULL, NULL, NULL);
            break;
		// LITERALS + IDENTIFIER
		case LIT_INTEGER:
		case LIT_CHAR:
		case LIT_TRUE:
		case LIT_FALSE:
		case TK_IDENTIFIER:
		case LIT_STRING:
			retvalue = newTac(astree->token, astree->node, NULL, NULL, NULL);
			break;
		// EXPRESSIONS
		case '&':
		case POINTER:
			aux[0] = generateTac(astree->sons[0]);
			retvalue = newTac(astree->token,newTemp(TEMP),aux[0]->target,NULL,aux[0]);
			break;
		case '+':
        	case '-':
        	case '*':
        	case '/':
        	case OR:
        	case AND:
		case '>':
		case '<':
		case LE:
		case GE:
		case EQ:
		case NE:
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac(astree->token,newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
		// CALLS
		case VECCALL:
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac(astree->token,newTemp(TEMP),aux[0]->target,aux[1]->target,auxResult);
			break;
		case ARGCALL:
			retvalue = appendTac(generateTac(astree->sons[0]),generateTac(astree->sons[1]));
			break;
		case FUNCALL:
			auxResult = generateTac(astree->sons[1]);
			retvalue = newTac(TAC_JMP,astree->sons[0]->node,NULL,NULL,auxResult);
			break;
		// DECLARATIONS
		case DECLARATION:
			aux[0] = generateTac(astree->sons[1]);
			aux[1] = generateTac(astree->sons[2]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac('=',aux[0]->target,aux[1]->target,NULL,auxResult);
			break;
		case DECLARATION_POINTER:
			aux[0] = generateTac(astree->sons[1]);
			aux[1] = generateTac(astree->sons[2]);
			auxResult = appendTac(aux[1],aux[0]);
			retvalue = newTac(TAC_INDIRECT_ATT,aux[0]->target,aux[1]->target,NULL,auxResult);
			break;
		case FUNC_DECLARATION:
			aux[0] = generateTac(astree->sons[3]->sons[0]);
			aux[1] = generateTac(astree->sons[3]->sons[1]);
			auxResult = appendTac(aux[0],aux[1]);
			retvalue = appendTac(newTac(TAC_LABEL,astree->sons[1]->node,NULL,NULL,NULL),auxResult);
			break;
		// FLOW CONTROL
		case IF_THEN:
			return tacIf(generateTac(astree->sons[0]),generateTac(astree->sons[1]),NULL);
			break;
		case IF_THEN_ELSE:
			return tacIf(generateTac(astree->sons[0]),generateTac(astree->sons[1]),generateTac(astree->sons[2]));
			break;
		case LOOP:
			return tacLoop(generateTac(astree->sons[0]),generateTac(astree->sons[1]));
			break;
		// ATTRIBUTION
		case '=':
			aux[0] = generateTac(astree->sons[0]);
			aux[1] = generateTac(astree->sons[1]);

			auxResult = appendTac(aux[1],aux[0]);

			retvalue = newTac('=',aux[0]->target,aux[1]->target,0,auxResult);
			break;
		// ETC
		case RETURN:
			auxResult = generateTac(astree->sons[0]);
			retvalue = newTac(RETURN,auxResult->target,NULL,NULL,auxResult);
			break;
		default:
			for(i=0 ; i<4 ; i++)
				childTac[i] = generateTac(astree->sons[i]);
			retvalue = appendTac(childTac[0], appendTac(childTac[1], appendTac(childTac[2], childTac[3])));

			break;
	}
		return retvalue;
	}
	return NULL;
}

tac * tacIf(tac * ifTac, tac * thenTac, tac * elseTac)
{
	tac * result;
	struct HNODE * testResult = ifTac->target;
	struct HNODE * elseLabel = newTemp(LABEL);

	tac * ifThen = appendTac(appendTac(ifTac,newTac(TAC_IFZ,elseLabel,testResult,NULL,NULL)),thenTac);

	if(elseTac == NULL)
	{
		result = appendTac(ifThen,newTac(TAC_LABEL,elseLabel,NULL,NULL,NULL));
	}
	else
	{
		result = appendTac( ifThen,appendTac( newTac( TAC_LABEL,elseLabel,NULL,NULL,NULL ),elseTac ) );
	}
	return result;
}

tac * tacLoop(tac * ifTac, tac * thenTac)
{
	tac * result;
	struct HNODE * testResult = ifTac->target;
	struct HNODE * beginLoop = newTemp(LABEL);
	struct HNODE * endLoop = newTemp(LABEL);


	tac * loop = appendTac(newTac(TAC_IFZ,endLoop,testResult,NULL,NULL),appendTac(thenTac,newTac(TAC_JMP,beginLoop,NULL,NULL,NULL)));

	result = appendTac(newTac(TAC_LABEL,beginLoop,NULL,NULL,NULL),appendTac(loop,newTac(TAC_LABEL,endLoop,NULL,NULL,NULL)));

	return result;
}

void printTac(tac * tac1)
{
	if(tac1)
	{
		printTac(tac1->prev);
		fprintf(stderr,"Tipo:");
		printTokens(tac1->type);
		fprintf(stderr, " | ");
		if(tac1->target)
            fprintf(stderr,"Target: %s |",tac1->target->value);
		if(tac1->op1)
			fprintf(stderr,"OP1: %s |",tac1->op1->value);
		if(tac1->op2)
			fprintf(stderr,"OP2: %s |",tac1->op2->value);
		printf("\n");
	}
}

