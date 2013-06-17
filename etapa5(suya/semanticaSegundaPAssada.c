#include <stdio.h>
#include <stdlib.h>

#include "declarations.h"
#include "astree.h"
#include "hash.h"

extern DECLARATION * escopoGlobal;

BOOL temErro2 = FALSE;

void VerificaProgram(ASTREE * node);
void VerificaVardecFundec(ASTREE * node);
void VerificaCorpo(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal, int tipoFunc);
void VerificaListCom(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal, int tipoFunc);
void VerificaCom(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal, int tipoFunc);
int TipoCompativelReturn(int tipoFunc,int tipoExp);
void VerificaListOut(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal);
int TipoCompativelComInput(int tipo);
int TipoCompativelComIndice (int tipo);
int TiposCompativeisVetor(int tipoVetor, int tipoExpressao);
int TiposCompativeisVariaveis(int tipoVariavel, int tipoExpressao);
int VerificaExpressao(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal);
int ConfereArgumentos(ASTREE * node, DECLARATION * funcArgs, DECLARATION * arguments, DECLARATION * escopoLocal);
int TipoPonteiro(int tipo);
int TipoFuncao(int tipo);
int TipoVetor(int tipo);
int TiposCompativeisBool(int tipo1, int tipo2);
int TiposCompativeisAlg(int tipo1, int tipo2);
int TiposCompativeisSoma(int tipo1, int tipo2);


BOOL Verifica2Passada(ASTREE * node)
{
	temErro2 = FALSE;

	VerificaProgram(node);

	return !temErro2;
}


void VerificaProgram(ASTREE * node)
{
	if (node == NULL)
		return;

	VerificaVardecFundec(node->son[0]);
	VerificaProgram(node->son[1]);
}

void VerificaVardecFundec(ASTREE * node)
{
	DECLARATION * decl;
	BOOL encontrou;
	HASH_NODE * nomeFuncao;
	
	if (node == NULL)
		return;
	//vardec ja foi verificado na primeira passada	
	
	if (node->type == ASTREE_FUNC)
	{
		//qual o nome da declaracao?
		nomeFuncao = node->son[1]->hashNode;		
		
		//encontra a declaracao da funcao no escopo global
		decl = escopoGlobal;
		encontrou = FALSE;
		while ((decl != NULL) && (encontrou == FALSE))
		{
			if (decl->hashNode == nomeFuncao)
				encontrou = TRUE;
			else
				decl = decl->next;	
		}
		
		if (encontrou == FALSE)
		{
			fprintf(stderr, "ERRO nome da funcao nao encontrada no escopo global. \n");
			return;
		}
		
		//verifica o corpo da funcao
		VerificaCorpo(node->son[4], decl->arguments, decl->escopoLocal, decl->type);
	}
}


void VerificaCorpo(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal, int tipoFunc)
{

	if (node == NULL)
		return;

	VerificaListCom(node->son[0], arguments, escopoLocal, tipoFunc);

}

void VerificaListCom(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal, int tipoFunc)
{
	if (node == NULL)
		return;

	if (node->type != ASTREE_LISTCOM)
		fprintf(stderr, "ERRO nao eh listcom. \n");

	VerificaCom(node->son[0], arguments, escopoLocal, tipoFunc);
	VerificaListCom(node->son[1], arguments, escopoLocal, tipoFunc);
}

void VerificaCom(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal, int tipoFunc)
{
	DECLARATION * decl;
	HASH_NODE * nome;
	int tipoExpr;

	switch (node->type)
	{
		case ASTREE_COM_ATR:
			nome = node->son[0]->hashNode;			
			//encontra declaracao -- primeiro argumentos, depois escopo local depois global
			decl = NULL;
			if ((decl = encontraDeclaracao(arguments, nome)) == NULL)
				if ((decl = encontraDeclaracao(escopoLocal, nome)) == NULL)
					if ((decl = encontraDeclaracao(escopoGlobal, nome)) == NULL)
					{
						fprintf(stderr, "Erro identificador nao encontrado na linha %d.\n", node->lineNumber);
						temErro2 = TRUE;
						return;
					}
			//verifica se o tipo da expressao é compativel o da declaracao
			if (TiposCompativeisVariaveis(decl->type, VerificaExpressao(node->son[1], arguments, escopoLocal)) == FALSE)			
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				temErro2 = TRUE;			
			}
				
			break;
		case ASTREE_COM_ATR_VECTOR:
			nome = node->son[0]->hashNode;
			//encontra declaracao -- primeiro argumentos, depois escopo local depois global
			decl = NULL;
			if ((decl = encontraDeclaracao(arguments, nome)) == NULL)
				if ((decl = encontraDeclaracao(escopoLocal, nome)) == NULL)
					if ((decl = encontraDeclaracao(escopoGlobal, nome)) == NULL)
					{
						fprintf(stderr, "Erro identificador nao encontrado na linha %d.\n", node->lineNumber);
						temErro2 = TRUE;
						return;
					}
			
			//verifica se o indice é tipo int
			if (TipoCompativelComIndice(VerificaExpressao(node->son[1] ,arguments, escopoLocal)) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				temErro2 = TRUE;	
			}

			//verifica se a expressao eh compatival	
			if (TiposCompativeisVetor(decl->type, VerificaExpressao(node->son[2], arguments, escopoLocal)) == FALSE)			
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				temErro2 = TRUE;			
			}

			break;
		case ASTREE_COM_INPUT:
			nome = node->son[0]->hashNode;
			//encontra declaracao -- primeiro argumentos, depois escopo local depois global
			decl = NULL;
			if ((decl = encontraDeclaracao(arguments, nome)) == NULL)
				if ((decl = encontraDeclaracao(escopoLocal, nome)) == NULL)
					if ((decl = encontraDeclaracao(escopoGlobal, nome)) == NULL)
					{
						fprintf(stderr, "Erro identificador nao encontrado na linha %d.\n", node->lineNumber);
						temErro2 = TRUE;
						return;
					}

			//o identificador nao pode ser um vetor nem uma funcao nem ponteiro
			if (TipoCompativelComInput(decl->type) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				temErro2 = TRUE;	
			}

			break;
		case ASTREE_COM_OUTPUT:

			//podem ser de qualquer tipo no momento TODO
			VerificaListOut(node->son[0], arguments, escopoLocal);

			break;
		case ASTREE_COM_RETURN:
			
			//tipo da expressao deve ser do tipo da funcao
			if (TipoCompativelReturn(tipoFunc, VerificaExpressao(node->son[0], arguments, escopoLocal)) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				temErro2 = TRUE;	
			}

			break;
		case ASTREE_COM_IFTHEN:
			
			//tipo da expressao deve ser TLIT_BOOL ou TIPO_BOOL
			tipoExpr = VerificaExpressao(node->son[0], arguments, escopoLocal);
			if ((tipoExpr != TLIT_BOOL) && (tipoExpr != TIPO_BOOL))
			{
				fprintf(stderr, "Erro semantica TIPO NAO BOOLEANO linha %d. \n", node->lineNumber);
				temErro2 = TRUE;
			}

			//verifica o comando
			VerificaCom(node->son[1], arguments, escopoLocal, tipoFunc);		

			break;
		case ASTREE_COM_IFTHENELSE:
			
			//tipo da expressao deve ser TLIT_BOOL ou TIPO_BOOL
			tipoExpr = VerificaExpressao(node->son[0], arguments, escopoLocal);
			if ((tipoExpr != TLIT_BOOL) && (tipoExpr != TIPO_BOOL))
			{
				fprintf(stderr, "Erro semantica TIPO NAO BOOLEANO linha %d. \n", node->lineNumber);
				temErro2 = TRUE;
			}

			//verifica os comandos
			VerificaCom(node->son[1], arguments, escopoLocal, tipoFunc);	
			VerificaCom(node->son[2], arguments, escopoLocal, tipoFunc);
			
			break;
		case ASTREE_COM_LOOP:
			//tipo da expressao deve ser TLIT_BOOL ou TIPO_BOOL
			tipoExpr = VerificaExpressao(node->son[0], arguments, escopoLocal);
			if ((tipoExpr != TLIT_BOOL) && (tipoExpr != TIPO_BOOL))
			{
				fprintf(stderr, "Erro semantica TIPO NAO BOOLEANO linha %d. \n", node->lineNumber);
				temErro2 = TRUE;
			}

			//verifica o comando
			VerificaCom(node->son[1], arguments, escopoLocal, tipoFunc);		


			break;
		case ASTREE_BODY:
			VerificaCorpo(node, arguments, escopoLocal, tipoFunc);

			break;
		default:
			fprintf(stderr, "ERRO Comando desconhecido: %d", node->type);
	}
}


int TipoCompativelReturn(int tipoFunc,int tipoExp)
{
	if (tipoFunc == tipoExp)
		return TRUE;
}

void VerificaListOut(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal)
{
	//TODO
}

//soh pode variavel
int TipoCompativelComInput(int tipo)
{	
	if ((tipo == TIPO_WORD) || (tipo == TIPO_BYTE) || (tipo == TIPO_BOOL))
		return TRUE;
	else
		return FALSE;


}

int TipoCompativelComIndice (int tipo)
{
	if ((tipo == TIPO_WORD) || (tipo == TIPO_BYTE) || (tipo == TLIT_INT))
		return TRUE;
	else
		return FALSE;
}

int TiposCompativeisVetor(int tipoVetor, int tipoExpressao)
{
	if (tipoVetor == TIPO_VWORD)
		if ((tipoExpressao == TIPO_WORD) || (tipoExpressao == TLIT_INT) || (tipoExpressao == TLIT_CHAR))
			return TRUE;

	if (tipoVetor == TIPO_VBYTE)
		if ((tipoExpressao == TIPO_BYTE) || (tipoExpressao == TLIT_INT) || (tipoExpressao == TLIT_CHAR))
			return TRUE;
	
	if (tipoVetor == TIPO_VBOOL)
		if ((tipoExpressao == TIPO_BOOL) || (tipoExpressao == TLIT_BOOL))
			return TRUE;

	return FALSE;
}

//nao esquecer q variavel pode ser um ponteiro, vetor, ponteiros podem receber inteiros, e contam como inteiros na avaliacao
//plo, seja: word a; word $pt; Então a = 1 + 2 + 3 está correto, enquanto a = 1 + 2 + pt é errado, pt = 1 + 2 ou pt = pt + 1 correto
int TiposCompativeisVariaveis(int tipoVariavel, int tipoExpressao)
{
	if (tipoVariavel == tipoExpressao)
		return TRUE;

	if (tipoVariavel == TIPO_WORD)
		if ((tipoExpressao == TLIT_INT) || (tipoExpressao == TLIT_CHAR))
			return TRUE;

	if (tipoVariavel == TIPO_BYTE)
		if ((tipoExpressao == TLIT_INT) || (tipoExpressao == TLIT_CHAR))
			return TRUE;

	if (tipoVariavel == TIPO_BOOL)
		if (tipoExpressao == TLIT_BOOL)
			return TRUE;

	
	return FALSE;
}

//tipos possiveis: todos
int VerificaExpressao(ASTREE * node, DECLARATION * arguments, DECLARATION * escopoLocal)
{	
	HASH_NODE * nome;
	DECLARATION * decl;
	int tipo1, tipo2;

	switch (node->type)
	{
		case ASTREE_IDENTIFIER:
			//encontra o identificador
			nome = node->hashNode;
			decl = NULL;
			if ((decl = encontraDeclaracao(arguments, nome)) == NULL)
				if ((decl = encontraDeclaracao(escopoLocal, nome)) == NULL)
					if ((decl = encontraDeclaracao(escopoGlobal, nome)) == NULL)
					{
						fprintf(stderr, "Erro identificador nao encontrado na linha %d.\n", node->lineNumber);
						temErro2 = TRUE;
						return ERRO;
					}
			return decl->type;
						
			break;
		case ASTREE_EXP_VECTOR:
			//encontra o identificador
			nome = node->son[0]->hashNode;
			decl = NULL;
			if ((decl = encontraDeclaracao(arguments, nome)) == NULL)
				if ((decl = encontraDeclaracao(escopoLocal, nome)) == NULL)
					if ((decl = encontraDeclaracao(escopoGlobal, nome)) == NULL)
					{
						fprintf(stderr, "Erro identificador nao encontrado na linha %d.\n", node->lineNumber);
						temErro2 = TRUE;
						return ERRO;
					}
			//verifica se o indice é tipo int
			if (TipoCompativelComIndice(VerificaExpressao(node->son[1] ,arguments, escopoLocal)) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				temErro2 = TRUE;	
			}

			if (decl->type == TIPO_VWORD)
				return TIPO_WORD;
			if (decl->type == TIPO_VBYTE)
				return TIPO_BYTE;
			if (decl->type == TIPO_VBOOL)
				return TIPO_BOOL;
			
			fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
			temErro2 = TRUE;	
			return ERRO;

			break;
		case ASTREE_VARLIT_INTEGER:
			return TLIT_INT;
			break;
		case ASTREE_VARLIT_FALSE:
			return TLIT_BOOL;
			break;
		case ASTREE_VARLIT_TRUE:
			return TLIT_BOOL;
			break;
		case ASTREE_VARLIT_CHAR:
			return TLIT_CHAR;
			break;
		case ASTREE_VARLIT_STRING:
			return TLIT_STRING;
			break;
		case ASTREE_EXP_PARENTESES:
			
			return VerificaExpressao(node->son[0], arguments, escopoLocal);			
			
			break;

		case ASTREE_ADD: //loucura aceita ponteiros, retorna um ponteiro
			//inteiro ou ponteiro?
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);

			if (TiposCompativeisSoma(tipo1, tipo2) == FALSE)
			{
				fprintf(stderr, "Erro semantica linha %d. \n", node->lineNumber);
				return ERRO;
			}
			if (TipoPonteiro(tipo1))
				return tipo1;
			if (TipoPonteiro(tipo2))
				return tipo2;

			return tipo1;		

			break;
		case ASTREE_SUB:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);

			if (TiposCompativeisAlg(tipo1, tipo2))
				return tipo1;


			break;
		case ASTREE_MUL:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);

			if (TiposCompativeisAlg(tipo1,tipo2))
				return tipo1;

			break;
		case ASTREE_DIV:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);

			if (TiposCompativeisAlg(tipo1,  tipo2))
				return tipo1;

			break;
		case ASTREE_EXP_LESSER:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_GREATER:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_SINGLEEQ:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_NOT:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisBool(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_LE:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_GE:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_EQ:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_NE:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisAlg(tipo1,tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_AND:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisBool(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_OR:
			tipo1 = VerificaExpressao(node->son[0], arguments, escopoLocal);
			tipo2 = VerificaExpressao(node->son[1], arguments, escopoLocal);
			if (TiposCompativeisBool(tipo1, tipo2))
				return TLIT_BOOL;

			break;
		case ASTREE_EXP_FUNCALL:
			nome = node->son[0]->hashNode;
			//encontra a declaracao no escopo global
			decl = NULL;
			if ((decl = encontraDeclaracao(escopoGlobal, nome)) == NULL)
			{
				fprintf(stderr, "Erro identificador nao encontrado na linha %d.\n", node->lineNumber);
				temErro2 = TRUE;
				return ERRO;
			}

			//verifica os argumentos
			if (ConfereArgumentos(node->son[1], copyList(decl->arguments), arguments, escopoLocal) == FALSE)
			{
				fprintf(stderr, "Erro argumentos invalidos linha %d.\n", node->lineNumber);
				temErro2 = TRUE;
				return ERRO;
			}

			return decl->type;

			break;
		case ASTREE_EXP_ADDR:
			//TODO

			break;
		case ASTREE_EXP_PTRVALUE:
			//TODO			

			break;
		default:
			fprintf(stderr, "ERRO EXPRESSAO TIPO INVALIDO.\n");
			return ERRO;
		
	}
}

int ConfereArgumentos(ASTREE * node, DECLARATION * funcArgs, DECLARATION * arguments, DECLARATION * escopoLocal)
{
	int tipoExpr;

	if ((node == NULL) && (arguments == NULL))
		return TRUE;
	if ((node == NULL) && (arguments != NULL))
		return FALSE;
	if ((node != NULL) && (arguments == NULL))
		return FALSE;
	
	//verifica se o tipo da expressao é o tipo do argumento
	tipoExpr = VerificaExpressao(node->son[0], arguments, escopoLocal);
	if (TiposCompativeisVariaveis(funcArgs->type, tipoExpr) == FALSE)
		return FALSE;	


	if (node->type == ASTREE_LISTPARAM)
		return ConfereArgumentos(node->son[1], funcArgs->next, arguments, escopoLocal);

	return TRUE;
}

int TipoPonteiro(int tipo)
{
	if ((tipo == TIPO_PWORD) || (tipo == TIPO_PBYTE) || (tipo == TIPO_PBOOL))
		return TRUE;
	else
		return FALSE;

}

int TipoFuncao(int tipo)
{
	if ((tipo == TIPO_FWORD) || (tipo == TIPO_FBYTE) || (tipo == TIPO_FBOOL))
		return TRUE;
	else
		return FALSE;
}
int TipoVetor(int tipo)
{
	if ((tipo == TIPO_VWORD) || (tipo == TIPO_VBYTE) || (tipo == TIPO_VBOOL))
		return TRUE;
	else
		return FALSE;
}

int TiposCompativeisBool(int tipo1, int tipo2)
{
	if ((tipo1 == TIPO_BOOL) && (tipo2 == TIPO_BOOL))
		return TRUE;

	if ((tipo1 == TIPO_BOOL) && (tipo2 == TLIT_BOOL))
		return TRUE;

	if ((tipo1 == TLIT_BOOL) && (tipo2 == TIPO_BOOL))
		return TRUE;

	return FALSE;

}

int TiposCompativeisAlg(int tipo1, int tipo2)
{
	if (TipoPonteiro(tipo1) || TipoPonteiro(tipo2) || TipoVetor(tipo1) || TipoVetor(tipo2) || TipoFuncao(tipo1) || TipoFuncao(tipo2))
		return FALSE;	
	if (tipo1 == tipo2)
		return TRUE;
	
	if (((tipo1 == TIPO_WORD) || (tipo1 == TIPO_BYTE)) && ((tipo2 == TLIT_INT) || (tipo2 == TLIT_CHAR)))
		return TRUE;
	if (((tipo2 == TIPO_WORD) || (tipo2 == TIPO_BYTE)) && ((tipo1 == TLIT_INT) || (tipo1 == TLIT_CHAR)))
		return TRUE;
	
	return FALSE;
}

int TiposCompativeisSoma(int tipo1, int tipo2)
{
	if (TipoPonteiro(tipo1) && ((tipo2 == TLIT_INT) || (tipo2 == TIPO_WORD) || (tipo2 == TIPO_BYTE)))
		return TRUE;

	if (TipoPonteiro(tipo2) && ((tipo1 == TLIT_INT) || (tipo1 == TIPO_WORD) || (tipo1 == TIPO_BYTE)))
		return TRUE;
		
	if (TipoPonteiro(tipo1) || TipoPonteiro(tipo2) || TipoVetor(tipo1) || TipoVetor(tipo2) || TipoFuncao(tipo1) || TipoFuncao(tipo2))
		return FALSE;	
	if (tipo1 == tipo2)
		return TRUE;
	
	if (((tipo1 == TIPO_WORD) || (tipo1 == TIPO_BYTE)) && ((tipo2 == TLIT_INT) || (tipo2 == TLIT_CHAR)))
		return TRUE;
	if (((tipo2 == TIPO_WORD) || (tipo2 == TIPO_BYTE)) && ((tipo1 == TLIT_INT) || (tipo1 == TLIT_CHAR)))
		return TRUE;
	
	return FALSE;
	

}
