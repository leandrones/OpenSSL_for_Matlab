#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include "mex.h"

#define ECCTYPE  "prime256v1"


/*
 *  mexFunction:  Matlab entry function into this C code
 *  Inputs: 
 *      int nlhs:   Number of left hand arguments (output)
 *      mxArray *plhs[]:   The left hand arguments (output)
 *      int nrhs:   Number of right hand arguments (inputs)
 *      const mxArray *prhs[]:   The right hand arguments (inputs)
 *
 * Notes:
 *      (Left)  goes_out = foo(goes_in);    (Right)
 */


// Compile with
// mex genecp_nistp256.c -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, 
  const mxArray *prhs[]) {
   
  /* ---------------------------------------------------------- *
   * Variable declaration                                       *
   * ---------------------------------------------------------- */
    
  BIO               *outbio = NULL;
  EC_KEY            *myecc  = NULL;
  EVP_PKEY          *pkey   = NULL;
  int               eccgrp;
  char              *publickey_file_name = "PublicKey.pem";
  char              *privatkey_file_name = "PrivateKey.pem";

  /* ---------------------------------------------------------- *
   * These function calls initialize openssl for correct work.  *
   * ---------------------------------------------------------- */
  //OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

  /* ---------------------------------------------------------- *
   * Create the Input/Output BIO's.                             *
   * ---------------------------------------------------------- */
  outbio  = BIO_new(BIO_s_file());
  outbio = BIO_new_fp(stdout, BIO_NOCLOSE);

  /* ---------------------------------------------------------- *
   * Create a EC key sructure, setting the group type from NID  *
   * ---------------------------------------------------------- */
  eccgrp = OBJ_txt2nid(ECCTYPE);
  myecc = EC_KEY_new_by_curve_name(eccgrp);

  /* -------------------------------------------------------- *
   * For cert signing, we use  the OPENSSL_EC_NAMED_CURVE flag*
   * ---------------------------------------------------------*/
  EC_KEY_set_asn1_flag(myecc, OPENSSL_EC_NAMED_CURVE);

  /* -------------------------------------------------------- *
   * Create the public/private EC key pair here               *
   * ---------------------------------------------------------*/
  if (! (EC_KEY_generate_key(myecc)))
    BIO_printf(outbio, "Error generating the ECC key.");

  /* -------------------------------------------------------- *
   * Converting the EC key into a PKEY structure let us       *
   * handle the key just like any other key pair.             *
   * ---------------------------------------------------------*/
  pkey=EVP_PKEY_new();
  if (!EVP_PKEY_assign_EC_KEY(pkey,myecc))
    BIO_printf(outbio, "Error assigning ECC key to EVP_PKEY structure.");

  /* -------------------------------------------------------- *
   * Now we show how to extract EC-specifics from the key     *
   * ---------------------------------------------------------*/
  myecc = EVP_PKEY_get1_EC_KEY(pkey);
  const EC_GROUP *ecgrp = EC_KEY_get0_group(myecc);

  /* ---------------------------------------------------------- *
   * Here we print the key length, and extract the curve type.  *
   * ---------------------------------------------------------- */
  BIO_printf(outbio, "ECC Key size: %d bit\n", EVP_PKEY_bits(pkey));
  BIO_printf(outbio, "ECC Key type: %s\n", OBJ_nid2sn(EC_GROUP_get_curve_name(ecgrp)));

  /* ---------------------------------------------------------- *
   * Here we save the private/public key data in PEM format.   *
   * ---------------------------------------------------------- */
  FILE *f1;
  f1 = fopen(privatkey_file_name, "wb");
  PEM_write_PrivateKey(f1, pkey, NULL, NULL, 0, NULL, NULL);
  fclose(f1);

  FILE *f2;
  f2 = fopen(publickey_file_name, "wb");
  PEM_write_PUBKEY(f2, pkey);
  fclose(f2);

  /* ---------------------------------------------------------- *
   * Free up all structures                                     *
   * ---------------------------------------------------------- */
  EVP_PKEY_free(pkey);
  EC_KEY_free(myecc);
  BIO_free_all(outbio);

  exit(0);
}
