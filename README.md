# OpenSSL_for_Matlab

Our objective with this project is to port
key generation, signing and verification algorithms
from C/C++ to Matlab. These algorithms are contained in
the OpenSSL library for C. They will be converted into
code that is readable and executable by Matlab. The results
for Matlab will then be compared with  the equivalent algorithms present
in the OpenSSL's C library in order to evaluate the feasability of
this implementation.

# Setup

Once the source code has been cloned, the first thing to do is generate
the files we use for the demos. In order to save space on the repository,
these files should be generated locally. The files/ directory contains
a script called generate_files.sh, which can be executed both on MAC OS
and Linux (running bash).

From the main source code directory, type the following on a *MAC OS*
machine (requires the mkfile command):

```shell
cd files/
./generate_files.sh -m
```

Alternatively, on *Linux* ( requires the dd package ):

```shell
cd files/
./generate_files.sh -l
```

With the necessary files generated, most of the code can be run
in any order. Obviously, the Matlab-related code (on the main source
directory) requires Matlab to be run, as does the OpenSSL C library. All
the Makefiles assume OpenSSL's default C library
installation folder being */usr/local/opt/openssl/include*; if that's
not the case, the Makefile inside versionC/ and the buildMex.m in the
main directory should be modified accordingly.

We'll explain the scripts one by one.

## buildMex.m
This script doesn't need to be explicitly ran, as it is already called
by all the other .m scripts. Its function is to compile the three
.c files into Matlab-executable code.

## main.m
This Matlab script contains the bare minimum to test functionality of
the functions. For Matlab, we use three files on the main directory,
each one executing one of the three necessary functions:

+ genecp_nistp.c For generating ECDSA key pairs of various sizes
+ digital_signature.c For signing using the private key and a file
+ verify_signature.c For verifying a signature given the original file and the public key

The script will use buildMex() to compile the files in a Matlab format
according to the given OS (we currently support MAC OS and Linux). A
simple pop-up menu allows the user to choose the size of the ECDSA private
key and then each function will be executed once. This will make sure
there are no errors.

## main_script.m
This can be used to make a more detailed benchmark of the functions.
Each block of code executes one of the three functions 1000 times and
calculates the average execution time for each of the functions running
on Matlab.

## plot_generating_times.m
With this script it is possible to calculate the average time required
for generating keys of different sizes. It will execute the same function
a given number of times and calculate an average for each of the
four key sizes supported. A plot is returned after that.

## plot_signing_times.m
This script will do a similar thing to plot_generating_times.m, the
difference being that it will calculate average signature and verification
times as a function of file size, varying from 1MB to 40MB.
It generates a plot for both signing and verification as well. The
private key size can be any of the four supported.

## versionC/Makefile
For comparison, we can also execute the same kind of cryptographic operations using C code and the openSSL library. versionC/ contains equivalents
for most of the .m scripts in C. The source code can be compiled
(requires gcc as C compiler) using make where the argument can be
one of the following:

+ gen -> Creates executable genecp_nistp256_versionC, which calculates key generation times for a 256 key and calculates a time average out of 1000 iterations
+ sign -> Creates executable digital_signature_versionC, which calculates signature times and calculates a time average out of 1000 iterations
+ verif -> Creates executable verify_signature_versionC which calculates verification times and calculates a time average out of 1000 iterations
+ sign_size -> Creates executable digital_signature_filesize, which generates a text file containing the first iteration's signature time for each file size going from 1MB to 40MB.
+ verif_size -> Creates executable verify_signature_filesize, which generates a text file containing the first iteration's verification time for each file size going from 1MB to 40MB.

## files/Mesurer.sh
This requires bash and a recent version of the OpenSSL CLI. This bash
script can calculate average times out of 1000 iterations of each
function when run on the OpenSSL CLI. Three options can be given
when calling the script:

+ -g Will calculate average time on the CLI for key generation (256 bits private key)
+ -s Will calculate average time on the CLI for file signature (1MB file)
+ -v Will calculate average time on the CLI for signature verification

