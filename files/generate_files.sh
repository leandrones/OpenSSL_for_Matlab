#!/bin/bash

# This will generate 50 files of increasing size, to test our signing on
# The i-th file is named i.txt and has a size of i bytes
# Execute this from inside the files directory

for i in `seq 1 50`
do
    VAR1=$i
    VAR1+="M"
    mkfile $VAR1 $i.txt
done
