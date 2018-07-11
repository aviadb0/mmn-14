.invalid "hi"
VALID: .string "hello"
mov VALID[r1][r22],r2
LOOP: cmp r2,0
bne LOOP
.mat [1][1] 3,3,3
stop
