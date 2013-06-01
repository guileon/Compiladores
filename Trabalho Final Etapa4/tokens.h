/* 
 * Lista dos tokens, com valores constantes associados.
 * Este arquivo serah posterioremente substituido, nao acrescente nada.
 * Os valores das constantes sao arbitrarios, mas nao podem ser alterados.
 * Cada valor deve ser distinto e fora da escala ascii. 
 * Assim, nao conflitam entre si e com os tokens representados pelo proprio
 * valor ascii de caracteres isolados. 
 */
 
/*#define KW_WORD       256
#define KW_BOOL       258
#define KW_BYTE       259
#define KW_IF         261
#define KW_THEN       262
#define KW_ELSE       263
#define KW_LOOP       264
#define KW_INPUT      266
#define KW_RETURN     267
#define KW_OUTPUT     268

#define OPERATOR_LE   270
#define OPERATOR_GE   271
#define OPERATOR_EQ   272
#define OPERATOR_NE   273
#define OPERATOR_AND  274
#define OPERATOR_OR   275
#define WHILE         276
#define PROG	      277
#define COMMAND_LIST  278
#define DECLARATION_LIST 279


#define TK_IDENTIFIER 280
#define LIT_INTEGER   281
#define LIT_FALSE     283
#define LIT_TRUE	    284
#define LIT_CHAR      285
#define LIT_STRING    286*/

#define LE 304
#define GE 305
#define EQ 306
#define NE 307
#define AND 308
#define OR 309

#define IF_THEN 401
#define IF_THEN_ELSE 402
#define LOOP 403

#define ARGCALL 500
#define FUNCALL 501
#define LIST 502
#define ARGUMENTS 503
#define D_NODE 504
#define FUNC_DECLARATION 505
#define PROG 506
#define DECLARATION 507
#define DECLARATION_POINTER 508
#define DECLARATION_VEC 509
#define DECLARATION_VEC_INIT 510
#define CMD_SEQ 511
#define OUTPUT 512
#define INPUT 513
#define RETURN 514
#define BLOCK 515
#define OUTPUT_L 516
#define VECCALL 517
#define POINTER 518


#define ID_WORD 519
#define ID_BYTE 520
#define ID_BOOL 521

#define ID_VECTOR 522
#define ID_SCALAR 523 
#define ID_POINTER 524
#define ID_FUNC 525

//#define TOKEN_ERROR   1000

/* END OF FILE */