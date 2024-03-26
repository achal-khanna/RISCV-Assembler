.data
addi x11, x0, 4
array: .word 1111, 1011, 1100, 1000

.text
auipc x4, 65536
addi x10, x0, 0
addi x5, x0, 0
addi x6, x0, 4
addi x7, x0, 3
addi x9, x0, 2
addi x14, x0, 1
lw x12, 0(x4)
addi x30, x0, 2
Loop:
    addi x5, x5, 1

    andi x13, x12, 1
    beq x13, x0, next1
    addi x10, x10, 1
    next1:
    mul x12, x12, x30
    andi x13, x12, 1
    beq x13, x0, next2
    addi x10, x10, 1
    next2:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next3
    addi x10, x10, 1
    next3:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next4
    addi x10, x10, 1
    next4:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next5
    addi x10, x10, 1
    next5:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next6
    addi x10, x10, 1
    next6:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next7
    addi x10, x10, 1
    next7:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next8
    addi x10, x10, 1
    next8:
    mul x12, x12, x30

    andi x13, x12, 1
    beq x13, x0, next9
    addi x10, x10, 1
    next9:

    beq x5, x14, func1
    beq x5, x9, func2
    beq x5, x7, func3
    beq x5, x6, exit

func1:
    lw x12, 4(x4)
    jal x0, Loop
func2:
    lw x12, next(x4)
    jal x0, Loop
func3:
    lw x12, 12(x4)
    jal x0, Loop
exit:
    addi x0, x0, 0
