#include "tac.h"
#include "parser.tab.h"

tac * HELPgenerateTac(astreeNode * node);

void printTokenTac(int token)
{
	switch(token)
	{
		case TAC_MOV:	fprintf(stderr,"MOVE"); break; 
		case TAC_I_MOV:fprintf(stderr,"IMOV"); break;
		case TAC_LABEL:	fprintf(stderr,"LABL"); break;
		case TAC_JMP:		fprintf(stderr,"JUMP"); break;
		case TAC_IFZ:		fprintf(stderr,"JIFZ"); break;
		case TAC_CALL		:fprintf(stderr,"CALL"); break;
		case TAC_RETURN		:fprintf(stderr,"TRET"); break;
		case TAC_ARG		:fprintf(stderr,"TARG"); break;

		case TAC_ADD		:fprintf(stderr,"OADD"); break;
		case TAC_SUB		:fprintf(stderr,"OSUB"); break;
		case TAC_MUL		:fprintf(stderr,"OMUL"); break;
		case TAC_DIV		:fprintf(stderr,"ODIV"); break;
		case TAC_OR			:fprintf(stderr,"OPOR"); break;
		case TAC_AND		:fprintf(stderr,"OAND"); break;
		case TAC_EQ			:fprintf(stderr,"OPEQ"); break;
		case TAC_NE			:fprintf(stderr,"OPNE"); break;
		case TAC_GE			:fprintf(stderr,"OPGE"); break;
		case TAC_LE			:fprintf(stderr,"OPLE"); break;
		case TAC_GREATER	:fprintf(stderr,"OPGR"); break;
		case TAC_LESS		:fprintf(stderr,"OPLS"); break;

		case TAC_VEC_READ	:fprintf(stderr,"VREA"); break;
		case TAC_IDENTIFIER	:fprintf(stderr,"IDEN"); break;
		case TAC_INTEGER	:fprintf(stderr,"INTE"); break;
		case TAC_TRUE		:fprintf(stderr,"TRUE"); break;
		case TAC_FALSE		:fprintf(stderr,"FALS"); break;
		case TAC_STRING		:fprintf(stderr,"STRI"); break;
		case TAC_GET_ADDRESS:fprintf(stderr,"GETA"); break;
		case TAC_POINTER	:fprintf(stderr,"POIN"); break;
		case TAC_OUTPUT		:fprintf(stderr,"OUTP"); break;
		case TAC_INPUT		:fprintf(stderr,"INPU"); break;
		
		case TAC_BEGIN_FUNCTION:	fprintf(stderr,"BEGF");	break;
		case TAC_END_FUNCTION:		fprintf(stderr,"ENDF"); break;
	}
}

void printTac(tac * tac1)
{
	if(tac1->prev)
		printTac(tac1->prev);
	fprintf(stderr,"Type:  ");
	printTokenTac(tac1->type);
	fprintf(stderr," | ");
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

void printTacInverted(tac * tac1);
void printInverted(tac * tac1);

void printInverted(tac * tac1)
{
	tac * auxTac=NULL;
	if(tac1)
	{
		for(auxTac = tac1 ; auxTac->prev ; auxTac = auxTac->prev);
		printTacInverted(auxTac);
	}
}

void printTacInverted(tac * tac1)
{
	fprintf(stderr,"Type:  ");
	printTokenTac(tac1->type);
	fprintf(stderr," | ");
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
	
	
	if(tac1->next)
	{	
		printTacInverted(tac1->next);
	}
		
}

tac * createTac(int type_, hashNode * target_, hashNode * op1_, hashNode * op2_)
{
	tac * newTac = (tac *)calloc(1,sizeof(tac));
	newTac->type = type_;
	newTac->target = target_;
	newTac->op1 = op1_;
	newTac->op2 = op2_;
	newTac->prev = NULL;
	newTac->next = NULL;
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
			tac1->next = auxTac1;
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
		tacSons[0] = HELPgenerateTac(node->sons[1]);
		tacSons[1] = HELPgenerateTac(node->sons[2]);
		
		temp1 = tacSons[1]->target;
		if(node->sons[1] && node->sons[1]->hashPointer)
			newTac = createTac(TAC_MOV,node->sons[1]->hashPointer,temp1,NULL);
		else
			newTac = NULL;
			
			
		initializations = mergeTac(initializations,newTac);
		return mergeTac(tacSons[0],tacSons[1]);
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
		tacSons[0] = HELPgenerateTac(node->sons[1]);
		if(node->sons[3])
		{
			tacSons[1] = HELPgenerateTac(node->sons[3]);
		}
		
		if(tacSons[1])
		{
			temp1 = tacSons[1]->target;
		}
		
		if(node->sons[1] && node->sons[1]->hashPointer)
		{
			newTac = createTac(TAC_MOV,node->sons[1]->hashPointer,temp1,NULL);
		}
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
	
	if(node && node->sons[1] && node->sons[1]->hashPointer)
	{
		tacSons[0] = HELPgenerateTac(node->sons[1]);
		tacSons[1] = HELPgenerateTac(node->sons[2]);
		
		temp1 = tacSons[1]->target;
		newTac = createTac(TAC_I_MOV,node->sons[1]->hashPointer,temp1,NULL);
		
		initializations = mergeTac(initializations,mergeTac(createTac(TAC_CALLOC,node->sons[1]->hashPointer,NULL,NULL),newTac));
		
		return mergeTac(tacSons[0],tacSons[1]);
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
		tacSons[0] = HELPgenerateTac(node->sons[0]);
		temp1 = tacSons[0]->target;
		newTac = createTac(TAC_ARG,temp1,NULL,NULL);
		return mergeTac(tacSons[0],mergeTac(newTac,HELPgenerateTac(node->sons[1])));
	}
	else
		return NULL;
}

tac * vectorReadTac(astreeNode * node)
{
	tac * newTac = NULL;
	tac * tacSons[1];
	if(node && node->sons[0] && node->sons[0]->hashPointer)
	{
		tacSons[0] = HELPgenerateTac(node->sons[1]);
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

	if(node && node->sons[0] && node->sons[0]->hashPointer)
	{
		tacSons[0] = HELPgenerateTac(node->sons[1]);
		newTac = createTac(TAC_CALL,node->sons[0]->hashPointer,NULL,NULL);
		
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
		tacSons[0] = HELPgenerateTac(node->sons[0]);
		tacSons[1] = HELPgenerateTac(node->sons[1]);
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
		tacSons[0] = HELPgenerateTac(node->sons[0]);
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
	if(node && node->sons[0] && node->sons[0]->hashPointer)
	{
		tacSons[0] = HELPgenerateTac(node->sons[1]);
		newTac = createTac(TAC_MOV,node->sons[0]->hashPointer,tacSons[0]->target,NULL);
		return mergeTac(tacSons[0],newTac);
	}
	else
		return NULL;
}

tac * ifThenElse(astreeNode * node)
{
	hashNode * elseLabel = NULL;
	hashNode * endIfLabel = NULL;
	tac * tacSons[1];
	tac * tacThen=NULL;
	tac * tacElse=NULL;
	tac * newTac = NULL;
	tac * endIf = NULL;
	if(node)
	{
		endIfLabel = newLabel();
		tacThen = HELPgenerateTac(node->sons[1]);
		tacThen = mergeTac(tacThen,createTac(TAC_JMP,endIfLabel,NULL,NULL));
		tacSons[0] = HELPgenerateTac(node->sons[0]);
		elseLabel = newLabel();
		endIf = createTac(TAC_LABEL,endIfLabel,NULL,NULL);
		if(node->sons[2]) /* if then else */
		{
			tacElse = HELPgenerateTac(node->sons[2]);
			tacElse = mergeTac(createTac(TAC_LABEL,elseLabel,NULL,NULL),tacElse);
			tacElse = mergeTac(tacElse,endIf);
			newTac = createTac(TAC_IFZ,elseLabel,tacSons[0]->target,NULL);
			
		}
		else	/* if then */
		{
			tacElse = createTac(TAC_LABEL,elseLabel,NULL,NULL);
			tacElse = mergeTac(tacElse,endIf);
			newTac = createTac(TAC_IFZ,elseLabel,tacSons[0]->target,NULL);
		}
		return mergeTac(tacSons[0],mergeTac(mergeTac(newTac,tacThen),tacElse));
	}
	else
		return NULL;
}

tac * loop(astreeNode * node)
{
	tac * tacLoop = NULL;
	tac * newTac = NULL;
	tac * tacElse = NULL;
	tac * tacSons[2];
	tac * tacJmp = NULL;
	hashNode * loopLabel = NULL;
	hashNode * elseLabel = NULL;
	if(node)
	{
		tacSons[0] = HELPgenerateTac(node->sons[0]);
		tacSons[1] = HELPgenerateTac(node->sons[1]);
		loopLabel = newLabel();
		elseLabel = newLabel();
		tacLoop = createTac(TAC_LABEL,loopLabel,NULL,NULL);
		tacElse = createTac(TAC_LABEL,elseLabel,NULL,NULL);
		newTac = createTac(TAC_IFZ,elseLabel,tacSons[0]->target,NULL);
		tacJmp = createTac(TAC_JMP,loopLabel,NULL,NULL);
		return mergeTac(mergeTac(mergeTac(mergeTac(mergeTac(tacLoop,tacSons[0]),newTac),tacSons[1]),tacJmp),tacElse);
	}
	else
		return NULL;
	
}

tac * declareFunctionTac(astreeNode * node)
{
	return 
	mergeTac(
		mergeTac(
			mergeTac(
				createTac(TAC_LABEL,node->sons[1]->hashPointer,NULL,NULL),
				createTac(TAC_BEGIN_FUNCTION,node->sons[1]->hashPointer,NULL,NULL)),
				HELPgenerateTac(node->sons[4])),
				createTac(TAC_END_FUNCTION,node->sons[1]->hashPointer,NULL,NULL));
}

tac * outputList(astreeNode * node)
{
	hashNode * hashPt = NULL;
	tac * auxTac = NULL;
	
	if(node)
	{
		if(node->sons[0]->hashPointer)
		{
			hashPt = node->sons[0]->hashPointer;
			return mergeTac(createTac(TAC_OUTPUT,hashPt,NULL,NULL),HELPgenerateTac(node->sons[1]));
		}
		else
		{
			auxTac = HELPgenerateTac(node->sons[0]);
			hashPt = auxTac->target;
			return mergeTac(auxTac,mergeTac(createTac(TAC_OUTPUT,hashPt,NULL,NULL),HELPgenerateTac(node->sons[1])));
		}
	}
	else
		return NULL;
}

tac * pointerWriteTac(astreeNode * node)
{
	if(node)
	{
		tac * tacSons[1];
		tac * newTac = NULL;
		if(node && node->sons[0] && node->sons[0]->hashPointer)
		{
			tacSons[0] = HELPgenerateTac(node->sons[1]);
			newTac = createTac(TAC_I_MOV,node->sons[0]->hashPointer,tacSons[0]->target,NULL);
			return mergeTac(tacSons[0],newTac);
		}
		else
			return NULL;
	}
	else
		return NULL;
}

tac * HELPgenerateTac(astreeNode * node)
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
			case PROGRAM: 		newTac = mergeTac(HELPgenerateTac(node->sons[0]),HELPgenerateTac(node->sons[1]));		break;
			case LIT_LIST: 		break;

			/* palavras reservadas de tipo */
			case BOOL: 					break;			
			case WORD: 					break;		
			case BYTE: 					break;
			
			/* declarações */
			case DECLARATION_SCALAR:	newTac = declarationTacScalar(node);	break;
			case DECLARATION_POINTER: 	newTac = declarationTacPointer(node);	break;
			case DECLARATION_VECTOR: 	newTac = declarationTacVector(node);	break;
			case DECLARATION_FUNCTION: 	newTac = declareFunctionTac(node);break;
			case ARG_DECLARATION: 		break;

			/* expressões */
			case ARGCALL: 				newTac = argcallTac(node);	break;		
			case SCALAR_READ:			newTac = HELPgenerateTac(node->sons[0]);	break;	
			case VECTOR_READ: 			newTac = vectorReadTac(node);	break;	
			case GET_REFERENCE: 		newTac = unop(node,TAC_GET_ADDRESS);	break;
			case POINTER: 				newTac = unop(node,TAC_POINTER);	break;		
			case FUNCALL: 				newTac = tacFuncall(node);	break;		
			case PAR: 					newTac = HELPgenerateTac(node->sons[0]);	break;			
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
			case BLOCK: 				newTac = HELPgenerateTac(node->sons[0]);	break;
			case OUTPUT_LIST: 			newTac = outputList(node);				break;
			case SCALAR_WRITE: 			newTac = scalarWriteTac(node); break;
			case VECTOR_WRITE: 			break;
			case POINTER_WRITE: 		newTac = pointerWriteTac(node);	break;
			case INPUT: 				newTac = unop(node,TAC_INPUT);	break;
			case OUTPUT: 				newTac = HELPgenerateTac(node->sons[0]); break;
			case RETURN: 				newTac = unop(node,TAC_RETURN);	break;
			case IF_THEN: 				newTac = ifThenElse(node);	break;
			case IF_THEN_ELSE: 			newTac = ifThenElse(node);	break;
			case LOOP: 					newTac = loop(node);		break;
			case CMD_SEQ: 				newTac = mergeTac(HELPgenerateTac(node->sons[0]),HELPgenerateTac(node->sons[1]));			break;
			
			/* default? */
			default : break;
		}
	}
	return newTac;
}

tac * generateTac(astreeNode * node)
{
	initializations = NULL;
	return HELPgenerateTac(node);
}