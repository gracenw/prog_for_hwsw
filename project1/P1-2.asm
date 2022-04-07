# This program solves a match puzzle.
#
# Date: 03/01/2019
# Your Name: Gracen Wallace

.data
Reference:   .alloc 1				# allocate space for reference pattern
Candidates:  .alloc 8				# allocate space for puzzle candidates

.text
MPuzzle:	addi $1,$0,Reference		# set memory base
		swi 582				# create and display puzzles
		sw $31, 4($29)
		addi $3,$0,0			# int offset=0
		lw $1,Reference($0)		# $1 <- Reference
loop:		lw $2,Candidates($3)		# $2 <- Candidate[offset]
		beq $2,$1,cont			# if Candidates[offset]==Reference, jump to cont
		jal r90				# rotate 90
		jal r90				# rotate 180
		jal r90				# rotate 270
		lw $4,Reference($0)		# $4 <- Reference
		andi $1,$4,0x0000C000		# Extract most signficant 2 bits from reference
		addi $5,$0,0x00000003		# $5 <- 0x00000003, variable to use for masking
		addi $6,$0,12			# $6 <- 12, variable to use for shifting
		addi $8,$0,0			# $8 <- 0, other variable to use for shifting
rev:		and $7,$4,$5			# mask 2 bits of Reference
		srlv $7,$7,$8
                sllv $7,$7,$6			# shift bits left by shifting variable
                or $1,$1,$7			# or with altered Reference
                sll $5,$5,2			# shift masking variable left to extract next two bits
                beq $6,$0,flip			# if shifting variable is zero, jump to cont
                addi $6,$6,-2			# decrement shifting variable by 2
		addi $8,$8,2
		j rev				# jump to rev
flip:		beq $2,$1,cont			# flip horizontal
		jal r90				# rotate 90 horizontal flip
		jal r90				# flip vertical
		jal r90				# rotate 90 vertical flip
		addi $4,$0,28			# $8 <- 28
		beq $3,$4,cont			# jump to loop if offset is not equal to 28
		addi $3,$3,4			# offset+=4
		j loop				# jump to loop
cont:		swi 583				# highlight match
		lw $31,4($29)
		jr $31				# return to operating system
r90:		andi $4,$1,0x0000F000		# extract most significant 4 bits, with 16 0 bits
		srl $4,$4,12			# shift most significant 4 bits by 12
		andi $5,$1,0x00000FFF		# extract 12 other bits
		sll $5,$5,4			#shift 12 other bits to the left by 4
		or $1,$4,$5			# or extracted values to produce 90 degree rotation
		beq $2,$1,cont			# if Candidates[offset]==Reference, jump to cont
		jr $31				# jump to return address from jal
