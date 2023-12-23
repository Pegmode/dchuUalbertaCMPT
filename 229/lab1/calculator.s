#Daniel Chu
#1493374
#University of Alberta
#CMPUT 229
#Lab 1
.data

.text
lw s0,0(a1) # test for commandline arguement vector
lw a0,a1 #load commandline arguemtn vector in Syscall print string vector
li a7,4 #syscall number 4 (printstring)
ecall #make syscall