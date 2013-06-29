	.def	_getchar;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	___main;	.scl	2;	.type	32;	.endef
	.bss
	.globl _main
_a:
	.long 1
_b:
	.long 1
_c:
	.long 1
__temp4:
	.long 1
__temp10:
	.long 1
_x:
	.long 1
__temp2:
	.long 1
__temp9:
	.long 1
__temp0:
	.long 1
__temp7:
	.long 1
__temp13:
	.long 1
__temp5:
	.long 1
__temp3:
	.long 1
__temp12:
	.long 1
__temp1:
	.long 1
__temp8:
	.long 1
__temp11:
	.long 1
__temp6:
	.long 1
	.section .rdata,"dr"
avaco:
	.ascii "avaco\0"

number :
	.ascii "number \0"

lala :
	.ascii "lala \0"

_n:
	.ascii "\n\0"

aba:
	.ascii "aba\0"

_PRINT_INT:
	.ascii "%d\0"
	.text

_main:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	call ___main
// Move
	movl $1 , %eax
	movl %eax , _c
// Move
	movl $0 , %eax
	movl %eax , _x
// Move
	movl $22 , %eax
	movl %eax , _b
// Move
	movl $12 , %eax
	movl %eax , _a
//Operation OR
	movl $1 , %eax
	testl %eax , %eax
	jne __label4
	movl _x , %eax
	testl %eax , %eax
	je __label5
__label4:
	movl $1, %eax
	jmp __label6
__label5:
	movl $0, %eax
__label6:
	movl %eax , __temp13
// Move
	movl __temp13 , %eax
	movl %eax , _x
	call _getchar
	subl	$48 , %eax
	movl %eax , _a
	call _getchar
	subl	$48 , %eax
	movl %eax , _b
// Multiplication
	movl $10 , %eax
	movl _a , %ebx
	mul %ebx
	movl	%eax , __temp9
// Addition
	movl __temp9 , %eax
	addl _b , %eax
	movl %eax , __temp10
// Move
	movl __temp10 , %eax
	movl %eax , _a
// Multiplication
	movl _a , %eax
	movl $2 , %ebx
	mul %ebx
	movl	%eax , __temp8
// Move
	movl __temp8 , %eax
	movl %eax , _a
// Output
	movl	$lala  , (%esp)
	call _printf
// Output
	movl _a , %eax
	movl	%eax, 4(%esp)
	movl	$_PRINT_INT, (%esp)
	call _printf
// Output
	movl	$_n , (%esp)
	call _printf
//Operation AND
	movl $0 , %eax
	testl %eax , %eax
	je __label7
	movl $1 , %eax
	testl %eax , %eax
	je __label7
	movl $1 , %eax
	jmp __label8
__label7:
	movl $0, %eax
__label8:
	movl %eax , __temp7
// IF
	movl __temp7 , %eax
	testl %eax , %eax
	je __label3
// Output
	movl	$avaco , (%esp)
	call _printf
	jmp __label2
__label3:
__label2:
// Multiplication
	movl _b , %eax
	movl $2 , %ebx
	mul %ebx
	movl	%eax , __temp6
// Move
	movl __temp6 , %eax
	movl %eax , _b
// Output
	movl _b , %eax
	movl	%eax, 4(%esp)
	movl	$_PRINT_INT, (%esp)
	call _printf
// Output
	movl	$_n , (%esp)
	call _printf
// Division
	movl _b , %eax
	movl $3 , %edx
	movl	%edx, 28(%esp)
	cltd
	idivl 28(%esp)
	movl	%eax , __temp5
// Move
	movl __temp5 , %eax
	movl %eax , _b
// Output
	movl _b , %eax
	movl	%eax, 4(%esp)
	movl	$_PRINT_INT, (%esp)
	call _printf
// Output
	movl	$_n , (%esp)
	call _printf
// Move
	movl $0 , %eax
	movl %eax , _a
// Move
	movl $20 , %eax
	movl %eax , _b
__label0:
// IF
	movl _x , %eax
	testl %eax , %eax
	je __label1
// Op >
	movl _b , %edx
	movl _a , %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl	%eax , __temp4
// Move
	movl __temp4 , %eax
	movl %eax , _x
// Addition
	movl _a , %eax
	addl $1 , %eax
	movl %eax , __temp3
// Move
	movl __temp3 , %eax
	movl %eax , _a
// Subtraction
	movl _b , %eax
	subl $1 , %eax
	movl %eax , __temp2
// Move
	movl __temp2 , %eax
	movl %eax , _b
// Output
	movl	$number  , (%esp)
	call _printf
// Output
	movl _c , %eax
	movl	%eax, 4(%esp)
	movl	$_PRINT_INT, (%esp)
	call _printf
// Output
	movl	$_n , (%esp)
	call _printf
// Addition
	movl _c , %eax
	addl $1 , %eax
	movl %eax , __temp1
// Move
	movl __temp1 , %eax
	movl %eax , _c
	jmp __label0
__label1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
_foo:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
// Addition
	movl _a , %eax
	addl $10 , %eax
	movl %eax , __temp0
// Move
	movl __temp0 , %eax
	movl %eax , _b
// Output
	movl	$aba , (%esp)
	call _printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
