.data
array: .word 10, 20, 30, 40, 50

.text
addi x15, x0, 1
func1:
    auipc x4 65536
    addi x4 x4 -4
    lw x12 4(x4)
    addi x15, x15, 1
    add x13, x11, x12
    bne x14, x0, func1
