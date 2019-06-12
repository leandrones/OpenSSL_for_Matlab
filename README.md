# OpenSSL_for_Matlab

Our objective with this project is to port
key generation, signing and verification algorithms
from C/C++ to Matlab. They will be compared with
the equivalent algorithms present in the OpenSSL's
C API in order to evaluate the feasability of this implementation.

## TO DO List (Long term)
+ Functions in C/C++
  1. Generate asymmetric key pair (Angelo)[DONE]
  2. Sign file with private key (Matheus)[DONE]
  3. Verify signature with public key (Leandro)[DONE]
+ Mex Files[DONE]
+ Benchmarking
+ Final Presentation

## Next week
+ Generate the keys and compare times for NIST P-224 et 384 
+ Make code work on Windows
+ (See the key generation in parallel on Matlab)

## For the presentation
+ Screen of the main_script.m with the output
+ Separate signature name from block name
+ Put text on the left when there are images
+ Put references below in the slides
+ Key sizes in octets
+ Put contents of the signature
+ Line above to specify average
+ Plot comparing average times on mex and C, en fonction de numero d'iterations
+ Put dimensions in the same unit
+ Make a graph acumulating the time along the number of iterations