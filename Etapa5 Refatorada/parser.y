%{
/*	EDUARDO DELAZERI FERREIRA
	GUILHERME LEON BERNO DE JESUS	*/
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "tokens.h"
#include "astree.h"
void yyerror();

%}

%union
{
	struct hashNode_s * node;
	struct astreeNode_s * astreeNode;
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

START:		PROG 		{ doAll($1); }
	;

PROG:		DECLARATION PROG  							{ $$ = (astreeNode *)newAstreeNode(PROGRAM, $1, $2, NULL, NULL, NULL,NULL,getLineNumber()) ; }
	|		FUNC_DECLARATION PROG 						{ $$ = (astreeNode *)newAstreeNode(PROGRAM, $1, $2, NULL, NULL, NULL,NULL,getLineNumber()) ; }
	|					  								{ $$ = NULL ; }
	; 
	
LIST:			LITERAL LIST 							{ $$ = (astreeNode *)newAstreeNode(LIT_LIST, $1, $2, NULL, NULL, NULL,NULL,getLineNumber()) ; }
	|													{ $$ = NULL ;}
	;
	
TYPE:		KW_BOOL 									{ $$ = (astreeNode *)newAstreeNode(BOOL,NULL,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	| 		KW_WORD 									{ $$ = (astreeNode *)newAstreeNode(WORD,NULL,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	| 		KW_BYTE 									{ $$ = (astreeNode *)newAstreeNode(BYTE,NULL,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	;

IDENTIFIER: TK_IDENTIFIER 								{ $$ = (astreeNode *)newAstreeNode(TK_IDENTIFIER,NULL,NULL,NULL,NULL,NULL,$1,getLineNumber()); }
	;
	
LITERAL:		LIT_INTEGER 							{ $$ = (astreeNode *)newAstreeNode(LIT_INTEGER,NULL,NULL,NULL,NULL,NULL,$1,getLineNumber()); }
	| 			LIT_FALSE								{ $$ = (astreeNode *)newAstreeNode(LIT_FALSE,NULL,NULL,NULL,NULL,NULL,$1,getLineNumber()); }
	| 			LIT_TRUE								{ $$ = (astreeNode *)newAstreeNode(LIT_TRUE,NULL,NULL,NULL,NULL,NULL,$1,getLineNumber()); }
	| 			LIT_STRING								{ $$ = (astreeNode *)newAstreeNode(LIT_STRING,NULL,NULL,NULL,NULL,NULL,$1,getLineNumber()); }
	| 			LIT_CHAR								{ $$ = (astreeNode *)newAstreeNode(LIT_CHAR,NULL,NULL,NULL,NULL,NULL,$1,getLineNumber()); }
	;
	
DECLARATION:	TYPE IDENTIFIER ':' LITERAL ';' 				{ $$ = (astreeNode *)newAstreeNode(DECLARATION_SCALAR,$1,$2,$4,NULL,NULL,NULL,getLineNumber()); }				
	|			TYPE '$'IDENTIFIER ':' LITERAL ';'				{ $$ = (astreeNode *)newAstreeNode(DECLARATION_POINTER,$1,$3,$5,NULL,NULL,NULL,getLineNumber()); }	
	|			TYPE IDENTIFIER '[' EXPRESSION ']' ':'LIST ';' 	{ $$ = (astreeNode *)newAstreeNode(DECLARATION_VECTOR,$1,$2,$4,$7,NULL,NULL,getLineNumber()); }	
	|			TYPE IDENTIFIER '[' EXPRESSION ']' ';'			{ $$ = (astreeNode *)newAstreeNode(DECLARATION_VECTOR,$1,$2,$4,NULL,NULL,NULL,getLineNumber()); }	
	;
	
	
DECLARATION_WO_VEC: 	TYPE IDENTIFIER ':' LITERAL ';' DECLARATION_WO_VEC			{ $$ = (astreeNode *)newAstreeNode(PROGRAM,newAstreeNode(DECLARATION_SCALAR,$1,$2,$4,NULL,NULL,NULL,getLineNumber()),$6,NULL,NULL,NULL,NULL,getLineNumber()); }
	|					TYPE '$'IDENTIFIER ':' LITERAL ';' DECLARATION_WO_VEC 		{ $$ = (astreeNode *)newAstreeNode(PROGRAM,newAstreeNode(DECLARATION_POINTER,$1,$3,$5,NULL,NULL,NULL,getLineNumber()),$7,NULL,NULL,NULL,NULL,getLineNumber()); }
	|					{ $$ = NULL; }
	;	

FUNC_DECLARATION:	TYPE IDENTIFIER '(' ARGUMENTS ')' DECLARATION_WO_VEC BLOCK 		{ $$ = (astreeNode *)newAstreeNode(DECLARATION_FUNCTION,$1,$2,$4,$6,$7,NULL,getLineNumber()); }
	|				TYPE IDENTIFIER '(' ')' DECLARATION_WO_VEC BLOCK 				{ $$ = (astreeNode *)newAstreeNode(DECLARATION_FUNCTION,$1,$2,NULL,$5,$6,NULL,getLineNumber()); }
	;

ARGUMENTS:	TYPE IDENTIFIER 														{ $$ = (astreeNode *)newAstreeNode(ARG_DECLARATION,$1,$2,NULL,NULL,NULL,NULL,getLineNumber()); }
	|		TYPE IDENTIFIER ',' ARGUMENTS 											{ $$ = (astreeNode *)newAstreeNode(ARG_DECLARATION,$1,$2,$4,NULL,NULL,NULL,getLineNumber()); }
	;	

ARGUMENTS_CALL: EXPRESSION 															{ $$ = (astreeNode *)newAstreeNode(ARGCALL,$1,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION ',' ARGUMENTS_CALL										{ $$ = (astreeNode *)newAstreeNode(ARGCALL,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|																				{ $$ = NULL;}
	;
	
EXPRESSION:		IDENTIFIER 							{ $$ = (astreeNode *)newAstreeNode(SCALAR_READ,$1,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }//$1; }
	|			IDENTIFIER '[' EXPRESSION ']'		{ $$ = (astreeNode *)newAstreeNode(VECTOR_READ,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			'&' IDENTIFIER 						{ $$ = (astreeNode *)newAstreeNode(GET_REFERENCE,$2,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			'*' IDENTIFIER 						{ $$ = (astreeNode *)newAstreeNode(POINTER,$2,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			LITERAL								{ $$ = $1; }
	|			'(' EXPRESSION ')' 					{ $$ = (astreeNode *)newAstreeNode(PAR,$2,NULL,NULL,NULL,NULL,NULL,getLineNumber());}
	|			EXPRESSION '*' EXPRESSION 			{ $$ = (astreeNode *)newAstreeNode(MUL,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION '+' EXPRESSION 			{ $$ = (astreeNode *)newAstreeNode(ADD,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION '/' EXPRESSION 			{ $$ = (astreeNode *)newAstreeNode(DIV,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION '-' EXPRESSION 			{ $$ = (astreeNode *)newAstreeNode(SUB,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			IDENTIFIER '(' ARGUMENTS_CALL ')' 	{ $$ = (astreeNode *)newAstreeNode(FUNCALL,$1,$3,NULL,NULL,NULL,NULL,getLineNumber());}
	|			EXPRESSION OPERATOR_OR EXPRESSION 	{ $$ = (astreeNode *)newAstreeNode(OR,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION OPERATOR_AND EXPRESSION 	{ $$ = (astreeNode *)newAstreeNode(AND,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION OPERATOR_LE EXPRESSION 	{ $$ = (astreeNode *)newAstreeNode(LE,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION OPERATOR_GE EXPRESSION 	{ $$ = (astreeNode *)newAstreeNode(GE,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION OPERATOR_EQ EXPRESSION 	{ $$ = (astreeNode *)newAstreeNode(EQ,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION OPERATOR_NE EXPRESSION 	{ $$ = (astreeNode *)newAstreeNode(NE,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION '<' EXPRESSION 			{ $$ = (astreeNode *)newAstreeNode(LESS,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|			EXPRESSION '>' EXPRESSION 			{ $$ = (astreeNode *)newAstreeNode(GREATER,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	;

BLOCK: '{' CMD_SEQ '}' 								{ $$ = (astreeNode *)newAstreeNode(BLOCK,$2,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	;

OUTPUT:		EXPRESSION								{ $$ = (astreeNode *)newAstreeNode(OUTPUT_LIST,$1,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	|		EXPRESSION ',' OUTPUT 					{ $$ = (astreeNode *)newAstreeNode(OUTPUT_LIST,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	;

CMD:		IDENTIFIER '=' EXPRESSION 							{ $$ = (astreeNode *)newAstreeNode(SCALAR_WRITE,$1,$3,NULL,NULL,NULL,NULL,getLineNumber()); }
	|		IDENTIFIER '[' EXPRESSION ']' '=' EXPRESSION		{ $$ = (astreeNode *)newAstreeNode(VECTOR_WRITE,$1,$3,$6,NULL,NULL,NULL,getLineNumber()); }
	|		'*' IDENTIFIER '=' EXPRESSION						{ $$ = (astreeNode *)newAstreeNode(POINTER_WRITE,$2,$4,NULL,NULL,NULL,NULL,getLineNumber()); }
	|		KW_INPUT IDENTIFIER 								{ $$ = (astreeNode *)newAstreeNode(INPUT,$2,NULL,NULL,NULL,NULL,NULL,getLineNumber()); }
	|		KW_OUTPUT OUTPUT  									{ $$ = (astreeNode *)newAstreeNode(OUTPUT, $2, NULL, NULL, NULL, NULL,NULL,getLineNumber()); }
	|		KW_RETURN EXPRESSION 								{ $$ = (astreeNode *)newAstreeNode(RETURN, $2, NULL, NULL, NULL, NULL,NULL,getLineNumber()); }
	|		BLOCK 												{ $$ = $1; }
	|		KW_IF '(' EXPRESSION ')' KW_THEN CMD %prec IFX				{ $$ = (astreeNode *)newAstreeNode(IF_THEN, $3, $6, NULL, NULL, NULL,NULL,getLineNumber()); }
	|		KW_IF '(' EXPRESSION ')' KW_THEN CMD KW_ELSE CMD 	{ $$ = (astreeNode *)newAstreeNode(IF_THEN_ELSE, $3, $6, $8, NULL, NULL,NULL,getLineNumber()); }
	|		KW_LOOP '(' EXPRESSION ')' CMD 						{ $$ = (astreeNode *)newAstreeNode(LOOP,$3,$5,NULL,NULL,NULL,NULL,getLineNumber()); }
	|															{ $$ = NULL; }
	;

	
CMD_SEQ:	CMD ';' CMD_SEQ 						{ $$ = (astreeNode *)newAstreeNode(CMD_SEQ, $1, $3, NULL, NULL, NULL,NULL,getLineNumber()); }
	|												{ $$ = NULL;}
	;


%%

void yyerror()
{
	printf("PARSER ERROR on line %d\n",getLineNumber());
	exit(3);
}
