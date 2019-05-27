#!/bin/bash
# This will measure the times to make different operations
# through the OpenSSL CLI
# Author: Matheus Augusto da Silva

function usage_statement {
    echo "USAGE: $(basename ${0}) -gsv" >&2
    echo '    -g Generates a ECDSA key pair 100 times, calculates average time' >&2
    echo '    -s Signs a file 100 times, calculates average time' >&2
    echo '    -v Verifies a hash 100 times, calculates average time' >&2
    exit 1
}

if [[ "${#}" = 0 ]]
then
   usage_statement
fi

# Parse the command line arguments
while getopts gsv OPTION
    do
    case ${OPTION} in
	g)
	    GENERATE='true'
	    echo 'Going to calculate average generation times.'
	    ;;
	s)
	    SIGN='true'
	    echo 'Going to calculate average signing times.'
	    ;;
	v)
	    VERIFY='true'
	    echo 'Going to calculate average verification times.'
	    ;;
	*)
	    echo 'Argument unknown' >&2
	    usage_statement
	    ;;
    esac
done

if [[ "${GENERATE}" = 'true' ]]
then
    res1=$(date +%s.%N)
    for i in  {0..1000..1}
    do
	openssl ecparam -name prime256v1 -genkey -noout -out PrivateKey.pem
	openssl ec -in PrivateKey.pem -pubout -out PublicKey.pem &>/dev/null
    done
    
    res2=$(date +%s.%N)
    
    dt=$(echo "$res2 - $res1" | bc)
    dd=$(echo "$dt/86400" | bc)
    dt2=$(echo "$dt-86400*$dd" | bc)
    dh=$(echo "$dt2/3600" | bc)
    dt3=$(echo "$dt2-3600*$dh" | bc)
    dm=$(echo "$dt3/60" | bc)
    ds=$(echo "$dt3-60*$dm" | bc)
    
    printf "Total generation time: %02.4f ms\n" $ds
fi

if [[ "${SIGN}" = 'true' ]]
then
    res1=$(date +%s.%N)
    for i in  {0..1000..1}
    do
	openssl dgst -sha256 -sign PrivateKey.pem generate_files.sh > signature.bin
    done
    
    res2=$(date +%s.%N)
    
    dt=$(echo "$res2 - $res1" | bc)
    dd=$(echo "$dt/86400" | bc)
    dt2=$(echo "$dt-86400*$dd" | bc)
    dh=$(echo "$dt2/3600" | bc)
    dt3=$(echo "$dt2-3600*$dh" | bc)
    dm=$(echo "$dt3/60" | bc)
    ds=$(echo "$dt3-60*$dm" | bc)
    
    printf "Total signing time: %02.4f ms\n" $ds
fi

if [[ "${VERIFY}" = 'true' ]]
then
    res1=$(date +%s.%N)
    for i in  {0..1000..1}
    do
	openssl dgst -sha256 -verify PublicKey.pem -signature signature.bin generate_files.sh &>/dev/null
    done
    
    res2=$(date +%s.%N)
    
    dt=$(echo "$res2 - $res1" | bc)
    dd=$(echo "$dt/86400" | bc)
    dt2=$(echo "$dt-86400*$dd" | bc)
    dh=$(echo "$dt2/3600" | bc)
    dt3=$(echo "$dt2-3600*$dh" | bc)
    dm=$(echo "$dt3/60" | bc)
    ds=$(echo "$dt3-60*$dm" | bc)
    
    printf "Total verification time: %02.4f ms\n" $ds
fi
