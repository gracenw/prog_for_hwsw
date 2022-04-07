#	               Baseline
#
# This program computes the union of two ten element sets of integers.
#
# ECE 2035 Homework 1-3
# Name: Gracen Wallace
# Date: 01/25/19

.data
# DO NOT change the following three labels (you may change the initial values):
SetA:	.word	243, -459, 826, -535, 264, 698, 268, 281, 921, 886
SetB:	.word	864, 281, 781, 698, -535, 128, 886, -336, 790, 826
SetC:	.alloc  20

# Also, for HW1 (only), do not write values to registers $0, $29, $30, or $31

.text	
	addi $3, $0, 0 #int i=0
	addi $8, $0, 0 #int Size=0
	addi $16, $0, 4
loopM:	slti $4, $3, 10 #if i<10, $4=1
	beq $4, $0, exitM #if $4=0, branch to exit
	mult $3, $16
	mflo $12
	lw $1, SetA($12) #element A
	lw $2, SetB($12) #element B
	addi $5, $0, 0 #int j=0
	addi $6, $0, 0 #int k=0
loopA:	slt $7, $3, $5 #if i<j, $7=1
	bne $7, $0, exitA #if $7=1, branch to exit
	mult $5, $16
	mflo $13
	lw $9, SetB($13) #temp element B to compare
	beq $1, $9, loopB #if element A==element B, skip rest of A loop and store statement
	addi $5, $5, 1	#j++
	j loopA
exitA:	mult $8, $16
	mflo $15
	sw $1, SetC($15) #store element A in SetC if no duplicates were found
	addi $8, $8, 1 #Size++
loopB:	slt $10, $3, $6 #if i<k, $10=1
	bne $10, $0, exitB #if $10=1, branch to exit
	mult $6, $16
	mflo $14
	lw $11, SetA($14) #temp element A to compare
	beq $2, $11, return #if element A==element B, skip rest of B  loop and store statement
	addi $6, $6, 1 #k++
	j loopB
exitB:	mult $8, $16
        mflo $15
	sw $2, SetC($15) #store element B in SetC if no duplicates were found
	addi $8, $8, 1 #Size++
return:	addi $3, $3, 1 #i++
	j loopM #return to main loop
exitM:	jr $31 #return to OS
