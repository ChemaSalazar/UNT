	.file	"prog3.c"
	.section	.rodata
.LC0:
	.string	"Enter a value:"
.LC1:
	.string	"%d"
.LC2:
	.string	"The sum is : %d is =%d \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	subl	$12, %esp
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-12(%ebp), %eax
	pushl	%eax
	pushl	$.LC1
	call	__isoc99_scanf
	addl	$16, %esp
	movl	-12(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	square_sum
	addl	$16, %esp
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	subl	$4, %esp
	pushl	%edx
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	square_sum
	.type	square_sum, @function
square_sum:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L3
	movl	$0, %eax
	jmp	.L4
.L3:
	movl	8(%ebp), %eax
	subl	$1, %eax
	subl	$12, %esp
	pushl	%eax
	call	square_sum
	addl	$16, %esp
	movl	%eax, %edx
	movl	8(%ebp), %eax
	imull	8(%ebp), %eax
	addl	%edx, %eax
.L4:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	square_sum, .-square_sum
	.ident	"GCC: (Ubuntu 4.9.4-2ubuntu1~12.04) 4.9.4"
	.section	.note.GNU-stack,"",@progbits
