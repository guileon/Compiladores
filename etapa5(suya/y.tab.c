#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20110908

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
#include <stdio.h>
#include "hash.h"
#include "astree.h"

/*gambiarra:*/
extern ASTREE * arvore;

/*megagambiarra*/
int getLineNumber();

int yyerror(char *);


char t[] = "TRUE";
char f[] = "FALSE";
char tkbool[] = "bool";
char tkword[] = "word";
char tkbyte[] = "byte";

#line 23 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union	
{
	HASH_NODE * node; /*como os numeros sao em hexadecimal nao adianta ter um int*/
	char * string;
	ASTREE * astree;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 53 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define KW_WORD 257
#define KW_BOOL 258
#define KW_BYTE 259
#define KW_IF 260
#define KW_THEN 261
#define KW_ELSE 262
#define KW_LOOP 263
#define KW_INPUT 264
#define KW_RETURN 265
#define KW_OUTPUT 266
#define OPERATOR_LE 267
#define OPERATOR_GE 268
#define OPERATOR_EQ 269
#define OPERATOR_NE 270
#define OPERATOR_AND 271
#define OPERATOR_OR 272
#define TK_IDENTIFIER 273
#define LIT_INTEGER 274
#define LIT_FALSE 275
#define LIT_TRUE 276
#define LIT_CHAR 277
#define LIT_STRING 278
#define SCALAR 279
#define SYMBOL_LABEL 280
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    0,    6,    6,    6,    6,    4,    5,    8,
    8,    1,    1,    1,    1,    1,    2,    2,    2,    7,
    9,    9,   10,   10,   12,   13,   13,   14,   14,   11,
   15,   15,   16,   16,   16,   16,   16,   16,   16,   16,
   16,   17,   17,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,   18,   18,   19,   19,
};
static const short yylen[] = {                            2,
    2,    2,    0,    5,    6,    6,    8,    1,    1,    2,
    0,    1,    1,    1,    1,    1,    1,    1,    1,    7,
    1,    1,    4,    2,    0,    2,    0,    5,    6,    3,
    3,    0,    3,    6,    2,    2,    2,    6,    8,    5,
    1,    3,    1,    1,    4,    1,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    4,    2,    2,    1,    1,    3,    1,
};
static const short yydefred[] = {                         0,
   17,   18,   19,    0,    0,    0,    0,    8,    0,    0,
    1,    2,    0,    0,    0,    0,    0,   12,   13,   14,
   15,   16,    0,    9,    0,    0,    0,   22,   21,    0,
    4,    0,    0,    0,    5,    0,    6,    0,    0,    0,
    0,    0,    0,   23,    0,    0,    0,   20,   26,   10,
    7,    0,    0,    0,    0,    0,    0,    0,    0,   41,
    0,    0,    0,    0,    0,    0,   35,    0,    0,    0,
   46,    0,    0,    0,   36,    0,    0,   30,    0,    0,
   28,    0,    0,   64,    0,   63,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   31,   29,    0,    0,   47,
   56,   57,   58,   59,   60,   61,   48,   49,   50,   51,
   52,   53,   54,   55,    0,    0,   65,    0,   66,   42,
    0,    0,   40,   45,    0,   62,    0,    0,   67,    0,
    0,   39,
};
static const short yydgoto[] = {                          4,
   71,    5,   74,   73,   25,    6,    7,   43,   27,   28,
   60,   29,   40,   41,   61,   62,   75,  128,  129,
};
static const short yysindex[] = {                      -242,
    0,    0,    0,    0,  -31, -242, -242,    0, -263,  -27,
    0,    0,  -39, -241, -249, -242, -241,    0,    0,    0,
    0,    0,  -11,    0,  -40, -263,   14,    0,    0,    1,
    0,   36,   21, -242,    0, -241,    0, -242,  -30,  -43,
 -242, -241,   25,    0, -263,   28, -114,    0,    0,    0,
    0,   32, -241,   57,   64, -263,  -38,  -38,  -47,    0,
  -20,   39, -241,   51,  -38,  -38,    0, -263,  -38, -263,
    0,  100,  -29,  -15,    0,  -38,  -38,    0, -114,   52,
    0,    9,   16,    0,   40,    0,  -38,  -38,  -38,  -38,
  -38,  -38,  -38,  -38,  -38,  -38,  -38,  -38,  -38,  -38,
  -38,  -38,  -38,  100,   46,    0,    0, -147, -114,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   70,   76,    0,   75,    0,    0,
   63, -114,    0,    0,  -38,    0,  -38, -140,    0,  100,
 -114,    0,
};
static const short yyrindex[] = {                       127,
    0,    0,    0,    0,    0,  127,  127,    0,    0,    0,
    0,    0,    0,    0,    0,   84,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   87,   11,    0,   81,    0,    0,    0,    0,
   11,   81,    0,    0,    0,    0,   10,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -58,  -21,  -56,    0,    0,    0,    0,   10,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   84,    0,  -52,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  103,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   82,    0,  -51,
    0,    0,
};
static const short yygindex[] = {                        61,
  112,   58,  125,  347,    0,    0,    0,  111,    0,  117,
  116,   55,  123,    0,   79,  -66,   65,    0,   31,
};
#define YYTABLESIZE 488
static const short yytable[] = {                         70,
   37,   69,   43,   68,    9,   45,   33,   34,   47,    8,
  102,   44,   16,   76,    1,    2,    3,  100,   17,   44,
   44,   44,   44,   44,   24,   44,   95,   93,  103,   94,
   14,   96,   18,   19,   20,   21,   22,   44,   44,   44,
   44,  100,  133,   77,   97,   99,   98,   31,  100,  108,
   95,   93,   32,   94,   34,   96,  109,   95,   93,   35,
   94,  101,   96,   15,   38,  138,   11,   12,   97,   99,
   98,   44,  100,   26,  142,   97,   99,   98,  100,   47,
  110,   95,   93,   51,   94,   53,   96,   95,   93,   63,
   94,   39,   96,   36,   37,   26,   65,   79,   39,   97,
   99,   98,  100,   66,   78,   97,   99,   98,  100,   81,
  107,   95,   93,  132,   94,  136,   96,   95,   93,  135,
   94,  141,   96,  137,   25,   23,    3,   24,   30,   97,
   99,   98,  100,   27,   32,   97,   99,   98,  131,   11,
   38,   95,   93,   68,   94,   54,   96,   42,   55,   56,
   57,   58,   50,   42,   44,   48,  127,  106,    8,   97,
   99,   98,  134,   49,   64,  139,    0,  130,    0,    0,
    0,    0,    0,    0,   80,    0,    0,    0,    0,    0,
    0,   72,    0,    0,    0,    0,    0,    0,    0,   82,
   83,    0,    0,   85,    0,    0,    0,    0,    0,    0,
  104,  105,    0,   37,    0,   43,    0,    0,    0,   33,
   34,  111,  112,  113,  114,  115,  116,  117,  118,  119,
  120,  121,  122,  123,  124,  125,  126,    0,    0,    0,
    0,    0,    0,    0,    8,   18,   19,   20,   21,   22,
   44,    8,    8,    0,    0,   44,   44,   44,   44,   44,
   44,   87,   88,   89,   90,   91,   92,    0,    0,  126,
    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   87,   88,   89,   90,   91,
   92,    0,   87,   88,   89,   90,   91,   92,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   87,   88,   89,   90,
   91,   92,   87,   88,   89,   90,   91,   92,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   87,   88,   89,   90,
   91,   92,   87,   88,   89,   90,   91,   92,    0,    0,
    0,   10,    0,    0,    0,   13,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   87,   88,   89,   90,
   91,   92,   33,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   46,    0,    0,    0,    0,
    0,   52,    0,   59,    0,    0,    0,    0,    0,    0,
    0,    0,   67,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   84,    0,   86,    0,    0,    0,
    0,    0,    0,    0,    0,   59,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   59,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   59,    0,
    0,    0,    0,    0,    0,    0,    0,   59,
};
static const short yycheck[] = {                         38,
   59,   40,   59,   42,   36,   36,   59,   59,  123,  273,
   40,   33,   40,   61,  257,  258,  259,   33,   58,   41,
   42,   43,   44,   45,  274,   47,   42,   43,   44,   45,
   58,   47,  274,  275,  276,  277,  278,   59,   60,   61,
   62,   33,  109,   91,   60,   61,   62,   59,   33,   41,
   42,   43,   93,   45,   41,   47,   41,   42,   43,   59,
   45,   91,   47,   91,   44,  132,    6,    7,   60,   61,
   62,   93,   33,   16,  141,   60,   61,   62,   33,  123,
   41,   42,   43,   59,   45,   58,   47,   42,   43,   58,
   45,   34,   47,   58,   59,   38,   40,   59,   41,   60,
   61,   62,   33,   40,  125,   60,   61,   62,   33,   59,
   59,   42,   43,  261,   45,   41,   47,   42,   43,   44,
   45,  262,   47,   61,   41,   14,    0,   41,   17,   60,
   61,   62,   33,  123,  125,   60,   61,   62,   93,   59,
   59,   42,   43,   41,   45,  260,   47,   36,  263,  264,
  265,  266,   42,   42,   38,   40,  102,   79,  273,   60,
   61,   62,   93,   41,   53,  135,   -1,  103,   -1,   -1,
   -1,   -1,   -1,   -1,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   57,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   65,
   66,   -1,   -1,   69,   -1,   -1,   -1,   -1,   -1,   -1,
   76,   77,   -1,  262,   -1,  262,   -1,   -1,   -1,  262,
  262,   87,   88,   89,   90,   91,   92,   93,   94,   95,
   96,   97,   98,   99,  100,  101,  102,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,
  262,  273,  273,   -1,   -1,  267,  268,  269,  270,  271,
  272,  267,  268,  269,  270,  271,  272,   -1,   -1,  135,
   -1,  137,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,  271,
  272,   -1,  267,  268,  269,  270,  271,  272,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,  267,  268,  269,  270,  271,  272,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,  267,  268,  269,  270,  271,  272,   -1,   -1,
   -1,    5,   -1,   -1,   -1,    9,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,   26,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   39,   -1,   -1,   -1,   -1,
   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   56,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   68,   -1,   70,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   79,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  109,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  132,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  141,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 280
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,"'$'",0,"'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_WORD","KW_BOOL","KW_BYTE",
"KW_IF","KW_THEN","KW_ELSE","KW_LOOP","KW_INPUT","KW_RETURN","KW_OUTPUT",
"OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND",
"OPERATOR_OR","TK_IDENTIFIER","LIT_INTEGER","LIT_FALSE","LIT_TRUE","LIT_CHAR",
"LIT_STRING","SCALAR","SYMBOL_LABEL",
};
static const char *yyrule[] = {
"$accept : program",
"program : vardec program",
"program : fundec program",
"program :",
"vardec : vartype identifier ':' varlit ';'",
"vardec : vartype '$' identifier ':' varlit ';'",
"vardec : vartype identifier '[' integerlit ']' ';'",
"vardec : vartype identifier '[' integerlit ']' ':' listlit ';'",
"identifier : TK_IDENTIFIER",
"integerlit : LIT_INTEGER",
"listlit : varlit listlit",
"listlit :",
"varlit : LIT_INTEGER",
"varlit : LIT_FALSE",
"varlit : LIT_TRUE",
"varlit : LIT_CHAR",
"varlit : LIT_STRING",
"vartype : KW_WORD",
"vartype : KW_BOOL",
"vartype : KW_BYTE",
"fundec : vartype identifier '(' arguments ')' listlocaldec body",
"arguments : vazio",
"arguments : listarg",
"listarg : vartype identifier ',' listarg",
"listarg : vartype identifier",
"vazio :",
"listlocaldec : localdec listlocaldec",
"listlocaldec :",
"localdec : vartype identifier ':' varlit ';'",
"localdec : vartype '$' identifier ':' varlit ';'",
"body : '{' listcom '}'",
"listcom : com ';' listcom",
"listcom :",
"com : identifier '=' exp",
"com : identifier '[' exp ']' '=' exp",
"com : KW_INPUT identifier",
"com : KW_OUTPUT listout",
"com : KW_RETURN exp",
"com : KW_IF '(' exp ')' KW_THEN com",
"com : KW_IF '(' exp ')' KW_THEN com KW_ELSE com",
"com : KW_LOOP '(' exp ')' com",
"com : body",
"listout : exp ',' listout",
"listout : exp",
"exp : identifier",
"exp : identifier '[' exp ']'",
"exp : varlit",
"exp : '(' exp ')'",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : exp '<' exp",
"exp : exp '>' exp",
"exp : exp '=' exp",
"exp : exp '!' exp",
"exp : exp OPERATOR_LE exp",
"exp : exp OPERATOR_GE exp",
"exp : exp OPERATOR_EQ exp",
"exp : exp OPERATOR_NE exp",
"exp : exp OPERATOR_AND exp",
"exp : exp OPERATOR_OR exp",
"exp : identifier '(' param ')'",
"exp : '&' identifier",
"exp : '*' identifier",
"param : vazio",
"param : listparam",
"listparam : exp ',' listparam",
"listparam : exp",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 193 "parser.y"

int yyerror(char * s)
{
	fprintf(stderr, "Erro \"%s\" na linha %d.\n", s, getLineNumber());
	exit(3);
}

#line 423 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 83 "parser.y"
	{yyval.astree = arvore = astreeCreate(ASTREE_PROGRAM, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 2:
#line 84 "parser.y"
	{yyval.astree = arvore = astreeCreate(ASTREE_PROGRAM, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 3:
#line 85 "parser.y"
	{yyval.astree = NULL;}
break;
case 4:
#line 88 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARDEC_VAR, yystack.l_mark[-4].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL, NULL, getLineNumber());  }
break;
case 5:
#line 89 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARDEC_PTR, yystack.l_mark[-5].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL, NULL, getLineNumber()); }
break;
case 6:
#line 90 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARDEC_VECTOR, yystack.l_mark[-5].astree, yystack.l_mark[-4].astree, yystack.l_mark[-2].astree, NULL, NULL, NULL, getLineNumber()); }
break;
case 7:
#line 91 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARDEC_VECTOR_INITIALIZED, yystack.l_mark[-7].astree, yystack.l_mark[-6].astree, yystack.l_mark[-4].astree, yystack.l_mark[-1].astree, NULL, NULL, getLineNumber()); }
break;
case 8:
#line 94 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_IDENTIFIER, NULL, NULL, NULL, NULL, NULL, yystack.l_mark[0].node, getLineNumber());}
break;
case 9:
#line 97 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_INTEGERLIT, NULL, NULL, NULL, NULL, NULL, yystack.l_mark[0].node, getLineNumber());}
break;
case 10:
#line 100 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_LISTLIT, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 11:
#line 101 "parser.y"
	{yyval.astree = NULL;}
break;
case 12:
#line 104 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARLIT_INTEGER, NULL,NULL, NULL, NULL, NULL, yystack.l_mark[0].node, getLineNumber()); }
break;
case 13:
#line 105 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARLIT_FALSE, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 14:
#line 106 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARLIT_TRUE, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 15:
#line 107 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARLIT_CHAR, NULL, NULL, NULL, NULL, NULL, yystack.l_mark[0].node, getLineNumber()); }
break;
case 16:
#line 108 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARLIT_STRING, NULL, NULL, NULL, NULL, NULL, yystack.l_mark[0].node, getLineNumber()); }
break;
case 17:
#line 111 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARTYPE_WORD, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 18:
#line 112 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARTYPE_BOOL, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 19:
#line 113 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARTYPE_BYTE, NULL, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 20:
#line 116 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNC, yystack.l_mark[-6].astree, yystack.l_mark[-5].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, getLineNumber());  }
break;
case 21:
#line 118 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 22:
#line 119 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ARG_LIST, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 23:
#line 121 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_LISTARG_VIRG, yystack.l_mark[-3].astree, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, getLineNumber()); }
break;
case 24:
#line 122 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_LISTARG, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 25:
#line 125 "parser.y"
	{yyval.astree = 0;}
break;
case 26:
#line 128 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LIST_LOCAL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 27:
#line 129 "parser.y"
	{yyval.astree = NULL;}
break;
case 28:
#line 132 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LOCALDEC_VAR, yystack.l_mark[-4].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL, NULL, getLineNumber());  }
break;
case 29:
#line 133 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LOCALDEC_PTR, yystack.l_mark[-5].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL, NULL, getLineNumber()); }
break;
case 30:
#line 136 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_BODY, yystack.l_mark[-1].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber()); }
break;
case 31:
#line 139 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_LISTCOM, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 32:
#line 140 "parser.y"
	{yyval.astree = NULL;}
break;
case 33:
#line 145 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_ATR, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 34:
#line 146 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_ATR_VECTOR, yystack.l_mark[-5].astree, yystack.l_mark[-3].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, getLineNumber());}
break;
case 35:
#line 147 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_INPUT, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 36:
#line 148 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_OUTPUT, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 37:
#line 149 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_RETURN, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 38:
#line 150 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_IFTHEN, yystack.l_mark[-3].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 39:
#line 151 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_IFTHENELSE, yystack.l_mark[-5].astree, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, getLineNumber());}
break;
case 40:
#line 152 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_COM_LOOP, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 41:
#line 153 "parser.y"
	{yyval.astree = yystack.l_mark[0].astree;}
break;
case 42:
#line 156 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_LISTOUT, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 43:
#line 157 "parser.y"
	{yyval.astree = yystack.l_mark[0].astree;}
break;
case 44:
#line 160 "parser.y"
	{yyval.astree = yystack.l_mark[0].astree;}
break;
case 45:
#line 161 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_VECTOR, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 46:
#line 162 "parser.y"
	{yyval.astree = yystack.l_mark[0].astree;}
break;
case 47:
#line 163 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_PARENTESES, yystack.l_mark[-1].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 48:
#line 165 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_ADD,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0,0, NULL, getLineNumber());}
break;
case 49:
#line 166 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_SUB,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0,0, NULL, getLineNumber());}
break;
case 50:
#line 167 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_MUL,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0,0, NULL, getLineNumber());}
break;
case 51:
#line 168 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_DIV,yystack.l_mark[-2].astree,yystack.l_mark[0].astree,0,0,0, NULL, getLineNumber());}
break;
case 52:
#line 169 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_LESSER, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 53:
#line 170 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_GREATER, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 54:
#line 171 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_SINGLEEQ, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 55:
#line 172 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_NOT, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 56:
#line 173 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_LE, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 57:
#line 174 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_GE, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 58:
#line 175 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_EQ, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 59:
#line 176 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_NE, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 60:
#line 177 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_AND, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 61:
#line 178 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_OR, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 62:
#line 179 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_FUNCALL, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 63:
#line 180 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_ADDR, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 64:
#line 181 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_EXP_PTRVALUE, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 65:
#line 184 "parser.y"
	{yyval.astree = 0;}
break;
case 66:
#line 185 "parser.y"
	{yyval.astree = yystack.l_mark[0].astree;}
break;
case 67:
#line 188 "parser.y"
	{yyval.astree = astreeCreate(ASTREE_LISTPARAM, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, NULL, NULL, NULL, NULL, getLineNumber());}
break;
case 68:
#line 189 "parser.y"
	{yyval.astree = yystack.l_mark[0].astree;}
break;
#line 901 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
