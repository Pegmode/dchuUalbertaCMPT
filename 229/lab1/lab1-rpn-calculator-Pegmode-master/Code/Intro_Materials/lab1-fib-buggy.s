#
# CMPUT 229 Student Submission License
# Version 1.0
#
# Copyright 2017 Adam Wolfe Gordon
#
# Unauthorized redistribution is forbidden in all circumstances. Use of this
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
# Assignment:           1
# Due Date:             September 27, 2010
# Name:                 Adam Wolfe Gordon
# Unix ID:              awolfe
# Lecture Section:      A1
# Instructor:           Nelson Amaral
# Lab Section:          D04
# Teaching Assistant:   Adam Wolfe Gordon
#---------------------------------------------------------------

#---------------------------------------------------------------
# The main program asks the user to input an integer, N, then
# calculates and prints the first N numbers of the fibonacci
# sequence.
#
# Register Usage:
#
#       a0: used for syscall arguments and return values
#       t0: N, the number of numbers to calculate
#       t1: loop counter
#       t3: the lower "current" number in the sequence
#       t4: the higher "current" number in the sequence
#       t5: temporary storage for the old higher number
#
#---------------------------------------------------------------

	.data
prompt:
	.asciz "Input N: "
space:
	.asciz " "
alldone:
	.asciz "\nI hope you enjoyed the Fibonacci sequence.\n"
	
	.text
main:
	# Print the prompt
	li      a7, 4
	la      a0, prompt
	ecall

	# Read in N
	li      a7, 5
	ecall

	# Move N to t0
	mv      t0, a0
	# Counter in t1 -- start at 0
	li      t1, 0

	# Load the first values of the Fibonacci sequence (0 and 1)
	li      t3, 0
	li      t4, 1

loop:
	# Check the loop condition
	beq     t0, t1, done
	# Increment the counter
	addi    t1, t1, 1
	
	# Print the next number in the sequence
	li      a7, 1
	mv      a0, t3
	ecall
	li      a7, 4
	la      a0, space
	ecall

	# Update the series
	mv      t5, t3
	add     t4, t3, t4
	mv      t3, t5
	
	# Loop!
	j loop
	
done:
	# Print a friendly message
	li      a7, 4
	la      a0, alldone
	ecall

