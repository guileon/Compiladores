#include <stdio.h>

#include "hash.h"

int main (int argc, char *argv[])
{
	HASH_NODE * nodo;

	printf("Iniciando hash...\n");
	hashInit();
	
	nodo = hashInsert("Teste",1);
	nodo = hashInsert("Teste2",1);
	nodo = hashInsert("Teste3",1);
	nodo = hashInsert("Teste4",1);
	nodo = hashInsert("Teste5",1);
	nodo = hashInsert("Teste2",1);

	hashPrint();

	
	return 0;

}
