/*
Grupo: Bruno Gabriel Fernandes - Suya Castilhos

Rotinas de Hash

Para Modo Debug, descomente a linha "#define DEBUG_ON"

*/

//#define DEBUG_ON

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "hash.h"
#include "astree.h"
#include "y.tab.h"




HASH_NODE *Table[HASH_SIZE];

void hashInit(void)
{
int i;
for (i=0; i< HASH_SIZE; ++i)
        Table[i]=0;
}

int hashAddress(char *text)
{
        int add =1;
        int i=0;
        for(i=0; i<strlen(text); ++i)
                add = ((add * text[i]) % HASH_SIZE ) +1;
        return add-1;
}

HASH_NODE *hashInsert(char *text, int type)
{
        HASH_NODE *node;
	
	//se for do tipo char ou string, retira a primeira e a ultima letra
	if ((type == LIT_CHAR) || (type == LIT_STRING))
	{
		#ifdef DEBUG_ON
			fprintf(stderr, "Entrei no tratador de remocao de envelope.\n", text, type);
		#endif
		strcpy(text, text+1);
		text[strlen(text)-1] = '\0'; 
	}

#ifdef DEBUG_ON
	fprintf(stderr, "Novo simbolo (%s) tipo %d\n", text, type);
#endif

	//so insere se nao existe simbolo na tabela com o mesmo tipo	
	if ((node = nodeAlreadyExists(text, type)) != NULL)
		return node;

#ifdef DEBUG_ON
	fprintf(stderr, "Nodo inserido.\n");
#endif

        int address = hashAddress(text);
        node = (HASH_NODE*) calloc(1,sizeof(HASH_NODE));
        node->type = type;
        node->text = (char *) calloc(strlen(text)+1,sizeof(char));
        strcpy(node->text,text);
        
        node->next = Table[address];
        Table[address] = node;
        return node;

}


HASH_NODE *hashFind(char * text)
{
 
HASH_NODE* node;
node = Table[hashAddress(text)]; 
                
for( ; node; node = node->next)
	if (strcmp(node->text, text) == 0)
	{
		#ifdef DEBUG_ON
			fprintf(stderr,"(Simbolo (%s) ja esta na tabela)\n", text);
		#endif
		return node;
	}
 
return NULL;                
}

void hashPrint(void)
{
	int i;	
	HASH_NODE * node;
	
	for (i = 0; i < HASH_SIZE; i++)
	{
		for (node = Table[i]; node; node = node->next)
		{
			fprintf(stderr, "Node(%s) \n", node->text);
		}
	}

}

HASH_NODE * nodeAlreadyExists(char * text, int type)
{
	HASH_NODE* node;
	node = Table[hashAddress(text)]; 
                
	for( ; node; node = node->next)
		if ((strcmp(node->text, text) == 0) && (node->type == type))
		{
#ifdef DEBUG_ON
			fprintf(stderr,"(Simbolo (%s) do tipo %d ja esta na tabela)\n", text, type);
#endif
			return node;
		}
 
	return NULL;    
}

HASH_NODE *makeTemp()
{
    static int nextTemp = 0;
    char buffer[128];

    sprintf(buffer, "__Temporarioo$_%d", nextTemp++);

    return hashInsert(buffer, SCALAR);
}

HASH_NODE *makeLabel()
{
    static int nextTemp = 0;
    char buffer[128];

    sprintf(buffer, "__Temporarioo$_%d", nextTemp++);

    return hashInsert(buffer, SYMBOL_LABEL); //existe symbol_label?
}
