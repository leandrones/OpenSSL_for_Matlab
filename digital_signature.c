#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <matrix.h>
#include <string.h>
#include "mex.h"

#define ECCTYPE           "prime256v1"
//#define COPY_BUFFER_MAXSIZE 1048576
//#define signaturename "mysignature.txt"

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
// mex -g genecp_nistp256.c -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include

//int main(){
void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
  const mxArray *prhs[]){

  /* ---------------------------------------------------------- *
   * Variable declaration                                       *
   * ---------------------------------------------------------- */

  EVP_PKEY             *pkey   = NULL;
  EC_KEY               *myecc  = NULL;
  EVP_MD_CTX           *mdctx = NULL;
  unsigned char        *sig = NULL;
  long unsigned int    slen;
  int                  eccgrp;
  srand (1);

  unsigned char *keyFileName;
  keyFileName = mxArrayToString(prhs[0]);
  unsigned char *myfilename;
  myfilename = mxArrayToString(prhs[1]);
  unsigned char *signaturename;
  signaturename = mxArrayToString(prhs[2]);
  

  /* ---------------------------------------------------------- *
   * These function calls initialize openssl for correct work.  *
   * ---------------------------------------------------------- */
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

  /* ---------------------------------------------------------- *
   * Read private key from file                                 *
   * ---------------------------------------------------------- */
  FILE *fkey;
  fkey = fopen(keyFileName, "rb");
  PEM_read_PrivateKey(fkey, &pkey, NULL, NULL);
  fclose(fkey);

  /* ---------------------------------------------------------- *
   * This reads the contents of the file to be signed           *
   * ---------------------------------------------------------- */
  char * msg = 0;
  //msg = malloc(COPY_BUFFER_MAXSIZE);
  long unsigned int length;
  FILE * f = fopen (myfilename, "rb");
  if(f == NULL)
    {
      printf("Failed to open file: %s\n", myfilename);
      exit(1);
    }
  else
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      msg = malloc (length);
      if (msg)
	{
	  fread (msg, 1, length, f);
	}
      fclose (f);
    }

  /* ---------------------------------------------------------- *
   * If there are no errors, this signs the contents of the file*
   * This will return a digest of the file                      *
   * ---------------------------------------------------------- */
  if (msg != NULL)
    {

      /* Create the Message Digest Context */
      if(!(mdctx = EVP_MD_CTX_create())) goto err;

      /* Initialise the DigestSign operation - SHA-256 has been selected as the message digest function in this example */
      if (1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey)) goto err;

      /* Call update with the message */
      if(1 != EVP_DigestSignUpdate(mdctx, msg, length)) goto err;

      /* Finalise the DigestSign operation */
      /* First call EVP_DigestSignFinal with a NULL sig parameter to obtain the length of the */
      /* signature. Length is returned in slen */

      if(1 != EVP_DigestSignFinal(mdctx, NULL, &slen)) goto err;

      /* Allocate memory for the signature based on size in slen */
      if(!(sig = OPENSSL_malloc(sizeof(unsigned char) * (slen)))) goto err;

      /* Obtain the signature */
      if(1 != EVP_DigestSignFinal(mdctx, sig, &slen)) goto err;

      FILE * fout = fopen (signaturename, "wb");
      if (fout == NULL)
	{
	  printf("Failed to open file: %s\n", signaturename);
	  exit(1);
	}
      fwrite(sig,1,slen,fout);
      fclose(fout);

      int sucess = 1;

    err:
      {
	if(sucess != 1) mexPrintf("There was an error\n");
      }

    }

}

