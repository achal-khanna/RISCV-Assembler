# RISC-V Assembler
### CS204 Project
#### Team members-  Achal khanna(2021MEB1263),   Ujjawal kumar(2021MEB1331),  Ujjwal Rai(2021MEB1332)


## Objective:
To build an assembler that converts 32 bit RISC-V assembly code to machine code using C++. 


## Supported Instructions:

| **# R format** | add  | and | or | sll | slt | sra | srl | sub | xor | mul | div | rem |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |

| **# I format** | addi  | andi | ori | lb | ld | lh | lw | jalr |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |

| **# S format** | sb  | sw | sd | sh | 
| :---: | :---: | :---: | :---: | :---: | 

| **# SB format** | beq  | bne | bge | blt | 
| :---: | :---: | :---: | :---: | :---: | 

| **# U format** | auipc  | lui | 
| :---: | :---: | :---: | 

| **# UJ format** | jal  | 
| :---: | :---: |

Assembler directives .text, .data, .byte, .half, .word, .dword and .asciiz are supported. 

## Notes:  
#### Pseudo instruction and floating point operations are not supported.
#### End of program is specified by 0xFFFFFFFF.
#### Data segment is also printed in .mc file after machine code is generated.

## Directory structure:
#### The assembler.cpp takes input.asm as input file and generate the output.mc. Each line in input.asm is one instruction. The output.mc is generated after the execution. 

## How to execute:
#### Clone the repository: git clone https://github.com/achal-khanna/RISCV-Assembler
#### Write your assembly code in input.asm
#### Execute the assembler.asm and output.mc will be generated







