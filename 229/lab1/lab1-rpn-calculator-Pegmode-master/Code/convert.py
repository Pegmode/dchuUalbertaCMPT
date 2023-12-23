#
# CMPUT 229 Public Materials License
# Version 1.0
#
# Copyright 2017 University of Alberta
# Copyright 2017 Kristen Newbury
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
'''
Author: Kristen Newbury
Date: August 4 2017

takes a .txt file as input and produces a .bin file
containing the binary word representation of each int(separated by newline) in the textfile

sample usage:

    python3 convert.py sample.txt

'''

import sys, re

if len(sys.argv) == 2:
    textfile = sys.argv[1]
else:
    print("No text file names supplied")

#open .txt file
f = open(textfile)
try:
    word = int(f.readline().rstrip())
except ValueError:  #if there is an invalid character or no lines in the file to read
    sys.exit()

#open a .bin file to write to
newFName = re.sub('.txt$', '.bin', textfile) #substitute extension on input, go from .txt to .bin file
newF = open(newFName, "wb")
#read every int in the .txt, word by word
while word != "":
    try:
        binword = (word).to_bytes(4, byteorder='little', signed='True')
        #write each int as actual binary to the .bin files
        newF.write(binword)
        word = int(f.readline().rstrip())
    except ValueError:
        print("Error: .txt file should only contain integers")
        sys.exit()

