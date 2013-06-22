/* 	hash armazena a estrutura e os métodos para se lidar com
	uma tabela hash, além de possuir a estrutura de uma lista
	de inteiros, utilizada para armazenar os tipos dos argu-
	mentos de uma função */
	
#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "test.h"

#define HASH_SIZE 997

/* estrutura para armazenar o tipo da lista de argumentos da função  */
struct intList_s;
struct intList_s
{
	int value;
	struct intList_s * next;
};
typedef struct intList_s intList;

/* estrutura para armazenar o nodo da hash */
struct hashNode_s;
struct hashNode_s
{
	int type;
	int dataType;
	char * value;
	struct hashNode_s * next;
	intList * functionArguments;
	
};
typedef struct hashNode_s hashNode;

/* armazenamento global da hash */
hashNode * hashTable[HASH_SIZE];

int nextTempNumber;
int nextLabelNumber;

/* funções de acesso a hash */
void startHash();
void printHash();
intList * insertIntList(int value_, intList * oldList);
hashNode * insertHash(char * text, int type);
hashNode * newTemp();
hashNode * newLabel();


#endif