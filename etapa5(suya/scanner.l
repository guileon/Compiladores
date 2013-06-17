%{

#include "hash.h"
#include "astree.h"
#include "y.tab.h"


int lineNumber =1;
int running =1;

int yyerror(char *);

%}

%x COMM

HEXDIGIT			[0-9a-fA-F]
ID_CHAR       			[A-Za-z0-9_]

%%

word				{ return KW_WORD; }
bool				{ return KW_BOOL; }
byte				{ return KW_BYTE;}
if					{ return KW_IF; }
then				{ return KW_THEN;}
else				{ return KW_ELSE;}
loop				{ return KW_LOOP; }
input				{ return KW_INPUT;}
return				{ return KW_RETURN;}
output				{ return KW_OUTPUT;}

"<="				{ return OPERATOR_LE;}
">="				{ return OPERATOR_GE;}
"=="				{ return OPERATOR_EQ;}
"!="				{ return OPERATOR_NE;}
"&&"				{ return OPERATOR_AND;}
"||"				{ return OPERATOR_OR;}

FALSE				{ return LIT_FALSE; }
TRUE				{ return LIT_TRUE; }
'.'				{ yylval = (YYSTYPE)hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }
\"[^\"]*\"			{ yylval = (YYSTYPE)hashInsert(yytext, LIT_STRING); return LIT_STRING; }		

[A-Za-z]{ID_CHAR}*  		{ yylval = (YYSTYPE)hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}
(-{HEXDIGIT}+)|([0-9]{HEXDIGIT}*) { yylval = (YYSTYPE)hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER; }


","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$"  { return yytext[0]; }


\/\/.*				{ }
"/*"				BEGIN(COMM);

\n				{ ++ lineNumber; }
[ \t]+				{ }
.				{ yyerror("Caracter invalido."); }



<COMM>"*/" 		BEGIN(INITIAL);
<COMM>. 		{ }
<COMM>\n		{ ++ lineNumber; }	

%%

int getLineNumber()
{
	return lineNumber;
}

int yywrap()
{ 
	running = 0;
	return 1;
}

void initMe (void)
{
	hashInit();
	return;
}





