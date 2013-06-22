%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
#include "tokens.h"
void yyerror();

%}

%union
{
	hashNode * hash;
	astreeNode * astree;
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


%token <hash>TK_IDENTIFIER
%token <hash>LIT_INTEGER  
%token <hash>LIT_FALSE    
%token <hash>LIT_TRUE	    
%token <hash>LIT_CHAR     
%token <hash>LIT_STRING   

%token TOKEN_ERROR



%nonassoc IFX
%nonassoc KW_ELSE
%nonassoc '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_OR OPERATOR_AND
%left '+' '-'
%left '*' '/'



%type <astree> literal
%type <astree> identifier

%type <astree> argList // ARGUMENTS_CALL
%type <astree> litList
%type <astree> outputList

%type <astree> type
%type <astree> declarationScalar
%type <astree> declarationVector
%type <astree> funcDeclaration
%type <astree> declaration

%type <astree> program
%type <astree> argDeclaration
%type <astree> block
%type <astree> expression

%type <astree> cmd
%type <astree> cmdSeq
%%


START: 	program	{ processAstree($1); }
	;
	
program: 	declaration ';' program	{ $$ = (astreeNode *)newAstreeNode(PROGRAM, $1, $3, 0, 0, 0, 0, getLineNumber()); }
	|		funcDeclaration program	{ $$ = (astreeNode *)newAstreeNode(PROGRAM, $1, $2, 0, 0, 0, 0, getLineNumber()); }
	|								{ $$ = NULL; }
	;


litList:	literal litList	{ $$ = (astreeNode *)newNode(LIT_LIST, $1, $2, 0, 0, 0, 0, getLineNumber()); }
	|						{ $$ = NULL; }
	;

type:	KW_BOOL	{ $$ = (astreeNode *)newNode(BOOL, 0,0,0,0,0,0,getLineNumber()); }
	|	KW_WORD	{ $$ = (astreeNode *)newNode(WORD, 0,0,0,0,0,0,getLineNumber()); } 
	|	KW_BYTE	{ $$ = (astreeNode *)newNode(BYTE, 0,0,0,0,0,0,getLineNumber()); }
	;
	
identifier: TK_IDENTIFIER	{ $$ = (astreeNode *)newNode(TK_IDENTIFIER,0,0,0,0,0,$1,getLineNumber); }
	;

literal:	LIT_INTEGER	{ $$ = (astreeNode *)newNode(LIT_INTEGER,0,0,0,0,0,$1,getLineNumber); }
	|		LIT_FALSE	{ $$ = (astreeNode *)newNode(LIT_FALSE,0,0,0,0,0,$1,getLineNumber); }
	|		LIT_TRUE	{ $$ = (astreeNode *)newNode(LIT_TRUE,0,0,0,0,0,$1,getLineNumber); }
	|		LIT_STRING	{ $$ = (astreeNode *)newNode(LIT_STRING,0,0,0,0,0,$1,getLineNumber); }
	|		LIT_CHAR	{ $$ = (astreeNode *)newNode(LIT_CHAR,0,0,0,0,0,$1,getLineNumber); }
	;
	
declaration:	declarationScalar	{ $$ = $1; }
	|			declarationVector	{ $$ = $1; }
	;
	
declarationScalar:	type identifier ':' literal		{ $$ = (astreeNode *)newNode(DECLARATION_SCALAR,$1,$2,$4,0,0,0,getLineNumber()); }
	|				type '$' identifier ':' literal	{ $$ = (astreeNode *)newNode(DECLARATION_POINTER,$1,$3,$5,0,0,0,getLineNumber()); }
	;

declarationVector:	type identifier '[' literal ']' ':' litList	{ $$ = (astreeNode *)newNode(DECLARATION_VECTOR,$1,$2,$4,$7,0,0,getLineNumber()); }
	|				type identifier '[' literal ']'				{ $$ = (astreeNode *)newNode(DECLARATION_VECTOR,$1,$2,$4,0,0,0,getLineNumber()); }
	;

funcDeclaration:	type identifier '(' argDeclaration ')' declarationScalar block	{ $$ = (astreeNode *)newNode(DECLARATION_FUNCTION,$1,$2,$4,$6,$7,0,getLineNumber); }
	|				type identifier '(' ')' declarationScalar block	{ $$ = (astreeNode *)newNode(DECLARATION_FUNCTION,$1,$2, 0 ,$5,$6,0,getLineNumber); }
	;

argDeclaration:	type identifier						{ $$ = (astreeNode *)newNode(ARG_DECLARATION,$1,$2,0,0,0,0,getLineNumber()); }
	|			type identifier ',' argDeclaration	{ $$ = (astreeNode *)newNode(ARG_DECLARATION,$1,$2,$4,0,0,0,getLineNumber()); }
	;

argList:	expression				{ $$ = (astreeNode *)newNode(ARGCALL,$1,0,0,0,0,0,getLineNumber()); }
	|		expression ',' argList 	{ $$ = (astreeNode *)newNode(ARGCALL,$1,$3,0,0,0,0,getLineNumber()); }
	|								{ $$ = NULL; }
	;

expression:	identifier								{ $$ = (astreeNode *)newNode(SCALAR_READ,$1,0,0,0,0,0,getLineNumber()); }
	|		identifier '[' expression ']'			{ $$ = (astreeNode *)newNode(VECTOR_READ,$1,0,0,0,0,0,getLineNumber()); }
	|		'&' identifier							{ $$ = (astreeNode *)newNode(GET_REFERENCE,$2,0,0,0,0,0,getLineNumber()); }							
	|		'*' identifier							{ $$ = (astreeNode *)newNode(POINTER,$2,0,0,0,0,0,getLineNumber()); }
	|		identifier '(' argList ')'				{ $$ = (astreeNode *)newNode(FUNCALL,$1,$3,0,0,0,0,getLineNumber()); }
	|		literal									{ $$ = $1; }
	|		'(' expression ')'						{ $$ = (astreeNode *)newNode(PAR,$2,0,0,0,0,0,getLineNumber()); }
	|		expression '+' expression				{ $$ = (astreeNode *)newNode(ADD,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression '-' expression				{ $$ = (astreeNode *)newNode(SUB,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression '*' expression				{ $$ = (astreeNode *)newNode(MUL,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression '/' expression				{ $$ = (astreeNode *)newNode(DIV,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression OPERATOR_OR expression		{ $$ = (astreeNode *)newNode(OR,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression OPERATOR_AND expression		{ $$ = (astreeNode *)newNode(AND,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression OPERATOR_LE expression		{ $$ = (astreeNode *)newNode(LE,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression OPERATOR_GE expression		{ $$ = (astreeNode *)newNode(GE,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression OPERATOR_EQ expression		{ $$ = (astreeNode *)newNode(EQ,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression OPERATOR_NE expression		{ $$ = (astreeNode *)newNode(NE,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression '<' expression				{ $$ = (astreeNode *)newNode(GREATER,$1,$3,0,0,0,0,getLineNumber()); }
	|		expression '>' expression				{ $$ = (astreeNode *)newNode(LESS,$1,$3,0,0,0,0,getLineNumber()); }
	;

block: '{' cmdSeq '}'	{ $$ = (astreeNode *)newNode(BLOCK,$2,0,0,0,0,0,getLineNumber()); }
	;

outputList:	LIT_STRING					{ $$ = (astreeNode *)newNode(OUTPUT_LIST,$1,0,0,0,0,0,getLineNumber()); }
	|		expression					{ $$ = (astreeNode *)newNode(OUTPUT_LIST,$1,0,0,0,0,0,getLineNUmber()); }
	|		LIT_STRING ',' outputList	{ $$ = (astreeNode *)newNode(OUTPUT_LIST,$1,$3,0,0,0,0,getLineNUmber()); }
	|		expression ',' outputList	{ $$ = (astreeNode *)newNode(OUTPUT_LIST,$1,$3,0,0,0,0,getLineNUmber()); }
	;

cmdSeq:	cmd ';' cmdSeq	{ $$ = (astreeNode *)newNode(CMD_SEQ, $1,$3,0,0,0,0,getLineNumber()); }
	;
	
cmd:		identifier '=' expression							{ $$ = (astreeNode *)newNode(SCALAR_WRITE,$1,$3,0,0,0,0,getLineNumber()); }
	|		identifier '[' expression ']' '=' expression		{ $$ = (astreeNode *)newNode(VECTOR_WRITE,$1,$3,$6,0,0,0,getLineNumber()); }
	|		'*' identifier '=' expression						{ $$ = (astreeNode *)newNode(POINTER_WRITE,$2,$4,0,0,0,0,getLineNumber()); }
	|		KW_INPUT identifier									{ $$ = (astreeNode *)newNode(INPUT, $2,0,0,0,0,0,getLineNumber()); }
	|		KW_OUTPUT outputList								{ $$ = (astreeNode *)newNode(OUTPUT, $2,0,0,0,0,0,getLineNumber()); }
	|		KW_RETURN expression								{ $$ = (astreeNode *)newNode(RETURN, $2,0,0,0,0,0,getLineNumber()); }
	|		block												{ $$ = $1; }
	|		KW_IF '(' expression ')' KW_THEN cmd %prec IFX		{ $$ = (astreeNode *)newNode(IF_THEN, $3,$6,0,0,0,0,getLineNumber()); }
	|		KW_IF '(' expression ')' KW_THEN cmd KW_ELSE cmd	{ $$ = (astreeNode *)newNode(IF_THEN_ELSE, $3,$6,$8,0,0,0,getLineNumber()); }
	|		KW_LOOP '(' expression ')' cmd						{ $$ = (astreeNode *)newNode(LOOP, $3,$5,0,0,0,0,getLineNumber()); }
	|															{ $$ = NULL; }
	;
	

%%

void yyerror()
{
	printf("PARSER ERROR on line %d\n",getLineNumber());
	exit(3);
}
