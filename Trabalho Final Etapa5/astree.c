#include "astree.h"
#include "test.h"
#define TESTE1 fprintf(pfile,"T1\n");
#define TESTE2 fprintf(pfile,"T2\n");
#define SHOW printToken(
#define NOW ); fprintf(pfile,"\n");
#define SHOW_INT fprintf(pfile,"%d\n",

#define TRUE 1
#define FALSE 0

int hasError =0;


void printTokens(int t)
{
	switch(t)
	{
	case LE: fprintf(stderr,"LE"); break;
	case GE: fprintf(stderr,"GE");break;
	case EQ: fprintf(stderr,"EQ");break;
	case NE: fprintf(stderr,"NE");break;
	case AND: fprintf(stderr,"AND");break;
	case OR: fprintf(stderr,"OR");break;

	case IF_THEN: fprintf(stderr,"IF_THEN");break;
	case IF_THEN_ELSE: fprintf(stderr,"IF_THEN_ELSE");break;
	case LOOP: fprintf(stderr,"LOOP");break;

	case FUNC_DECLARATION: fprintf(stderr,"FUNC_DECLARATION");break;
	case DECLARATION:fprintf(stderr,"DECLARATION"); break;
	case DECLARATION_POINTER: fprintf(stderr,"DECLARATION_POINTER");break;
	case DECLARATION_VEC: fprintf(stderr,"DECLARATION_VEC");break;
	case DECLARATION_VEC_INIT: fprintf(stderr,"DECLARATION_VEC_INIT");break;
	case OUTPUT: fprintf(stderr,"OUTPUT");break;
	case INPUT: fprintf(stderr,"INPUT");break;
	case RETURN: fprintf(stderr,"RETURN");break;
	case VECCALL: fprintf(stderr,"VECCAL");break;
	case POINTER: fprintf(stderr,"POINTER");break;
	case NORMAL : fprintf(stderr,"NORMAL");break;

	case ID_WORD: fprintf(stderr,"WORD");break;
	case ID_BYTE: fprintf(stderr,"BYTE");break;
	case ID_BOOL: fprintf(stderr,"BOOL");break;

	case ID_VECTOR: fprintf(stderr,"VECTOR");break;
	case ID_SCALAR: fprintf(stderr,"SCALAR");break; 
	case ID_POINTER: fprintf(stderr,"POINTER");break;
	case ID_FUNC: fprintf(stderr,"FUNC");break;

	case TEMP: fprintf(stderr,"TEMP");break;
	case LABEL: fprintf(stderr,"LABEL");break;

	case TAC_JMP: fprintf(stderr,"JMP");break;
	case TAC_IFZ : fprintf(stderr,"IFZ");break;
	case TAC_LABEL: fprintf(stderr,"LABEL");break;


	case KW_WORD: fprintf(stderr,"KW_WORD");break;      
	case KW_BOOL: fprintf(stderr,"KW_BOOL");break;      
	case KW_BYTE: fprintf(stderr,"KW_BYTE");break;      
	case KW_IF: fprintf(stderr,"KW_IF");break;        
	case KW_THEN: fprintf(stderr,"KW_THEN");break;      
	case KW_ELSE: fprintf(stderr,"KW_ELSE");break;      
	case KW_LOOP: fprintf(stderr,"KW_LOOP");break;      
	case KW_INPUT: fprintf(stderr,"KW_INPUT");break;     
	case KW_RETURN:fprintf(stderr,"KW_RETURN"); break;    
	case KW_OUTPUT: fprintf(stderr,"KW_OUTPUT");break;    

	case OPERATOR_LE: fprintf(stderr,"OP_LE");break;  
	case OPERATOR_GE: fprintf(stderr,"OP_GE");break;  
	case OPERATOR_EQ: fprintf(stderr,"OP_EQ");break;  
	case OPERATOR_NE: fprintf(stderr,"OP_NE");break;  
	case OPERATOR_AND: fprintf(stderr,"OP_AND");break; 
	case OPERATOR_OR: fprintf(stderr,"OP_OR");break;  


	case TK_IDENTIFIER: fprintf(stderr,"TK_IDENTIFIER");break;
	case LIT_INTEGER: fprintf(stderr,"LIT_INT");break;  
	case LIT_FALSE: fprintf(stderr,"LIT_FALSE");break;    
	case LIT_TRUE: fprintf(stderr,"LIT_TRUE");break;	    
	case LIT_CHAR: fprintf(stderr,"LIT_CHAR");break;     
	case LIT_STRING: fprintf(stderr,"LIT_STRING");break;   

	case TOKEN_ERROR: break;

	default: fprintf(stderr,"%c", t);break;
	}
}

void doAll(struct a_NODE * node)
{
	printNode(node);
	semanticEvaluation(node);
	printTac(generateTac(node));
	printHash();
	//generateTac(node);
}

void a_setFile(char* file)
{
	filename = file;
}

struct a_NODE * newNode(
	TOKEN _token,
	struct a_NODE * son1,
	struct a_NODE * son2,
	struct a_NODE * son3,
	struct a_NODE * son4,
	struct HNODE * value,
	int lineN)
{

	int sonsTest[4]={0,0,0,0};
	int sonNumber =0;
	int i;
	if(son1){
		sonsTest[0] = 1;
		sonNumber++;
	}
	if(son2){
		sonsTest[1] = 1;
		sonNumber++;
	}
	if(son3){
		sonsTest[2] = 1;
		sonNumber++;
	}
	if(son4){
		sonsTest[3] = 1;
		sonNumber++;
	}
	struct a_NODE * newNode = (struct a_NODE*)calloc(1,sizeof(struct a_NODE));
	newNode->sons = (struct a_NODE**) calloc(4,sizeof(struct a_NODE*));
	newNode->token = _token;
	newNode->lineNumber = lineN;
	if(sonsTest[0])
		newNode->sons[0] = son1;
	else
		newNode->sons[0] = NULL;
	if(sonsTest[1])
		newNode->sons[1] = son2;
	else
		newNode->sons[1] = NULL;
	if(sonsTest[2])
		newNode->sons[2] = son3;
	else
		newNode->sons[2] = NULL;
	if(sonsTest[3])
		newNode->sons[3] = son4;
	else
		newNode->sons[3] = NULL;
	if(value)
	{
		newNode->node = value;
	}
	return newNode;

}



int firstTime = 1;

void clearFile(FILE* pfile)
{
	pfile = fopen(filename,"w");
	fprintf(pfile,"");
	fclose(pfile);
}

void printToFile(FILE * pfile,char* string)
{
	if(firstTime)
	{
		clearFile(pfile);
		firstTime=0;
	}
	pfile = fopen(filename,"a+");
	fprintf(pfile,"%s",string);
	fclose(pfile);

}

int testArguments(struct HNODE *node1, struct a_NODE *node2)
{
	int argNumber =1;
    struct intList * aux;
	struct a_NODE * aux2;
	aux = node1->args;
	aux2 = node2;
	while(aux || aux2)
	{

		if(!aux && aux2)
		{

			hasError++;{hasError++;printf("Semantic error: wrong number of arguments(given %d, should be less) on function call on line %d\n",argNumber,aux2->lineNumber);}
			return FALSE;
		}
		else if(aux && !aux2)
		{
			hasError++;{hasError++;printf("Semantic error: wrong number of arguments(given %d, should be more) on function call\n",argNumber-1);}
			return FALSE;
		}
		else
			if(aux->v == KW_BOOL)
			{
				if(!isBoolean(aux2->sons[0]))
				{
					hasError++;{hasError++;printf("Semantic error: argument of number %d is of wrong type(should be boolean) on line %d\n",argNumber,aux2->lineNumber);}
					return FALSE;
				}
				else
				{
					argNumber++;
					aux = aux->next;
					aux2 = aux2->sons[1];
				}
			}
			else if(aux->v == KW_WORD || aux->v == KW_BYTE)
			{
				if(!isInt(aux2->sons[0]))
				{
					hasError++;{hasError++;printf("Semantic error: argument number %d is of wrong type(should be integer) on line %d\n",argNumber,aux2->lineNumber);}
					return FALSE;
				}
				else
				{
					argNumber++;
					aux = aux->next;
					aux2 = aux2->sons[1];
				}
			}
	}
	return TRUE;
}

void semanticEvaluation(struct a_NODE *node)
{
	declareFunctions(node);
	verify(node);
	if(hasError)
	{
		printf("\nFOUND %d ERRORS\n\n",hasError);
		exit(3);
	}
	else
	{
		printf("\nNO ERRORS\n\n");
		//exit(0);
	}
}

struct HNODE * currentFunction;

void declareFunctions(struct a_NODE *node)
{
	struct a_NODE * aux;
	if(node)
	{
		if(node->token == FUNC_DECLARATION)
		{
			node->sons[1]->node->type = ID_FUNC;
			if(node->sons[0]->token == KW_BOOL)
				node->sons[1]->node->dataType = ID_BOOL;
			else if(node->sons[0]->token == KW_WORD)
				node->sons[1]->node->dataType = ID_WORD;
			else if(node->sons[0]->token == KW_BYTE)
				node->sons[1]->node->dataType = ID_BYTE;

			//currentFunction = node->sons[1]->node;

			aux = node->sons[2];
			for(aux = node->sons[2] ; aux != NULL ; aux = aux->sons[2])
			{
				aux->sons[1]->node->type = ID_SCALAR;
				if(aux->sons[0]->token == KW_BOOL)
				{
					aux->sons[1]->node->dataType = ID_BOOL;
				}
				else if(aux->sons[0]->token == KW_WORD)
				{
					aux->sons[1]->node->dataType = ID_WORD;
				}
				else if(aux->sons[0]->token == KW_BYTE)
				{
					aux->sons[1]->node->dataType = ID_BYTE;
				}

				node->sons[1]->node->args = insertInIntList(aux->sons[0]->token,node->sons[1]->node->args);
			}
		}
		else
		{
			declareFunctions(node->sons[0]);
			declareFunctions(node->sons[1]);
			declareFunctions(node->sons[2]);
			declareFunctions(node->sons[3]);
		}
	}
}


void verify(struct a_NODE * node_p)
{
	struct a_NODE * aux;
	if(node_p)
	{
	struct a_NODE node_ = *node_p;

	switch(node_.token)
	{
		// TOKENS
		case LIT_TRUE:

			break;
		case LIT_FALSE:

			break;
		case LIT_INTEGER:

			break;
		case TK_IDENTIFIER:
			break;
		case LIT_CHAR:

			break;
		case LIT_STRING:

			break;
		// LIST
		case LIST:
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		// TYPE
		case KW_BOOL:
			break;
		case KW_WORD:
			break;
		case KW_BYTE:
			break;
		// FUNC_DECLARATION
		case ARGUMENTS:
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			if((node_.sons[2])!=NULL)
			{
				verify((node_.sons[2]));
			}
			break;
		case D_NODE: // GAMBIARRATION
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		case FUNC_DECLARATION:
			/*node_.sons[1]->node->type = ID_FUNC;
			if(node_.sons[0]->token == KW_BOOL)
				node_.sons[1]->node->dataType = ID_BOOL;
			else if(node_.sons[0]->token == KW_WORD)
				node_.sons[1]->node->dataType = ID_WORD;
			else if(node_.sons[0]->token == KW_BYTE)
				node_.sons[1]->node->dataType = ID_BYTE;

			currentFunction = node_.sons[1]->node;

			aux = node_.sons[2];
			for(aux = node_.sons[2] ; aux != NULL ; aux = aux->sons[2])
			{
				aux->sons[1]->node->type = ID_SCALAR;
				if(aux->sons[0]->token == KW_BOOL)
				{
					aux->sons[1]->node->dataType = ID_BOOL;
				}
				else if(aux->sons[0]->token == KW_WORD)
				{
					aux->sons[1]->node->dataType = ID_WORD;
				}
				else if(aux->sons[0]->token == KW_BYTE)
				{
					aux->sons[1]->node->dataType = ID_BYTE;
				}

				node_.sons[1]->node->args = insertInIntList(aux->sons[0]->token,node_.sons[1]->node->args);
			}
			*/
			currentFunction = node_.sons[1]->node;
			verify((node_.sons[3])); // SEMPRE D_NODE , GAMBIARRATIONN

			break;
		// DECLARATIONS
		case PROG:
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		case DECLARATION:
			if(node_.sons[1]->node->type != SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error on line %d: variable %s already declared \n",node_.lineNumber,node_.sons[1]->node->value);}
			else
			{
				if(node_.sons[0]->token == KW_BOOL)
					node_.sons[1]->node->dataType = ID_BOOL;
				else if(node_.sons[0]->token == KW_WORD)
					node_.sons[1]->node->dataType = ID_WORD;
				else if(node_.sons[0]->token == KW_BYTE)
					node_.sons[1]->node->dataType = ID_BYTE;
				node_.sons[1]->node->type = ID_SCALAR;
				if(!(
					(node_.sons[0]->token == KW_BOOL && (node_.sons[2]->token == LIT_TRUE || node_.sons[2]->token == LIT_FALSE)) ||
					(((node_.sons[0]->token == KW_WORD) || (node_.sons[0]->token == KW_BYTE)) && ((node_.sons[2]->token == LIT_INTEGER)||(node_.sons[2]->token == LIT_CHAR)))))
					{hasError++;printf("Semantic error on line %d: Scalar initialized wrong.\n",node_.lineNumber);}
			}

			break;
		case DECLARATION_POINTER:
			if(node_.sons[1]->node->type != SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error on line %d: variable already declared\n",node_.lineNumber);}
			else
			{
				if(node_.sons[0]->token == KW_BOOL)
					node_.sons[1]->node->dataType = ID_BOOL;
				else if(node_.sons[0]->token == KW_WORD)
					node_.sons[1]->node->dataType = ID_WORD;
				else if(node_.sons[0]->token == KW_BYTE)
					node_.sons[1]->node->dataType = ID_BYTE;
				node_.sons[1]->node->type = ID_POINTER;
			}
			break;
		case DECLARATION_VEC:
			if(node_.sons[1]->node->type != SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error on line %d: variable already declared\n",node_.lineNumber);}
			else
			{
				if(node_.sons[0]->token == KW_BOOL)
					node_.sons[1]->node->dataType = ID_BOOL;
				else if(node_.sons[0]->token == KW_WORD)
					node_.sons[1]->node->dataType = ID_WORD;
				else if(node_.sons[0]->token == KW_BYTE)
					node_.sons[1]->node->dataType = ID_BYTE;
				node_.sons[1]->node->type = ID_VECTOR;

				if(!isInt(node_.sons[2]))
					{hasError++;printf("Semantic error on line %d: Vector with not-integer size\n",node_.lineNumber);}
			}
			break;
		case DECLARATION_VEC_INIT:
			if(node_.sons[1]->node->type != SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error on line %d: variable already declared\n",node_.lineNumber);}
			else
			{
				if(node_.sons[0]->token == KW_BOOL)
					node_.sons[1]->node->dataType = ID_BOOL;
				else if(node_.sons[0]->token == KW_WORD)
					node_.sons[1]->node->dataType = ID_WORD;
				else if(node_.sons[0]->token == KW_BYTE)
					node_.sons[1]->node->dataType = ID_BYTE;
				node_.sons[1]->node->type = ID_VECTOR;

				if(!isInt(node_.sons[2]))
					{hasError++;printf("Semantic error on line %d: Vector with not-integer size\n",node_.lineNumber);}
				if(!(node_.sons[3]->token == LIST))
					{hasError++;printf("Semantic error on line %d: Vector initialized wrong.\n",node_.lineNumber);}
			}
			break;

		// EXPRESSION
		case '&':
			if(!(node_.sons[0]->node->type==ID_SCALAR))
				{hasError++;printf("Semantic error: getting reference for not-scalar on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			break;
		case POINTER:
			if(!(node_.sons[0]->node->type==ID_POINTER))
				{hasError++;printf("Semantic error: using not-pointer as pointer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			break;
		case '*':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1])))
				{hasError++;printf("Semantic error: multiplying not integer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case '(':
			verify((node_.sons[0]));
			break;
		case '+':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1])))
				{hasError++;printf("Semantic error: adding not integer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case '-':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1])))
				{hasError++;printf("Semantic error: subtracting not integer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case '/':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1])))
				{hasError++;printf("Semantic error: dividing not integer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case OR:
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1])))
				{hasError++;printf("Semantic error: '||' with not boolean on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case AND:
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1])))
				{hasError++;printf("Semantic error: '&&' with not boolean on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case LE:
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case EQ:
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case GE:
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case NE:
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case '>':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1])))
				{hasError++;printf("Semantic error: '>' with not integer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case '<':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1])))
				{hasError++;printf("Semantic error: '<' with not integer on line %d\n",node_.lineNumber);}
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		case VECCALL:
			if(node_.sons[0]->node->type == SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error: Vector %s not declared used on line %d\n",node_.sons[0]->node->value,node_.lineNumber);}
			if(!isInt(node_.sons[1]))
				{hasError++;printf("Semantic error: Vector index not integer on line %d\n",node_.lineNumber);}
			if(!(node_.sons[0]->node->type==ID_VECTOR))
				{hasError++;printf("Semantic error: Something not-vector used as vector on line %d\n",node_.lineNumber);}
			break;
		case NORMAL:
			if(node_.sons[0]->node->type == SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error: Variable %s not declared used on line %d\n",node_.sons[0]->node->value,node_.lineNumber);}
			if(node_.sons[0]->node->type != ID_SCALAR && node_.sons[0]->node->type != ID_POINTER)
				{hasError++;printf("Semantic error: Something not-scalar used as scalar on line %d\n",node_.lineNumber);}
			break;
		// FUNCALL ARGCALL CMD_SEQ
		case FUNCALL:
			if(node_.sons[0]->node->type == SYMBOL_IDENTIFIER)
				{hasError++;printf("Semantic error: Function %s not yet declared used on line %d\n",node_.sons[0]->node->value,node_.lineNumber);}
			if(!(node_.sons[0]->node->type==ID_FUNC))
				{hasError++;printf("Semantic error: Something not-function used as function on line %d\n",node_.lineNumber);}
			testArguments(node_.sons[0]->node,node_.sons[1]);
			break;
		case ARGCALL:
			break;
		case CMD_SEQ:
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		// OUTPUT
		case OUTPUT_L:
			verify(node_.sons[0]);
			verify(node_.sons[1]);
			break;
		// CMD
		case INPUT:
			verify(node_.sons[0]);
			break;
		case OUTPUT:
			verify(node_.sons[0]);
			break;
		case RETURN:
			if(!currentFunction)
				{hasError++;printf("Semantic error: 'return' in wrong place on line %d\n",node_.lineNumber);}
			else if(currentFunction->dataType == ID_WORD)
			{
				if(!isInt(node_.sons[0]))
					{hasError++;printf("Semantic error: wrong return type for function %s, on line %d\n",currentFunction->value,node_.lineNumber);}
			}
			else if(currentFunction->dataType == ID_BYTE)
			{
				if(!isInt(node_.sons[0]))
					{hasError++;printf("Semantic error: wrong return type for function %s, on line %d\n",currentFunction->value,node_.lineNumber);}
			}
			else if(currentFunction->dataType == ID_BOOL)
			{
				if(!isBoolean(node_.sons[0]))
					{hasError++;printf("Semantic error: wrong return type for function %s, should be boolean, on line %d\n",currentFunction->value,node_.lineNumber);}
			}
			break;
		case BLOCK:
			verify((node_.sons[0]));
			break;
		case '=':
			verify(node_.sons[1]); ////////////////////////////////////////////////////////////////////// REMEMBER
			if(node_.sons[0]->token == VECCALL)
			{
				if(!(node_.sons[0]->sons[0]->node->type == ID_VECTOR))
					{hasError++;printf("Semantic error: not-vector used as vector on line %d\n",node_.lineNumber);}

				if(!isInt(node_.sons[0]->sons[1]))
					{hasError++;printf("Semantic error: vector index is not integer on line %d\n",node_.lineNumber);}

				if(node_.sons[0]->sons[0]->node->dataType == ID_WORD)
				{
					if(!isInt(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to integer vector from not-integer on line %d\n",node_.lineNumber);}
				}
				else if(node_.sons[0]->sons[0]->node->dataType == ID_BYTE)
				{
					if(!isInt(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to integer vector from not-integer on line %d\n",node_.lineNumber);}
				}
				else if(node_.sons[0]->sons[0]->node->dataType == ID_BOOL)
				{
					if(!isBoolean(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to boolean vector from not-boolean on line %d\n",node_.lineNumber);}
				}
				else
					{hasError++;printf("Semantic error: identifier %s not declared on line %d\n",node_.sons[0]->node->value,node_.lineNumber);}
			}
			else if(node_.sons[0]->token == POINTER)
			{
				if(node_.sons[0]->sons[0]->node->type != ID_POINTER)
					{hasError++;printf("Semantic error: dereferencing non-pointer on line %d\n",node_.lineNumber);}
				if(node_.sons[0]->sons[0]->node->dataType == ID_WORD)
				{

					if(!isInt(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to integer scalar from not-integer on line %d\n",node_.lineNumber);}
				}
				else if(node_.sons[0]->sons[0]->node->dataType == ID_BYTE)
				{
					if(!isInt(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to integer scalar from not-integer on line %d\n",node_.lineNumber);}
				}
				else if(node_.sons[0]->sons[0]->node->dataType == ID_BOOL)
				{
					if(!isBoolean(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to boolean scalar from not-boolean on line %d\n",node_.lineNumber);}
				}
				else
					{hasError++;printf("Semantic error: identifier %s not declared on line %d\n",node_.sons[0]->node->value,node_.lineNumber);}
			}
			else if(node_.sons[0]->node->type == ID_POINTER)
			{
				if(!isPt(node_.sons[1]))
				{
					{hasError++;printf("Semantic error: atributin a non-pointer to a pointer on line %d\n",node_.lineNumber);}
				}

			}
			else if(node_.sons[0]->node->type == ID_SCALAR)
			{
				if(node_.sons[0]->node->type == ID_VECTOR)
					{hasError++;printf("Semantic error: vector used as not-vector on line %d\n",node_.lineNumber);}
				if(node_.sons[0]->node->dataType == ID_WORD)
				{
					if(!isInt(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to integer scalar from not-integer on line %d\n",node_.lineNumber);}
				}
				else if(node_.sons[0]->node->dataType == ID_BYTE)
				{
					if(!isInt(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to integer scalar from not-integer on line %d\n",node_.lineNumber);}
				}
				else if(node_.sons[0]->node->dataType == ID_BOOL)
				{
					if(!isBoolean(node_.sons[1]))
						{hasError++;printf("Semantic error: atributing to boolean scalar from not-boolean on line %d\n",node_.lineNumber);}
				}
				else
					{hasError++;printf("Semantic error: identifier %s not declared on line %d\n",node_.sons[0]->node->value,node_.lineNumber);}
			}
			else
			{
				{hasError++;printf("Semantic error: atributing to non-variable on line %d\n",node_.lineNumber);}
			}
			break;
		case IF_THEN:
			if(!isBoolean(node_.sons[0]))
				{hasError++;printf("Semantic error: if called with not-boolean on line %d\n",node_.lineNumber);}
			verify(node_.sons[1]);
			break;
		case IF_THEN_ELSE:
			if(!isBoolean(node_.sons[0]))
				{hasError++;printf("Semantic error: if called with not-boolean on line %d\n",node_.lineNumber);}
			verify(node_.sons[1]);
			verify(node_.sons[2]);
			break;
		case LOOP :
			if(!isBoolean(node_.sons[0]))
				{hasError++;printf("Semantic error: loop called with not-boolean on line %d\n",node_.lineNumber);}
			verify(node_.sons[1]);
			break;
		// DEFAULT
		default:
			break;

	} // switch
	} // if node
}




void printNode(struct a_NODE * node_p)
{

	FILE *pfile;
	if(node_p)
	{
	struct a_NODE node_ = *node_p;

	switch(node_.token)
	{
		// TOKENS
		case LIT_TRUE:
			printToFile(pfile,(node_.node)->value);
			break;
		case LIT_FALSE:
			printToFile(pfile,(node_.node)->value);
			break;
		case LIT_INTEGER:
			printToFile(pfile,(node_.node)->value);
			break;
		case TK_IDENTIFIER:
			printToFile(pfile,(node_.node)->value);
			break;
		case LIT_CHAR:
			printToFile(pfile,"'");
			printToFile(pfile,(node_.node)->value);
			printToFile(pfile,"'");
			break;
		case LIT_STRING:
			printToFile(pfile,"\"");
			printToFile(pfile,(node_.node)->value);
			printToFile(pfile,"\"");
			break;
		// LIST
		case LIST:
			printNode((node_.sons[0]));
			if((node_.sons[1])!=NULL)
			{
				printToFile(pfile," ");
				printNode((node_.sons[1]));

			}
			break;
		// TYPE
		case KW_BOOL:
			printToFile(pfile,"bool ");
			break;
		case KW_WORD:
			printToFile(pfile,"word ");
			break;
		case KW_BYTE:
			printToFile(pfile,"byte ");
			break;
		// FUNC_DECLARATION
		case ARGUMENTS:
			printNode((node_.sons[0]));
			printNode((node_.sons[1]));
			if((node_.sons[2])!=NULL)
			{
				printToFile(pfile,",");
				printNode((node_.sons[2]));
			}
			break;
		case D_NODE: // GAMBIARRATION
			if((node_.sons[0])!=NULL)
				printNode((node_.sons[0]));
			printNode((node_.sons[1]));
			break;
		case FUNC_DECLARATION:
			printNode((node_.sons[0]));
			printNode((node_.sons[1]));
			printToFile(pfile,"(");
			if((node_.sons[2])!=NULL)
				printNode((node_.sons[2]));
			printToFile(pfile,")");

			printNode((node_.sons[3])); // SEMPRE D_NODE , GAMBIARRATIONN

			break;
		// DECLARATIONS
		case PROG:
			printNode((node_.sons[0]));
			//printToFile(pfile,";");
			if((node_.sons[1])!=NULL)
				printNode((node_.sons[1]));
			break;
		case DECLARATION:
			printNode((node_.sons[0]));
			printNode((node_.sons[1]));
			printToFile(pfile,":");
			printNode((node_.sons[2]));
			printToFile(pfile,";");
			break;
		case DECLARATION_POINTER:
			printNode((node_.sons[0]));
			printToFile(pfile,"$");
			printNode((node_.sons[1]));
			printToFile(pfile,":");
			printNode((node_.sons[2]));
			printToFile(pfile,";");
			break;
		case DECLARATION_VEC:
			printNode((node_.sons[0]));
			printNode((node_.sons[1]));
			printToFile(pfile,"[");
			printNode((node_.sons[2]));
			printToFile(pfile,"]");
			printToFile(pfile,";");
			break;
		case DECLARATION_VEC_INIT:
			printNode((node_.sons[0]));
			printNode((node_.sons[1]));
			printToFile(pfile,"[");
			printNode((node_.sons[2]));
			printToFile(pfile,"]");
			printToFile(pfile,":");
			printNode((node_.sons[3]));
			printToFile(pfile,";");
			break;

		// EXPRESSION
		case '&':
			printToFile(pfile,"&");
			printNode((node_.sons[0]));
			break;
		case POINTER:
			printToFile(pfile,"*");
			printNode((node_.sons[0]));
			break;
		case '*':
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"*");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case '(':
			printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,")");
			break;
		case '+':
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"+");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case '-':
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"-");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case '/':
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"/");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case OR:
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"||");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case AND:
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"&&");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case LE:
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"<=");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case EQ:
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"==");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case GE:
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,">=");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case NE:
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"!=");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case '>':
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,">");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case '<':
			//printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,"<");
			printNode((node_.sons[1]));
			//printToFile(pfile,")");
			break;
		case VECCALL:
			printNode((node_.sons[0]));
			printToFile(pfile,"[");
			printNode((node_.sons[1]));
			printToFile(pfile,"]");
			break;
		case NORMAL:
			printNode((node_.sons[0]));
		// FUNCALL ARGCALL CMD_SEQ
		case FUNCALL:
			printNode((node_.sons[0]));
			printToFile(pfile,"(");
			if((node_.sons[1])!=NULL)
				printNode((node_.sons[1])) ;
			printToFile(pfile,")");
			break;
		case ARGCALL:
			printNode((node_.sons[0]));
			if(node_.sons[1]!=NULL)
			{
				printToFile(pfile,",");
				printNode((node_.sons[1]));
			}
			break;
		case CMD_SEQ:
			printNode((node_.sons[0]));
			printToFile(pfile,";");
			if(node_.sons[1]!=NULL)
			{
				printNode((node_.sons[1]));
			}
			break;
		// OUTPUT
		case OUTPUT_L:
			printNode((node_.sons[0]));
			if(node_.sons[1]!=NULL)
			{
				printToFile(pfile,",");
				printNode((node_.sons[1]));
			}
			break;
		// CMD
		case INPUT:
			printToFile(pfile,"input ");
			printNode((node_.sons[0]));
			printToFile(pfile," ");
			break;
		case OUTPUT:
			printToFile(pfile,"output ");
			printNode((node_.sons[0]));
			printToFile(pfile," ");
			break;
		case RETURN:
			printToFile(pfile,"return ");
			printNode((node_.sons[0]));
			printToFile(pfile," ");
			break;
		case BLOCK:
			printToFile(pfile,"{");
			printNode((node_.sons[0]));
			printToFile(pfile,"}");
			printToFile(pfile," ");
			break;
		case '=':
			printNode((node_.sons[0]));
			printToFile(pfile,"=");
			printNode((node_.sons[1]));
			printToFile(pfile," ");
			break;
		case IF_THEN:
			printToFile(pfile,"if(");
			printNode((node_.sons[0]));
			printToFile(pfile,")then ");
			printNode((node_.sons[1]));
			printToFile(pfile," ");
			break;
		case IF_THEN_ELSE:
			printToFile(pfile,"if(");
			printNode((node_.sons[0]));
			printToFile(pfile,")then ");
			printNode((node_.sons[1]));
			printToFile(pfile,"else ");
			printNode((node_.sons[2]));
			printToFile(pfile," ");
			break;
		case LOOP :
			printToFile(pfile,"loop");
			printToFile(pfile,"(");
			printNode((node_.sons[0]));
			printToFile(pfile,")");
			printNode((node_.sons[1]));
			printToFile(pfile," ");
			break;
		// DEFAULT
		default:
			printToFile(pfile,"DEFAULT");
			break;

	} // switch
	} // if node
}

int isBoolean(struct a_NODE *node)
{
	if(!node) // testa se é nulo
		return FALSE;

	if(node->token == LIT_TRUE || node->token == LIT_FALSE) // testa os literais
		return TRUE;

	if(node->token == TK_IDENTIFIER && node->node->dataType == ID_BOOL) // testa variável
		return TRUE;

	if(node->token == POINTER) // testa ponteiro
		return TRUE;

	if(node->token == FUNCALL && (node->sons[0]->node->dataType == ID_WORD || node->sons[0]->node->dataType == ID_BYTE)) // testa se é função
		return FALSE;

	if(node->token == FUNCALL && node->sons[0]->node->dataType == ID_BOOL)
		return TRUE;

	if(node->token == VECCALL && node->sons[0]->node->dataType == ID_WORD) // testa vetor
		return FALSE;

	if(node->token == VECCALL && node->sons[0]->node->dataType == ID_BYTE) // testa vetor
		return FALSE;

	if(node->token == VECCALL && node->sons[0]->node->dataType == ID_BOOL) // testa vetor
		return TRUE;

	if(node->token == '+' || node->token == '-' || node->token == '*' || node->token == '/') // testa os operadores que retornam inteiro
		return FALSE;

	if(node->token == EQ || node->token == NE || node->token == GE || node->token == LE || node->token == '>' || node->token == '<') // testa os operadores que retornam booleano
		return TRUE;

	if(isBoolean(node->sons[0]))
		return TRUE;

	if(isBoolean(node->sons[0]) && isBoolean(node->sons[1])) // testa os filhos
		return TRUE;

	return FALSE;
}

int isInt(struct a_NODE *node)
{
	if(!node) // testa se o nodo é nulo
		return FALSE;

	if(node->token == LIT_INTEGER) // testa se é um literal inteiro
		return TRUE;

	if(node->token == LIT_CHAR)
		return TRUE;

	if(node->token == VECCALL && node->sons[0]->node->dataType == ID_WORD) // faz o teste para ver se são vetores do tipo certo
		return TRUE;
	if(node->token == VECCALL && node->sons[0]->node->dataType == ID_BYTE)
		return TRUE;

	if(node->token == POINTER) // testa se é um ponteiro desreferenciado
		return TRUE;
	if(node->token == FUNCALL && (node->sons[0]->node->dataType == ID_WORD || node->sons[0]->node->dataType == ID_BYTE)) // testa se é uma função com retorno correto
		return TRUE;

	if(node->token == FUNCALL && node->sons[0]->node->dataType == ID_BOOL) // testa o oposto do anterior?
		return FALSE;

	if(node->token == EQ || node->token == NE || node->token == GE || node->token == LE || node->token == '>' || node->token == '<') // testa se é um operador que retorna booleano
		return FALSE;
	if(node->token == '+' || node->token == '-' || node->token == '*' || node->token == '/') // testa se é um operador que rertorna inteiro
		return TRUE;

	if(node->token == TK_IDENTIFIER && (node->node->dataType == ID_WORD || node->node->dataType == ID_BYTE)) // testa se é uma variável do tipo correto
		return TRUE;

	if(node->sons[1] && isInt(node->sons[0]) && isInt(node->sons[1])) // potencialmente bobagem
		return TRUE;
	else if(!node->sons[1] && isInt(node->sons[0])) // testa os filhos
		return TRUE;

	return FALSE;
}


int isPt(struct a_NODE *node)
{
	if(!node)
		return FALSE;
	if(node->token == '&')
		return TRUE;
	if(node->token == TK_IDENTIFIER && node->node->type == ID_POINTER)
		return TRUE;

	if(node->token == '+' && isPt(node->sons[0]) && isInt(node->sons[1]))
		return TRUE;
	if(node->token == '+' && isPt(node->sons[1]) && isInt(node->sons[0]))
		return TRUE;
	if(isPt(node->sons[0]))
		return TRUE;
	return FALSE;
}


