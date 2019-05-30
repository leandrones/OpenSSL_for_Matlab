#!/bin/bash

# This will generate 100 files of increasing size, to test our signing on
# The i-th file is named i.txt and has a size of i bytes
# Execute this from inside the files directory

for i in `seq 1 50`
do
    dd if=/dev/urandom of="$i.txt"  bs=1M  count="$i"
done
