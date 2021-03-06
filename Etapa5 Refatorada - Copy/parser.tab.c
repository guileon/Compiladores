
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

/*	EDUARDO DELAZERI FERREIRA
	GUILHERME LEON BERNO DE JESUS	*/
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "tokens.h"
#include "astree.h"
void yyerror();



/* Line 189 of yacc.c  */
#line 86 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_WORD = 258,
     KW_BOOL = 259,
     KW_BYTE = 260,
     KW_IF = 261,
     KW_THEN = 262,
     KW_ELSE = 263,
     KW_LOOP = 264,
     KW_INPUT = 265,
     KW_RETURN = 266,
     KW_OUTPUT = 267,
     OPERATOR_LE = 268,
     OPERATOR_GE = 269,
     OPERATOR_EQ = 270,
     OPERATOR_NE = 271,
     OPERATOR_AND = 272,
     OPERATOR_OR = 273,
     TK_IDENTIFIER = 274,
     LIT_INTEGER = 275,
     LIT_FALSE = 276,
     LIT_TRUE = 277,
     LIT_CHAR = 278,
     LIT_STRING = 279,
     TOKEN_ERROR = 280,
     IFX = 281
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 14 "parser.y"

	struct hashNode_s * node;
	struct astreeNode_s * astreeNode;



/* Line 214 of yacc.c  */
#line 155 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 167 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    35,     2,    41,     2,
      38,    39,    31,    29,    40,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    34,
      27,    44,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    12,    15,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    40,    47,
      56,    63,    70,    78,    79,    87,    94,    97,   102,   104,
     108,   109,   111,   116,   119,   122,   124,   128,   132,   136,
     140,   144,   149,   153,   157,   161,   165,   169,   173,   177,
     181,   185,   187,   191,   195,   202,   207,   210,   213,   216,
     218,   225,   234,   240,   245,   246,   250
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    47,    -1,    52,    47,    -1,    54,    47,
      -1,    -1,    51,    48,    -1,    -1,     4,    -1,     3,    -1,
       5,    -1,    19,    -1,    20,    -1,    21,    -1,    22,    -1,
      24,    -1,    23,    -1,    49,    50,    33,    51,    34,    -1,
      49,    35,    50,    33,    51,    34,    -1,    49,    50,    36,
      57,    37,    33,    48,    34,    -1,    49,    50,    36,    57,
      37,    34,    -1,    49,    50,    33,    51,    34,    53,    -1,
      49,    35,    50,    33,    51,    34,    53,    -1,    -1,    49,
      50,    38,    55,    39,    53,    58,    -1,    49,    50,    38,
      39,    53,    58,    -1,    49,    50,    -1,    49,    50,    40,
      55,    -1,    57,    -1,    57,    40,    56,    -1,    -1,    50,
      -1,    50,    36,    57,    37,    -1,    41,    50,    -1,    31,
      50,    -1,    51,    -1,    38,    57,    39,    -1,    57,    31,
      57,    -1,    57,    29,    57,    -1,    57,    32,    57,    -1,
      57,    30,    57,    -1,    50,    38,    56,    39,    -1,    57,
      18,    57,    -1,    57,    17,    57,    -1,    57,    13,    57,
      -1,    57,    14,    57,    -1,    57,    15,    57,    -1,    57,
      16,    57,    -1,    57,    27,    57,    -1,    57,    28,    57,
      -1,    42,    61,    43,    -1,    57,    -1,    57,    40,    59,
      -1,    50,    44,    57,    -1,    50,    36,    57,    37,    44,
      57,    -1,    31,    50,    44,    57,    -1,    10,    50,    -1,
      12,    59,    -1,    11,    57,    -1,    58,    -1,     6,    38,
      57,    39,     7,    60,    -1,     6,    38,    57,    39,     7,
      60,     8,    60,    -1,     9,    38,    57,    39,    60,    -1,
      50,    38,    56,    39,    -1,    -1,    60,    34,    61,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    76,    76,    79,    80,    81,    84,    85,    88,    89,
      90,    93,    96,    97,    98,    99,   100,   103,   104,   105,
     106,   110,   111,   112,   115,   116,   119,   120,   123,   124,
     125,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     149,   152,   153,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   171,   172
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_WORD", "KW_BOOL", "KW_BYTE", "KW_IF",
  "KW_THEN", "KW_ELSE", "KW_LOOP", "KW_INPUT", "KW_RETURN", "KW_OUTPUT",
  "OPERATOR_LE", "OPERATOR_GE", "OPERATOR_EQ", "OPERATOR_NE",
  "OPERATOR_AND", "OPERATOR_OR", "TK_IDENTIFIER", "LIT_INTEGER",
  "LIT_FALSE", "LIT_TRUE", "LIT_CHAR", "LIT_STRING", "TOKEN_ERROR", "IFX",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "':'", "';'", "'$'", "'['",
  "']'", "'('", "')'", "','", "'&'", "'{'", "'}'", "'='", "$accept",
  "START", "PROG", "LIST", "TYPE", "IDENTIFIER", "LITERAL", "DECLARATION",
  "DECLARATION_WO_VEC", "FUNC_DECLARATION", "ARGUMENTS", "ARGUMENTS_CALL",
  "EXPRESSION", "BLOCK", "OUTPUT", "CMD", "CMD_SEQ", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    60,    62,    43,
      45,    42,    47,    58,    59,    36,    91,    93,    40,    41,
      44,    38,   123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    47,    48,    48,    49,    49,
      49,    50,    51,    51,    51,    51,    51,    52,    52,    52,
      52,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    59,    59,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     6,     8,
       6,     6,     7,     0,     7,     6,     2,     4,     1,     3,
       0,     1,     4,     2,     2,     1,     3,     3,     3,     3,
       3,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     6,     4,     2,     2,     2,     1,
       6,     8,     5,     4,     0,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     9,     8,    10,     0,     2,     0,     5,     5,     1,
      11,     0,     0,     3,     4,     0,     0,     0,     0,     0,
      12,    13,    14,    16,    15,     0,     0,     0,     0,    31,
      35,     0,    23,     0,     0,     0,    17,    34,     0,    33,
       0,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    23,    18,
      36,     0,     0,    28,    44,    45,    46,    47,    43,    42,
      48,    49,    38,    40,    37,    39,     7,    20,     0,     0,
      64,    25,     0,     0,    32,    41,    30,     0,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
       0,    27,    24,    29,    19,     6,     0,     0,     0,     0,
      56,    58,    51,    57,     0,     0,    30,     0,    64,    50,
       0,    23,     0,     0,     0,     0,     0,     0,    53,    65,
      23,    21,     0,    64,    52,    55,     0,    63,    22,    64,
      62,     0,    60,    54,    64,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,    87,    55,    29,    30,     7,    56,     8,
      34,    62,    63,    98,   113,    99,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -81
static const yytype_int16 yypact[] =
{
      77,   -81,   -81,   -81,     8,   -81,   -17,    77,    77,   -81,
     -81,     0,    33,   -81,   -81,    -5,    95,   251,     9,    95,
     -81,   -81,   -81,   -81,   -81,    -4,     0,   251,     0,   -12,
     -81,   199,    77,     0,   -16,    20,   -81,   -81,   160,   -81,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,    13,   -10,     1,    23,    77,   -81,
     -81,   224,    28,   126,   280,   280,   280,   280,   280,   280,
     280,   280,    19,    19,   -81,   -81,    95,   -81,     0,    43,
      46,   -81,    77,     1,   -81,   -81,   251,    44,    95,    53,
      95,    56,    57,     0,   251,   251,     0,    24,   -81,    69,
      62,   -81,   -81,   -81,   -81,   -81,    95,    73,   251,   251,
     -81,   286,   132,   -81,    64,   251,   251,   251,    46,   -81,
      76,    77,   166,   193,   251,   251,   249,    72,   286,   -81,
      77,   -81,   113,    90,   -81,   286,    78,   -81,   -81,    90,
     -81,   251,   115,   286,    90,   -81
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,    85,    36,     3,    -6,   -15,   -81,   -51,   -81,
      47,   -71,   -11,   -39,     2,   -80,     7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int16 yytable[] =
{
      12,    25,    10,     6,    35,    15,    31,    83,     9,    10,
       6,     6,     1,     2,     3,   103,    38,    81,    11,    10,
      37,    33,    39,    58,    40,    78,    41,    57,    19,    61,
      36,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    80,   102,   127,    76,    77,    32,    79,
      52,    53,    91,   140,    59,    92,    93,    94,    95,   142,
     115,    88,   116,    82,   145,    10,    16,    85,   117,    17,
     131,    18,    89,    88,    97,   107,    90,    96,   104,   138,
       1,     2,     3,   111,   112,    33,   106,   110,    80,   -66,
     114,   120,    13,    14,   108,   109,    91,   122,   123,    92,
      93,    94,    95,   118,   126,   119,   128,   121,   125,    10,
     130,   137,    97,   112,   135,    20,    21,    22,    23,    24,
     139,    96,   141,   144,   105,   129,   134,    97,     0,   101,
     143,     0,    80,    97,     0,     0,     0,     0,    97,    42,
      43,    44,    45,    46,    47,    42,    43,    44,    45,    46,
      47,     0,     0,    48,    49,    50,    51,    52,    53,    48,
      49,    50,    51,    52,    53,     0,    86,     0,     0,     0,
       0,     0,   124,    42,    43,    44,    45,    46,    47,    42,
      43,    44,    45,    46,    47,     0,     0,    48,    49,    50,
      51,    52,    53,    48,    49,    50,    51,    52,    53,    60,
       0,     0,     0,     0,     0,   132,    42,    43,    44,    45,
      46,    47,    42,    43,    44,    45,    46,    47,     0,     0,
      48,    49,    50,    51,    52,    53,    48,    49,    50,    51,
      52,    53,   133,     0,     0,     0,    54,    42,    43,    44,
      45,    46,    47,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    52,    53,     0,     0,     0,
       0,    84,    42,    43,    44,    45,    46,    47,     0,     0,
      10,    20,    21,    22,    23,    24,    48,    49,    50,    51,
      52,    53,    26,     0,     0,     0,   136,     0,     0,    27,
       0,     0,    28,   -67,   -67,   -67,   -67,   -67,   -67,    42,
      43,    44,    45,    46,    47,     0,     0,   -67,   -67,    50,
      51,    52,    53,    48,    49,    50,    51,    52,    53
};

static const yytype_int16 yycheck[] =
{
       6,    16,    19,     0,    19,    11,    17,    58,     0,    19,
       7,     8,     3,     4,     5,    86,    27,    56,    35,    19,
      26,    18,    28,    39,    36,    35,    38,    33,    33,    40,
      34,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    42,    83,   116,    33,    34,    39,    55,
      31,    32,     6,   133,    34,     9,    10,    11,    12,   139,
      36,    76,    38,    40,   144,    19,    33,    39,    44,    36,
     121,    38,    78,    88,    80,    90,    33,    31,    34,   130,
       3,     4,     5,    94,    95,    82,    33,    93,    42,    43,
      96,   106,     7,     8,    38,    38,     6,   108,   109,     9,
      10,    11,    12,    34,   115,    43,   117,    34,    44,    19,
      34,    39,   118,   124,   125,    20,    21,    22,    23,    24,
       7,    31,    44,     8,    88,   118,   124,   133,    -1,    82,
     141,    -1,    42,   139,    -1,    -1,    -1,    -1,   144,    13,
      14,    15,    16,    17,    18,    13,    14,    15,    16,    17,
      18,    -1,    -1,    27,    28,    29,    30,    31,    32,    27,
      28,    29,    30,    31,    32,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    40,    13,    14,    15,    16,    17,    18,    13,
      14,    15,    16,    17,    18,    -1,    -1,    27,    28,    29,
      30,    31,    32,    27,    28,    29,    30,    31,    32,    39,
      -1,    -1,    -1,    -1,    -1,    39,    13,    14,    15,    16,
      17,    18,    13,    14,    15,    16,    17,    18,    -1,    -1,
      27,    28,    29,    30,    31,    32,    27,    28,    29,    30,
      31,    32,    39,    -1,    -1,    -1,    37,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    37,    13,    14,    15,    16,    17,    18,    -1,    -1,
      19,    20,    21,    22,    23,    24,    27,    28,    29,    30,
      31,    32,    31,    -1,    -1,    -1,    37,    -1,    -1,    38,
      -1,    -1,    41,    13,    14,    15,    16,    17,    18,    13,
      14,    15,    16,    17,    18,    -1,    -1,    27,    28,    29,
      30,    31,    32,    27,    28,    29,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    46,    47,    49,    52,    54,     0,
      19,    35,    50,    47,    47,    50,    33,    36,    38,    33,
      20,    21,    22,    23,    24,    51,    31,    38,    41,    50,
      51,    57,    39,    49,    55,    51,    34,    50,    57,    50,
      36,    38,    13,    14,    15,    16,    17,    18,    27,    28,
      29,    30,    31,    32,    37,    49,    53,    50,    39,    34,
      39,    57,    56,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    33,    34,    35,    50,
      42,    58,    40,    53,    37,    39,    40,    48,    51,    50,
      33,     6,     9,    10,    11,    12,    31,    50,    58,    60,
      61,    55,    58,    56,    34,    48,    33,    51,    38,    38,
      50,    57,    57,    59,    50,    36,    38,    44,    34,    43,
      51,    34,    57,    57,    40,    44,    57,    56,    57,    61,
      34,    53,    39,    39,    59,    57,    37,    39,    53,     7,
      60,    44,    60,    57,     8,    60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 76 "parser.y"
    { doAll((yyvsp[(1) - (1)].astreeNode)); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 79 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(PROGRAM, (yyvsp[(1) - (2)].astreeNode), (yyvsp[(2) - (2)].astreeNode), NULL, NULL, NULL,NULL,getLineNumber()) ; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 80 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(PROGRAM, (yyvsp[(1) - (2)].astreeNode), (yyvsp[(2) - (2)].astreeNode), NULL, NULL, NULL,NULL,getLineNumber()) ; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    { (yyval.astreeNode) = NULL ; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 84 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LIT_LIST, (yyvsp[(1) - (2)].astreeNode), (yyvsp[(2) - (2)].astreeNode), NULL, NULL, NULL,NULL,getLineNumber()) ; ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 85 "parser.y"
    { (yyval.astreeNode) = NULL ;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 88 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(BOOL,NULL,NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 89 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(WORD,NULL,NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 90 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(BYTE,NULL,NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(TK_IDENTIFIER,NULL,NULL,NULL,NULL,NULL,(yyvsp[(1) - (1)].node),getLineNumber()); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LIT_INTEGER,NULL,NULL,NULL,NULL,NULL,(yyvsp[(1) - (1)].node),getLineNumber()); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LIT_FALSE,NULL,NULL,NULL,NULL,NULL,(yyvsp[(1) - (1)].node),getLineNumber()); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 98 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LIT_TRUE,NULL,NULL,NULL,NULL,NULL,(yyvsp[(1) - (1)].node),getLineNumber()); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 99 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LIT_STRING,NULL,NULL,NULL,NULL,NULL,(yyvsp[(1) - (1)].node),getLineNumber()); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 100 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LIT_CHAR,NULL,NULL,NULL,NULL,NULL,(yyvsp[(1) - (1)].node),getLineNumber()); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 103 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DECLARATION_SCALAR,(yyvsp[(1) - (5)].astreeNode),(yyvsp[(2) - (5)].astreeNode),(yyvsp[(4) - (5)].astreeNode),NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DECLARATION_POINTER,(yyvsp[(1) - (6)].astreeNode),(yyvsp[(3) - (6)].astreeNode),(yyvsp[(5) - (6)].astreeNode),NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DECLARATION_VECTOR,(yyvsp[(1) - (8)].astreeNode),(yyvsp[(2) - (8)].astreeNode),(yyvsp[(4) - (8)].astreeNode),(yyvsp[(7) - (8)].astreeNode),NULL,NULL,getLineNumber()); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DECLARATION_VECTOR,(yyvsp[(1) - (6)].astreeNode),(yyvsp[(2) - (6)].astreeNode),(yyvsp[(4) - (6)].astreeNode),NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(PROGRAM,newAstreeNode(DECLARATION_SCALAR,(yyvsp[(1) - (6)].astreeNode),(yyvsp[(2) - (6)].astreeNode),(yyvsp[(4) - (6)].astreeNode),NULL,NULL,NULL,getLineNumber()),(yyvsp[(6) - (6)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(PROGRAM,newAstreeNode(DECLARATION_POINTER,(yyvsp[(1) - (7)].astreeNode),(yyvsp[(3) - (7)].astreeNode),(yyvsp[(5) - (7)].astreeNode),NULL,NULL,NULL,getLineNumber()),(yyvsp[(7) - (7)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    { (yyval.astreeNode) = NULL; ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DECLARATION_FUNCTION,(yyvsp[(1) - (7)].astreeNode),(yyvsp[(2) - (7)].astreeNode),(yyvsp[(4) - (7)].astreeNode),(yyvsp[(6) - (7)].astreeNode),(yyvsp[(7) - (7)].astreeNode),NULL,getLineNumber()); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DECLARATION_FUNCTION,(yyvsp[(1) - (6)].astreeNode),(yyvsp[(2) - (6)].astreeNode),NULL,(yyvsp[(5) - (6)].astreeNode),(yyvsp[(6) - (6)].astreeNode),NULL,getLineNumber()); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 119 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(ARG_DECLARATION,(yyvsp[(1) - (2)].astreeNode),(yyvsp[(2) - (2)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(ARG_DECLARATION,(yyvsp[(1) - (4)].astreeNode),(yyvsp[(2) - (4)].astreeNode),(yyvsp[(4) - (4)].astreeNode),NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(ARGCALL,(yyvsp[(1) - (1)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(ARGCALL,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 125 "parser.y"
    { (yyval.astreeNode) = NULL;;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 128 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(SCALAR_READ,(yyvsp[(1) - (1)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 129 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(VECTOR_READ,(yyvsp[(1) - (4)].astreeNode),(yyvsp[(3) - (4)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(GET_REFERENCE,(yyvsp[(2) - (2)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 131 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(POINTER,(yyvsp[(2) - (2)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 132 "parser.y"
    { (yyval.astreeNode) = (yyvsp[(1) - (1)].astreeNode); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 133 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(PAR,(yyvsp[(2) - (3)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber());;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(MUL,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 135 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(ADD,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 136 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(DIV,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 137 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(SUB,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 138 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(FUNCALL,(yyvsp[(1) - (4)].astreeNode),(yyvsp[(3) - (4)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber());;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(OR,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(AND,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 141 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LE,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 142 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(GE,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 143 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(EQ,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 144 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(NE,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LESS,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 146 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(GREATER,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(BLOCK,(yyvsp[(2) - (3)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(OUTPUT_LIST,(yyvsp[(1) - (1)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(OUTPUT_LIST,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(SCALAR_WRITE,(yyvsp[(1) - (3)].astreeNode),(yyvsp[(3) - (3)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(VECTOR_WRITE,(yyvsp[(1) - (6)].astreeNode),(yyvsp[(3) - (6)].astreeNode),(yyvsp[(6) - (6)].astreeNode),NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(POINTER_WRITE,(yyvsp[(2) - (4)].astreeNode),(yyvsp[(4) - (4)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(INPUT,(yyvsp[(2) - (2)].astreeNode),NULL,NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(OUTPUT, (yyvsp[(2) - (2)].astreeNode), NULL, NULL, NULL, NULL,NULL,getLineNumber()); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(RETURN, (yyvsp[(2) - (2)].astreeNode), NULL, NULL, NULL, NULL,NULL,getLineNumber()); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    { (yyval.astreeNode) = (yyvsp[(1) - (1)].astreeNode); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(IF_THEN, (yyvsp[(3) - (6)].astreeNode), (yyvsp[(6) - (6)].astreeNode), NULL, NULL, NULL,NULL,getLineNumber()); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(IF_THEN_ELSE, (yyvsp[(3) - (8)].astreeNode), (yyvsp[(6) - (8)].astreeNode), (yyvsp[(8) - (8)].astreeNode), NULL, NULL,NULL,getLineNumber()); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(LOOP,(yyvsp[(3) - (5)].astreeNode),(yyvsp[(5) - (5)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber()); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(FUNCALL,(yyvsp[(1) - (4)].astreeNode),(yyvsp[(3) - (4)].astreeNode),NULL,NULL,NULL,NULL,getLineNumber());;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.astreeNode) = NULL; ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.astreeNode) = (astreeNode *)newAstreeNode(CMD_SEQ, (yyvsp[(1) - (3)].astreeNode), (yyvsp[(3) - (3)].astreeNode), NULL, NULL, NULL,NULL,getLineNumber()); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.astreeNode) = NULL;;}
    break;



/* Line 1455 of yacc.c  */
#line 1969 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 176 "parser.y"


void yyerror()
{
	printf("PARSER ERROR on line %d\n",getLineNumber());
	exit(3);
}

