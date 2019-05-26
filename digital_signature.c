#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <matrix.h>
#include <string.h>
#include "mex.h"

#define ECCTYPE           "prime256v1"
#define signature_output  "tosign.txt.sha256"

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

void Base64Encode( const unsigned char* buffer, 
		   size_t length, 
		   char** base64Text) { 
  BIO *bio, *b64;
  BUF_MEM *bufferPtr;
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_new(BIO_s_mem());
  bio = BIO_push(b64, bio);
  BIO_write(bio, buffer, length);
  BIO_flush(bio);
  BIO_get_mem_ptr(bio, &bufferPtr);
  BIO_set_close(bio, BIO_NOCLOSE);
  BIO_free_all(bio);
  *base64Text=(*bufferPtr).data;
}

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

  char *keyFileName;
  keyFileName = mxArrayToString(prhs[0]);
  char *myfilename;
  myfilename = mxArrayToString(prhs[1]);
  printf("File to sign %s\n",myfilename);

  /* ---------------------------------------------------------- *
   * These function calls initialize openssl for correct work.  *
   * ---------------------------------------------------------- */
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

  /* ---------------------------------------------------------- *
   * Read private key from file                                 *
   * ---------------------------------------------------------- */
  printf("Opening %s\n",keyFileName);
  FILE *fkey;
  fkey = fopen(keyFileName, "r");
  PEM_read_PrivateKey(fkey, &pkey, NULL, NULL);
  fclose(fkey);



  /* ---------------------------------------------------------- *
   * This reads the contents of the file to be signed           *
   * ---------------------------------------------------------- */
  char * msg = 0;
  long length;
  FILE * f = fopen (myfilename, "r");
  if (f)
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

  printf("Contents of file to sign: %s\n", msg);
  /* ---------------------------------------------------------- *
   * If there are no errors, this signs the contents of the file*
   * This will return a digest of the file                      *
   * ---------------------------------------------------------- */
  if (msg != NULL)
    {

      /* Create the Message Digest Context */
      if(!(mdctx = EVP_MD_CTX_create())) printf("There was an error\n");

      /* Initialise the DigestSign operation - SHA-256 has been selected as the message digest function in this example */
      if (1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey)) printf("There was an error\n");

      /* Call update with the message */
      if(1 != EVP_DigestSignUpdate(mdctx, msg, strlen(msg))) printf("There was an error\n");

      /* Finalise the DigestSign operation */
      /* First call EVP_DigestSignFinal with a NULL sig parameter to obtain the length of the */
      /* signature. Length is returned in slen */

      if(1 != EVP_DigestSignFinal(mdctx, NULL, &slen)) printf("There was an error\n");

      /* Allocate memory for the signature based on size in slen */
      if(!(sig = OPENSSL_malloc(sizeof(unsigned char) * (slen)))) printf("There was an error\n");

      /* Obtain the signature */
      if(1 != EVP_DigestSignFinal(mdctx, sig, &slen)) printf("There was an error\n");

      FILE * fout = fopen (signature_output, "wb");
      fwrite(sig,1,slen,fout);
      fclose(fout);

      char *output;
      Base64Encode(sig, slen, &output);
      printf("Signature (Encode base64) ======\n");
      printf("%s\n",output);
      printf("================================\n");
    }

  /* ---------------------------------------------------------- *
   * Free up all structures                                     *
   * ---------------------------------------------------------- */
  //if(*sig) OPENSSL_free(sig);
  //if(mdctx) EVP_MD_CTX_destroy(mdctx);
  //EVP_PKEY_free(pkey);
  //EC_KEY_free(myecc);
  //mxFree(keyFileName);
  //mxFree(myfilename);

  /* ---------------------------------------------------------- *
   * Returning file names to matlab                             *
   * ---------------------------------------------------------- */
  plhs[0] = mxCreateString(signature_output);

}

