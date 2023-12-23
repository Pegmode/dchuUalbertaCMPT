#
# CMPUT 229 Student Submission License
# Version 1.0
#
# Copyright 2019 Daniel Chu
#
# Redistribution is forbidden in all circumstances. Use of this
# software without explicit authorization from the author or CMPUT 229
# Teaching Staff is prohibited.
#
# This software was produced as a solution for an assignment in the course
# CMPUT 229 - Computer Organization and Architecture I at the University of
# Alberta, Canada. This solution is confidential and remains confidential 
# after it is submitted for grading.
#
# Copying any part of this solution without including this copyright notice
# is illegal.
#
# If any portion of this software is included in a solution submitted for
# grading at an educational institution, the submitter will be subject to
# the sanctions for plagiarism at that institution.
#
# If this software is found in any public website or public repository, the
# person finding it is kindly requested to immediately report, including 
# the URL or other repository locating information, to the following email
# address:
#
#          cmput229@ualberta.ca
#
#---------------------------------------------------------------
# CCID:                 dchu
# Lecture Section:      A2
# Instructor:           J. Nelson Amaral
# Lab Section:          D05
# Teaching Assistant:   
#---------------------------------------------------------------
# 

.include "common.s"

#----------------------------------
#        STUDENT SOLUTION
#----------------------------------
#Tokens
#Operand: non-negative integer
#Plus: -1
#Minus: -2
#Termination: -3

.text
calculator:
	#Args
	#a0:Tokens array pointer
	#a1:Stack pointer

	li t2,-3#initialize t2 for exit token
	li t3,-2#initialize t3 for minus token

	lw t1,0(a0)#load first token
		
loop1:
	blt t1,zero,isOperator#if token is not operand, branch to isOperator 
	jal zero,storeResult
	
isOperator:
	#pop 2 from stack
	lw,t6,0(a1)#load word from stack 
	addi a1,a1,-4#retract stack pointer
	lw,t5,0(a1)#load word from stack
	addi a1,a1,-4#retract stack pointer
	beq t1,t3 isSubtract #check if plus or minus token
	
isAdd:
	add t1,t5,t6
	jal zero,storeResult
	
isSubtract:
	sub t1,t5,t6#remember stack is first in last out for order this op
	
storeResult:
	#push to stack
	addi a1,a1,4#advance stack pointer
	sw t1,0(a1)#store word to stack
			
nextToken:
	addi a0,a0,4#Advance Token array pointer
	lw t1,0(a0)#Load next token
	bne t2,t1,loop1#if token is not exit token then loop
	
displayResult:
	li a7,1#PrintInt syscall
	lw a0,0(a1)#Arguement for PrintInt from top of stack
	ecall
	
	jr ra
	
