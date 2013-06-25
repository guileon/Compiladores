#include "tac.h"
#include "parser.tab.h"

void printTac(tac * tac1)
{
	if(tac1->prev)
		printTac(tac1->prev);
	fprintf(stderr,"Type %d |   ",tac1->type);
	fprintf(stderr,"Target: ");
	if(tac1->target)
		fprintf(stderr,"%s |",tac1->target->value);
	fprintf(stderr,"Op1: ");
	if(tac1->op1)
		fprintf(stderr,"%s |",tac1->op1->value);
	fprintf(stderr,"Op2: ");
	if(tac1->op2)
		fprintf(stderr,"%s |",tac1->op2->value);
		
	fprintf(stderr,"\n");
}

tac * createTac(int type_, hashNode * target_, hashNode * op1_, hashNode * op2_)
{
	tac * newTac = (tac *)calloc(1,sizeof(tac));
	newTac->type = type_;
	newTac->target = target_;
	newTac->op1 = op1_;
	newTac->op2 = op2_;
	newTac->prev = NULL;
	return newTac;
}

/*	a concatenação resulta na tac1 seguida da tac2 */
tac * mergeTac(tac * tac1, tac * tac2)
{
	tac * auxTac1 = NULL;

	if(tac2)
	{
		if(tac1)
		{
			for(auxTac1 = tac2 ; auxTac1->prev ; auxTac1 = auxTac1->prev);
			auxTac1->prev = tac1;
			return tac2;
		}
		else
		{
			return tac2;
		}
		
	}
	else if(tac1)
	{
		return tac1;
	}
	else
	{
		return NULL;
	}
}
/* cria a tac para declarações */
tac * declarationTacScalar(astreeNode * node)
{
	tac * newTac = NULL;	
	hashNode * temp1 = NULL;
	tac * tacSons[2];
	
	if(node)
	{
		tacSons[0] = generateTac(node->sons[1]);
		tacSons[1] = generateTac(node->sons[2]);
		
		temp1 = tacSons[1]->target;
		if(node->sons[1] && node->sons[1]->hashPointer)
			newTac = createTac(TAC_MOV,node->sons[1]->hashPointer,temp1,NULL);
		else
			newTac = NULL;
		return mergeTac(mergeTac(tacSons[0],tacSons[1]),newTac);
	}
	else
		return NULL;
}

tac * declarationTacVector(astreeNode * node)
{
	tac * newTac = NULL;	
	hashNode * temp1 = NULL;
	tac * tacSons[2];

	if(node)
	{
		tacSons[0] = generateTac(node->sons[1]);
		tacSons[1] = generateTac(node->sons[3]);
		
		temp1 = tacSons[1]->target;
		if(node->sons[1] && node->sons[1]->hashPointer)
			newTac = createTac(TAC_MOV,node->sons[1]->hashPointer,temp1,NULL);
		else
			newTac = NULL;
		return mergeTac(mergeTac(tacSons[0],tacSons[1]),newTac);
	}
	else
		return NULL;	
}

tac * declarationTacPointer(astreeNode * node)
{
	tac * newTac = NULL;	
	hashNode * temp1 = NULL;
	tac * tacSons[2];
	
	if(node)
	{
		tacSons[0] = generateTac(node->sons[1]);
		tacSons[1] = generateTac(node->sons[2]);
		
		temp1 = tacSons[1]->target;
		newTac = createTac(TAC_I_MOV,node->sons[1]->hashPointer,temp1,NULL);
		return mergeTac(mergeTac(tacSons[0],tacSons[1]),newTac);
	}
	else
		return NULL;
}

tac * argcallTac(astreeNode * node)
{
	tac * newTac = NULL;
	hashNode * temp1 = NULL;
	tac * tacSons[1];
	if(node)
	{		
		tacSons[0] = generateTac(node->sons[0]);
		temp1 = tacSons[0]->target;
		newTac = createTac(TAC_ARG,temp1,NULL,NULL);
		return mergeTac(newTac,generateTac(node->sons[1]));
	}
	else
		return NULL;
}

tac * vectorReadTac(astreeNode * node)
{
	tac * newTac = NULL;
	tac * tacSons[1];
	if(node)
	{
		tacSons[0] = generateTac(node->sons[1]);
		newTac = createTac(TAC_VEC_READ,newTemp(),node->sons[0]->hashPointer,tacSons[0]->target);
		return newTac;
	}
	else
		return NULL;
}

tac * tacFuncall(astreeNode * node)
{
	
	tac * tacSons[1];
	tac * newTac = NULL;

	if(node)
	{
		
		tacSons[0] = generateTac(node->sons[1]);
		newTac = createTac(TAC_CALL,node->sons[0]->hashPointer,tacSons[0]->target,NULL);
		return mergeTac(tacSons[0],newTac);
	}
	else
		return NULL;
}

tac * binop(astreeNode * node, int type)
{
	tac * tacSons[2];
	tac * newTac = NULL;
	if(node)
	{
		tacSons[0] = generateTac(node->sons[0]);
		tacSons[1] = generateTac(node->sons[1]);
		newTac = createTac(type,newTemp(),tacSons[0]->target,tacSons[1]->target);
		return mergeTac(mergeTac(tacSons[0],tacSons[1]),newTac);
	}
	else
		return NULL;	
}

tac * unop(astreeNode * node, int type)
{
	tac * tacSons[1];
	tac * newTac = NULL;
	if(node)
	{
		tacSons[0] = generateTac(node->sons[0]);
		newTac = createTac(type,newTemp(),tacSons[0]->target,NULL);
		return mergeTac(tacSons[0],newTac);
	}
	else
		return NULL;
}
tac * scalarWriteTac(astreeNode * node)
{
	tac * tacSons[1];
	tac * newTac = NULL;
	if(node)
	{
		tacSons[0] = generateTac(node->sons[1]);
		newTac = createTac(TAC_MOV,node->sons[0]->hashPointer,tacSons[0]->target,NULL);
		return mergeTac(tacSons[0],newTac);
	}
	else
		return NULL;
}

tac * ifThenElse(astreeNode * node)
{
	hashNode * elseLabel = NULL;
	tac * tacSons[1];
	tac * tacThen=NULL;
	tac * tacElse=NULL;
	tac * newTac = NULL;
	if(node)
	{
		tacThen = generateTac(node->sons[1]);
		tacSons[0] = generateTac(node->sons[0]);
		elseLabel = newLabel();
		
		if(node->sons[2]) /* if then else */
		{
			tacElse = generateTac(node->sons[2]);
			tacElse = mergeTac(createTac(TAC_LABEL,elseLabel,NULL,NULL),tacElse);
			newTac = createTac(TAC_IFZ,elseLabel,tacSons[0]->target,NULL);
			return mergeTac(mergeTac(newTac,tacThen),tacElse);
			
		}
		else	/* if then */
		{
			tacElse = createTac(TAC_LABEL,elseLabel,NULL,NULL);
			newTac = createTac(TAC_IFZ,elseLabel,tacSons[0]->target,NULL);
			return mergeTac(mergeTac(newTac,tacThen),tacElse);
		}
	}
	else
		return NULL;
}

tac * loop(astreeNode * node)
{
	tac * tacLoop = NULL;
	tac * newTac = NULL;
	tac * tacElse = NULL;
	tac * tacSons[1];
	tac * tacJmp = NULL;
	hashNode * loopLabel = NULL;
	hashNode * elseLabel = NULL;
	if(node)
	{
		tacSons[0] = generateTac(node->sons[0]);
		loopLabel = newLabel();
		elseLabel = newLabel();
		tacLoop = createTac(TAC_LABEL,loopLabel,NULL,NULL);
		tacElse = createTac(TAC_LABEL,elseLabel,NULL,NULL);
		newTac = createTac(TAC_IFZ,elseLabel,tacSons[0]->target,NULL);
		tacJmp = createTac(TAC_JMP,loopLabel,NULL,NULL);
		return mergeTac(mergeTac(mergeTac(mergeTac(tacLoop,newTac),tacSons[0]),tacJmp),tacElse);
	}
	else
		return NULL;
	
}

tac * generateTac(astreeNode * node)
{
	tac * newTac = NULL;	

	/* garantia de que não vai tentar imprimir nodo NULL */
	if(node)
	{
		switch(node->type)
		{
			/* literais e identificadores */
			case TK_IDENTIFIER: newTac = createTac(TAC_IDENTIFIER,node->hashPointer,NULL,NULL); 	break;
			case LIT_INTEGER: 	newTac = createTac(TAC_INTEGER,node->hashPointer,NULL,NULL);		break;
			case LIT_TRUE: 		newTac = createTac(TAC_TRUE,node->hashPointer,NULL,NULL);			break;
			case LIT_FALSE: 	newTac = createTac(TAC_FALSE,node->hashPointer,NULL,NULL);			break;
			case LIT_STRING: 	newTac = createTac(TAC_STRING,node->hashPointer,NULL,NULL);			break;
			case LIT_CHAR: 		newTac = createTac(TAC_INTEGER,node->hashPointer,NULL,NULL);		break;
			
			/* listas */
			case PROGRAM: 		newTac = mergeTac(generateTac(node->sons[0]),generateTac(node->sons[1]));		break;
			case LIT_LIST: 				break;

			/* palavras reservadas de tipo */
			case BOOL: 					break;			
			case WORD: 					break;		
			case BYTE: 					break;
			
			/* declarações */
			case DECLARATION_SCALAR:	newTac = declarationTacScalar(node);	break;
			case DECLARATION_POINTER: 	newTac = declarationTacPointer(node);	break;
			case DECLARATION_VECTOR: 	newTac = declarationTacVector(node);	break;
			case DECLARATION_FUNCTION: 	newTac = mergeTac(createTac(TAC_LABEL,node->sons[1]->hashPointer,NULL,NULL),generateTac(node->sons[4]));break;
			case ARG_DECLARATION: 		break;

			/* expressões */
			case ARGCALL: 				newTac = argcallTac(node);	break;		
			case SCALAR_READ:			newTac = generateTac(node->sons[0]);	break;	
			case VECTOR_READ: 			newTac = vectorReadTac(node);	break;	
			case GET_REFERENCE: 		newTac = unop(node,TAC_GET_ADDRESS);	break;
			case POINTER: 				newTac = unop(node,TAC_POINTER);	break;		
			case FUNCALL: 				newTac = tacFuncall(node);	break;		
			case PAR: 					newTac = generateTac(node->sons[0]);	break;			
			case ADD: 					newTac = binop(node,TAC_ADD);	break;			
			case SUB: 					newTac = binop(node,TAC_SUB);	break;			
			case MUL: 					newTac = binop(node,TAC_MUL);	break;			
			case DIV: 					newTac = binop(node,TAC_DIV);	break;			
			case OR: 					newTac = binop(node,TAC_OR);	break;			
			case AND: 					newTac = binop(node,TAC_AND);	break;			
			case LE: 					newTac = binop(node,TAC_LE);	break;			
			case GE: 					newTac = binop(node,TAC_GE);	break;			
			case EQ: 					newTac = binop(node,TAC_EQ);	break;			
			case NE: 					newTac = binop(node,TAC_NE);	break;			
			case GREATER: 				newTac = binop(node,TAC_GREATER);	break;		
			case LESS: 					newTac = binop(node,TAC_LESS);	break;
				
			/* CMD e CMD_SEQ */	
			case BLOCK: 				newTac = generateTac(node->sons[0]);	break;
			case OUTPUT_LIST: 			newTac = mergeTac(generateTac(node->sons[0]),generateTac(node->sons[1]));	break;
			case SCALAR_WRITE: 			newTac = scalarWriteTac(node); break;
			case VECTOR_WRITE: 			break;
			case POINTER_WRITE: 		break;
			case INPUT: 				break;
			case OUTPUT: 				break;
			case RETURN: 				newTac = unop(node,TAC_RETURN);	break;
			case IF_THEN: 				newTac = ifThenElse(node);	break;
			case IF_THEN_ELSE: 			newTac = ifThenElse(node);	break;
			case LOOP: 					newTac = loop(node);		break;
			case CMD_SEQ: 				newTac = mergeTac(generateTac(node->sons[0]),generateTac(node->sons[1]));			break;
			
			/* default? */
			default : break;
		}
	}
	
	return newTac;
}