#     Color Matcher
#
# Your Name: Gracen Wallace
#
# Date: 02/01/2019
#
# This program finds the two closest colors in a eight color palette.
#
#  required output register usage:
#  $10: minimum total component difference
#  $11 and $12: memory addresses of the two closest colors

.data
Array:  .alloc  8               # allocate static space for packed color data

.text
ColorMatch:	addi $1, $0, Array		# set memory base
		swi 500				# create color palette and update memory
		addi $3, $0, 4			# for future use
		addi $4, $0, -1			# for future use
		addi $2, $0, 1			# int i=1
main:		slti $5, $2, 8			# $5=1 if i<8
		beq $5, $0, endmain		# if i>=8, branch to endmain
		mult $2, $3			# i*4
		mflo $6				# multiply current i by 4 to word align
		add $7, $0, $6			# creat temp value to increment and extract RGB
		add $6, $6, $1			# store in $6 base address of current Array[i]
		lbu $16, Array($7)		# store in $16 blue value of Array[i]
		addi $7, $7, 1			# increment byte variable
		lbu $17, Array($7)		# store in $17 green value of Array[i]
		addi $7, $7, 1			# increment byte variable
		lbu $18, Array($7)		# store in $18 red value of Array[i]
		addi $8, $0, 0			# int j=0
sub:		slt $9, $8, $2			# $9=1 if j<i
		beq $9, $0, endsub		# if j>=i, branch to endsub
		mult $8, $3			# j*4
		mflo $7				# multiply current j by 4 to word align
		add $9, $7, $0			# create temp variable to increment and extract RGB
		add $7, $7, $1			# store in $7 base address of current Array[j]
		lbu $19, Array($9)		# store in $19 blue value of Array[j]
		addi $9, $9, 1			# increment byte variable
		lbu $20, Array($9)		# store in $20 green value of Array[j]
		addi $9, $9, 1			# increment byte variable
		lbu $21, Array($9)		# store in $21 red value of Array[j]
		sub $22, $16, $19		# find blue value difference in $22
		slt $25, $0, $22		# $25=1 if 0<blue difference
		beq $25, $0, bneg		# if 0>blue difference, branch to bneg
bcont:		sub $23, $17, $20		# find green difference value in $23
		slt $25, $0, $23		# $25=1 if 0<green difference
		beq $25, $0, gneg		# if 0>green difference, branch to gneg
gcont:		sub $24, $18, $21		# find red difference value in $24
		slt $25, $0, $24		# $25=1 if 0<red difference
		beq $25, $0, rneg		# if 0>red difference, branch to rneg
rcont:		add $9, $22, $23		# add together blue and green differences in $9
		add $9, $9, $24			# add together blue & green and red differences in $9
		addi $25, $0, 1			# temp to compare, $25=1
		beq $2, $25, assign		# if i==1, jump to assign (first val set baseline)
		slt $25, $9, $10		# $25=1 if current total difference<established total difference
		bne $25, $0, assign		# if current diff<established diff, branch to assign
resume:		addi $8, $8, 1			# j++
		j sub 				# jump to sub loop
endsub:		addi $2, $2, 1			# i++
		j main				# jump to main loop
assign:		add $10, $9, $0			# set established total difference to current total difference
		add $11, $7, $0			# set established closest address to current closest address
		add $12, $6, $0			# set other established closest address to other current closest address
		j resume			# jump back to continue sub loop
bneg:		mult $22, $4			# blue diff*-1
		mflo $22			# store absolute value of blue diff in $22
		j bcont				# jump back to place in sub loop
gneg:		mult $23, $4			# green diff*-1
		mflo $23			# store absolute value of green diff in $23
		j gcont				# jump back to place in sub loop
rneg:	 	mult $24, $4			# red diff*-1
		mflo $24			# store absolute value of red diff in $24
		j rcont				# jump back to place in sub loop
endmain:	swi 581				# call correct values for colormatch
		jr $31				# return to caller
