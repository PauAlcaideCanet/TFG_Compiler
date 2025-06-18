li $a0, 2
sw $a0, 0($sp)
addiu $sp, $sp, -4
li $a0, 3
lw $t1, 4($sp)
addiu $sp, $sp, 4
add $a0, $t1, $a0
