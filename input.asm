# RISC-V Assembly Code with Standard ISA Instructions
# Sample containing all required Instructions

# Data Section
.data
my_data: .half 42, 25, 36          # Define a 32-bit word with value 42

# Text Section
.text

    # R-Type Instructions
    add x1, x2, x3         # Add
    and x4, x5, x6         # Bitwise AND
    or x7, x8, x9          # Bitwise OR
    sll x10, x11, x0        # Shift Left Logical
    slt x12, x13, x14      # Set Less Than
    sra x15, x16, x0       # Shift Right Arithmetic
    srl x17, x18, x0        # Shift Right Logical
    sub x19, x20, x21      # Subtract
    xor x22, x23, x24      # Bitwise XOR
    mul x25, x26, x27      # Multiply
    div x28, x29, x30      # Divide
    rem x31, x1, x2        # Remainder

    # I-Type Instructions
    addi x1, x2, 10        # Add Immediate
    andi x3, x4, 15        # AND Immediate
    ori x5, x6, 20         # OR Immediate
    lb x7, 0(x8)           # Load Byte
    ld x9, 0(x10)          # Load Doubleword
    lh x11, 0(x12)         # Load Halfword
    lw x13, 0(x14)         # Load Word
    jalr x15, x16, 0       # Jump and Link Register
    jal x17, label1           # Jump and Link

    # S-Type Instructions
    sb x18, 0(x19)         # Store Byte
    sw x20, 0(x21)         # Store Word
    sd x22, 0(x23)         # Store Doubleword
    sh x24, 0(x25)         # Store Halfword

    # SB-Type Instructions
    beq x26, x27, label1   # Branch if Equal
    bne x28, x29, label2   # Branch if Not Equal
    bge x30, x31, label3   # Branch if Greater Than or Equal
    blt x11, x2, label4    # Branch if Less Than

    # U-Type Instructions
    auipc x3, 100          # Add Upper Immediate to PC
    lui x4, 200            # Load Upper Immediate

    # UJ-Type Instructions

.data
hello: .asciiz "dnjncmsk"
hell: .byte 32

.text
addi x0, x0, 0
jal x1, heloo

heloo:
    addi x1, x1, 1
    addi x1, x2, 10

end:

    # Assembly Directives

# Labels
label1:
    addi x1, x1, 1                     # No operation (placeholder)
label2:
    addi x1, x1, 1                     # No operation (placeholder)
label3:
    addi x1, x1, 1
label4:
    addi x1, x1, 1                     # No operation (placeholder)
label5: 
    addi x1, x1, 1                     # No operation (placeholder)
    

# End of Program
