#include "table.h"
#include "tokens.h"
#define T1 printf("<");
#define T2 printf(">\n");
// GUILHERME LEON BERNO DE JESUS
// EDUARDO FERREIRA

char * addTerminator(char* text)
{
	int j;
	char* value;
	value = (char*)calloc(strlen(text),sizeof(char));
	for(j=0 ; j<strlen(text); j++)
		value[j] = text[j];
	value[strlen(text)]='\0';
	return value;

}

void table_start(void)
{
	int i=0;
	for(i=0 ; i < HASH_SIZE ; i++)
		table[i] = NULL;
}
int table_address(char *text)
{
	int add =1;
	int i=0;
	for(i=0; i<strlen(text); ++i)
			add = ((add * text[i]) % HASH_SIZE ) +1;
	return add-1;
}
struct HNODE *table_insertTable(char *text, int type)
{
	struct HNODE *new;
	int add = table_address(text);
	int j;
	new = (struct HNODE*) calloc(1,sizeof(struct HNODE));
	new->type = type;
	new->dataType = 0;
	new->args = NULL;
	switch(type)
	{
		case SYMBOL_UNDEFINED: 
				break;
		case SYMBOL_LIT_INTEGER:
				new->value = addTerminator(text);
				break;
		case SYMBOL_LIT_FLOATING: 
				break;
		case SYMBOL_LIT_TRUE:	
				new->value = "TRUE";
				break;
		case SYMBOL_LIT_FALSE:
				new->value = "FALSE";
				break;
		case SYMBOL_LIT_CHAR:	
				new->value = (char*)calloc(2,sizeof(char));
				new->value[0] = text[1];
				new->value[1] = '\0';
				break;
		case SYMBOL_LIT_STRING:
				new->value = (char*)calloc(strlen(text)-1,sizeof(char));
				for(j=1 ; j < strlen(text)-1 ; j++)
					new->value[j-1]=text[j];
				new->value[strlen(text)-2]='\0';
				break;
		case SYMBOL_IDENTIFIER:	
				new->value = addTerminator(text);
				break;
	}
	new->next = table[add];
	
	
	if(!table_isInTable(text))
		table[add] = new;
	else
		return table_find(text);
	return new;

}
struct HNODE *table_find(char * text)
{
	int i;
	struct HNODE* node;
	struct HNODE* retNode;
	i = table_address(text);
	for(node=table[i]; strcmp(node->value,text)!=0 ; node = node->next);
	retNode=node;
	return retNode;
	
}

int table_isInTable(char* text)
{
	int i;
	int retValue=0;
	struct HNODE* node;
	
	for (i=0; i<HASH_SIZE; i++)
		for(node=table[i]; node; node = node->next)
			{
				if(strcmp(text,node->value)==0)
					retValue=1;
			}
	return retValue;
}



void table_print(void)
{
	int i=0;
	struct HNODE* node;
	struct intList * aux;
	printf("Iniciando print...\n");
	for(i=0 ; i<HASH_SIZE ; i++)
	{
		for(node = table[i] ; node ; node = node->next)
		{
			//printf("\nTEXTO: %s\n",node->value);
			switch(node->type)
			{
				case SYMBOL_IDENTIFIER: printf("Valor: %s | Tipo: IDENTIFIER\n",node->value); break;
				case SYMBOL_LIT_INTEGER: printf("Valor: %s | Tipo: INTEGER\n",node->value); break;
				case SYMBOL_LIT_FALSE: printf("Valor: %s | Tipo: FALSE\n", node->value); break;
				case SYMBOL_LIT_TRUE: printf("Valor: %s | Tipo: TRUE\n",node->value); break;
				case SYMBOL_LIT_CHAR: printf("Valor: %s | Tipo: CHAR\n",node->value); break;
				case SYMBOL_LIT_STRING: printf("Valor: %s | Tipo: STRING\n",node->value); break;
				case ID_SCALAR: printf("Valor: %s | Scalar %d\n",node->value,node->dataType); break;
				case ID_FUNC: printf("Valor: %s | Function %d | ",node->value,node->dataType); 
					for(aux = node->args ; aux != NULL ; aux = aux->next)	printf(" %d, ",aux->v); printf("\n");
					break;
				case ID_VECTOR: printf("Valor: %s | Vector %d\n",node->value,node->dataType); break;
				case ID_POINTER:printf("Valor: %s | Pointer %d\n",node->value,node->dataType); break;
			}
		}
	}
	printf("...fim do print.\n");
}


struct intList * insertInIntList(int value, struct intList * oldList)
{
	struct intList * new = (struct intList *)calloc(1,sizeof(struct intList));
	struct intList * aux = oldList;
	new->v = value;
	new->next = NULL;
	if(oldList)
	{
		for(aux = oldList ; aux->next != NULL ; aux = aux->next);	
		aux->next = new;
		return oldList;
	}
	return new;
}