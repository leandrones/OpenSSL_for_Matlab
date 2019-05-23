#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <string.h>

#define ECCTYPE  "prime256v1"
#define filename "file_to_sign.txt"
#define hashed_file "file_to_sign.txt.sha256"

/* Still working on the signing part, just made sure the files are 
read correctly and all variables are there */

int main(){

  BIO               *inbio = NULL;
  EVP_PKEY          *pkey   = NULL;
  EC_KEY            *myecc  = NULL;
  EVP_MD_CTX        *mdctx = NULL;
  unsigned char     *sig = NULL;
  long unsigned int slen;
  int               ret = 0;
  int               eccgrp;

  /* ---------------------------------------------------------- *
   * These function calls initialize openssl for correct work.  *
   * ---------------------------------------------------------- */
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

  /* ---------------------------------------------------------- *
   * Create the Input/Output BIO's.                             *
   * ---------------------------------------------------------- */
  inbio  = BIO_new(BIO_s_file());
  inbio = BIO_new_fp(stdout, BIO_NOCLOSE);

  /* ---------------------------------------------------------- *
   * Create a EC key structure, setting the group type from NID  *
   * ---------------------------------------------------------- */
  eccgrp = OBJ_txt2nid(ECCTYPE);
  myecc = EC_KEY_new_by_curve_name(eccgrp);

  /* -------------------------------------------------------- *
   * For cert signing, we use  the OPENSSL_EC_NAMED_CURVE flag*
   * ---------------------------------------------------------*/
  EC_KEY_set_asn1_flag(myecc, OPENSSL_EC_NAMED_CURVE);

  /* ---------------------------------------------------------- *
   * Read private key from file                                 *
   * ---------------------------------------------------------- */
  FILE *f1;
  f1 = fopen("PublicKey.pem", "rb");
  PEM_read_PUBKEY(f1, &pkey, NULL, NULL);
  fclose(f1);
  /* -------------------------------------------------------- *
   * Now we show how to extract EC-specifics from the key     *
   * ---------------------------------------------------------*/
  myecc = EVP_PKEY_get1_EC_KEY(pkey);
  const EC_GROUP *ecgrp = EC_KEY_get0_group(myecc);

  /* ---------------------------------------------------------- *
   * Here we print the key length, and extract the curve type.  *
   * ---------------------------------------------------------- */
  BIO_printf(inbio, "ECC Key size: %d bit\n", EVP_PKEY_bits(pkey));
  BIO_printf(inbio, "ECC Key type: %s\n", OBJ_nid2sn(EC_GROUP_get_curve_name(ecgrp)));

  /* Create the Message Digest Context */
  if(!(mdctx = EVP_MD_CTX_create())) goto err;
  
  /* ---------------------------------------------------------- *
   * This reads the contents of the file to be signed           *
   * ---------------------------------------------------------- */
  char * msg = 0;
  long length;
  FILE * f = fopen (filename, "rb");
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

  /* ---------------------------------------------------------- *
   * If there are no errors, this signs the contents of the file*
   * This will return a digest of the file                      *
   * ---------------------------------------------------------- */
  if (msg)
    {
      /* Initialise the DigestSign operation - SHA-256 has been selected as the message digest function in this example */
      if(1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey)) goto err; // Vérifier si ça hashe bien
      // Vérifier que l'output soit bien cohérent avec la fonction de hachahge
      // n octets -> 256/8 -> 32
      // 2 parties à ECDSA
      // 32 octets x 2 -> r = 32 ; s = 32
      // clé privé  32 octets
      // clé publique 32 x 2 octets
      // montrer que tout est bien cohérent en termes d'algos
      
      /* Call update with the message */
      if(1 != EVP_DigestSignUpdate(mdctx, msg, strlen(msg))) goto err;
      
      /* Finalise the DigestSign operation */
      /* First call EVP_DigestSignFinal with a NULL sig parameter to obtain the length of the */
      /* signature. Length is returned in slen */
      
      if(1 != EVP_DigestSignFinal(mdctx, NULL, &slen)) goto err;
      
      /* Allocate memory for the signature based on size in slen */
      if(!(sig = OPENSSL_malloc(sizeof(unsigned char) * (slen)))) goto err;
      
      /* Obtain the signature */
      if(1 != EVP_DigestSignFinal(mdctx, sig, &slen)) goto err;

      printf("%s",sig);
      
      /* Success */
      ret = 1;
      
    err:
      if(ret != 1)
	{
	  /* Do some error handling */
	}
    } 

  /* ---------------------------------------------------------- *
   * Free up all structures                                     *
   * ---------------------------------------------------------- */
  if(*sig && !ret) OPENSSL_free(sig);
  if(mdctx) EVP_MD_CTX_destroy(mdctx);
  EVP_PKEY_free(pkey);
  EC_KEY_free(myecc);
  BIO_free_all(inbio);

}
