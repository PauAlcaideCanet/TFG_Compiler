li $a0, 1
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 1
lw $t1, 4($sp)
addiu $sp, $sp, 4
add $a0, $t1, $a0
beq $a0, $zero, else_0
li $a0, 2
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 3
lw $t1, 4($sp)
addiu $sp, $sp, 4
add $a0, $t1, $a0
j endif_0
else_0:
li $a0, 3
endif_0:
