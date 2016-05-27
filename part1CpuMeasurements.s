	.file	"part1CpuMeasurements.cpp"
	.text
	.type	_ZL5rdtscv, @function
_ZL5rdtscv:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 19 "rdtsc.h" 1
	xor %eax, %eax;cpuid;rdtsc
# 0 "" 2
#NO_APP
	movl	%eax, -8(%rbp)
	movl	%edx, -4(%rbp)
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	salq	$32, %rdx
	orq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_ZL5rdtscv, .-_ZL5rdtscv
	.section	.rodata
	.align 8
.LC0:
	.string	"hello world!!!!!!!! WOOOOOOO!! %d \n"
	.align 8
.LC1:
	.string	"Time Mean:  %0.2f,   Time Standard Deviation:  %0.2f \n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	call	getpid
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$10, -20(%rbp)
	leaq	-8(%rbp), %rdx
	leaq	-16(%rbp), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	_Z22measureTimeMeasurementiRdS_
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, -40(%rbp)
	movsd	-40(%rbp), %xmm1
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	movl	$.LC1, %edi
	movl	$2, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.rodata
.LC2:
	.string	"Trial %d:  %0.2f \n"
	.text
	.globl	_Z22measureTimeMeasurementiRdS_
	.type	_Z22measureTimeMeasurementiRdS_, @function
_Z22measureTimeMeasurementiRdS_:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$64, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	movq	%rsp, %rax
	movq	%rax, %r12
	movl	-52(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -32(%rbp)
	movq	%rax, %rdx
	addq	$1, %rdx
	movq	%rdx, %r8
	movl	$0, %r9d
	movq	%rax, %rdx
	addq	$1, %rdx
	movq	%rdx, %rcx
	movl	$0, %ebx
	addq	$1, %rax
	salq	$3, %rax
	leaq	7(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %ebx
	movl	$0, %edx
	divq	%rbx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -24(%rbp)
	movl	$0, -36(%rbp)
	jmp	.L6
.L7:
	movl	$100000, %edi
	call	_Z28measureTimeMeasurementHelperi
	movsd	%xmm0, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	-24(%rbp), %rdx
	movl	-36(%rbp), %ecx
	movslq	%ecx, %rcx
	movq	%rax, (%rdx,%rcx,8)
	movq	-24(%rbp), %rax
	movl	-36(%rbp), %edx
	movslq	%edx, %rdx
	movq	(%rax,%rdx,8), %rax
	movl	-36(%rbp), %edx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	%edx, %esi
	movl	$.LC2, %edi
	movl	$1, %eax
	call	printf
	movq	-24(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z9calcStDevPdi
	movq	-24(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z8calcMeanPdi
	addl	$1, -36(%rbp)
.L6:
	movl	-36(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jl	.L7
	movq	-24(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z8calcMeanPdi
	movsd	%xmm0, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rax, (%rdx)
	movq	-24(%rbp), %rax
	movl	-52(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z9calcStDevPdi
	movsd	%xmm0, -80(%rbp)
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rdx)
	movq	%r12, %rsp
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	_Z22measureTimeMeasurementiRdS_, .-_Z22measureTimeMeasurementiRdS_
	.globl	_Z28measureTimeMeasurementHelperi
	.type	_Z28measureTimeMeasurementHelperi, @function
_Z28measureTimeMeasurementHelperi:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movl	%edi, -84(%rbp)
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-84(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -64(%rbp)
	movq	%rax, %rsi
	addq	$1, %rsi
	movq	%rsi, %r8
	movl	$0, %r9d
	movq	%rax, %rsi
	addq	$1, %rsi
	movq	%rsi, %rdx
	movl	$0, %ecx
	addq	$1, %rax
	salq	$3, %rax
	leaq	7(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -56(%rbp)
	movl	$0, -72(%rbp)
	jmp	.L9
.L12:
	call	_ZL5rdtscv
	movq	%rax, -48(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L10
.L11:
	addl	$1, -68(%rbp)
.L10:
	cmpl	$9, -68(%rbp)
	jle	.L11
	call	_ZL5rdtscv
	movq	%rax, -40(%rbp)
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	-56(%rbp), %rax
	movl	-72(%rbp), %edx
	movslq	%edx, %rdx
	movq	%rcx, (%rax,%rdx,8)
	addl	$8, -76(%rbp)
	addl	$1, -72(%rbp)
.L9:
	movl	-72(%rbp), %eax
	cmpl	-84(%rbp), %eax
	jl	.L12
	movq	-56(%rbp), %rax
	movl	-84(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z8calcMeanPyi
	movsd	%xmm0, -96(%rbp)
	movq	-96(%rbp), %rax
	movq	%rbx, %rsp
	movq	%rax, -96(%rbp)
	movsd	-96(%rbp), %xmm0
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_Z28measureTimeMeasurementHelperi, .-_Z28measureTimeMeasurementHelperi
	.globl	_Z5dummyiiiiiiii
	.type	_Z5dummyiiiiiiii, @function
_Z5dummyiiiiiiii:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	_Z5dummyiiiiiiii, .-_Z5dummyiiiiiiii
	.globl	_Z5dummyiiiiiii
	.type	_Z5dummyiiiiiii, @function
_Z5dummyiiiiiii:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	_Z5dummyiiiiiii, .-_Z5dummyiiiiiii
	.globl	_Z5dummyiiiiii
	.type	_Z5dummyiiiiii, @function
_Z5dummyiiiiii:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	_Z5dummyiiiiii, .-_Z5dummyiiiiii
	.globl	_Z5dummyiiiii
	.type	_Z5dummyiiiii, @function
_Z5dummyiiiii:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	_Z5dummyiiiii, .-_Z5dummyiiiii
	.globl	_Z5dummyiiii
	.type	_Z5dummyiiii, @function
_Z5dummyiiii:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	_Z5dummyiiii, .-_Z5dummyiiii
	.globl	_Z5dummyiii
	.type	_Z5dummyiii, @function
_Z5dummyiii:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	_Z5dummyiii, .-_Z5dummyiii
	.globl	_Z5dummyii
	.type	_Z5dummyii, @function
_Z5dummyii:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	_Z5dummyii, .-_Z5dummyii
	.globl	_Z5dummyi
	.type	_Z5dummyi, @function
_Z5dummyi:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	_Z5dummyi, .-_Z5dummyi
	.globl	_Z5dummyv
	.type	_Z5dummyv, @function
_Z5dummyv:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$88, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	_Z5dummyv, .-_Z5dummyv
	.globl	_Z8calcMeanPyi
	.type	_Z8calcMeanPyi, @function
_Z8calcMeanPyi:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, %eax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L26
.L29:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	js	.L27
	cvtsi2sdq	%rax, %xmm0
	jmp	.L28
.L27:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L28:
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L26:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L29
	cvtsi2sd	-28(%rbp), %xmm0
	movsd	-8(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	_Z8calcMeanPyi, .-_Z8calcMeanPyi
	.globl	_Z9calcStDevPyi
	.type	_Z9calcStDevPyi, @function
_Z9calcStDevPyi:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	$0, %eax
	movq	%rax, -16(%rbp)
	movl	$0, %eax
	movq	%rax, -8(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L32
.L35:
	movl	-24(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	js	.L33
	cvtsi2sdq	%rax, %xmm0
	jmp	.L34
.L33:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L34:
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	addl	$1, -24(%rbp)
.L32:
	movl	-24(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L35
	cvtsi2sd	-44(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L36
.L41:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	js	.L37
	cvtsi2sdq	%rax, %xmm0
	jmp	.L38
.L37:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L38:
	movapd	%xmm0, %xmm1
	subsd	-16(%rbp), %xmm1
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	js	.L39
	cvtsi2sdq	%rax, %xmm0
	jmp	.L40
.L39:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L40:
	subsd	-16(%rbp), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -20(%rbp)
.L36:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L41
	cvtsi2sd	-44(%rbp), %xmm0
	movsd	-8(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	sqrt
	movsd	%xmm0, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	_Z9calcStDevPyi, .-_Z9calcStDevPyi
	.globl	_Z8calcMeanPdi
	.type	_Z8calcMeanPdi, @function
_Z8calcMeanPdi:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, %eax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L44
.L45:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -12(%rbp)
.L44:
	movl	-12(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L45
	cvtsi2sd	-28(%rbp), %xmm0
	movsd	-8(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	_Z8calcMeanPdi, .-_Z8calcMeanPdi
	.globl	_Z9calcStDevPdi
	.type	_Z9calcStDevPdi, @function
_Z9calcStDevPdi:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	$0, %eax
	movq	%rax, -16(%rbp)
	movl	$0, %eax
	movq	%rax, -8(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L48
.L49:
	movl	-24(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	addl	$1, -24(%rbp)
.L48:
	movl	-24(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L49
	cvtsi2sd	-44(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L50
.L51:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movapd	%xmm0, %xmm1
	subsd	-16(%rbp), %xmm1
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	subsd	-16(%rbp), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	addl	$1, -20(%rbp)
.L50:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jl	.L51
	cvtsi2sd	-44(%rbp), %xmm0
	movsd	-8(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	call	sqrt
	movsd	%xmm0, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	_Z9calcStDevPdi, .-_Z9calcStDevPdi
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
