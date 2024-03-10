# if we have word stored at x11 as 12345678 and if we will convert it it should give 78563412 below is an example code for this.
lui x11, 0x5678
lui x12, 0x1234
slli x12, x12, 4
srli x11, x11, 12
or x11, x12, x11

#this convert function will convert from Big-Endian to Little-Endian and vice-versa for word stored at x11.
convert:
    slli x12, x11, 24
    slli x13, x11, 16
    srli x13, x13, 24
    slli x13, x13, 16
    or x12, x12, x13
    slli x13, x11, 8
    srli x13, x13, 24
    slli x13, x13, 8
    or x12, x12, x13
    slli x13, x11, 0
    srli x13, x13, 24
    slli x13, x13, 0
    or x12, x12, x13
