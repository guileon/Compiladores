
#include "astree.h"
#include "declarations.h"

int Tipo(ASTREE * node);
HASH_NODE * Identificador (ASTREE * node);
int TipoLiteral(ASTREE * node);
BOOL TiposEquivalentes(int tipo, int tipoLit);
int TipoP(ASTREE * node);
int TipoV(ASTREE * node);
HASH_NODE * TamanhoVetor (ASTREE * node);
BOOL verificaListLit(ASTREE * node, int tipo);
int TipoF(ASTREE * node);
BOOL InsereArgumentos (DECLARATION * declaracao, ASTREE * node);
BOOL InsereDeclaracoesLocais(DECLARATION * declaracao, ASTREE * node);

DECLARATION * escopoGlobal = NULL;

void imprimeDeclaracoes()
{
	DECLARATION * decl = escopoGlobal;
	DECLARATION * intern;	
	
	fprintf(stderr, "LISTA DE DECLARACOES: \n");

	while (decl != NULL)
	{
		fprintf(stderr, "Tipo: %d Nome: %s\n", decl->type, decl->hashNode->text);
		fprintf(stderr, "Argumentos: \n");
		intern = decl->arguments;
		while (intern != NULL)
		{
			fprintf(stderr, "\tTipo: %d Nome: %s\n", intern->type, intern->hashNode->text);
			intern = intern->next;
		}
		fprintf(stderr, "Escopo Local: \n");
		intern = decl->escopoLocal;
		while (intern != NULL)
		{
			fprintf(stderr,"\tTipo: %d Nome: %s\n", intern->type, intern->hashNode->text);
			intern = intern->next;
		}
		
		decl = decl->next;
	}

}

BOOL temErro = FALSE;
BOOL VerificaPrimeiraPassada(ASTREE * node)
{
	temErro = FALSE;
	
	Verifica(node);

	return !temErro;
}

BOOL Verifica(ASTREE * node)
{
	int tipo, tipoLit;
	HASH_NODE * hashNode;
	HASH_NODE * tamanho;
	DECLARATION * declaracao;
	
	if (node == NULL)
		return TRUE;

	
		
	switch(node->type)
	{

		case ASTREE_PROGRAM:
			Verifica(node->son[0]); 
			Verifica(node->son[1]);
			
			break;		
		case ASTREE_VARDEC_VAR:
			//fprintf(stderr, "AQUI\n"); 
			//tipo
			tipo = Tipo(node->son[0]);
			if (tipo == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}

			//identificador
			hashNode = Identificador(node->son[1]);	
			if (hashNode == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}

			//literal, verifica o tipo
			tipoLit = TipoLiteral(node->son[2]);
			if (tipoLit == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}
			
			
			//verifica se os tipos são adequados
			if (!TiposEquivalentes(tipo, tipoLit))
			{
				fprintf(stderr, "Erro semantica TIPO ERRADO linha %d \n", node->lineNumber);
				temErro = TRUE;
			}

			//verifica se eh declaracao dupla
			if (alreadyDeclared(escopoGlobal, hashNode))
			{
				fprintf(stderr, "Erro semantica DECLARACAO DUPLA linha %d \n", node->lineNumber);
				temErro = TRUE;
			}

			//insere na lista de declaracoes
			addDeclaration(&escopoGlobal, hashNode, tipo);			
			
			//debug
			//fprintf(stderr, "VERIFICADO VARDEC VAR TIPO:%d IDENTIFICADOR:%s TIPOLIT:%d\n", tipo, hashNode->text, tipoLit);

			break;

		case ASTREE_VARDEC_PTR:
			//tipo
			tipo = TipoP(node->son[0]);
			if (tipo == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}	
			//identificador
			hashNode = Identificador(node->son[1]);	
			if (hashNode == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}

			//literal, verifica o tipo
			tipoLit = TipoLiteral(node->son[2]);
			if (tipoLit == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}

			//verifica se os tipos são adequados
			if (!TiposEquivalentes(tipo, tipoLit))
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			
			//verifica se eh declaracao dupla
			if (alreadyDeclared(escopoGlobal, hashNode))
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}
			
			//insere na lista de declaracoes
			addDeclaration(&escopoGlobal, hashNode, tipo);			
			
			break;

		case ASTREE_VARDEC_VECTOR:
			//tipo
			tipo = TipoV(node->son[0]);
			if (tipo == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			//identificador
			hashNode = Identificador(node->son[1]);	
			if (hashNode == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}

			//tamanho
			tamanho = TamanhoVetor(node->son[2]);
			if (tamanho == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			
			//verifica se eh declaracao dupla
			if (alreadyDeclared(escopoGlobal, hashNode))
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			
			//insere na lista de declaracoes
			addDeclaration(&escopoGlobal, hashNode, tipo);			
			
			break;

		case ASTREE_VARDEC_VECTOR_INITIALIZED:
			//tipo
			tipo = TipoV(node->son[0]);
			if (tipo == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}
			//identificador
			hashNode = Identificador(node->son[1]);	
			if (hashNode == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}

			//tamanho
			tamanho = TamanhoVetor(node->son[2]);
			if (tamanho == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			
			//verificar se os valores sao do mesmo tipo do vetor			
			if (verificaListLit(node->son[3], tipo) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}

			//verifica se eh declaracao dupla
			if (alreadyDeclared(escopoGlobal, hashNode))
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			
			//insere na lista de declaracoes
			addDeclaration(&escopoGlobal, hashNode, tipo);			
			
			break;

		case ASTREE_FUNC:
			//tipo
			tipo = TipoF(node->son[0]);
			if (tipo == ERRO)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}
			//identificador
			hashNode = Identificador(node->son[1]);	
			if (hashNode == NULL)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;
			}

			//verifica se eh declaracao dupla
			if (alreadyDeclared(escopoGlobal, hashNode))
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}

			//insere na lista de declaracoes
			declaracao = addDeclaration(&escopoGlobal, hashNode, tipo);

			//insere os argumentos
			if (InsereArgumentos(declaracao, node->son[2]) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}

			//declarações locais
			if (InsereDeclaracoesLocais(declaracao, node->son[3]) == FALSE)
			{
				//fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
				temErro = TRUE;	
			}
			

			//corpo nao verifica ainda! só na próxima passada
		
	}

	return TRUE;

}

BOOL InsereDeclaracaoLocal(DECLARATION * declaracao, ASTREE * node)
{
//localdec
int tipo, tipoLit;
HASH_NODE * hashNode;

	if (node->type == ASTREE_LOCALDEC_VAR)
	{
		//tipo
		tipo = Tipo(node->son[0]);
		if (tipo == ERRO)
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;	
		}

		//identificador
		hashNode = Identificador(node->son[1]);	
		if (hashNode == NULL)
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}

		//literal, verifica o tipo
		tipoLit = TipoLiteral(node->son[2]);
		if (tipoLit == ERRO)
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}
		
		
		//verifica se os tipos são adequados
		if (!TiposEquivalentes(tipo, tipoLit))
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}		

		//verifica se eh declaracao dupla
		if (alreadyDeclared(declaracao->arguments, hashNode))
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}
		if (alreadyDeclared(declaracao->escopoLocal, hashNode))
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}
		
		//insere na lista de declaracoes locais
		addDeclaration(&(declaracao->escopoLocal), hashNode, tipo);

		return TRUE;		
		

	}
	else if(node->type == ASTREE_LOCALDEC_PTR)
	{
		//tipo
		tipo = TipoP(node->son[0]);
		if (tipo == ERRO)
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}	
		//identificador
		hashNode = Identificador(node->son[1]);	
		if (hashNode == NULL)
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}

		//literal, verifica o tipo
		tipoLit = TipoLiteral(node->son[2]);
		if (tipoLit == ERRO)
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}

		//verifica se os tipos são adequados
		if (!TiposEquivalentes(tipo, tipoLit))
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}
		
		//verifica se eh declaracao dupla
		if (alreadyDeclared(declaracao->arguments, hashNode))
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}
		if (alreadyDeclared(declaracao->escopoLocal, hashNode))
		{
			fprintf(stderr, "Erro semantica linha %d \n", node->lineNumber);
			temErro = TRUE;
		}
		
		//insere na lista de declaracoes
		addDeclaration(&(declaracao->escopoLocal), hashNode, tipo);	
	}	
	else
		return FALSE;
}

BOOL InsereDeclaracoesLocais(DECLARATION * declaracao, ASTREE * node)
{
//listlocaldec
	if (node == NULL)
		return TRUE;

	if (InsereDeclaracaoLocal(declaracao, node->son[0]) == FALSE)
	{
		temErro = TRUE;
		return InsereDeclaracoesLocais(declaracao, node->son[1]);
	}	
	else
		return InsereDeclaracoesLocais(declaracao, node->son[1]);

}


BOOL InsereArgumentos2 (DECLARATION * declaracao, ASTREE * node)
{
	if (node == NULL)
	{	
		//fprintf(stderr, "AQUI3");
		return TRUE;
	}
	
	//fprintf(stderr, "AQUI4");	

	int tipo = Tipo(node->son[0]);
	if (tipo == ERRO)
		temErro = TRUE;
	HASH_NODE * hashNode = Identificador(node->son[1]);
	if (hashNode == NULL)
		temErro = TRUE;

	if (alreadyDeclared(declaracao->arguments, hashNode))
		temErro = TRUE;

	addDeclaration(&(declaracao->arguments), hashNode, tipo);

	InsereArgumentos2 (declaracao, node->son[2]);
	
	return TRUE;
}

BOOL InsereArgumentos (DECLARATION * declaracao, ASTREE * node)
{
	if (node == NULL)
	{	
		//fprintf(stderr, "AQUI2");
		return TRUE;
	}
	
	return InsereArgumentos2 (declaracao, node->son[0]);
	
}

BOOL verificaListLit(ASTREE * node, int tipo)
{
	int tipoLit;
	if (node == NULL)
		return TRUE;

	//verifica o varlit
	tipoLit = TipoLiteral(node->son[0]);
	if (!TiposEquivalentes(tipo, tipoLit))
		return FALSE;

	return verificaListLit(node->son[1], tipo);
}

HASH_NODE * TamanhoVetor (ASTREE * node)
{
	if (node == NULL)
		return NULL;	
	if (node->type != ASTREE_INTEGERLIT)
		return NULL;
	
	return node->hashNode;
}


int Tipo(ASTREE * node)
{
	if (node == NULL)
		return ERRO;
	switch (node->type)
	{
		case ASTREE_VARTYPE_WORD:
			return TIPO_WORD;
		case ASTREE_VARTYPE_BYTE:
			return TIPO_BYTE;
		case ASTREE_VARTYPE_BOOL:
			return TIPO_BOOL;
		default:
			return ERRO;
	}

}

int TipoF(ASTREE * node)
{
	if (node == NULL)
		return ERRO;
	switch (node->type)
	{
		case ASTREE_VARTYPE_WORD:
			return TIPO_FWORD;
		case ASTREE_VARTYPE_BYTE:
			return TIPO_FBYTE;
		case ASTREE_VARTYPE_BOOL:
			return TIPO_FBOOL;
		default:
			return ERRO;
	}

}

int TipoP(ASTREE * node)
{
	if (node == NULL)
		return ERRO;
	switch (node->type)
	{
		case ASTREE_VARTYPE_WORD:
			return TIPO_PWORD;
		case ASTREE_VARTYPE_BYTE:
			return TIPO_PBYTE;
		case ASTREE_VARTYPE_BOOL:
			return TIPO_PBOOL;
		default:
			return ERRO;
	}

}

int TipoV(ASTREE * node)
{
	if (node == NULL)
		return ERRO;
	switch (node->type)
	{
		case ASTREE_VARTYPE_WORD:
			return TIPO_VWORD;
		case ASTREE_VARTYPE_BYTE:
			return TIPO_VBYTE;
		case ASTREE_VARTYPE_BOOL:
			return TIPO_VBOOL;
		default:
			return ERRO;
	}

}

HASH_NODE * Identificador (ASTREE * node)
{
	if (node == NULL)
		return NULL;
	if (node->type == ASTREE_IDENTIFIER)
		return node->hashNode;
	else
		return NULL;
}

int TipoLiteral(ASTREE * node)
{
	switch(node->type)
	{
		case ASTREE_VARLIT_INTEGER:
			return TLIT_INT;
		case ASTREE_VARLIT_FALSE:
		case ASTREE_VARLIT_TRUE:
			return TLIT_BOOL;
		case ASTREE_VARLIT_CHAR:
			return TLIT_CHAR;
		case ASTREE_VARLIT_STRING:
			return TLIT_STRING;
		default:
			return ERRO;
		

	}
}

BOOL TiposEquivalentes(int tipo, int tipoLit)
{
	if ((tipo == TIPO_WORD) || (tipo == TIPO_BYTE) || (tipo == TIPO_PWORD) || (tipo == TIPO_PBYTE)  || (tipo == TIPO_PBOOL) || (tipo == TIPO_VWORD) || (tipo == TIPO_VBYTE))
		if (tipoLit == TLIT_INT)
			return TRUE;
			
	if ((tipo == TIPO_WORD) || (tipo == TIPO_BYTE))
		if (tipoLit == TLIT_CHAR)
			return TRUE;

	if ((tipo == TIPO_BOOL) || (tipo == TIPO_VBOOL))
		if (tipoLit == TLIT_BOOL)
			return TRUE;

	return FALSE;
}
