#include "astree.h"
#include "parser.tab.h"

void doAll(astreeNode * node)
{
	printAstreeNode(node);
	semanticEvaluation(node);
	printHash();
	printTac(generateTac(node));
}

astreeNode * newAstreeNode(int type_, astreeNode * son1, astreeNode * son2, astreeNode * son3, astreeNode * son4, astreeNode * son5, hashNode * hashPointer_, int lineNumber_)
{
	/* inicialização das variáveis */
	astreeNode * newNode = calloc (1,sizeof(astreeNode));
	
	/* atribuição do novo nodo */
	newNode->type = type_;
	
	/* atribui os filhos ~chato~ */
	if(son1)
		newNode->sons[0] = son1;
	else
		newNode->sons[0] = NULL;
		
	if(son2)
		newNode->sons[1] = son2;
	else
		newNode->sons[1] = NULL;
		
	if(son3)
		newNode->sons[2] = son3;
	else
		newNode->sons[2] = NULL;
		
	if(son4)
		newNode->sons[3] = son4;
	else
		newNode->sons[3] = NULL;
		
	if(son5)
		newNode->sons[4] = son5;
	else
		newNode->sons[4] = NULL;
	
	/* atribui o ponteiro pra hash */
	if(hashPointer_)
		newNode->hashPointer = hashPointer_;
	else
		newNode->hashPointer = NULL;
		
	/* atribui o número de linha */
	newNode->lineNumber = lineNumber_;
	
	return newNode;
}
/* funções para escrever no arquivo */
void setFileName(char * filename_)
{
	if(filename_)
	{
		filename = filename_;
	}
	else
	{
		filename = "out.txt";
	}
	firstTime =1;
}


void clearFile()
{
	pfile = fopen(filename,"w");
	if(pfile)
	{
		fprintf(pfile,"%s","");
		fclose(pfile);
	}
}


void printToFile(char* string)
{
	if(string)
	{
		if(firstTime)
		{
			clearFile();
			firstTime=0;
		}
		pfile = fopen(filename,"a+");
		if(pfile)
		{
			fprintf(pfile,"%s",string);
			fclose(pfile);
		}
	}

}


/* funções de impressão dos nodos */
void printIdentifier(hashNode * node)
{
	if(node)
	{
		printToFile(node->value);
	}
}
void printInteger(hashNode *node)
{
	if(node)
	{
		printToFile(node->value);
	}
}
void printLitTrue()
{
	printToFile("true");
}
void printLitFalse()
{
	printToFile("false");
}
void printLitString(hashNode *node)
{
	if(node)
	{
		printToFile("\"");
		printToFile(node->value);
		printToFile("\"");
	}
}
void printLitChar(hashNode *node)
{
	if(node)
	{
		printToFile("'");
		printToFile(node->value);
		printToFile("'");
	}
}
void printProgram(astreeNode * node1, astreeNode * node2)
{
	if(node1)
	{
		printAstreeNode(node1);
		printAstreeNode(node2);
	}
}
void printLitList(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	if(node2)
	{
		printToFile(" ");
		printAstreeNode(node2);
	}
}
void printBool()
{
	printToFile("bool");
}
void printWord()
{
	printToFile("word");
}
void printByte()
{
	printToFile("byte");
}
void printDeclarationScalar(astreeNode * node1, astreeNode * node2, astreeNode * node3)
{
	printAstreeNode(node1);
	printToFile(" ");
	if(node2 && node2->hashPointer)
	{
		printToFile(node2->hashPointer->value);
	}
	printToFile(":");
	printAstreeNode(node3);
	printToFile(";\n");
}
void printDeclarationPointer(astreeNode * node1, astreeNode * node2, astreeNode * node3)
{
	printAstreeNode(node1);
	printToFile(" ");
	printToFile("$");
	if(node2 && node2->hashPointer)
	{
		printToFile(node2->hashPointer->value);
	}
	printToFile(":");
	printAstreeNode(node3);
	printToFile(";\n");
}
void printDeclarationVector(astreeNode * node1, astreeNode * node2, astreeNode * node3, astreeNode * node4)
{
	printAstreeNode(node1);
	printToFile(" ");
	if(node2 && node2->hashPointer)
	{
		printToFile(node2->hashPointer->value);
	}
	printToFile("[");
	printAstreeNode(node3);
	printToFile("]");
	if(node4)
	{
		printToFile(":");
		printAstreeNode(node4);
	}
	printToFile(";\n");
}
void printDeclarationFunction(astreeNode * node1, astreeNode * node2, astreeNode * node3, astreeNode * node4, astreeNode * node5)
{
	printAstreeNode(node1);
	printToFile(" ");
	if(node2 && node2->hashPointer)
	{
		printToFile(node2->hashPointer->value);
	}
	printToFile("(");
	printAstreeNode(node3);
	printToFile(")");
	if(node4)
	{
		printToFile("\n");
		printAstreeNode(node4);
	}
	else
	{
		printToFile("\n");
	}
	printAstreeNode(node5);
}
void printArgDeclaration(astreeNode * node1, astreeNode * node2, astreeNode * node3)
{
	printAstreeNode(node1);
	printToFile(" ");
	printAstreeNode(node2);
	if(node3)
	{
		printToFile(",");
		printToFile(" ");
		printAstreeNode(node3);
	}
}
void printArgCall(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	if(node2)
	{
		printToFile(",");
		printToFile(" ");
		printAstreeNode(node2);
	}
	
}
void printScalarRead(astreeNode * node1)
{
	if(node1 && node1->hashPointer)
	{
		printToFile(node1->hashPointer->value);
	}
}
void printVectorRead(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	printToFile("[");
	printAstreeNode(node2);
	printToFile("]");
}
void printGetReference(astreeNode * node1)
{
	printToFile("&");
	printAstreeNode(node1);
}
void printPointer(astreeNode * node1)
{
	printToFile("*");
	printAstreeNode(node1);
}
void printFuncall(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	printToFile("(");
	printAstreeNode(node2);
	printToFile(")");
}
void printPar(astreeNode * node1)
{
	printToFile("(");
	printAstreeNode(node1);
	printToFile(")");
}

/*função auxiliar para a impressao de expressões binárias */
void printBin(char * operation, astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	printToFile(operation);
	printAstreeNode(node2);
}
void printAdd(astreeNode * node1, astreeNode * node2)
{
	printBin("+",node1,node2);
}
void printSub(astreeNode * node1, astreeNode * node2)
{
	printBin("-",node1,node2);
}
void printMul(astreeNode * node1, astreeNode * node2)
{
	printBin("*",node1,node2);
}
void printDiv(astreeNode * node1, astreeNode * node2)
{
	printBin("/",node1,node2);
}
void printOr(astreeNode * node1, astreeNode * node2)
{
	printBin("||",node1,node2);
}
void printAnd(astreeNode * node1, astreeNode * node2)
{
	printBin("&&",node1,node2);
}
void printLe(astreeNode * node1, astreeNode * node2)
{
	printBin("<=",node1,node2);
}
void printGe(astreeNode * node1, astreeNode * node2)
{
	printBin(">=",node1,node2);
}
void printEq(astreeNode * node1, astreeNode * node2)
{
	printBin("==",node1,node2);
}
void printNe(astreeNode * node1, astreeNode * node2)
{
	printBin("!=",node1,node2);
}
void printGreater(astreeNode * node1, astreeNode * node2)
{
	printBin(">",node1,node2);
}
void printLess(astreeNode * node1, astreeNode * node2)
{
	printBin("<",node1,node2);
}
void printBlock(astreeNode * node1)
{
	printToFile("{\n");
	printAstreeNode(node1);
	printToFile("\n}\n");
}
void printOutputList(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	if(node2)
	{
		printToFile(",");
		printToFile(" ");
		printAstreeNode(node2);
	}
}
void printScalarWrite(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	printToFile(" ");
	printToFile("=");
	printToFile(" ");
	printAstreeNode(node2);
	
}
void printVectorWrite(astreeNode * node1, astreeNode * node2, astreeNode * node3)
{
	printAstreeNode(node1);
	printToFile("[");
	printAstreeNode(node2);
	printToFile("]");
	printToFile(" ");
	printToFile("=");
	printToFile(" ");
	printAstreeNode(node3);
}
void printPointerWrite(astreeNode * node1, astreeNode * node2)
{
	printToFile("*");
	printAstreeNode(node1);
	printToFile(" ");
	printToFile("=");
	printToFile(" ");
	printAstreeNode(node2);
}
void printInput(astreeNode * node1)
{
	printToFile("input");
	printToFile(" ");
	printAstreeNode(node1);
}
void printOutput(astreeNode * node1)
{
	printToFile("output");
	printToFile(" ");
	printAstreeNode(node1);
}
void printReturn(astreeNode * node1)
{
	printToFile("return");
	printToFile(" ");
	printAstreeNode(node1);
}
void printIfThen(astreeNode * node1, astreeNode * node2)
{
	printToFile("if");
	printToFile("(");
	printAstreeNode(node1);
	printToFile(")");
	printToFile(" then ");
	printAstreeNode(node2);
}
void printIfThenElse(astreeNode * node1, astreeNode * node2, astreeNode * node3)
{
	printToFile("if");
	printToFile("(");
	printAstreeNode(node1);
	printToFile(")");
	printToFile(" then ");
	printAstreeNode(node2);
	printToFile(" else ");
	printAstreeNode(node3);
}
void printLoop(astreeNode * node1, astreeNode * node2)
{
	printToFile("loop");
	printToFile("(");
	printAstreeNode(node1);
	printToFile(") ");
	printAstreeNode(node2);
}
void printCmdSeq(astreeNode * node1, astreeNode * node2)
{
	printAstreeNode(node1);
	printToFile(";\n");
	printAstreeNode(node2);
}


void printAstreeNode(astreeNode * node)
{
	/* garantia de que não vai tentar imprimir nodo NULL */
	if(node)
	{
		switch(node->type)
		{
			/* literais e identificadores */
			case TK_IDENTIFIER: printIdentifier(node->hashPointer);	break;
			case LIT_INTEGER: 	printInteger(node->hashPointer); 	break;
			case LIT_TRUE: 		printLitTrue();						break;
			case LIT_FALSE: 	printLitFalse();					break;
			case LIT_STRING: 	printLitString(node->hashPointer);	break;
			case LIT_CHAR: 		printLitChar(node->hashPointer);	break;
			
			/* listas */
			case PROGRAM: 				printProgram(node->sons[0],node->sons[1]); 	break;	
			case LIT_LIST: 				printLitList(node->sons[0],node->sons[1]);	break;

			/* palavras reservadas de tipo */
			case BOOL: 					printBool();break;				
			case WORD: 					printWord();break;				
			case BYTE: 					printByte();break;
			
			/* declarações */
			case DECLARATION_SCALAR: 	printDeclarationScalar(node->sons[0],node->sons[1],node->sons[2]); 									break;	
			case DECLARATION_POINTER: 	printDeclarationPointer(node->sons[0],node->sons[1],node->sons[2]); 								break;	
			case DECLARATION_VECTOR: 	printDeclarationVector(node->sons[0],node->sons[1],node->sons[2],node->sons[3]); 					break;	
			case DECLARATION_FUNCTION: 	printDeclarationFunction(node->sons[0],node->sons[1],node->sons[2],node->sons[3],node->sons[4]); 	break;
			case ARG_DECLARATION: 		printArgDeclaration(node->sons[0],node->sons[1],node->sons[2]); 									break;	

			/* expressões */
			case ARGCALL: 				printArgCall(node->sons[0],node->sons[1]);		break;				
			case SCALAR_READ:			printScalarRead(node->sons[0]);					break;			
			case VECTOR_READ: 			printVectorRead(node->sons[0], node->sons[1]);	break;			
			case GET_REFERENCE: 		printGetReference(node->sons[0]);				break;		
			case POINTER: 				printPointer(node->sons[0]);					break;				
			case FUNCALL: 				printFuncall(node->sons[0],node->sons[1]);		break;				
			case PAR: 					printPar(node->sons[0]);						break;					
			case ADD: 					printAdd(node->sons[0], node->sons[1]);			break;					
			case SUB: 					printSub(node->sons[0], node->sons[1]);			break;					
			case MUL: 					printMul(node->sons[0], node->sons[1]);			break;					
			case DIV: 					printDiv(node->sons[0], node->sons[1]);			break;					
			case OR: 					printOr(node->sons[0], node->sons[1]);			break;					
			case AND: 					printAnd(node->sons[0], node->sons[1]);			break;					
			case LE: 					printLe(node->sons[0], node->sons[1]);			break;					
			case GE: 					printGe(node->sons[0], node->sons[1]);			break;					
			case EQ: 					printEq(node->sons[0], node->sons[1]);			break;					
			case NE: 					printNe(node->sons[0], node->sons[1]);			break;					
			case GREATER: 				printGreater(node->sons[0], node->sons[1]);		break;				
			case LESS: 					printLess(node->sons[0], node->sons[1]);		break;
				
			/* CMD e CMD_SEQ */	
			case BLOCK: 				printBlock(node->sons[0]);						break;				
			case OUTPUT_LIST: 			printOutputList(node->sons[0],node->sons[1]);	break;			
			case SCALAR_WRITE: 			printScalarWrite(node->sons[0],node->sons[1]);	break;		
			case VECTOR_WRITE: 			printVectorWrite(node->sons[0],node->sons[1],node->sons[2]);	break;		
			case POINTER_WRITE: 		printPointerWrite(node->sons[0],node->sons[1]);	break;		
			case INPUT: 				printInput(node->sons[0]);						break;				
			case OUTPUT: 				printOutput(node->sons[0]);						break;				
			case RETURN: 				printReturn(node->sons[0]);						break;				
			case IF_THEN: 				printIfThen(node->sons[0],node->sons[1]);		break;				
			case IF_THEN_ELSE: 			printIfThenElse(node->sons[0],node->sons[1],node->sons[2]);		break;		
			case LOOP: 					printLoop(node->sons[0],node->sons[1]);			break;
			case CMD_SEQ: 				printCmdSeq(node->sons[0],node->sons[1]);		break;
			
			/* default? */
			default : break;
		}
	}
}