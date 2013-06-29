#include "assembler.h"

void assembleTac(tac * tac1);

/* funções para escrever no arquivo */
void setAssemblerFileName(char * filename_)
{
	if(filename_)
	{
		filenameAssembler = filename_;
	}
	else
	{
		filenameAssembler = "assembler.s";
	}
	firstTimeAssembler =1;
}


void clearAssembler()
{
	assemblerFile = fopen(filenameAssembler,"w");
	if(assemblerFile)
	{
		fprintf(assemblerFile,"%s","");
		fclose(assemblerFile);
	}
}


void printToAssembler(char* string)
{
	if(string)
	{
		if(firstTimeAssembler)
		{
			clearAssembler();
			firstTimeAssembler=0;
		}
		assemblerFile = fopen(filenameAssembler,"a+");
		if(assemblerFile)
		{
			fprintf(assemblerFile,"%s",string);
			fclose(assemblerFile);
		}
	}

}
/* given a string, returns it substituting \ for _  */
char * removeSlash(char * string)
{

	char * auxString=NULL;
	int i=0;
	
	auxString = (char *) calloc(strlen(string),sizeof(char));
	for(i=0 ; i < strlen(string) ; i++)
	{
		if(string[i] == '\\')
			auxString[i] = '_';
		else
			auxString[i] = string[i];
	}
	return auxString;
}

/* given a hashNode, returns the variable name to be written to file */
char * variableName(hashNode * hashPointer)
{
	char * newString = NULL;
	char * name = NULL;
	int i=0;
	if(hashPointer)
	{
		name = hashPointer->value;
		newString = (char *) calloc(strlen(name)+2,sizeof(char));
		for(i=0 ; i < strlen(name) ; i++)
		{
			newString[i+1] = name[i];
		}
		newString[0] = '_';
	}
	
	return newString;
}

void initAssembler()
{
	tac * auxTac = NULL;
	if(initializations)
		for(auxTac = initializations ; auxTac->prev ; auxTac = auxTac->prev);
	initializations = auxTac;
	printToAssembler("	.def	_getchar;	.scl	2;	.type	32;	.endef\n	.def	_printf;	.scl	2;	.type	32;	.endef\n	.def	___main;	.scl	2;	.type	32;	.endef\n	.bss\n	.globl _main\n");
}

void endAssembler()
{

}

void ASMdeclareScalar(hashNode * hashNode_)
{
	if(hashNode_)
	{
		printToAssembler(variableName(hashNode_));
		printToAssembler(":\n");
		printToAssembler("	.long 1\n");
	}
}

void declareVariables()
{

	hashNode * hashAux = NULL;
	int i=0;
	for(i=0 ; i < HASH_SIZE ; i++)
	{
		for(hashAux = hashTable[i] ; hashAux ; hashAux = hashAux->next)
		{
			if(hashAux->type == ID_SCALAR || hashAux->type == TEMP)
			{
				ASMdeclareScalar(hashAux);
			}
		}
	}
	
	printToAssembler("	.section .rdata,\"dr\"\n");
}

void declareLiterals(hashNode ** hashTable)
{
	hashNode * hashAux = NULL;	
	int i=0;
	
	for(i=0 ; i < HASH_SIZE ; i++)
	{
		for(hashAux = hashTable[i] ; hashAux ; hashAux = hashAux->next)
		{
			if(hashAux->type == SYMBOL_LIT_STRING)
			{
				printToAssembler(removeSlash(hashAux->value));
				printToAssembler(":\n");
				printToAssembler("	.ascii \"");
				printToAssembler(hashAux->value);
				printToAssembler("\\0\"\n\n");
			}
		}
	}
	
	printToAssembler("_PRINT_INT:\n");
	printToAssembler("	.ascii \"%d\\0\"\n");
	printToAssembler("	.text\n\n");
}

void begFun(hashNode * hashPointer)
{
	printToAssembler("	.cfi_startproc\n	pushl	%ebp\n	.cfi_def_cfa_offset 8\n	.cfi_offset 5, -8\n	movl	%esp, %ebp\n	.cfi_def_cfa_register 5\n	andl	$-16, %esp\n	subl	$32, %esp\n");
	if(hashPointer && strcmp(hashPointer->value,"main")==0)
	{
		
		printToAssembler("	call ___main\n");
		assembleTac(initializations);
	}
}

void endFun()
{
	printToAssembler("	leave\n	.cfi_restore 5\n	.cfi_def_cfa 4, 4\n	ret\n	.cfi_endproc\n");
}

void label(hashNode * hashPointer)
{
	if(hashPointer)
	{
		printToAssembler(variableName(hashPointer));
		printToAssembler(":\n");
	}
}

void tacCall(hashNode * hashPointer)
{
	if(hashPointer)
	{
		printToAssembler("	call ");
		printToAssembler(variableName(hashPointer));
		printToAssembler("\n");
	}
}

void printOp(hashNode * hashPointer)
{
	if(hashPointer)
	{
		if(hashPointer->type == SYMBOL_LIT_INTEGER)
		{
			printToAssembler("$");
			printToAssembler(hashPointer->value);
		}
		else if(hashPointer->type == SYMBOL_LIT_TRUE)
		{
			printToAssembler("$1");
		}
		else if(hashPointer->type == SYMBOL_LIT_FALSE)
		{
			printToAssembler("$0");
		}
		else if(hashPointer->type == ID_SCALAR || hashPointer->type == TEMP)
		{
			printToAssembler(variableName(hashPointer));
		}
		else
		{
			printToAssembler(variableName(hashPointer));
		}
	}
}

void tacAdd(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Addition\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	addl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	movl ");
		printToAssembler("%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
		
	}
}

void tacIf(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// IF\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	testl %eax , %eax\n");
		printToAssembler("	je ");
		printToAssembler(variableName(tac1->target));
		printToAssembler("\n");
	}	
}

void tacJmp(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("	jmp ");
		printToAssembler(variableName(tac1->target));
		printToAssembler("\n");
	}
}

void tacLoop(tac * tac1)
{
	if(tac1)
	{
		
	}
}

void tacSub(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Subtraction\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	subl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	movl ");
		printToAssembler("%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
		
	}
}

void tacMul(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Multiplication\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %ebx\n");
		printToAssembler("	mul %ebx\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
	}
}

void tacDiv(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Division\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl	%edx, 28(%esp)\n");
		printToAssembler("	cltd\n");
		printToAssembler("	idivl 28(%esp)\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
		
	}
}

void tacMov(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Move\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	movl %eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
	}
}

void tacOutput(hashNode * hashPointer)
{
	if(hashPointer)
	{
		printToAssembler("// Output\n");
		if(hashPointer->type == SYMBOL_LIT_STRING)
		{	
			printToAssembler("	movl	$");
			printToAssembler(removeSlash(hashPointer->value));
			printToAssembler(" , (%esp)\n");
			printToAssembler("	call _printf\n");
		}
		else if(hashPointer->type == ID_SCALAR)
		{
			printToAssembler("	movl ");
			printOp(hashPointer);
			printToAssembler(" , %eax\n");
			printToAssembler("	movl	%eax, 4(%esp)\n");
			printToAssembler("	movl	$_PRINT_INT, (%esp)\n");
			printToAssembler("	call _printf\n");
		}
	}
	else
		T"NULL OUTPUT"L
}

void tacGreater(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Op >\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	cmpl %eax, %edx\n");
		printToAssembler("	setg %al\n");
		printToAssembler("	movzbl %al, %eax\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");		
	}
}

void tacLess(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Op >\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	cmpl %eax, %edx\n");
		printToAssembler("	setg %al\n");
		printToAssembler("	movzbl %al, %eax\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");		
	}
}

void tacEqual(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Op >\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	cmpl %eax, %edx\n");
		printToAssembler("	sete %al\n");
		printToAssembler("	movzbl %al, %eax\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");		
	}
}

void tacNotEqual(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Op >\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	cmpl %eax, %edx\n");
		printToAssembler("	setne %al\n");
		printToAssembler("	movzbl %al, %eax\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");		
	}
}

void tacGreaterEqual(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Op >\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	cmpl %eax, %edx\n");
		printToAssembler("	setge %al\n");
		printToAssembler("	movzbl %al, %eax\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");		
	}
}

void tacLessEqual(tac * tac1)
{
	if(tac1)
	{
		printToAssembler("// Op >\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %edx\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	cmpl %eax, %edx\n");
		printToAssembler("	setle %al\n");
		printToAssembler("	movzbl %al, %eax\n");
		printToAssembler("	movl	%eax , ");
		printOp(tac1->target);
		printToAssembler("\n");		
	}
}

void tacAnd(tac * tac1)
{
	hashNode * L2=NULL;
	hashNode * L3=NULL;
	if(tac1)
	{
		L2 = newLabel();
		L3 = newLabel();
	
		printToAssembler("//Operation AND\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	testl %eax , %eax\n");
		printToAssembler("	je ");
		printOp(L2);
		printToAssembler("\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	testl %eax , %eax\n");
		printToAssembler("	je ");
		printOp(L2);
		printToAssembler("\n");
		printToAssembler("	movl $1 , %eax\n");
		printToAssembler("	jmp ");
		printOp(L3);
		printToAssembler("\n");
		printOp(L2);
		printToAssembler(":\n");
		printToAssembler("	movl $0, %eax\n");
		printOp(L3);
		printToAssembler(":\n");
		printToAssembler("	movl %eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
	
	}
}

void tacOr(tac * tac1)
{
	hashNode * L2=NULL;
	hashNode * L3=NULL;
	hashNode * L4=NULL;
	if(tac1)
	{
		L2 = newLabel();
		L3 = newLabel();
		L4 = newLabel();
	
		printToAssembler("//Operation OR\n");
		printToAssembler("	movl ");
		printOp(tac1->op1);
		printToAssembler(" , %eax\n");
		printToAssembler("	testl %eax , %eax\n");
		printToAssembler("	jne ");
		printOp(L2);
		printToAssembler("\n");
		printToAssembler("	movl ");
		printOp(tac1->op2);
		printToAssembler(" , %eax\n");
		printToAssembler("	testl %eax , %eax\n");
		printToAssembler("	je ");
		printOp(L3);
		printToAssembler("\n");
		printOp(L2);
		printToAssembler(":\n");
		printToAssembler("	movl $1, %eax\n");
		printToAssembler("	jmp "); 
		printOp(L4);
		printToAssembler("\n");
		printOp(L3);
		printToAssembler(":\n");
		printToAssembler("	movl $0, %eax\n");
		printOp(L4);
		printToAssembler(":\n");
		printToAssembler("	movl %eax , ");
		printOp(tac1->target);
		printToAssembler("\n");
	
	}
}

void tacInput(hashNode * hashPointer)
{
	if(hashPointer)
	{
		printToAssembler("	call _getchar\n");
		printToAssembler("	subl	$48 , %eax\n");
		printToAssembler("	movl %eax , ");
		printOp(hashPointer);
		printToAssembler("\n");
	}
}

void assembleTac(tac * tac1)
{
	if(tac1)
	{
		switch(tac1->type)
		{
			case TAC_MOV:		tacMov(tac1);	break; 
			case TAC_I_MOV:		break;
			case TAC_LABEL:		label(tac1->target); break;
			case TAC_JMP:		tacJmp(tac1);		break;
			case TAC_IFZ:		tacIf(tac1);	break;
			case TAC_CALL:		tacCall(tac1->target);break;
			case TAC_RETURN:	break;
			case TAC_ARG:		break;

			case TAC_ADD	:	tacAdd(tac1);	break;
			case TAC_SUB	:	tacSub(tac1);	break;
			case TAC_MUL	:	tacMul(tac1);	break;
			case TAC_DIV	:	tacDiv(tac1);	break;
			case TAC_OR		:	tacOr(tac1);	break;
			case TAC_AND	:	tacAnd(tac1);	break;
			case TAC_EQ		:	tacEqual(tac1);			break;
			case TAC_NE		:	tacNotEqual(tac1);		break;
			case TAC_GE		:	tacGreaterEqual(tac1);	break;
			case TAC_LE		:	tacLessEqual(tac1);		break;
			case TAC_GREATER:	tacGreater(tac1);	break;
			case TAC_LESS	:	tacLess(tac1);		break;

			case TAC_VEC_READ	:break;
			case TAC_IDENTIFIER	:break;
			case TAC_INTEGER	:break;
			case TAC_TRUE		:break;
			case TAC_FALSE		:break;
			case TAC_STRING		:break;
			case TAC_GET_ADDRESS:break;
			case TAC_POINTER	:break;
			case TAC_OUTPUT		:tacOutput(tac1->target);	break;
			case TAC_INPUT		:tacInput(tac1->op1);	break;
			
			case TAC_BEGIN_FUNCTION:	begFun(tac1->target);	break;
			case TAC_END_FUNCTION:		endFun(); break;
		}
	}
	if(tac1->next)
	{
		assembleTac(tac1->next);
	}
	
}

void assemble(tac * tac1)
{
	tac * auxTac = NULL;
	setAssemblerFileName(NULL);
	
	
	
	
	initAssembler();
	declareVariables(hashTable);
	declareLiterals(hashTable);
	
	for(auxTac = tac1 ; auxTac->prev ; auxTac = auxTac->prev);
	assembleTac(auxTac);
	
	endAssembler();
}