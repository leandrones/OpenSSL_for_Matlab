#!/bin/bash

res1=$(date +%s.%N)
for i in  {0..1000..1}
do
    openssl ecparam -name prime256v1 -genkey -noout -out key.pem
    openssl ec -in key.pem -pubout -out public.pem &>/dev/null
done

res2=$(date +%s.%N)

dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)

printf "Total runtime: %02.4f ms\n" $ds
