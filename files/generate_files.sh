#!/bin/bash

# This will generate 100 files of increasing size, to test our signing on
# The i-th file is named i.txt and has a size of i bytes
# Execute this from inside the files directory

for i in `seq 1 100`
do
    dd if=/dev/urandom of="$i.txt"  bs=1c  count="$i"
done
