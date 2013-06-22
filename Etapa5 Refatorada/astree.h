/* 	astree aramazena os métodos de criação e impressão em arquivo
	de uma abstract sintax tree, ela também possui a função doAll
	que realiza a impressão da árvore e a sua avaliação semântica */


#ifndef ASTREE
#define ASTREE

#include "hash.h"
#include "tokens.h"
#include "test.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* número máximo de filhos de um nodo */
#define MAX_SONS 5

/* tipo que representa um nodo da astree */
struct astreeNode_s;
struct astreeNode_s
{
	int type;
	struct astreeNode_s * sons[MAX_SONS];
	hashNode * hashPointer;
	int lineNumber;
};

typedef struct astreeNode_s astreeNode;

#include "semantic.h"

/* variaveis usadas para acesso ao arquivo */
FILE * pfile;
int firstTime;
char * filename;

void setFileName(char * filename_);
void doAll(astreeNode * node);
void printAstreeNode(astreeNode * node);
astreeNode * newAstreeNode(int type_, astreeNode * son1, astreeNode * son2, astreeNode * son3, astreeNode * son4, astreeNode * son5, hashNode * hashPointer_, int lineNumber_);

#endif