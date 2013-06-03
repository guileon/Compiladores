%{
//EDUARDO DELAZERI FERREIRA
//GUILHERME LEON BERNO DE JESUS
#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#include "tokens.h"
#include "astree.h"
void yyerror();

%}

%union
{
	struct HNODE* node;
	struct a_NODE* astreeNode;
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
%token <node>LIT_FALSE    
%token <node>LIT_TRUE	    
%token <node>LIT_CHAR     
%token <node>LIT_STRING   

%token TOKEN_ERROR



%nonassoc IFX
%nonassoc KW_ELSE
%nonassoc '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_OR OPERATOR_AND
%left '+' '-'
%left '*' '/'



/* labrador */
// labrador
%type <astreeNode> LITERAL
%type <astreeNode> EXPRESSION
%type <astreeNode> IDENTIFIER
%type <astreeNode> ARGUMENTS_CALL
%type <astreeNode> PROG
%type <astreeNode> LIST
%type <astreeNode> TYPE
%type <astreeNode> DECLARATION
%type <astreeNode> DECLARATION_WO_VEC
%type <astreeNode> FUNC_DECLARATION
%type <astreeNode> ARGUMENTS
%type <astreeNode> BLOCK
%type <astreeNode> OUTPUT
%type <astreeNode> CMD
%type <astreeNode> CMD_SEQ
%%

START:		PROG 		{ printNode($1);verify($1); }
	;

PROG:		DECLARATION PROG  							{ $$ = (struct a_NODE*)newNode(PROG, $1, $2, NULL, NULL, NULL) ; }
	|		FUNC_DECLARATION PROG 						{ $$ = (struct a_NODE*)newNode(PROG, $1, $2, NULL, NULL, NULL) ; }
	|					  								{ $$ = NULL ; }
	; 
	
LIST:			LITERAL LIST 							{ $$ = (struct a_NODE*)newNode(LIST, $1, $2, NULL, NULL, NULL) ; }
	|													{ $$ = NULL ;}
	;
	
TYPE:		KW_BOOL 									{ $$ = (struct a_NODE*)newNode(KW_BOOL,NULL,NULL,NULL,NULL,NULL); }
	| 		KW_WORD 									{ $$ = (struct a_NODE*)newNode(KW_WORD,NULL,NULL,NULL,NULL,NULL); }
	| 		KW_BYTE 									{ $$ = (struct a_NODE*)newNode(KW_BYTE,NULL,NULL,NULL,NULL,NULL); }
	;

IDENTIFIER: TK_IDENTIFIER 								{ $$ = (struct a_NODE*)newNode(TK_IDENTIFIER,NULL,NULL,NULL,NULL,$1); }
	;
	
LITERAL:		LIT_INTEGER 							{ $$ = (struct a_NODE*)newNode(LIT_INTEGER,NULL,NULL,NULL,NULL,$1); }
	| 			LIT_FALSE								{ $$ = (struct a_NODE*)newNode(LIT_FALSE,NULL,NULL,NULL,NULL,$1); }
	| 			LIT_TRUE								{ $$ = (struct a_NODE*)newNode(LIT_TRUE,NULL,NULL,NULL,NULL,$1); }
	| 			LIT_STRING								{ $$ = (struct a_NODE*)newNode(LIT_STRING,NULL,NULL,NULL,NULL,$1); }
	| 			LIT_CHAR								{ $$ = (struct a_NODE*)newNode(LIT_CHAR,NULL,NULL,NULL,NULL,$1); }
	;
	
DECLARATION:	TYPE IDENTIFIER ':' LITERAL ';' 				{ $$ = (struct a_NODE*)newNode(DECLARATION,$1,$2,$4,NULL,NULL); }				
	|			TYPE '$'IDENTIFIER ':' LITERAL ';'				{ $$ = (struct a_NODE*)newNode(DECLARATION_POINTER,$1,$3,$5,NULL,NULL); }	
	|			TYPE IDENTIFIER '[' EXPRESSION ']' ':'LIST ';' 	{ $$ = (struct a_NODE*)newNode(DECLARATION_VEC_INIT,$1,$2,$4,$7,NULL); }	
	|			TYPE IDENTIFIER '[' EXPRESSION ']' ';'			{ $$ = (struct a_NODE*)newNode(DECLARATION_VEC,$1,$2,$4,NULL,NULL); }	
	;
	
	
DECLARATION_WO_VEC: 	TYPE IDENTIFIER ':' LITERAL ';' DECLARATION_WO_VEC			{ $$ = (struct a_NODE*)newNode(PROG,newNode(DECLARATION,$1,$2,$4,NULL,NULL),$6,NULL,NULL,NULL); }
	|					TYPE '$'IDENTIFIER ':' LITERAL ';' DECLARATION_WO_VEC 		{ $$ = (struct a_NODE*)newNode(PROG,newNode(DECLARATION_POINTER,$1,$3,$5,NULL,NULL),$7,NULL,NULL,NULL); }
	|					{ $$ = NULL; }
	;	

FUNC_DECLARATION:	TYPE IDENTIFIER '(' ARGUMENTS ')' DECLARATION_WO_VEC BLOCK 		{ $$ = (struct a_NODE*)newNode(FUNC_DECLARATION,$1,$2,$4,newNode(D_NODE,$6,$7,NULL,NULL,NULL),NULL); }
	|				TYPE IDENTIFIER '(' ')' DECLARATION_WO_VEC BLOCK 				{ $$ = (struct a_NODE*)newNode(FUNC_DECLARATION,$1,$2,NULL,newNode(D_NODE,$5,$6,NULL,NULL,NULL),NULL); }
	;

ARGUMENTS:	TYPE IDENTIFIER 														{ $$ = (struct a_NODE*)newNode(ARGUMENTS,$1,$2,NULL,NULL,NULL); }
	|		TYPE IDENTIFIER ',' ARGUMENTS 											{ $$ = (struct a_NODE*)newNode(ARGUMENTS,$1,$2,$4,NULL,NULL); }
	;	

ARGUMENTS_CALL: EXPRESSION 															{ $$ = (struct a_NODE*)newNode(ARGCALL,$1,NULL,NULL,NULL,NULL); }
	|			EXPRESSION ',' ARGUMENTS_CALL										{ $$ = (struct a_NODE*)newNode(ARGCALL,$1,$3,NULL,NULL,NULL); }
	|																				{ $$ = NULL;}
	;
	
EXPRESSION:		IDENTIFIER 							{ $$ = $1; }
	|			IDENTIFIER '[' EXPRESSION ']'		{ $$ = (struct a_NODE*)newNode(VECCALL,$1,$3,NULL,NULL,NULL); }
	|			'&' IDENTIFIER 						{ $$ = (struct a_NODE*)newNode('&',$2,NULL,NULL,NULL,NULL); }
	|			'*' IDENTIFIER 						{ $$ = (struct a_NODE*)newNode(POINTER,$2,NULL,NULL,NULL,NULL); }
	|			LITERAL								{ $$ = $1; }
	|			'(' EXPRESSION ')' 					{ $$ = (struct a_NODE*)newNode('(',$2,NULL,NULL,NULL,NULL);}
	|			EXPRESSION '*' EXPRESSION 			{ $$ = (struct a_NODE*)newNode('*',$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION '+' EXPRESSION 			{ $$ = (struct a_NODE*)newNode('+',$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION '/' EXPRESSION 			{ $$ = (struct a_NODE*)newNode('/',$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION '-' EXPRESSION 			{ $$ = (struct a_NODE*)newNode('-',$1,$3,NULL,NULL,NULL); }
	|			IDENTIFIER '(' ARGUMENTS_CALL ')' 	{ $$ = (struct a_NODE*)newNode(FUNCALL,$1,$3,NULL,NULL,NULL);}
	|			EXPRESSION OPERATOR_OR EXPRESSION 	{ $$ = (struct a_NODE*)newNode(OR,$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION OPERATOR_AND EXPRESSION 	{ $$ = (struct a_NODE*)newNode(AND,$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION OPERATOR_LE EXPRESSION 	{ $$ = (struct a_NODE*)newNode(LE,$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION OPERATOR_GE EXPRESSION 	{ $$ = (struct a_NODE*)newNode(GE,$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION OPERATOR_EQ EXPRESSION 	{ $$ = (struct a_NODE*)newNode(EQ,$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION OPERATOR_NE EXPRESSION 	{ $$ = (struct a_NODE*)newNode(NE,$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION '<' EXPRESSION 			{ $$ = (struct a_NODE*)newNode('<',$1,$3,NULL,NULL,NULL); }
	|			EXPRESSION '>' EXPRESSION 			{ $$ = (struct a_NODE*)newNode('>',$1,$3,NULL,NULL,NULL); }
	;

BLOCK: '{' CMD_SEQ '}' 								{ $$ = (struct a_NODE*)newNode(BLOCK,$2,NULL,NULL,NULL,NULL); }
	;

OUTPUT:		EXPRESSION								{ $$ = (struct a_NODE*)newNode(OUTPUT_L,$1,NULL,NULL,NULL,NULL); }
	|		EXPRESSION ',' OUTPUT 					{ $$ = (struct a_NODE*)newNode(OUTPUT_L,$1,$3,NULL,NULL,NULL); }
	;

CMD:		IDENTIFIER '=' EXPRESSION 							{ $$ = (struct a_NODE*)newNode('=',$1,$3,NULL,NULL,NULL); }
	|		IDENTIFIER '[' EXPRESSION ']' '=' EXPRESSION		{ $$ = (struct a_NODE*)newNode('=',newNode(VECCALL,$1,$3,NULL,NULL,NULL),$6,NULL,NULL,NULL); }
	|		'*' IDENTIFIER '=' EXPRESSION						{ $$ = (struct a_NODE*)newNode('=',newNode(POINTER,$2,NULL,NULL,NULL,NULL),$4,NULL,NULL,NULL); }
	|		KW_INPUT IDENTIFIER 								{ $$ = (struct a_NODE*)newNode(INPUT,$2,NULL,NULL,NULL,NULL); }
	|		KW_OUTPUT OUTPUT  									{ $$ = (struct a_NODE*)newNode(OUTPUT, $2, NULL, NULL, NULL, NULL); }
	|		KW_RETURN EXPRESSION 								{ $$ = (struct a_NODE*)newNode(RETURN, $2, NULL, NULL, NULL, NULL); }
	|		BLOCK 												{ $$ = $1; }
	|		KW_IF '(' EXPRESSION ')' KW_THEN CMD %prec IFX				{ $$ = (struct a_NODE*)newNode(IF_THEN, $3, $6, NULL, NULL, NULL); }
	|		KW_IF '(' EXPRESSION ')' KW_THEN CMD KW_ELSE CMD 	{ $$ = (struct a_NODE*)newNode(IF_THEN_ELSE, $3, $6, $8, NULL, NULL); }
	|		KW_LOOP '(' EXPRESSION ')' CMD 						{ $$ = (struct a_NODE*)newNode(LOOP,$3,$5,NULL,NULL,NULL); }
	|															{ $$ = NULL; }
	;

	
CMD_SEQ:	CMD ';' CMD_SEQ 						{ $$ = (struct a_NODE*)newNode(CMD_SEQ, $1, $3, NULL, NULL, NULL); }
	|												{ $$ = NULL;}
	;


%%

void yyerror()
{
	printf("PARSER ERROR on line %d\n",getLineNumber());
	exit(3);
}
