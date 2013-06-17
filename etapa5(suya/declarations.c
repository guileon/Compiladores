#include <stdio.h>
#include <stdlib.h>


#include "astree.h"
#include "declarations.h"



DECLARATION * addDeclaration(DECLARATION ** declarationList, HASH_NODE * hashNode, int type)
{
	DECLARATION * newDec = malloc(sizeof(DECLARATION));
	
	newDec->type = type;
	newDec->hashNode = hashNode;
	newDec->arguments = NULL;
	newDec->escopoLocal = NULL;
	newDec->next = *declarationList;
	*declarationList = newDec;
	return newDec;

}

BOOL alreadyDeclared(DECLARATION * declarationList, HASH_NODE * hashNode)
{
	DECLARATION * dec = declarationList;
	
	while (dec != NULL)
	{
		if (dec->hashNode == hashNode)
			return TRUE;
		dec = dec->next;
	}	

	return FALSE;
}

DECLARATION * encontraDeclaracao(DECLARATION * declarationList, HASH_NODE * hashNode)
{
	DECLARATION * dec = declarationList;
	
	while (dec != NULL)
	{
		if (dec->hashNode == hashNode)
			return dec;
		dec = dec->next;
	}	

	return NULL;
}

DECLARATION * copyList(DECLARATION * list)
{	
	DECLARATION * newList = NULL;
	DECLARATION * decl;
	while (list != NULL)
	{
		decl = malloc(sizeof(DECLARATION));
		decl->hashNode = list->hashNode;
		decl->type = list->type;
		decl->arguments = NULL;
		decl->escopoLocal = NULL;
		decl->next = newList;
		newList = decl;

		list = list->next;
	}
	return newList;
}
