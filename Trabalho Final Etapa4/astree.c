#include "astree.h"
#include "test.h"
#define TESTE1 fprintf(pfile,"T1\n");
#define TESTE2 fprintf(pfile,"T2\n");
#define SHOW printToken(
#define NOW ); fprintf(pfile,"\n");
#define SHOW_INT fprintf(pfile,"%d\n",


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
	struct HNODE * value)
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
	fprintf(pfile,string);
	fclose(pfile);

}

void setId(int token, struct a_NODE * node, int type)
{
	if(node)
	{
		node->type = token;
		node->dataType = type;
	}
}

struct HNODE * currentFunction;
 
void verify(struct a_NODE * node_p)
{

	FILE *pfile;
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
				printToFile(pfile,",");
				verify((node_.sons[2]));
			}
			break;
		case D_NODE: // GAMBIARRATION
			if((node_.sons[0])!=NULL)
				verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		case FUNC_DECLARATION:
			node_.sons[1]->node->type = ID_FUNC;
			if(node_.sons[0]->token = KW_BOOL)
				node_.sons[1]->node->dataType = ID_BOOL;
			else if(node_.sons[0]->token = KW_WORD)
				node_.sons[1]->node->dataType = ID_WORD;
			else if(node_.sons[0]->token = KW_BYTE)
				node_.sons[1]->node->dataType = ID_BYTE;
				
			currentFunction = node_.sons[1]->node;
			verify((node_.sons[0])); 
			verify((node_.sons[1]));
			printToFile(pfile,"(");	
			if((node_.sons[2])!=NULL)
				verify((node_.sons[2])); 
			printToFile(pfile,")");
			
			verify((node_.sons[3])); // SEMPRE D_NODE , GAMBIARRATIONN
			
			break;
		// DECLARATIONS
		case PROG:
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		case DECLARATION:
			setId(node_.sons[0]->token,node_.sons[1],ID_SCALAR);
			if(!(
				(node_.sons[0]->token == KW_BOOL && (node_.sons[1]->token == LIT_TRUE || node_.sons[1]->token == LIT_FALSE)) ||
				(((node_.sons[0]->token == KW_WORD) || (node_.sons[0]->token == KW_BYTE)) && (node_.sons[1]->token == LIT_INTEGER))))
				printf("Semantic error on line %d: Scalar initialized wrong.\n",getLineNumber()));
				
			break;
		case DECLARATION_POINTER:
			setId(node_.sons[0]->token,node_.sons[1],ID_POINTER);
			break;
		case DECLARATION_VEC:
			setId(node_.sons[0]->token,node_.sons[1],ID_VECTOR);
			break;
		case DECLARATION_VEC_INIT:
			if(!isInt(node_.sons[2]))
				printf("Semantic error on line %d: Vector with not-integer size\n",getLineNumber());
			setId(node_.sons[0]->token,node_.sons[1],ID_VECTOR);
			if(!(node_.sons[3]->token == LIST))
				printf("Semantic error on line %d: Vector initialized wrong.\n",getLineNumber());
			break;
	
		// EXPRESSION
		case '&': 
			if(!(node_.sons[0]->node->type==ID_SCALAR)) 
				printf("Semantic error: geting reference for not-scalar on line %d\n",getLineNumber());
			break;
		case POINTER: 
			if(!(node_.sons[0]->node->type==ID_POINTER))
				printf("Semantic error: using not-pointer as pointer on line %d\n",getLineNumber());
			break;
		case '*': 
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1]))
				printf("Semantic error: multiplying not integer on line %d\n",getLineNumber());
			break;
		case '(': 
			verify((node_.sons[0])); 
			break;
		case '+':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1]))
				printf("Semantic error: adding not integer on line %d\n",getLineNumber());
			break;
		case '-':
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1]))
				printf("Semantic error: subtracting not integer on line %d\n",getLineNumber());
			break;
		case '/': 
			if(!(isInt(node_.sons[0]) && isInt(node_.sons[1]))
				printf("Semantic error: dividing not integer on line %d\n",getLineNumber());
			break;
		case OR: 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '||' with not boolean on line %d\n",getLineNumber());
			break;
		case AND: 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '&&' with not boolean on line %d\n",getLineNumber());
			break;
		case LE: 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '<=' with not boolean on line %d\n",getLineNumber());
			break;
		case EQ: 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '==' with not boolean on line %d\n",getLineNumber());
			break;
		case GE: 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '>=' with not boolean on line %d\n",getLineNumber());
			break;
		case NE: 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '!=' with not boolean on line %d\n",getLineNumber());
			break;
		case '>': 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '>' with not boolean on line %d\n",getLineNumber());
			break;
		case '<': 
			if(!(isBoolean(node_.sons[0]) && isBoolean(node_.sons[1]))
				printf("Semantic error: '<' with not boolean on line %d\n",getLineNumber());
			break;
		case VECCALL:
			if(!isInt(node_.sons[1])
				printf("Semantic error: Vector index not integer on line %d\n",getLineNumber());
			if(!(node_.sons[0]->node->type==ID_VECTOR))
				printf("Semantic error: Something not-vector used as vector on line %d\n",getLineNumber());
			break;
		// FUNCALL ARGCALL CMD_SEQ
		case FUNCALL:	
			if(!(node_.sons[0]->node->type==ID_FUNC))
				printf("Semantic error: Something not-function used as function on line %d\n",getLineNumber());
			testArguments(node_.sons[0]->node,node_.sons[1]); ////////////////////////////////////////////////////// TO DO
			break;
		case ARGCALL:
			break;
		case CMD_SEQ:
			verify((node_.sons[0]));
			verify((node_.sons[1]));
			break;
		// OUTPUT
		case OUTPUT_L:
			break;
		// CMD
		case INPUT: 
			break;
		case OUTPUT:
			break;
		case RETURN:
			if(!(node_.sons[0]->node->dataType == currentFunction->dataType))
				printf("Semantic error: wrong return type for function %s, on line %d\n",currentFunction->value,getLineNumber());
			break;
		case BLOCK:
			verify((node_.sons[0]));
			break;
		case '=':
			if(node_.sons[0]->token == VECCAL)
			{
				if(node_.sons[0]->sons[0]->dataType == ID_WORD)
				{
					if(!isInt(node_.sons[1]))
						printf("Semantic error: atributing to integer vector from not-integer on line %d",getLineNumber());
				}
				else if(node_.sons[0]->sons[0]->dataType == ID_BYTE)
				{
					if(!isInt(node_.sons[1]))
						printf("Semantic error: atributing to integer vector from not-integer on line %d",getLineNumber());
				}
				else if(node_.sons[0]->sons[0]->dataType == ID_BOOL)
				{
					if(!isBoolean(node_.sons[1]))
						printf("Semantic error: atributing to boolean vector from not-boolean on line %d",getLineNumber());
				}
			}
			else if(node_.sons[0]->token == POINTER)
			{
			
			}
			else
			{
				if(node_.sons[0]->dataType == ID_WORD)
				{
					if(!isInt(node_.sons[1]))
						printf("Semantic error: atributing to integer scalar from not-integer on line %d",getLineNumber());
				}
				else if(node_.sons[0]->dataType == ID_BYTE)
				{
					if(!isInt(node_.sons[1]))
						printf("Semantic error: atributing to integer scalar from not-integer on line %d",getLineNumber());
				}
				else if(node_.sons[0]->dataType == ID_BOOL)
				{
					if(!isBoolean(node_.sons[1]))
						printf("Semantic error: atributing to boolean scalar from not-boolean on line %d",getLineNumber());
				}
			}
			break;
		case IF_THEN: 
			if(!isBoolean(node_.sons[0]))
				printf("Semantic error: if called with not-boolean on line %d\n",getLineNumber());
			break;
		case IF_THEN_ELSE: 
			if(!isBoolean(node_.sons[0]))
				printf("Semantic error: if called with not-boolean on line %d\n",getLineNumber());
			break;
		case LOOP :
			if(!isBoolean(node_.sons[0]))
				printf("Semantic error: loop called with not-boolean on line %d\n",getLineNumber());
			break;
		// DEFAULT
		default: 
			printToFile(pfile,"DEFAULT");
			break;
		
	} // switch
	} // if node
}

#define TRUE 1
#define FALSE 0


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
	if((node->_token == LIT_TRUE) || (node->_token == LIT_FALSE))
		return TRUE;
	else if(node->value->dataType == id_BOOLEAN)
		return TRUE;
	else return FALSE;
}

int isInt(struct a_NODE *node)
{
	if(node->_token == LIT_INTEGER)
		return TRUE;
	else if(node->value->dataType == id_INTEGER)
		return TRUE;
	return FALSE;
}


int isPt(struct a_NODE *node)
{
	if(node->value->dataType == ID_POINTER)
		return TRUE;
	return FALSE;
}


