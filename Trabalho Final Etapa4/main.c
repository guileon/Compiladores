#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char ** argv)
{
	
	int l;
	setFile(argv[1]);
	initMe();
	/*do{
		
		l = yylex();
		switch(l)
		{
			case 	KW_WORD:    	printf("Word on line %d\n",getLineNumber());	;break;  
			case 	KW_BOOL:    printf("Bool on line %d\n",getLineNumber());break;
			case     KW_BYTE:    printf("Byte on line %d\n",getLineNumber());  ;break;
			case     KW_IF:      printf("If on line %d\n",getLineNumber());  ;break;
			case     KW_THEN:     printf("Then on line %d\n",getLineNumber()); ;break;
			case     KW_ELSE:     printf("Else on line %d\n",getLineNumber()); ;break;
			case     KW_LOOP:     printf("Loop on line %d\n",getLineNumber()); ;break;
			case     KW_INPUT:    printf("Input on line %d\n",getLineNumber()); ;break;
			case     KW_RETURN:    printf("Return on line %d\n",getLineNumber());;break;
			case     KW_OUTPUT:    printf("Output on line %d\n",getLineNumber());;break;    
			case     OPERATOR_LE:  printf("Less or Equal on line %d\n",getLineNumber());;break;
			case     OPERATOR_GE:  printf("Greater or Equal on line %d\n",getLineNumber());;break;
			case     OPERATOR_EQ:  printf("Equal on line %d\n",getLineNumber());;break;
			case     OPERATOR_NE:  printf("Not Equal on line %d\n",getLineNumber());;break;
			case     OPERATOR_AND: printf("AND on line %d\n",getLineNumber());;break;
			case     OPERATOR_OR:  printf("OR on line %d\n",getLineNumber());;break;
			case     TK_IDENTIFIER: printf("Identifier on line %d\n",getLineNumber());;break;
			case     LIT_INTEGER:  printf("Integer on line %d\n",getLineNumber());;break;
			case     LIT_FALSE:    printf("False on line %d\n",getLineNumber());;break;
			case     LIT_TRUE:	 printf("True on line %d\n",getLineNumber());;break;
			case     LIT_CHAR:   printf("Char on line %d\n",getLineNumber());;break;  
			case     LIT_STRING: printf("String on line %d\n",getLineNumber());;break;  
			case     TOKEN_ERROR: printf("ERROR on line %d\n",getLineNumber());;break;
			default: break;
		}        
	}while(isRunning());*/
	//char d[5];
	char * ret = argv[2];
	//char * aux = malloc(sizeof(char)*strlen(ret));
	
	//strcpy(aux,ret);
	
	//strcpy(d,"del ");
	
	//strcat(d,ret);
	
	
	
	//system("del out.txt"); 
	
	a_setFile(ret);
	yyparse();

	//getchar();
	//printHash();
	//printf("oi");
	system(ret);
	exit(0);
	//getchar();
	
}