#ifndef TOKENS
#define TOKENS

/*	1*** para símbolos da hash
	2*** para símbolos da astree
	3*** para símbolos da tac */
	
/* simbolos da hash */
#define TEMP					1001
#define LABEL 					1002
#define SYMBOL_LIT_INTEGER 		1003
#define SYMBOL_LIT_FLOATING 	1004
#define SYMBOL_LIT_TRUE 		1005
#define SYMBOL_LIT_FALSE 		1006
#define SYMBOL_LIT_CHAR 		1007
#define SYMBOL_LIT_STRING 		1008
#define SYMBOL_IDENTIFIER 		1009

#define	ID_SCALAR				1010
#define ID_POINTER				1011
#define ID_VECTOR				1012
#define ID_FUNCTION				1013
		
#define T_INTEGER				1014
#define T_BOOLEAN				1015

/* símbolos da astree */
#define PROGRAM 				2001
#define LIT_LIST 				2002
#define BOOL 					2003
#define WORD 					2004
#define BYTE					2005
#define DECLARATION_SCALAR		2006
#define DECLARATION_POINTER		2007
#define DECLARATION_VECTOR		2008
#define DECLARATION_FUNCTION	2009
#define ARG_DECLARATION			2010
#define ARGCALL					2011
#define SCALAR_READ				2012
#define VECTOR_READ				2013
#define GET_REFERENCE			2014
#define POINTER					2015
#define FUNCALL					2016
#define PAR						2017
#define ADD						2018
#define SUB						2019
#define MUL						2020
#define DIV						2021
#define OR						2022
#define AND						2023
#define LE						2024
#define GE						2025
#define EQ						2026
#define NE						2027
#define GREATER					2028
#define LESS					2029
#define BLOCK					2030
#define OUTPUT_LIST				2031
#define SCALAR_WRITE			2032
#define VECTOR_WRITE			2033
#define POINTER_WRITE			2034
#define INPUT					2035
#define OUTPUT					2036
#define RETURN					2037
#define IF_THEN					2038
#define IF_THEN_ELSE			2039
#define LOOP					2040
#define CMD_SEQ					2041
/* símbolos da tac */
#define TAC_MOV					3001
#define TAC_I_MOV				3002
#define TAC_LABEL				3003
#define TAC_JMP					3004
#define TAC_IFZ					3005
#define TAC_CALL				3008
#define TAC_RETURN				3009
#define TAC_ARG					3010

#define TAC_ADD					3011
#define TAC_SUB					3012
#define TAC_MUL					3013
#define TAC_DIV					3014
#define TAC_OR					3015
#define TAC_AND					3016
#define TAC_EQ					3017
#define TAC_NE					3018
#define TAC_GE					3019
#define TAC_LE					3020
#define TAC_GREATER				3021
#define TAC_LESS				3022

#define TAC_VEC_READ			3023
#define TAC_IDENTIFIER			3024
#define TAC_INTEGER				3025
#define TAC_TRUE				3026
#define TAC_FALSE				3027
#define TAC_STRING				3028
#define TAC_GET_ADDRESS			3029
#define TAC_POINTER				3030
#define TAC_OUTPUT				3031
#define TAC_INPUT				3032

#define TAC_BEGIN_FUNCTION		3033
#define TAC_END_FUNCTION		3034

#endif