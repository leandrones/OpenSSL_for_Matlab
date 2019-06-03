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

## Next week
+ Generate the keys for NIST P-224 et 384[DONE]
+ (See the key generation in parallel on Matlab)
+ Solve the the different signing outputs[DONE]
+ Build the file_size x execution_time graph for signing[DONE]
+ Measure the times for the signature verification[DONE]
+ Build the file_size x execution_time graph for the verification[DONE]
