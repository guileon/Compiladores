#include<stdio.h>

#include "astree.h"
#include "tac.h"

//prototypes

//implementation

TAC* generateCode(ASTREE* node)
{
	int i;
	TAC *code[MAX_SONS];
	TAC *result;
	
	if (!node)
		return 0;
	
	//process children first recursivelly
	
	for (i=0; i<MAX_SONS; ++i)
		if (node->son[i])
			code[i] = generateCode(node->son[i]);
		else
			code[i] = 0;
	
	switch(node->type)
	{
		case ASTREE_SYMBOL: result = tac_create(TAC_SYMBOL, node->symbol, 0, 0); break; //nao temos SYMBOL
		case ASTREE_ADD: result = make_binop(code[0], code[1], TAC_ADD); break;
		case ASTREE_SUB: result = make_binop(code[0], code[1], TAC_SUB); break;
		case ASTREE_MUL: result = make_binop(code[0], code[1], TAC_MUK); break;
		case ASTREE_DIV: result = make_binop(code[0], code[1], TAC_DIV); break;
		case ASTREE_SCALAR_ASS: result = tac_join(code[0],tac_create(TAC_MOV,node->symbol,(code[0])?code[0]->target:0,0)); break;
		case ASTREE_IFTHEN: result makeIfThen(code[0], code[1]); break;
		default: result = tac_join(tac_join(tac_join(code[0],code[1]),code[2]),code[3]); break; //gambiarra para nao precisar implementar tudo agora
	}
	
	fprintf(stderr,"---\n"); //print na tela pra ver a construção
	tac_print_list(result);
	return result;
}

TAC* make_binop(TAC* code0, TAC* code1, int type)
{
	TAC *result;
	TAC *nova;
	
	result = tac_join(code0, code1); 
	nova = tac_create(type, makeTemp(), (code0!=0)?code0->target:0, (code1!=0)?code1->target:0); //codes ainda podem ser ponteiros nulos em operações nao implementadas
	nova->prev = result;     //poderiamos ter usado tac_join tambem
	result = nova;	
	return result;
}

TAC* makeIfThen(TAC* code0, TAC* code1)
{
	TAC *nova1;
	TAC *nova2;
	HASH_NODE * label;
	label = makeTemp()
	
	nova1 = tac_create(TAC_JZ, label, (code0!=0)?code0->target:0); 
	nova2 = tac_create(TAC_LABEL, label, 0, 0);
	
	return tac_join(tac_join(tac_join(code0,nova1), code1), nova2);
}

