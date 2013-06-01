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

#define TRUE 1
#define FALSE 0

int verify(struct a_NODE * node) // coloca os tipos e as naturezas nas variaveis e testa se variáveis foram redeclaradas
{
	if(node)
	{
	
	}
	else
		return TRUE;
	
}

int detectUndeclared() // testa se tem variáveis não declaradas
{
	return detect(SYMBOL_IDENTIFIER);
}

int testNature(struct a_NODE * node) // verifica as expressões, atribuições  usos
{
	
}

int verifyFunction(struct a_NODE * node) // verifica a entrada e os valores de retorno
{
}

int verifyVecRead(struct a_NODE *node) // verifica se os índices dos vetores são inteiros
{

}
