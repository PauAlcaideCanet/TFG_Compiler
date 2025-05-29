li $a0, 3
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 2
lw $t1, 4($sp)
addiu $sp, $sp, 4
seq $a0, $t1, $a0
bne $a0, $zero, L_true_0
li $a0, 1
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 1
lw $t1, 4($sp)
addiu $sp, $sp, 4
add $a0, $t1, $a0
j L_end_0
L_true_0:
li $a0, 3
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 2
lw $t1, 4($sp)
addiu $sp, $sp, 4
add $a0, $t1, $a0
L_end_0: