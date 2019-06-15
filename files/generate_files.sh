#!/bin/bash

# This will generate 50 files of increasing size, to test our signing on
# The i-th file is named i.txt and has a size of i bytes
# Execute this from inside the files directory

function usage_statement {
    echo "USAGE: $(basename ${0}) -gsv" >&2
    echo '    -m Generates files on a Mac machine' >&2
    echo '    -l Generates files on a Linux machine' >&2
    exit 1
}

if [[ "${#}" = 0 ]]
then
   usage_statement
fi

# Parse the command line arguments
while getopts ml OPTION
    do
    case ${OPTION} in
	m)
	    MAC='true'
	    echo 'Generating on MAC.'
	    ;;
	l)
	    LINUX='true'
	    echo 'Generating on Linux.'
	    ;;
	*)
	    echo 'Argument unknown' >&2
	    usage_statement
	    ;;
    esac
done


for i in `seq 1 50`
do
    if [[ "${MAC}" = 'true' ]]
    then
	VAR1=$i
	VAR1+="M"
	mkfile $VAR1 $i.txt
    fi

    if [[ "${LINUX}" = 'true' ]]
    then
	dd if=/dev/urandom of="${i}.txt"
    fi
done
