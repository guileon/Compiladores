%{
	#include "parser.tab.h"
	#include "tokens.h"
	#include "hash.h"
	#include "astree.h"
	
	void initMe(void);
	int getLineNumber(void);
	
	
	int nLines =1;
	int running = 1;
%}

DEC_DIGIT [0-9]
DIGIT [0-9a-fA-F]
CHARACTER [a-zA-Z_]
DIGIT_OR_CHARACTER [a-zA-Z0-9_]

%x MULTI_LINE_COMMENT

%%

word 								{ return KW_WORD; };
bool 								{ return KW_BOOL; };
byte 								{ return KW_BYTE; };
if   								{ return KW_IF; };
then 								{ return KW_THEN; };
else 								{ return KW_ELSE; };
loop 								{ return KW_LOOP; };
input 								{ return KW_INPUT; };
output 								{ return KW_OUTPUT; };
return 								{ return KW_RETURN; };

[,;:()\[\]\{}+\-*/<>=!&$] 			{ return yytext[0]; }
"<=" 								{ return OPERATOR_LE;};
">=" 								{ return OPERATOR_GE;};
"==" 								{ return OPERATOR_EQ;};
"!=" 								{ return OPERATOR_NE;};
"&&" 								{ return OPERATOR_AND;};
"||" 								{ return OPERATOR_OR;};

true|TRUE 							{ yylval.node = insertHash(yytext,SYMBOL_LIT_TRUE) ;return LIT_TRUE; };
false|FALSE 						{ yylval.node = insertHash(yytext,SYMBOL_LIT_FALSE) ;return LIT_FALSE; };
{CHARACTER}{DIGIT_OR_CHARACTER}* 	{ yylval.node = insertHash(yytext,SYMBOL_IDENTIFIER); return TK_IDENTIFIER; };
{DEC_DIGIT}{DIGIT}* 				{ yylval.node = insertHash(yytext,SYMBOL_LIT_INTEGER); return LIT_INTEGER; };
\'.\' 								{ yylval.node = insertHash(yytext,SYMBOL_LIT_CHAR); return LIT_CHAR; };
\"[^"]*\"							{ yylval.node = insertHash(yytext,SYMBOL_LIT_STRING) ;return LIT_STRING; };

"//".*"\n" 							{ nLines++; };
"/*" 								BEGIN(MULTI_LINE_COMMENT);
"\n" 								{ nLines++; }
" "|"	" 							{};
. 									{ return TOKEN_ERROR; }

<MULTI_LINE_COMMENT>"*/" 			BEGIN(INITIAL);
<MULTI_LINE_COMMENT>. 				{}
<MULTI_LINE_COMMENT>"\n" 			{ nLines++; }


%%

void setFile(char* fileName)
{
	yyin = fopen(fileName,"r");
}

void initMe()
{
	startHash();
}

int getLineNumber(void)
{
	return nLines;
}

int isRunning(void)
{
	return running;
}

int yywrap()
{
	running = 0;
	return 1;
}
