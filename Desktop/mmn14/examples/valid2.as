.entry MYMAT1
.entry LOL
MAIN: mov r0         ,r3
add r2,STR
LOOP: jmp      END
prn #-5
MYMAT1: .mat[2][2] 4  ,3,2,1
LOL:   prn r2
sub r1, r4
K: .data 22
inc K
 mov MYMAT1[r4][r1],r3
bne LOOP
END: stop
STR: .string "abcdef"
LENGTH: .data 6,-9,15

