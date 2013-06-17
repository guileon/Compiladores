#include<stdio.h>

#ifndef TAC_HEAD
#define TAC_HEADER

#define TAC_SYMBOL 
#define TAC_ADD
#define TAC_SUB
#define TAC_MUL
#define TAC_DIV
#define TAC_MOV
#define TAC_JZ
#define TAC_LABEL

#endif

typedef struct tac_node
{
  int type;
  HASH_NODE * target;
  HASH_NODE * op1;
  HASH_NODE * op2;
  struct tac_node * prev;
  struct tac_node * next;
} TAC;

TAC * tac_create(int type, HASH_NODE *target, HASH_NODE *op1, HASH_NODE *op2);
TAC * tac_join(TAC *l1, TAC *l2);
void tac_print_single(TAC *t);
void tac_print_list(TAC *first);
