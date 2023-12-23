#
# CMPUT 229 Public Materials License
# Version 1.0
#
# Copyright 2019 University of Alberta
# Copyright 2019 Abdulrahman Alattas
#
# This software is distributed to students in the course
# CMPUT 229 - Computer Organization and Architecture I at the University of
# Alberta, Canada.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#------------------------------
# Introductory Lab - Program Arguments
# Author: Abdulrahman Alattas
# Date: May 3, 2019
#------------------------------

.data
nl:         .asciz "\n"

.text
main:

    lw      s0, 0(a1)
    addi    s1, zero, 1

    L1: 
    lb      t0, 0(s0)
    beq     t0, zero, L1D
    addi    s0, s0, 1
    addi    s1, s1, 1
    j       L1
    L1D:

    addi    s0, s0, -1
    addi    s1, s1, -1
    li      a7, 0x0B

    L2:
    lb      a0, 0(s0)
    ecall
    addi    s0, s0, -1
    addi    s1, s1, -1
    bne     s1, zero, L2

exit:
    # print a newline
    la      a0, nl
    li      a7, 4
    ecall
    # exit
    li      a7, 10
    ecall
