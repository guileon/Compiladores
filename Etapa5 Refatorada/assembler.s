	.def	_getchar;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	___main;	.scl	2;	.type	32;	.endef
	.bss
	.globl _main
	.comm _a , 4 , 2
__temp4:
	.long 1
_i:
	.long 1
_x:
	.long 1
__temp2:
	.long 1
__temp0:
	.long 1
__temp5:
	.long 1
__temp3:
	.long 1
__temp1:
	.long 1
__temp6:
	.long 1
	.section .rdata,"dr"
_n:
	.ascii "\n\0"

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
	movl $0 , %eax
	movl %eax , _i
// Alloc
	movl $4, 4(%esp)
	movl $10 , %ebx
	movl %ebx, (%esp)
	call _calloc
	movl %eax, _a
// Move
	movl $12 , %eax
	movl %eax , _x
__label2:
// Op >
	movl $10 , %edx
	movl _i , %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl	%eax , __temp4
// IF
	movl __temp4 , %eax
	testl %eax , %eax
	je __label3
// Multiplication
	movl _i , %eax
	movl $2 , %ebx
	mul %ebx
	movl	%eax , __temp6
// Move indirect with offset
	movl $4 , %eax
	movl _i , %ebx
	mul %ebx
	movl %eax , %ebx
	movl _a , %eax
	addl %ebx , %eax
	movl __temp6 , %ecx
	movl %ecx , (%eax)
// Addition
	movl _i , %eax
	addl $1 , %eax
	movl %eax , __temp5
// Move
	movl __temp5 , %eax
	movl %eax , _i
	jmp __label2
__label3:
// Subtraction
	movl _i , %eax
	subl $1 , %eax
	movl %eax , __temp3
// Move
	movl __temp3 , %eax
	movl %eax , _i
__label0:
// Op >
	movl _i , %edx
	movl $0 , %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl	%eax , __temp0
// IF
	movl __temp0 , %eax
	testl %eax , %eax
	je __label1
// Pointer ( vector read )
	movl $4 , %eax
	movl _i , %ebx
	mul %ebx
	movl %eax , %ebx
	movl _a , %eax
	addl %ebx , %eax
	movl (%eax), %ebx
	movl %ebx , __temp2
// Output
	movl __temp2 , %eax
	movl	%eax, 4(%esp)
	movl	$_PRINT_INT, (%esp)
	call _printf
// Output
	movl	$_n , (%esp)
	call _printf
// Subtraction
	movl _i , %eax
	subl $1 , %eax
	movl %eax , __temp1
// Move
	movl __temp1 , %eax
	movl %eax , _i
	jmp __label0
__label1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
