#include "tokens.h"
#include "hash.h"
#include "astree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{
	setFile(argv[1]);
	setFileName(argv[2]);
	initMe();
	yyparse();
	exit(0);
	
	return 0;
}