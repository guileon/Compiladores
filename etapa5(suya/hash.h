/*
Grupo: Bruno Gabriel Fernandes - Suya Castilhos

Rotinas de Hash
*/

#ifndef _HASH_H__
#define _HASH_H__

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define HASH_SIZE 997

typedef struct hash_node
{
int type;
char *text;
struct hash_node *next;
} HASH_NODE;


void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashInsert(char *text, int type);
HASH_NODE *hashFind(char * text);
void hashPrint(void);
HASH_NODE *nodeAlreadyExists(char * text, int type);
HASH_NODE *makeTemp(void);
HASH_NODE *makeLabel(void);

#endif

