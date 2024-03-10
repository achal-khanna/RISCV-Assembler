#sample test code
jal x0 main
twice:                              # twice
        addi    x2, x2, -16          # create stack fx1me with 4 slots
        sw      x1, 12(x2)           # first slot keeps return address
        sw      x8, 8(x2)            # second slot keeps x8
        addi    x8, x2, 16           # set x8 to this stack fx1me
        sw      x10, -12(x8)          # store passing value (x) to slot 4
        lw      x10, -12(x8)          # get x
        add     x10, x10, x10           # x + x   return value in x10
        lw      x1, 12(x2)           # restore return address
        lw      x8, 8(x2)           
        addi    x2, x2, 16           # delete stack fx1me
        jalr x0 x1 0
main:                                 # main
        addi    x2, x2, -16           # stack fx1me has 4 slots
        sw      x1, 12(x2)           
        sw      x8, 8(x2)                     
        addi    x8, x2, 16
        addi      x10,x0,2
        auipc x6 0                 # pass number 2 in x10
        jalr x1, x6, -64                 # call twice  ***
        sw      x10, -12(x8)           # put return value to a
        addi      x10,x0,0
        lw      x1, 12(x2)            
        lw      x8, 8(x2)            
        addi    x2, x2, 16            # restore x2