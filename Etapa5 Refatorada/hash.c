#include "hash.h"
/* função de ipressão de tokens */
void printToken(int token)
{
	switch(token)
	{
		case TEMP:					fprintf(stderr,"TEMP");			break;
		case LABEL:					fprintf(stderr,"LABEL");		break;
		case SYMBOL_LIT_INTEGER: 	fprintf(stderr,"INT");			break;
		case SYMBOL_LIT_TRUE : 		fprintf(stderr,"TRUE");			break;
		case SYMBOL_LIT_FALSE : 	fprintf(stderr,"FALSE");		break;
		case SYMBOL_LIT_CHAR : 		fprintf(stderr,"CHAR");			break;
		case SYMBOL_LIT_STRING : 	fprintf(stderr,"STRING");		break;
		case SYMBOL_IDENTIFIER : 	fprintf(stderr,"IDENTIFIER");	break;

		case ID_SCALAR	:	 		fprintf(stderr,"SCALAR");		break;
		case ID_POINTER	:	 		fprintf(stderr,"POINTER");		break;
		case ID_VECTOR		: 		fprintf(stderr,"VECTOR");		break;
		case ID_FUNCTION	: 		fprintf(stderr,"FUNCTION");		break;
				
		case T_INTEGER	:	 		fprintf(stderr,"INTEGER");		break;
		case T_BOOLEAN	: 			fprintf(stderr,"BOOLEAN");		break;
		case BOOL:  				fprintf(stderr,"BOOL");			break;
		case WORD:  				fprintf(stderr,"WORD");			break;
		case BYTE:		 			fprintf(stderr,"BYTE");			break;
	}
}
/* função de utilização de intList */
intList * insertIntList(int value_, intList * oldList)
{
	intList * new = (intList *)calloc(1,sizeof(intList));
	intList * aux = oldList;
	new->value = value_;
	new->next = NULL;
	
	if(oldList)
	{
		for(aux = oldList ; aux->next != NULL ; aux = aux->next);
		aux->next = new;
		return oldList;
	}
	return new;
}

/* inicializa a hash */
void startHash()
{
	int i=0;
	
	nextTempNumber =0;
	nextLabelNumber =0;
	for(i=0 ; i < HASH_SIZE ; i++)
		hashTable[i] = NULL;
}

/* exibe um unico nodo */
void printNode(hashNode * node)
{
	intList * intListAux = NULL;

	if(node)
	{
		fprintf(stderr,"Type: ");printToken(node->type);fprintf(stderr,"| DataType: ");printToken(node->dataType);fprintf(stderr," | Value: %s |",node->value);
		
		for(intListAux = node->functionArguments ; intListAux ; intListAux = intListAux->next)
		{
			fprintf(stderr,"Argument: "); printToken(intListAux->value);fprintf(stderr," | ");
		}
		
		fprintf(stderr,"\n");
	}	
}

/* exibe toda a hash */
void printHash()
{
	int i=0;
	hashNode * node = NULL;
	
	fprintf(stderr,"Imprimindo a hash...\n");
	
	for(i=0 ; i < HASH_SIZE ; i++)
		for(node = hashTable[i] ; node ; node = node->next)
		{
			printNode(node);
		}
	fprintf(stderr,"Fim da impressao...\n");	
}

/* 	Função para obter um nodo da hash, buscando pelo campo 'value'
	Retorna NULL se não encontrar o valor */
hashNode * getNode(char *text)
{
	int i=0;
	hashNode * node = NULL;
	
	for(i=0 ; i < HASH_SIZE ; i++)
		for(node = hashTable[i] ; node ; node = node->next)
		{
			if(strcmp(node->value,text) == 0)
			{
				return node;
			}
		}
	return NULL;

}

/*	gera o valor de endereço da hash baseado na string */
int address(char * text)
{
	int add =1;
	int i=0;
	
	for(i=0; i<strlen(text); ++i)
	{
			add = ((add * text[i]) % HASH_SIZE ) +1;
	}
	return add-1;
}

/* adiciona um caractere terminador no final de uma string */
char * addTerminator(char* text)
{
	
	int j = 0;
	char* value = NULL;
	
	value = (char*)calloc(strlen(text),sizeof(char));
	for(j=0 ; j<strlen(text); j++)
		value[j] = text[j];
	value[strlen(text)]='\0';
	
	return value;

}

/* insere nodo na hash */
hashNode * insertHash(char * text, int type)
{
	/* inicialização das variáveis */
	int newAddress = 0;
	int j=0;
	hashNode * newNode = calloc(1,sizeof(hashNode));
	hashNode * returnValue = NULL;
	hashNode * existingNode = NULL;
	
	newAddress = address(text);
	
	/* switch do tipo para decidir como tratar o texto */
	switch(type)
	{
		case SYMBOL_LIT_INTEGER:
			newNode->value = addTerminator(text);
			break;
		case SYMBOL_LIT_TRUE:
			newNode->value = "TRUE";
			break;
		case SYMBOL_LIT_FALSE:
			newNode->value = "FALSE";
			break;
		case SYMBOL_LIT_CHAR:
			newNode->value = (char*)calloc(2,sizeof(char));
			newNode->value[0] = text[1];
			newNode->value[1] = '\0';
			break;
		case SYMBOL_LIT_STRING:
			newNode->value = (char*)calloc(strlen(text)-1,sizeof(char));
			for(j=1 ; j < strlen(text)-1 ; j++)
				newNode->value[j-1]=text[j];
			newNode->value[strlen(text)-2]='\0';
			break;
		case SYMBOL_IDENTIFIER:
			newNode->value = addTerminator(text);
			break;
		default: 
			newNode->value = addTerminator(text);  
			break;
	}
	
	/* teste para ver se não está na hash */
	existingNode = getNode(newNode->value);
	
	if(!existingNode)
	{
		/* atribuição do novo nodo */
		newNode->type = type;
		newNode->dataType = 0;
		newNode->next = hashTable[newAddress];
		newNode->functionArguments = NULL;

		hashTable[newAddress] = newNode;
		returnValue = newNode;
	}
	else
	{
		/* retorna o nodo já existente */
		returnValue = existingNode;
	}
	
	if(!returnValue)
	{
		fprintf(stderr,"CUIDADO : insert da Hash retornando valor NULL\n");
	}
	
	return returnValue;
	
}

/* cria novo temporario */
hashNode * newTemp()
{
	char tempName[20] = "";
	
	sprintf(tempName,"_temp%d",nextTempNumber);
	nextTempNumber++;
	return insertHash(tempName,TEMP);
}

/* cria nova label */
hashNode * newLabel()
{
	char labelName[20] ="";
	sprintf(labelName,"_label%d",nextLabelNumber);
	nextLabelNumber++;
	return insertHash(labelName,LABEL);
}