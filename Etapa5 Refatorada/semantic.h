/*	semantic contém o método utilizado para fazer a
	verificação semântica de uma astree */

#ifndef SEMANTIC
#define SEMANTIC

#include "hash.h"
#include "tokens.h"
#include "astree.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfErrors;
int semanticEvaluation(astreeNode * node);


#endif