#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
// #include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include "mex.h"

#define ECCTYPE  "prime256v1"
#define filename "../files/1.txt"
#define signed_file "../files/1.txt.sha256"
#define keyFileName "../PublicKey256.pem"

/* Still working on the signing part, just made sure the files are
read correctly and all variables are there */

int main(){
// void mexFunction(int nlhs, mxArray *plhs[], int nrhs, 
  // const mxArray *prhs[]){

    /* ------ Variable initialisation ------- */
    clock_t start, end;
    double cpu_time_used;
    double tableau[1000];
    int i;

   for (size_t i = 0; i < 1000; i++) {
    start = clock();
       
    BIO                  *inbio = NULL;
    EVP_PKEY             *pkey   = NULL;
    EC_KEY               *myecc  = NULL;
    EVP_MD_CTX           *mdctx = NULL;
    unsigned char        *sig = NULL;
    long unsigned int    slen;
    int                  success = 0;
    int                  eccgrp;

    //printf("%s\n%s\n%s\n",keyFileName,filename,signed_file);

    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();

    /* ---------------------------------------------------------- *
    * Create the Input/Output BIO's.                             *
    * ---------------------------------------------------------- */
    // inbio  = BIO_new(BIO_s_file());
    // inbio = BIO_new_fp(stdout, BIO_NOCLOSE);

    /* ---------------------------------------------------------- *
    * Read private key from file                                 *
    * ---------------------------------------------------------- */
    FILE *fkey;
    fkey = fopen(keyFileName, "rb");
    PEM_read_PUBKEY(fkey, &pkey, NULL, NULL);
    //PEM_read_bio_PrivateKey(inbio, &pkey, NULL, NULL);
    fclose(fkey);

    /* ---------------------------------------------------------- *
    * This reads the contents of the original file            *
    * ---------------------------------------------------------- */
    char * msg = 0;
    long unsigned int length;
    FILE * f = fopen (filename, "rb");
    if (f)
      {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        //printf("f tell msg = %ld\n",length);
        fseek (f, 0, SEEK_SET);
        msg = malloc (length);
        if (msg)
        {
          fread (msg, 1, length, f);
        }
        fclose (f);
      }
    /* ---------------------------------------------------------- *
    * This reads the contents of the signed file            *
    * ---------------------------------------------------------- */
    f = fopen (signed_file, "rb");
    if (f)
      {
        fseek (f, 0, SEEK_END);
        slen = ftell (f);
        //printf("f tell sig = %ld\n",slen);
        fseek (f, 0, SEEK_SET);
        sig = malloc (slen);
        if (sig)
        {
          fread (sig, 1, slen, f);
        }
        fclose (f);
      }

    // printf("My message: %s\n", msg);
    // printf("sig len = %d\n",slen);
    // for (size_t i = 0; i < length; i++)
    // {
    //   printf("%c",sig[i]);
    // }
    // printf("\n");
    /* ---------------------------------------------------------- *
    * If there are no errors, this hashes the contents of the file*
    * This will return a digest of the file                      *
    * ---------------------------------------------------------- */
    int verif_result;
    if (msg && sig)
    {

      /* Create the Message Digest Context */
      if(!(mdctx = EVP_MD_CTX_create())) goto err;

      /* Initialise the DigestSign operation - SHA-256 has been selected as the message digest function in this example */
      if (1 != EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL,pkey)) goto err;

      /* Call update with the message in plain text */
      if(1 != EVP_DigestVerifyUpdate(mdctx, msg, length)) goto err;

      /* Finalise the DigestVerify operation */
      /* Now the Verification is tested. It has output == 1
        if we have a success, 0 if the files are different
        and another value if there was an error */
      verif_result =  EVP_DigestVerifyFinal(mdctx, sig, slen);
      if(1 == verif_result){
        //printf("Verified OK\n");
        // mexPrintf("Verified OK\n");
      }
      else if(verif_result == 0) {
          //printf("Verification Failure\n");
        // mexPrintf("Verification Failure\n");
      }
      else{
        goto err;
      }

      success = 1;

    err:
      if(success != 1)
      {
        //printf("There was an error\n");
        // mexPrintf("There was an error\n");
      }
    }
       end = clock();
       cpu_time_used = (((double) (end - start)) / (CLOCKS_PER_SEC))*1000;
       tableau[i] =cpu_time_used;
  }
    FILE *f = fopen("verify_data_time_256mac.txt", "w");
    for(i=0;i<1000;i++){
        fprintf(f,"%f,",tableau[i] );
    }
    fclose(f);
    
}

