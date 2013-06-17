#include <stdio.h>
#include <stdlib.h>
#include "astree.h"


ASTREE *astreeCreate(int type, ASTREE*s0, ASTREE*s1, ASTREE*s2, ASTREE*s3, ASTREE*s4, HASH_NODE * hashNode, int lineNumber)
{
	ASTREE *node =0;
	
	
	node = (ASTREE*) malloc(sizeof(ASTREE));
	node->lineNumber = lineNumber;	
	node->type = type;
	node->hashNode = hashNode;
	node->son[0] = s0;
	node->son[1] = s1;
	node->son[2] = s2;
	node->son[3] = s3;
	node->son[4] = s4;
	return node;
}

void astreePrintSingle(ASTREE *node)
{
	if (!node)
		return;
	fprintf(stderr,"ASTREE(");
	switch (node->type)
	{
		case ASTREE_ADD: fprintf(stderr, "ASTREE ADD"); break;
		case ASTREE_SUB: fprintf(stderr, "ASTREE SUB"); break;
		case ASTREE_MUL: fprintf(stderr, "ASTREE MUL"); break;
		case ASTREE_DIV: fprintf(stderr, "ASTREE DIV"); break;
		case ASTREE_VARDEC_VAR: fprintf(stderr, "ASTREE VARDEC VAR"); break;
		case ASTREE_VARDEC_PTR: fprintf(stderr, "ASTREE VARDEC PTR"); break;
		case ASTREE_VARDEC_VECTOR: fprintf(stderr, "ASTREE VARDEC VECTOR"); break;
		case ASTREE_VARDEC_VECTOR_INITIALIZED: fprintf(stderr, "ASTREE VARDEC VECTOR INITIALIZED"); break;
		case ASTREE_IDENTIFIER: fprintf(stderr, "ASTREE IDENTIFIER"); break;
		case ASTREE_INTEGERLIT: fprintf(stderr, "ASTREE INTEGERLIT"); break;
		case ASTREE_LISTLIT: fprintf(stderr, "ASTREE LISTLIT"); break;
		case ASTREE_VARLIT_INTEGER: fprintf(stderr, "ASTREE VARLIT INTEGER"); break;
		case ASTREE_VARLIT_FALSE: fprintf(stderr, "ASTREE VARLIT FALSE"); break;
		case ASTREE_VARLIT_TRUE: fprintf(stderr, "ASTREE VARLIT TRUE"); break;
		case ASTREE_VARLIT_CHAR: fprintf(stderr, "ASTREE VARLIT CHAR"); break;
		case ASTREE_VARLIT_STRING: fprintf(stderr, "ASTREE VARLIT STRING"); break;
		case ASTREE_VARTYPE_WORD: fprintf(stderr, "ASTREE VARTYPE WORD"); break;
		case ASTREE_VARTYPE_BOOL: fprintf(stderr, "ASTREE VARTYPE BOOL"); break;
		case ASTREE_VARTYPE_BYTE: fprintf(stderr, "ASTREE VARTYPE BYTE"); break;
		
		case ASTREE_ARG_LIST: fprintf(stderr, "ASTREE LIST ARGUMENTS"); break;
		case ASTREE_LIST_LOCAL: fprintf(stderr, "ASTREE LIST LOCAL DECLARATIONS"); break;
		case ASTREE_BODY: fprintf(stderr, "ASTREE BODY"); break;
		case ASTREE_FUNC: fprintf(stderr, "ASTREE FUNC"); break;
		case ASTREE_PROGRAM: fprintf(stderr, "ASTREE PROGRAM"); break;
		case ASTREE_LISTARG: fprintf(stderr, "ASTREE LISTARG"); break;
		case ASTREE_LISTARG_VIRG: fprintf(stderr, "ASTREE LISTARG VIRG"); break;
		case ASTREE_LOCALDEC_VAR: fprintf(stderr, "ASTREE LOCALDEC VAR"); break;
		case ASTREE_LOCALDEC_PTR: fprintf(stderr, "ASTREE LOCALDEC PTR"); break;
		case ASTREE_LISTCOM: fprintf(stderr, "ASTREE LISTCOM"); break;
		case ASTREE_COM_ATR: fprintf(stderr, "ASTREE COM ATR"); break;
		case ASTREE_COM_ATR_VECTOR: fprintf(stderr, "ASTREE COM ATGR VECTOR"); break;
		case ASTREE_COM_INPUT: fprintf(stderr, "ASTREE COM INPUT"); break;
		case ASTREE_COM_OUTPUT: fprintf(stderr, "ASTREE COM OUTPUT"); break;
		case ASTREE_COM_RETURN: fprintf(stderr, "ASTREE COM RETURN"); break;
		case ASTREE_COM_IFTHEN: fprintf(stderr, "ASTREE COM IFTHEN"); break;
		case ASTREE_COM_IFTHENELSE: fprintf(stderr, "ASTREE COM IFTHENELSE"); break;
		case ASTREE_COM_LOOP: fprintf(stderr, "ASTREE COM LOOP"); break;
		case ASTREE_LISTOUT: fprintf(stderr, "ASTREE LISTOUT"); break;
		case ASTREE_EXP_VECTOR: fprintf(stderr, "ASTREE EXP VECTOR"); break;
		case ASTREE_EXP_PARENTESES: fprintf(stderr, "ASTREE EXP PARENTESES"); break;
		case ASTREE_EXP_LESSER: fprintf(stderr, "ASTREE EXP LESSER"); break;
		case ASTREE_EXP_GREATER: fprintf(stderr, "ASTREE EXP GREATER"); break;
		case ASTREE_EXP_SINGLEEQ: fprintf(stderr, "ASTREE EXP SINGLEEQ"); break;
		case ASTREE_EXP_NOT: fprintf(stderr, "ASTREE EXP NOT"); break;
		case ASTREE_EXP_LE: fprintf(stderr, "ASTREE EXP LE"); break;
		case ASTREE_EXP_GE: fprintf(stderr, "ASTREE EXP GE"); break;
		case ASTREE_EXP_EQ: fprintf(stderr, "ASTREE EXP EQ"); break;
		case ASTREE_EXP_NE: fprintf(stderr, "ASTREE EXP NE"); break;
		case ASTREE_EXP_AND: fprintf(stderr, "ASTREE EXP AND"); break;
		case ASTREE_EXP_OR: fprintf(stderr, "ASTREE EXP OR"); break;
		case ASTREE_EXP_FUNCALL: fprintf(stderr, "ASTREE EXP FUNCALL"); break;
		case ASTREE_EXP_ADDR: fprintf(stderr, "ASTREE EXP ADDR"); break;
		case ASTREE_EXP_PTRVALUE: fprintf(stderr, "ASTREE EXP PTRVALUE"); break;
		case ASTREE_LISTPARAM: fprintf(stderr, "ASTREE EXP LISTPARAM"); break;


		default: fprintf(stderr,"ASTREE UNKNOWN"); break;
	}

	if (node->hashNode != NULL)
		fprintf(stderr, ", VALUE=\"%s\"", node-> hashNode->text);

	fprintf(stderr,")\n");
}

void astreePrintRecursive(ASTREE *node, int depth)
{
	int i;	
	if (node == NULL)
		return;
	
	//identacao
	for (i = 0; i < depth; i++)
		fprintf(stderr, "\t");
	astreePrintSingle(node);
	
	//imprime os filhos
	for (i = 0; i < MAX_SONS; i++)
		if (node->son[i])
			astreePrintRecursive(node->son[i], depth + 1);

}



void astreePrintTree(ASTREE *node)
{
	astreePrintRecursive(node, 0);
}



void astreePTFRecursive(ASTREE * node, FILE * pFile)
{
	if (node == NULL)
		return;

	switch (node->type)
	{
		case ASTREE_ADD: astreePTFRecursive(node->son[0], pFile); fputs(" + ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_SUB: astreePTFRecursive(node->son[0], pFile); fputs(" - ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_MUL: astreePTFRecursive(node->son[0], pFile); fputs(" * ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_DIV: astreePTFRecursive(node->son[0], pFile); fputs(" / ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_VARDEC_VAR: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" : ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ; ", pFile); break;
		case ASTREE_VARDEC_PTR: astreePTFRecursive(node->son[0], pFile); fputs(" $ ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" : ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ; ", pFile); break;
		case ASTREE_VARDEC_VECTOR: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" [ ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ] ; ", pFile); break;
		case ASTREE_VARDEC_VECTOR_INITIALIZED: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" [ ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ] : ", pFile); astreePTFRecursive(node->son[3], pFile); fputs(" ; ", pFile); break;
		case ASTREE_IDENTIFIER: fputs(node->hashNode->text, pFile); fputs(" ", pFile); break;
		case ASTREE_INTEGERLIT: fputs(node->hashNode->text, pFile); fputs(" ", pFile); break;
		case ASTREE_LISTLIT: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_VARLIT_INTEGER: fputs(node->hashNode->text, pFile); fputs(" ", pFile); break;
		case ASTREE_VARLIT_FALSE: fputs("FALSE ", pFile); break;
		case ASTREE_VARLIT_TRUE: fputs("TRUE ", pFile); break;
		case ASTREE_VARLIT_CHAR: fputs("'", pFile); fputs(node->hashNode->text, pFile); fputs("' ", pFile); break;
		case ASTREE_VARLIT_STRING: fputs("\"", pFile); fputs(node->hashNode->text, pFile); fputs("\" ", pFile); break;
		case ASTREE_VARTYPE_WORD: fputs("word ", pFile); break;
		case ASTREE_VARTYPE_BOOL: fputs("bool ", pFile); break;
		case ASTREE_VARTYPE_BYTE: fputs("byte ", pFile); break;
		
		case ASTREE_ARG_LIST: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); break;
		case ASTREE_LIST_LOCAL: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_BODY: fputs(" { ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" } ", pFile); break;
		case ASTREE_FUNC: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ( ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ) ", pFile); astreePTFRecursive(node->son[3], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[4], pFile); fputs(" ", pFile); break;
		case ASTREE_PROGRAM: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_LISTARG: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_LISTARG_VIRG: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" , ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ", pFile); break;
		case ASTREE_LOCALDEC_VAR: astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" : ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ; ", pFile); break;
		case ASTREE_LOCALDEC_PTR: astreePTFRecursive(node->son[0], pFile); fputs(" $ ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" : ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ; ", pFile); break;
		case ASTREE_LISTCOM: astreePTFRecursive(node->son[0], pFile); fputs(" ; ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_ATR: astreePTFRecursive(node->son[0], pFile); fputs(" = ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_ATR_VECTOR: astreePTFRecursive(node->son[0], pFile); fputs(" [ ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ] = ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_INPUT: fputs(" input ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_OUTPUT: fputs(" output ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_RETURN:  fputs(" return ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_IFTHEN: fputs(" if ( ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ) then ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;  
		case ASTREE_COM_IFTHENELSE: fputs(" if ( ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ) then ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" else ", pFile); astreePTFRecursive(node->son[2], pFile); fputs(" ", pFile); break;
		case ASTREE_COM_LOOP: fputs(" loop ( ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ) ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break; 
		case ASTREE_LISTOUT:  astreePTFRecursive(node->son[0], pFile); fputs(" , ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_VECTOR: astreePTFRecursive(node->son[0], pFile); fputs(" [ ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ] ", pFile);
		case ASTREE_EXP_PARENTESES:  fputs(" ( ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ) ", pFile); break;
		case ASTREE_EXP_LESSER: astreePTFRecursive(node->son[0], pFile); fputs(" < ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;	
		case ASTREE_EXP_GREATER: astreePTFRecursive(node->son[0], pFile); fputs(" > ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_SINGLEEQ: astreePTFRecursive(node->son[0], pFile); fputs(" = ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_NOT: astreePTFRecursive(node->son[0], pFile); fputs(" ! ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_LE: astreePTFRecursive(node->son[0], pFile); fputs(" <= ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_GE: astreePTFRecursive(node->son[0], pFile); fputs(" >= ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_EQ: astreePTFRecursive(node->son[0], pFile); fputs(" == ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_NE: astreePTFRecursive(node->son[0], pFile); fputs(" != ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_AND: astreePTFRecursive(node->son[0], pFile); fputs(" && ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_OR: astreePTFRecursive(node->son[0], pFile); fputs(" || ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_FUNCALL: astreePTFRecursive(node->son[0], pFile); fputs(" ( ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ) ", pFile); break;
		case ASTREE_EXP_ADDR: fputs(" & ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); break;
		case ASTREE_EXP_PTRVALUE: fputs(" * ", pFile); astreePTFRecursive(node->son[0], pFile); fputs(" ", pFile); break;
		case ASTREE_LISTPARAM: astreePTFRecursive(node->son[0], pFile); fputs(" & ", pFile); astreePTFRecursive(node->son[1], pFile); fputs(" ", pFile); break;


		default: fprintf(stderr,"ASTREE UNKNOWN"); break;
	}
}

void astreePrintToFile(ASTREE *node, char * fileName)
{
	FILE * pFile = fopen(fileName, "w");
	
	astreePTFRecursive(node, pFile);	

	fclose(pFile);
}
