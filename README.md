# OpenSSL_for_Matlab

Our objective with this project is to port
key generation, signing and verification algorithms
from C/C++ to Matlab. They will be compared with
the equivalent algorithms present in the OpenSSL's
C API in order to evaluate the feasability of this implementation.

## TO DO List (Long term)
+ Functions in C/C++
  1. Generate asymmetric key pair (Angelo)
  2. Sign file with private key (Matheus)
  3. Verify signature with public key (Leandro)
+ Mex Files
+ Benchmarking

## Next week
+ Generate the keys for NIST P-224 et 384
+ (See the key generation in parallel on Matlab)
+ Solve the the different signing outputs
+ Build the file_size x execution_time graph for signing
+ Measure the times for the signature verification
+ Build the file_size x execution_time graph for the verification
