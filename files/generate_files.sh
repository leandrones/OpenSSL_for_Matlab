#!/bin/bash

# This will generate 100 files of increasing size, to test our signing on
# The i-th file is named output_i.dat and has a size of i MB
# Execute this from inside the files directory

for i in  {1..100..1}
do
    dd if=/dev/urandom of="${i}.txt"  bs=1c  count="${i}"
done
