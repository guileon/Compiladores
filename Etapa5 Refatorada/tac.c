#include "tac.h"

void printTac(int tac1)
{
	switch(tac1)
	{
		
	}
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

tac * generateTac(astreeNode * node)
{
	tac * newTac = (tac *) calloc(1,sizeof(tac));
	newTac = NULL;

	/* garantia de que não vai tentar imprimir nodo NULL */
	if(node)
	{
		switch(node->type)
		{
			/* literais e identificadores */
			case TK_IDENTIFIER: break;
			case LIT_INTEGER: 	break;
			case LIT_TRUE: 		break;
			case LIT_FALSE: 	break;
			case LIT_STRING: 	break;
			case LIT_CHAR: 		break;
			
			/* listas */
			case PROGRAM: 				break;
			case LIT_LIST: 				break;

			/* palavras reservadas de tipo */
			case BOOL: 					break;			
			case WORD: 					break;		
			case BYTE: 					break;
			
			/* declarações */
			case DECLARATION_SCALAR: 	break;
			case DECLARATION_POINTER: 	break;
			case DECLARATION_VECTOR: 	break;
			case DECLARATION_FUNCTION: 	break;
			case ARG_DECLARATION: 		break;

			/* expressões */
			case ARGCALL: 				break;		
			case SCALAR_READ:			break;	
			case VECTOR_READ: 			break;	
			case GET_REFERENCE: 		break;
			case POINTER: 				break;		
			case FUNCALL: 				break;		
			case PAR: 					break;			
			case ADD: 					break;			
			case SUB: 					break;			
			case MUL: 					break;			
			case DIV: 					break;			
			case OR: 					break;			
			case AND: 					break;			
			case LE: 					break;			
			case GE: 					break;			
			case EQ: 					break;			
			case NE: 					break;			
			case GREATER: 				break;		
			case LESS: 					break;
				
			/* CMD e CMD_SEQ */	
			case BLOCK: 				break;
			case OUTPUT_LIST: 			break;
			case SCALAR_WRITE: 			break;
			case VECTOR_WRITE: 			break;
			case POINTER_WRITE: 		break;
			case INPUT: 				break;
			case OUTPUT: 				break;
			case RETURN: 				break;
			case IF_THEN: 				break;
			case IF_THEN_ELSE: 			break;
			case LOOP: 					break;
			case CMD_SEQ: 				break;
			
			/* default? */
			default : break;
		}
	}
	
	return newTac;
}