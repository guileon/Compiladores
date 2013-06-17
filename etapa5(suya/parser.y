%{
#include <stdio.h>
#include "hash.h"
#include "astree.h"

//gambiarra:
extern ASTREE * arvore;

//megagambiarra
int getLineNumber();

int yyerror(char *);


char t[] = "TRUE";
char f[] = "FALSE";
char tkbool[] = "bool";
char tkword[] = "word";
char tkbyte[] = "byte";

%}

%union	
{
	HASH_NODE * node; //como os numeros sao em hexadecimal nao adianta ter um int
	char * string;
	ASTREE * astree;
}

%token KW_WORD
%token KW_BOOL
%token KW_BYTE
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_LOOP
%token KW_INPUT
%token KW_RETURN
%token KW_OUTPUT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token <node>TK_IDENTIFIER
%token <node>LIT_INTEGER
%token LIT_FALSE
%token LIT_TRUE
%token <node>LIT_CHAR
%token <node>LIT_STRING
%token <node>SCALAR
%token <node>SYMBOL_LABEL

%type <astree> program
%type <astree> varlit
%type <astree> vartype
%type <astree> exp
%type <astree> identifier
%type <astree> integerlit
%type <astree> vardec
%type <astree> fundec
%type <astree> listlit
%type <astree> arguments
%type <astree> listarg
%type <astree> body
%type <astree> vazio
%type <astree> listlocaldec
%type <astree> localdec
%type <astree> listcom
%type <astree> com
%type <astree> listout
%type <astree> param
%type <astree> listparam

%right KW_IF KW_THEN KW_ELSE
%left  OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR '+' '-' '*' '/' '<' '>'	'='	'!'

%%

program: vardec program			{$$ = arvore = astreeCreate(ASTREE_PROGRAM, $1, $2, NULL, NULL, NULL, NULL, getLineNumber());}
		| fundec program	{$$ = arvore = astreeCreate(ASTREE_PROGRAM, $1, $2, NULL, NULL, NULL, NULL, getLineNumber());}
		| 			{$$ = NULL;}
		;

vardec: vartype identifier ':' varlit ';'  { $$ = astreeCreate(ASTREE_VARDEC_VAR, $1, $2, $4, NULL, NULL, NULL, getLineNumber());  }
	| vartype '$' identifier ':' varlit ';'  { $$ = astreeCreate(ASTREE_VARDEC_PTR, $1, $3, $5, NULL, NULL, NULL, getLineNumber()); }
	| vartype identifier '[' integerlit ']' ';'  { $$ = astreeCreate(ASTREE_VARDEC_VECTOR, $1, $2, $4, NULL, NULL, NULL, getLineNumber()); }
	| vartype identifier '[' integerlit ']' ':' listlit ';'  { $$ = astreeCreate(ASTREE_VARDEC_VECTOR_INITIALIZED, $1, $2, $4, $7, NULL, NULL, getLineNumber()); }
	;

identifier: TK_IDENTIFIER {$$ = astreeCreate(ASTREE_IDENTIFIER, NULL, NULL, NULL, NULL, NULL, $1, getLineNumber());}
	;

integerlit: LIT_INTEGER {$$ = astreeCreate(ASTREE_INTEGERLIT, NULL, NULL, NULL, NULL, NULL, $1, getLineNumber());}
	;

listlit: varlit listlit {$$ = astreeCreate(ASTREE_LISTLIT, $1, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
	| 		{$$ = NULL;}
	;

varlit: LIT_INTEGER 	{ $$ = astreeCreate(ASTREE_VARLIT_INTEGER, NULL,NULL, NULL, NULL, NULL, $1, getLineNumber()); }
	| LIT_FALSE 	{ $$ = astreeCreate(ASTREE_VARLIT_FALSE, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
	| LIT_TRUE 	{ $$ = astreeCreate(ASTREE_VARLIT_TRUE, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
	| LIT_CHAR 	{ $$ = astreeCreate(ASTREE_VARLIT_CHAR, NULL, NULL, NULL, NULL, NULL, $1, getLineNumber()); }
	| LIT_STRING 	{ $$ = astreeCreate(ASTREE_VARLIT_STRING, NULL, NULL, NULL, NULL, NULL, $1, getLineNumber()); }
	; 

vartype : KW_WORD 	{ $$ = astreeCreate(ASTREE_VARTYPE_WORD, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
	| KW_BOOL 	{ $$ = astreeCreate(ASTREE_VARTYPE_BOOL, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
	| KW_BYTE 	{ $$ = astreeCreate(ASTREE_VARTYPE_BYTE, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
	; 

fundec: vartype identifier '(' arguments ')' listlocaldec  body { $$ = astreeCreate(ASTREE_FUNC, $1, $2, $4, $6, $7, NULL, getLineNumber());  }

arguments: vazio { $$ = $1; }
    | listarg { $$ = astreeCreate(ASTREE_ARG_LIST, $1, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }

listarg: vartype identifier ',' listarg 	{$$ = astreeCreate(ASTREE_LISTARG_VIRG, $1, $2, $4, NULL, NULL, NULL, getLineNumber()); }
	| vartype identifier 			{$$ = astreeCreate(ASTREE_LISTARG, $1, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
    ;

vazio: 		{$$ = 0;}
	;

listlocaldec: localdec listlocaldec { $$ = astreeCreate(ASTREE_LIST_LOCAL, $1, $2, NULL, NULL, NULL, NULL, getLineNumber()); }
	| 			    {$$ = NULL;}
	;
	
localdec: vartype identifier ':' varlit ';' 	{ $$ = astreeCreate(ASTREE_LOCALDEC_VAR, $1, $2, $4, NULL, NULL, NULL, getLineNumber());  }
	| vartype '$' identifier ':' varlit ';' { $$ = astreeCreate(ASTREE_LOCALDEC_PTR, $1, $3, $5, NULL, NULL, NULL, getLineNumber()); }
	;
	
body: '{' listcom '}' 				{ $$ = astreeCreate(ASTREE_BODY, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
	;
	
listcom: com ';' listcom	{$$ = astreeCreate(ASTREE_LISTCOM, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
	|			{$$ = NULL;} 
	;
	


com: identifier '=' exp 			{$$ = astreeCreate(ASTREE_COM_ATR, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | identifier '[' exp ']' '=' exp 		{$$ = astreeCreate(ASTREE_COM_ATR_VECTOR, $1, $3, $6, NULL, NULL, NULL, getLineNumber());}
  | KW_INPUT identifier 			{$$ = astreeCreate(ASTREE_COM_INPUT, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
  | KW_OUTPUT listout 				{$$ = astreeCreate(ASTREE_COM_OUTPUT, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
  | KW_RETURN exp 				{$$ = astreeCreate(ASTREE_COM_RETURN, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
  | KW_IF '(' exp ')' KW_THEN com  		{$$ = astreeCreate(ASTREE_COM_IFTHEN, $3, $6, NULL, NULL, NULL, NULL, getLineNumber());}
  | KW_IF '(' exp ')' KW_THEN com KW_ELSE com 	{$$ = astreeCreate(ASTREE_COM_IFTHENELSE, $3, $6, $8, NULL, NULL, NULL, getLineNumber());}
  | KW_LOOP '(' exp ')' com  			{$$ = astreeCreate(ASTREE_COM_LOOP, $3, $5, NULL, NULL, NULL, NULL, getLineNumber());}
  | body					{$$ = $1;}
  ;
  
listout: exp ',' listout			{$$ = astreeCreate(ASTREE_LISTOUT, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
	| exp					{$$ = $1;}
	;

exp: identifier					{$$ = $1;}
  | identifier '[' exp ']'			{$$ = astreeCreate(ASTREE_EXP_VECTOR, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | varlit  					{$$ = $1;}
  | '(' exp ')'					{$$ = astreeCreate(ASTREE_EXP_PARENTESES, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
  
  | exp '+' exp 		{$$ = astreeCreate(ASTREE_ADD,$1,$3,0,0,0, NULL, getLineNumber());}
  | exp '-' exp 		{$$ = astreeCreate(ASTREE_SUB,$1,$3,0,0,0, NULL, getLineNumber());}
  | exp '*' exp 		{$$ = astreeCreate(ASTREE_MUL,$1,$3,0,0,0, NULL, getLineNumber());}
  | exp '/' exp 		{$$ = astreeCreate(ASTREE_DIV,$1,$3,0,0,0, NULL, getLineNumber());}
  | exp '<' exp					{$$ = astreeCreate(ASTREE_EXP_LESSER, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp '>' exp 				{$$ = astreeCreate(ASTREE_EXP_GREATER, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp '=' exp 				{$$ = astreeCreate(ASTREE_EXP_SINGLEEQ, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp '!' exp					{$$ = astreeCreate(ASTREE_EXP_NOT, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp OPERATOR_LE exp				{$$ = astreeCreate(ASTREE_EXP_LE, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp OPERATOR_GE exp				{$$ = astreeCreate(ASTREE_EXP_GE, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp OPERATOR_EQ exp				{$$ = astreeCreate(ASTREE_EXP_EQ, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp OPERATOR_NE exp				{$$ = astreeCreate(ASTREE_EXP_NE, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp OPERATOR_AND exp			{$$ = astreeCreate(ASTREE_EXP_AND, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp OPERATOR_OR exp 			{$$ = astreeCreate(ASTREE_EXP_OR, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | identifier '(' param ')'			{$$ = astreeCreate(ASTREE_EXP_FUNCALL, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | '&' identifier				{$$ = astreeCreate(ASTREE_EXP_ADDR, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
  | '*' identifier				{$$ = astreeCreate(ASTREE_EXP_PTRVALUE, $2, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
  ;
  
param: vazio			{$$ = 0;}
  | listparam			{$$ = $1;}
  ;

listparam: exp ',' listparam	{$$ = astreeCreate(ASTREE_LISTPARAM, $1, $3, NULL, NULL, NULL, NULL, getLineNumber());}
  | exp				{$$ = $1;}
  ;

%%

int yyerror(char * s)
{
	fprintf(stderr, "Erro \"%s\" na linha %d.\n", s, getLineNumber());
	exit(3);
}

