	.def	_getchar;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	___main;	.scl	2;	.type	32;	.endef
	.bss
	.globl _main
_a:
	.long 1
	.comm _pt , 4 , 2
__temp0:
	.long 1
__temp1:
	.long 1
	.section .rdata,"dr"
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
	movl $12 , %eax
	movl %eax , _a
// Alloc
	movl	$4, 4(%esp)
	movl	$1, (%esp)
	call	_calloc
	movl	%eax, _pt
// Move indirect
	movl _pt , %eax
	movl $14 , (%eax)
// Get Address
	movl $_a , %eax
	movl %eax , __temp1
// Move
	movl __temp1 , %eax
	movl %eax , _pt
// Pointer
	movl _pt , %eax
	movl (%eax), %ebx
	movl %ebx , __temp0
// Output
	movl __temp0 , %eax
	movl	%eax, 4(%esp)
	movl	$_PRINT_INT, (%esp)
	call _printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
