#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ECCTYPE           "prime256v1"
#define myfilename "../files/1.txt"
#define signaturename "../files/1.txt.sha256"
#define keyFileName "../PrivateKey256.pem"


int main(){
  
  
  /* ---------------------------------------------------------- *
   * Variable declaration                                       *
   * ---------------------------------------------------------- */
  EVP_PKEY             *pkey;
  EVP_MD_CTX           *mdctx;
  unsigned char        *sig;
  long unsigned int    slen;

    /* ------ Variable initialisation ------- */
    clock_t start, end;
    double cpu_time_used;
    double tableau[1000];
    int i;
    
  for (size_t i = 0; i < 1000; i++) {
    start = clock();
    pkey = NULL;
    mdctx =  NULL;
    sig = NULL;
    
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
	  if(sucess != 1) printf("There was an error\n");
	}
	
      }

    if(*sig) OPENSSL_free(sig);
    if(mdctx) EVP_MD_CTX_destroy(mdctx);
    EVP_PKEY_free(pkey);
      end = clock();
      cpu_time_used = (((double) (end - start)) / (CLOCKS_PER_SEC))*1000;
      tableau[i] =cpu_time_used;

    }
    FILE *f = fopen("signData_mac256.txt", "w");
    for(i=0;i<1000;i++){
        fprintf(f,"%f,",tableau[i] );
    }
    fclose(f);

}
