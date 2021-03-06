#ifndef _declarations_h_
#define _declarations_h_

#include "hash.h"

//tipos de identificadores
#define ERRO 1
#define ID_ESCALAR 2
#define ID_VETOR 3
#define ID_PONTEIRO 4
#define ID_FUNCAO 5

#define TIPO_WORD 6 //variavel
#define TIPO_BYTE 7
#define TIPO_BOOL 8


#define TLIT_STRING 9
#define TLIT_BOOL 10
#define TLIT_CHAR 11
#define TLIT_INT 12

#define TIPO_PWORD 13
#define TIPO_PBYTE 14
#define TIPO_PBOOL 15

#define TIPO_VWORD 16
#define TIPO_VBYTE 17
#define TIPO_VBOOL 18

#define TIPO_FWORD 19
#define TIPO_FBYTE 20
#define TIPO_FBOOL 21


//lista de declaracoes
typedef struct declaration
{
	HASH_NODE * hashNode;
	int type;	
	struct declaration * arguments;
	struct declaration * escopoLocal;	
	struct declaration * next;

} DECLARATION;

DECLARATION * addDeclaration(DECLARATION ** declarationList, HASH_NODE * hashNode, int type);
BOOL alreadyDeclared(DECLARATION * declarationList, HASH_NODE * hashNode);
DECLARATION * encontraDeclaracao(DECLARATION * declarationList, HASH_NODE * hashNode);
DECLARATION * copyList(DECLARATION * list);


#endif
