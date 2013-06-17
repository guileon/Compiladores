#include <stdio.h>
#include "hash.h"
#include "tokens.h"
#include "astree.h"
#include "sintaxe.h"
#include "SemanticaSegundaPAssada.h"

int yydebug=1; 

int yylex();
extern char *yytext;
extern int running;
extern FILE *yyin;

ASTREE * arvore;

extern int running;
void initMe(void);

int main(int argc, char** argv)
{
  int tok = 0;
	if (argc < 3)
	{
		fprintf( stderr, "\nUso: ./etapa3 source_file output_file\n");
		exit(1);
	}

	//inicializacao
	initMe();
	

	//testar abertura do arquivo
	if(!(yyin = fopen(argv[1],"r")))
	{
		fprintf(stderr, "cannot open file\"%s\".\n",argv[1]);
		exit(2);
	}
	

	
	yyparse();



	fprintf(stderr, "Successful analysis.\n");
	//hashPrint();
	
	//imprime a arvore de analise
	//astreePrintTree(arvore);

	//verifica sintaxe
	if (VerificaPrimeiraPassada(arvore) == FALSE)
		fprintf(stderr, "Encontrado(s) erro(s) de semantica na primeira passada.\n\n");
	else
		fprintf(stderr, "Semantica OK primeira passada.\n\n");
	
	
	if (Verifica2Passada(arvore) == FALSE)
		fprintf(stderr, "Encontrado(s) erro(s) de semantica na segnda passada.\n\n");
	else
		fprintf(stderr, "Semantica OK segunda passada.\n\n");

	imprimeDeclaracoes();

	//cria o arquivo equivalente
	astreePrintToFile(arvore, argv[2]);

	exit(0);

}
