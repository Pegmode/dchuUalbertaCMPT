# Make sure you clear memory before loading this file

.data
	.word 76, -5, 23, 5
	.asciz "Hello"
	.ascii "World"
	.align 2
	.space 5
	.byte 42, 'h', 'i'
.text
main:
        li      a7, 10
        ecall
