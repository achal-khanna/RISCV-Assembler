mul     x6, x19, x5          # x6 = i * 9
add     x6, x6, s2          # x6 = i * 9 + col
add     x7, x7, x22          # x + i * 9 + col
lw      x28, 0(x7)           # x[i * 9 + col]
addi    x28, x28, -1          # x[i * 9 + col] - 1
sll     x29, x29, x28          # 1 << x[i * 9 + col] - 1
or      x21, x21, x29          # used |= ...