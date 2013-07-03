#include "semantic.h"
#include "parser.tab.h"
/* funções auxiliares para semantic.c */
int isIdentifierInteger(astreeNode * node);
int isListInteger(astreeNode * node);
int isInteger(astreeNode * node);
int isIdentifierBoolean(astreeNode * node);
int isListBoolean(astreeNode * node);
int isBoolean(astreeNode * node);
void declareFunctions(astreeNode * node);
void evaluate(astreeNode * node);
int isPointerOperation(astreeNode * node);

hashNode * currentFunction = NULL;


/* funções auxiliares de avaliação de inteiros */
int isIdentifierInteger(astreeNode * node)
{
	if(node && node->type == TK_IDENTIFIER)
	{
		if(node->hashPointer && node->hashPointer->dataType == T_INTEGER && node->hashPointer->type != ID_POINTER) 
			return TRUE; 
		else 
			return FALSE; 
	}
	else
	{
		return FALSE;
	}
}

int isListInteger(astreeNode * node)
{
	if(node && node->type == LIT_LIST)
	{
		if(isInteger(node->sons[0]) && isListInteger(node->sons[1]))
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/* função para descobrir se um nodo retorna um valor inteiro */
int isInteger(astreeNode * node)
{
	int returnValue = FALSE;
	if(node)
	{
		switch(node->type)
		{
			/* literais e identificadores */
			case TK_IDENTIFIER: returnValue = isIdentifierInteger(node);break;
			case LIT_INTEGER:	returnValue = TRUE; 	 				break;
			case LIT_TRUE: 		returnValue = FALSE;					break;
			case LIT_FALSE: 	returnValue = FALSE;					break;
			case LIT_STRING: 	returnValue = FALSE;					break;
			case LIT_CHAR: 		returnValue = TRUE;						break;
			
			/* listas */
			case PROGRAM: 		returnValue = FALSE;					break;	
			case LIT_LIST: 		returnValue = isListInteger(node);		break;

			/* palavras reservadas de tipo */
			case BOOL: 			returnValue = FALSE;		break;				
			case WORD: 			returnValue = FALSE;		break;				
			case BYTE: 			returnValue = FALSE;		break;
			
			/* declarações */
			case DECLARATION_SCALAR: 	returnValue = FALSE;	break;	
			case DECLARATION_POINTER: 	returnValue = FALSE;	break;	
			case DECLARATION_VECTOR: 	returnValue = FALSE;	break;	
			case DECLARATION_FUNCTION:	returnValue = FALSE; 	break;
			case ARG_DECLARATION: 		returnValue = FALSE;	break;	

			/* expressões */
			case ARGCALL: 			returnValue = FALSE;	break;				
			case SCALAR_READ:		returnValue = isInteger(node->sons[0]);	break;			
			case VECTOR_READ: 		returnValue = isInteger(node->sons[0]);	break;			
			case GET_REFERENCE: 	returnValue = FALSE;	break;		
			case POINTER: 			returnValue = TRUE;		break;				
			case FUNCALL: 			returnValue = isInteger(node->sons[0]);	break;				
			case PAR: 				returnValue = isInteger(node->sons[0]);	break;					
			case ADD: 				returnValue = TRUE;		break;					
			case SUB: 				returnValue = TRUE;		break;					
			case MUL: 				returnValue = TRUE;		break;					
			case DIV: 				returnValue = TRUE;		break;					
			case OR: 				returnValue = FALSE;	break;					
			case AND: 				returnValue = FALSE;	break;					
			case LE: 				returnValue = FALSE;	break;					
			case GE: 				returnValue = FALSE;	break;					
			case EQ: 				returnValue = FALSE;	break;					
			case NE: 				returnValue = FALSE;	break;					
			case GREATER: 			returnValue = FALSE;	break;				
			case LESS: 				returnValue = FALSE;	break;
				
			/* CMD e CMD_SEQ */	
			case BLOCK: 			returnValue = FALSE;	break;				
			case OUTPUT_LIST: 		returnValue = FALSE;	break;			
			case SCALAR_WRITE: 		returnValue = isInteger(node->sons[0]);	break;		
			case VECTOR_WRITE: 		returnValue = isInteger(node->sons[0]);	break;		
			case POINTER_WRITE: 	returnValue = TRUE;		break;		
			case INPUT: 			returnValue = FALSE;	break;				
			case OUTPUT: 			returnValue = FALSE;	break;				
			case RETURN: 			returnValue = FALSE;	break;				
			case IF_THEN: 			returnValue = FALSE;	break;				
			case IF_THEN_ELSE: 		returnValue = FALSE;	break;		
			case LOOP: 				returnValue = FALSE;	break;
			case CMD_SEQ: 			returnValue = FALSE;	break;
			
			/* default? */
			default : break;
		}
	}
	else
	{
		returnValue = FALSE;
	}
	return returnValue;
}

/* funções auxiliares de avaliação de booleanos */
int isIdentifierBoolean(astreeNode * node)
{
	if(node && node->type == TK_IDENTIFIER)
	{
		if(node->hashPointer && node->hashPointer->dataType == T_BOOLEAN) 
			return TRUE; 
		else 
			return FALSE; 
	}
	else
	{
		return FALSE;
	}
}

int isListBoolean(astreeNode * node)
{
	if(node && node->type == LIT_LIST)
	{
		if(isBoolean(node->sons[0]) && isListBoolean(node->sons[1]))
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		return TRUE;
	}
}


/* função para descobrir se um nodo retorna um valor booleano */
int isBoolean(astreeNode * node)
{
	int returnValue = FALSE;
	if(node)
	{
		switch(node->type)
		{
			/* literais e identificadores */
			case TK_IDENTIFIER: returnValue = isIdentifierBoolean(node);break;
			case LIT_INTEGER:	returnValue = FALSE; 	 				break;
			case LIT_TRUE: 		returnValue = TRUE;					break;
			case LIT_FALSE: 	returnValue = TRUE;					break;
			case LIT_STRING: 	returnValue = FALSE;					break;
			case LIT_CHAR: 		returnValue = FALSE;						break;
			
			/* listas */
			case PROGRAM: 		returnValue = FALSE;					break;	
			case LIT_LIST: 		returnValue = isListBoolean(node);		break;

			/* palavras reservadas de tipo */
			case BOOL: 			returnValue = FALSE;		break;				
			case WORD: 			returnValue = FALSE;		break;				
			case BYTE: 			returnValue = FALSE;		break;
			
			/* declarações */
			case DECLARATION_SCALAR: 	returnValue = FALSE;	break;	
			case DECLARATION_POINTER: 	returnValue = FALSE;	break;	
			case DECLARATION_VECTOR: 	returnValue = FALSE;	break;	
			case DECLARATION_FUNCTION:	returnValue = FALSE; 	break;
			case ARG_DECLARATION: 		returnValue = FALSE;	break;	

			/* expressões */
			case ARGCALL: 			returnValue = FALSE;	break;				
			case SCALAR_READ:		returnValue = isBoolean(node->sons[0]);	break;			
			case VECTOR_READ: 		returnValue = isBoolean(node->sons[0]);	break;			
			case GET_REFERENCE: 	returnValue = FALSE;	break;		
			case POINTER: 			returnValue = TRUE;		break;				
			case FUNCALL: 			returnValue = isBoolean(node->sons[0]);	break;				
			case PAR: 				returnValue = isBoolean(node->sons[0]);	break;					
			case ADD: 				returnValue = FALSE;		break;					
			case SUB: 				returnValue = FALSE;		break;					
			case MUL: 				returnValue = FALSE;		break;					
			case DIV: 				returnValue = FALSE;		break;					
			case OR: 				returnValue = TRUE;	break;					
			case AND: 				returnValue = TRUE;	break;					
			case LE: 				returnValue = TRUE;	break;					
			case GE: 				returnValue = TRUE;	break;					
			case EQ: 				returnValue = TRUE;	break;					
			case NE: 				returnValue = TRUE;	break;					
			case GREATER: 			returnValue = TRUE;	break;				
			case LESS: 				returnValue = TRUE;	break;
				
			/* CMD e CMD_SEQ */	
			case BLOCK: 			returnValue = FALSE;	break;				
			case OUTPUT_LIST: 		returnValue = FALSE;	break;			
			case SCALAR_WRITE: 		returnValue = isBoolean(node->sons[0]);	break;		
			case VECTOR_WRITE: 		returnValue = isBoolean(node->sons[0]);	break;		
			case POINTER_WRITE: 	returnValue = TRUE;		break;		
			case INPUT: 			returnValue = FALSE;	break;				
			case OUTPUT: 			returnValue = FALSE;	break;				
			case RETURN: 			returnValue = FALSE;	break;				
			case IF_THEN: 			returnValue = FALSE;	break;				
			case IF_THEN_ELSE: 		returnValue = FALSE;	break;		
			case LOOP: 				returnValue = FALSE;	break;
			case CMD_SEQ: 			returnValue = FALSE;	break;
			
			/* default? */
			default : break;
		}
	}
	else
	{
		returnValue = FALSE;
	}
	return returnValue;
}

void semanticError(char * msg, char* name, int lineNumber)
{
	fprintf(stderr,"WARNING: semantic error on line %d:",lineNumber);
	fprintf(stderr,"%s",msg);
	fprintf(stderr,"%s\n",name);
	numberOfErrors++;
}

/* função de adicionar uma função na hash */
void addFunctionToHash(astreeNode * node)
{
	intList * intListAux = NULL;
	astreeNode * astreeNodeAux = NULL;

	if(node)
	{
		if(node->sons[0] && node->sons[1] && node->sons[1]->hashPointer)
		{
			switch(node->sons[0]->type)
			{
				case WORD: node->sons[1]->hashPointer->dataType = T_INTEGER; 	break;
				case BOOL: node->sons[1]->hashPointer->dataType = T_BOOLEAN;	break;
				case BYTE: node->sons[1]->hashPointer->dataType = T_INTEGER;	break;		
			}
			
			if(node->sons[1]->hashPointer->type != SYMBOL_IDENTIFIER)
				semanticError("Function already declared:",node->sons[1]->hashPointer->value,node->lineNumber);
				
			node->sons[1]->hashPointer->type = ID_FUNCTION;
			
			if(node->sons[2])
			{
				intListAux = node->sons[1]->hashPointer->functionArguments;
				for(astreeNodeAux = node->sons[2] ; astreeNodeAux ; astreeNodeAux = astreeNodeAux->sons[2])
				{
					intListAux = insertIntList(astreeNodeAux->sons[0]->type, intListAux);
				}
				
				node->sons[1]->hashPointer->functionArguments = intListAux;
			}
		}
	}
}

void declareFunctions(astreeNode * node)
{
	if(node)
	{
		switch(node->type)
		{
			case DECLARATION_FUNCTION: addFunctionToHash(node);									break;
			case PROGRAM: declareFunctions(node->sons[0]);	declareFunctions(node->sons[1]);	break;
			default: break;
			
		}
	}
}

void declareScalar(astreeNode * node)
{
	if(node)
	{
		if(node && node->sons[1] && node->sons[1]->hashPointer && node->sons[1]->hashPointer->type != SYMBOL_IDENTIFIER)
		{
			semanticError("Identifier already declared:",node->sons[1]->hashPointer->value,node->lineNumber);
		}
		else if(node && node->sons[1] && node->sons[1]->hashPointer)
		{
			node->sons[1]->hashPointer->type = ID_SCALAR;
			switch(node->sons[0]->type)
			{
				case WORD:	
					node->sons[1]->hashPointer->dataType = T_INTEGER; 
					if(!isInteger(node->sons[2])) 
						semanticError("Scalar initialized wrong, should be integer:",node->sons[1]->hashPointer->value,node->lineNumber);
						break;
				case BYTE: 	
					node->sons[1]->hashPointer->dataType = T_INTEGER; 
					if(!isInteger(node->sons[2])) 
						semanticError("Scalar initialized wrong, should be integer:",node->sons[1]->hashPointer->value,node->lineNumber);
						break;
				case BOOL:	node->sons[1]->hashPointer->dataType = T_BOOLEAN; 
					if(!isBoolean(node->sons[2])) 
						semanticError("Scalar initialized wrong, should be boolean:",node->sons[1]->hashPointer->value,node->lineNumber);
						break;
			}
		}
	}

}
void declarePointer(astreeNode * node)
{
	if(node)
	{
		if(node && node->sons[1] && node->sons[1]->hashPointer && node->sons[1]->hashPointer->type != SYMBOL_IDENTIFIER)
		{
			semanticError("Identifier already declared:",node->sons[1]->hashPointer->value,node->lineNumber);
		}
		else if(node && node->sons[1] && node->sons[1]->hashPointer)
		{
			node->sons[1]->hashPointer->type = ID_POINTER;
			switch(node->sons[0]->type)
			{
				case WORD:	
					node->sons[1]->hashPointer->dataType = T_INTEGER; 
					if(!isInteger(node->sons[2])) 
						semanticError("Scalar initialized wrong, should be integer:",node->sons[1]->hashPointer->value,node->lineNumber);
						break;
				case BYTE: 	node->sons[1]->hashPointer->dataType = T_INTEGER;	break;
					node->sons[1]->hashPointer->dataType = T_INTEGER; 
					if(!isInteger(node->sons[2])) 
						semanticError("Scalar initialized wrong, should be integer:",node->sons[1]->hashPointer->value,node->lineNumber);
						break;
				case BOOL:	node->sons[1]->hashPointer->dataType = T_BOOLEAN; 
					if(!isBoolean(node->sons[2])) 
						semanticError("Scalar initialized wrong, should be boolean:",node->sons[1]->hashPointer->value,node->lineNumber);
						break;
			}
		}
	}
}
void declareVector(astreeNode * node)
{
	if(node)
	{
		if(node && node->sons[1] && node->sons[1]->hashPointer && node->sons[1]->hashPointer->type != SYMBOL_IDENTIFIER)
		{
			semanticError("Identifier already declared:",node->sons[1]->hashPointer->value,node->lineNumber);
		}
		else if(node && node->sons[1] && node->sons[1]->hashPointer)
		{
			node->sons[1]->hashPointer->type = ID_VECTOR;
			if(!isInteger(node->sons[2]))
				semanticError("Vector index is not integer:",node->sons[1]->hashPointer->value,node->lineNumber);
			if(node->sons[3])
			{
				switch(node->sons[0]->type)
				{
					case WORD:	
						node->sons[1]->hashPointer->dataType = T_INTEGER; 
						if(!isInteger(node->sons[3])) 
							semanticError("Vector initialized wrong, should be integer:",node->sons[1]->hashPointer->value,node->lineNumber);
							break;
					case BYTE: 	node->sons[1]->hashPointer->dataType = T_INTEGER;	break;
						node->sons[1]->hashPointer->dataType = T_INTEGER; 
						if(!isInteger(node->sons[3])) 
							semanticError("Vector initialized wrong, should be integer:",node->sons[1]->hashPointer->value,node->lineNumber);
							break;
					case BOOL:	node->sons[1]->hashPointer->dataType = T_BOOLEAN; 
						if(!isBoolean(node->sons[3])) 
							semanticError("Vector initialized wrong, should be boolean:",node->sons[1]->hashPointer->value,node->lineNumber);
							break;
				}
			}
		}
	}
}
int isDeclared(hashNode * node)
{
	if(node && node->type == SYMBOL_IDENTIFIER)
		return FALSE;
	else
		return TRUE;
}
int isScalar(astreeNode * node)
{
	if(node)
	{
		if(!isDeclared(node->hashPointer))
			semanticError("Variable not declared:",node->hashPointer->value,node->lineNumber);
		if(node->hashPointer->type!=ID_SCALAR)
			return FALSE;
		else return TRUE;
	}
	else
		return FALSE;
}
int isPointer(astreeNode * node)
{
	if(node)
	{
		if(!isDeclared(node->hashPointer))
			semanticError("Variable not declared:",node->hashPointer->value,node->lineNumber);
		if(node->hashPointer->type!=ID_POINTER)
			return FALSE;
		else return TRUE;
	}
	else
		return FALSE;
}
/* para saber se o nodo retorna um ponteiro por uma operação de ponteiro */
int isPointerOperation(astreeNode * node)
{
	if(node)
	{
		if(node->type == ADD)
		{
			if(isPointer(node->sons[0]))
			{
				if(isInteger(node->sons[1]))
					return TRUE;
				else
					return FALSE;
			}
			else if(isPointer(node->sons[1]))
			{
				if(isInteger(node->sons[0]))
					return TRUE;
				else
					return FALSE;
			}
			else
				return FALSE;
		}	
		else if(node->type == GET_REFERENCE)
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	return FALSE;
}

int isVector(astreeNode * node)
{
	if(node)
	{
		if(!isDeclared(node->hashPointer))
			semanticError("Variable not declared:",node->hashPointer->value,node->lineNumber);
		if(node->hashPointer->type!=ID_VECTOR)
			return FALSE;
		else return TRUE;
	}
	else
		return FALSE;
}
int isFunction(astreeNode * node)
{
	if(node)
	{
		if(!isDeclared(node->hashPointer))
			semanticError("Variable not declared:",node->hashPointer->value,node->lineNumber);
		if(node->hashPointer->type!=ID_FUNCTION)
			return FALSE;
		else return TRUE;
	}
	else
		return FALSE;
}
void funcallTest(astreeNode * node)
{
	hashNode * hashNodeAux = NULL;
	intList * intListAux = NULL;
	astreeNode * astreeNodeAux = NULL;
	int argNumber = 1;
	char errorMessage[50];
	
	if(node)
	{
		hashNodeAux = node->sons[0]->hashPointer;
		intListAux = hashNodeAux->functionArguments;
		astreeNodeAux = node->sons[1];
		while(intListAux && astreeNodeAux)
		{
			sprintf(errorMessage,"Argument of number %d does not match on function: ",argNumber);
			switch(intListAux->value)
			{
				case BOOL: if(!isBoolean(astreeNodeAux->sons[0])) semanticError(errorMessage,hashNodeAux->value,node->lineNumber); break;
				case WORD: if(!isInteger(astreeNodeAux->sons[0])) semanticError(errorMessage,hashNodeAux->value,node->lineNumber);break;
				case BYTE: if(!isInteger(astreeNodeAux->sons[0])) semanticError(errorMessage,hashNodeAux->value,node->lineNumber);break;
			}
			argNumber++;
			intListAux = intListAux->next;
			astreeNodeAux = astreeNodeAux->sons[1];
		}
		
		if(intListAux && !astreeNodeAux)
		{
			semanticError("Wrong number of arguments (should be more) on function: ",hashNodeAux->value,node->lineNumber);
		}
		else if(!intListAux && astreeNodeAux)
		{
			semanticError("Wrong number of arguments (should be less) on function: ",hashNodeAux->value,node->lineNumber);
		}
	}
}
	
void scalarWriteTest(astreeNode * node)
{
	if(node)
	{	
		if(!isScalar(node->sons[0]) && !isPointer(node->sons[0]))
			semanticError("Left side variable is not scalar or pointer:",node->sons[0]->hashPointer->value,node->lineNumber);
		if(isPointer(node->sons[0]))
		{
			if(!isPointerOperation(node->sons[1]))
				semanticError("Incompatible atribution, right side should be pointer","",node->lineNumber);
		}
		else
		{
			switch(node->sons[0]->hashPointer->dataType)
			{
				case T_BOOLEAN: if(!isBoolean(node->sons[1])) semanticError("Incompatible atribution, right side should be boolean","",node->lineNumber); break;
				case T_INTEGER: if(!isInteger(node->sons[1])) semanticError("Incompatible atribution, right side should be integer","",node->lineNumber); break;
			}
		}
		
	}
}	
void vectorWriteTest(astreeNode * node)
{
	if(node)
	{
		if(!isVector(node->sons[0]))
			semanticError("Left side variable is not vector:",node->sons[0]->hashPointer->value,node->lineNumber);
		if(!isInteger(node->sons[1]))
			semanticError("Vector index is not an integer:",node->sons[0]->hashPointer->value,node->lineNumber);
		switch(node->sons[0]->hashPointer->dataType)
		{
			case T_BOOLEAN: if(!isBoolean(node->sons[2])) semanticError("Incompatible atribution, right side should be boolean","",node->lineNumber); break;
			case T_INTEGER: if(!isInteger(node->sons[2])) semanticError("Incompatible atribution, right side should be integer","",node->lineNumber); break;
		}
	}
}
void pointerWriteTest(astreeNode * node)
{
	if(node)
	{
		if(!isPointer(node->sons[0]))
		{
			semanticError("Something not pointer used as pointer:",node->sons[0]->hashPointer->value,node->lineNumber);
		}
		else if(!isInteger(node->sons[1]) && !isBoolean(node->sons[1]))
		{
			semanticError("Atributing non-value to pointer:",node->sons[0]->hashPointer->value,node->lineNumber);
		}
	}
}
void returnTest(astreeNode * node)
{
	if(node)
	{
		if(currentFunction)
		{
			switch(currentFunction->dataType)
			{
				case T_INTEGER: 
					if(!isInteger(node->sons[0])) 
						semanticError("Wrong return type (should be integer) for function ",currentFunction->value,node->lineNumber); 
					break;
				case T_BOOLEAN:
					if(!isBoolean(node->sons[0])) 
						semanticError("Wrong return type (should be boolean) for function ",currentFunction->value,node->lineNumber); 
					break;
			}
		}
		else
			semanticError("RETURN in wrong place","",node->lineNumber);
	}
}

void evaluate(astreeNode * node)
{
	if(node)
	{
		switch(node->type)
		{
			/* literais e identificadores */
			case TK_IDENTIFIER: break;
			case LIT_INTEGER:	break;
			case LIT_TRUE: 		break;
			case LIT_FALSE: 	break;
			case LIT_STRING: 	break;
			case LIT_CHAR: 		break;
			
			/* listas */
			case PROGRAM:  evaluate(node->sons[0]); evaluate(node->sons[1]);		break;	
			case LIT_LIST: 	break;

			/* palavras reservadas de tipo */
			case BOOL: 			break;				
			case WORD: 			break;				
			case BYTE: 			break;
			
			/* declarações */
			case DECLARATION_SCALAR: 	declareScalar(node);	break;	
			case DECLARATION_POINTER:	declarePointer(node);	break;	
			case DECLARATION_VECTOR: 	declareVector(node);	break;	
			case DECLARATION_FUNCTION:	currentFunction = node->sons[1]->hashPointer; evaluate(node->sons[3]); evaluate(node->sons[4]); break;
			case ARG_DECLARATION: 		break;	

			/* expressões */
			/* NOTA: as funçÕes auxiliares para avaliar os nodos NÃO CHAMAM evaluate para os nodos filhos, por isso o evaluate está aqui */
			case ARGCALL: 		evaluate(node->sons[0]); evaluate(node->sons[1]);	break;				
			case SCALAR_READ:	if(!isScalar(node->sons[0]) && !isPointer(node->sons[0])) semanticError("Using non-scalar as scalar: ",node->sons[0]->hashPointer->value,node->lineNumber);			break;			
			case VECTOR_READ: 	if(!isVector(node->sons[0])) semanticError("Using non-vector as vector: ",node->sons[0]->hashPointer->value,node->lineNumber); if(!isInteger(node->sons[1])) semanticError("Vector with index non-integer","",node->lineNumber);	break;			
			case GET_REFERENCE: if(!isDeclared(node->sons[0]->hashPointer)) semanticError("Variable undeclared:",node->sons[0]->hashPointer->value,node->lineNumber);	break;		
			case POINTER: 		if(!isPointer(node->sons[0])) semanticError("Using non-scalar as scalar: ",node->sons[0]->hashPointer->value,node->lineNumber);			break;				
			case FUNCALL: 		funcallTest(node); evaluate(node->sons[1]);			break;				
			case PAR: 			evaluate(node->sons[0]);							break;					
			case ADD: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("Adding something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case SUB: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("Subtracting something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case MUL: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("Multiplying something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case DIV: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("Dividing something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case OR: 			if(!isBoolean(node->sons[0]) || !isBoolean(node->sons[1])) semanticError("OR with something not boolean","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case AND: 			if(!isBoolean(node->sons[0]) || !isBoolean(node->sons[1])) semanticError("AND with something not boolean","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case LE: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("<= with something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case GE: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError(">= with something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case EQ: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("== with something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case NE: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("!= with something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;					
			case GREATER: 		if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("> with something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;				
			case LESS: 			if(!isInteger(node->sons[0]) || !isInteger(node->sons[1])) semanticError("< with something not integer","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);	break;
				
			/* CMD e CMD_SEQ */	
			/* NOTA: as funçÕes auxiliares para avaliar os nodos NÃO CHAMAM evaluate para os nodos filhos, por isso o evaluate está aqui */
			case BLOCK: 		evaluate(node->sons[0]);							break;		
			case OUTPUT_LIST: 	evaluate(node->sons[0]); evaluate(node->sons[1]);	break;			
			case SCALAR_WRITE: 	scalarWriteTest(node);	evaluate(node->sons[1]);	break;		
			case VECTOR_WRITE: 	vectorWriteTest(node);	evaluate(node->sons[1]);	break;		
			case POINTER_WRITE: pointerWriteTest(node);	evaluate(node->sons[1]);	break;		
			case INPUT: 															break;				
			case OUTPUT: 		evaluate(node->sons[0]);							break;				
			case RETURN: 		returnTest(node); evaluate(node->sons[0]);			break;				
			case IF_THEN: 		if(!isBoolean(node->sons[0])) semanticError("IF conditional is not boolean","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);							break;				
			case IF_THEN_ELSE: 	if(!isBoolean(node->sons[0])) semanticError("IF conditional is not boolean","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]); evaluate(node->sons[2]);	break;		
			case LOOP: 			if(!isBoolean(node->sons[0])) semanticError("LOOP conditional is not boolean","",node->lineNumber); evaluate(node->sons[0]);evaluate(node->sons[1]);						break;
			case CMD_SEQ: 		evaluate(node->sons[0]); evaluate(node->sons[1]);	break;
			
			/* default? */
			default : break;
		}
	}
}


int semanticEvaluation(astreeNode * node)
{
	numberOfErrors = 0;
	
	declareFunctions(node);
	evaluate(node);
	
	if(numberOfErrors > 0)
	{	
		fprintf(stderr,"%d errors\n",numberOfErrors);
		return FALSE;
	}
	else
	{
		fprintf(stderr,"No errors\n");
		return TRUE;
	}
}