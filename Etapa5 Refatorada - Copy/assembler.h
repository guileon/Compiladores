#ifndef ASSEMBLER
#define ASSEMBLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"

char * filenameAssembler;
int firstTimeAssembler;
FILE * assemblerFile;
void assemble(tac * tac1);

#endif