#include "Encrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "openssl/evp.h"
#include "openssl/x509.h"
#include <openssl/sha.h>
#include <assert.h>

#define File_Buffer_Size 1024

int Encrypt_File(char *EncryptF,char *CipherF)
{
	unsigned char out[File_Buffer_Size];
	int outl;
	unsigned char in[File_Buffer_Size];
	int inl;
	int rv;
	FILE *fpIn;
	FILE *fpOut;

	unsigned char key[EVP_MAX_KEY_LENGTH];
	unsigned char iv[EVP_MAX_KEY_LENGTH];

	assert(EncryptF != NULL);

	printf("The %s will be saved to be encrypted\n",EncryptF);	
	fpIn = fopen(EncryptF,"rb");
	if(fpIn == NULL)
	{
		printf("fault:can't open the %s\n",EncryptF);
		return 0;
	}

	fpOut = fopen(CipherF,"wt");
	printf("The ciphertext will be saved in %s\n",CipherF);
	if(fpOut == NULL)
	{
		fclose(fpIn);
		printf("Fault:save the ciphertext files\n");
		return 0;
	}

	char* des = (char *)malloc(SHA_DIGEST_LENGTH*2 +1);

	if( !shaFile(EncryptF,des) )
	{
		printf("Fault:can't Obtain the encryption-key\n");
		return 0;
	}
	else
	{
		int i=0;
		for(;i < 24;++i)
		{
			key[i] = des[i];
//			printf("%c",key[i]);
		}
	
		for(i = 0;i < 8;++i)
			iv[i] = i;
	}
	free(des);

	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);

	rv = EVP_EncryptInit_ex(&ctx,EVP_des_ede3_cbc(),NULL,key,iv);
	if(rv != 1)
	{
		printf("fault:cannot initialize ctx");
		return 0;
	}
	
	for(;;)
	{
		inl = fread(in,1,1024,fpIn);
		if(inl <= 0)
			break;
		rv = EVP_EncryptUpdate(&ctx,out,&outl,in,inl);
		if(rv != 1)
		{
			fclose(fpIn);
			fclose(fpOut);
			EVP_CIPHER_CTX_cleanup(&ctx);
			printf("fault:EncryptUpdate");
			return 0;
		}
		fwrite(out,1,outl,fpOut);
	}
	rv = EVP_EncryptFinal_ex(&ctx,out,&outl);
	if(rv != 1)
	{
		fclose(fpIn);
		fclose(fpOut);
		EVP_CIPHER_CTX_cleanup(&ctx);
		printf("fault:EncryptFinal");
		return 0;
	}

	fwrite(out,1,outl,fpOut);

	fclose(fpIn);
	fclose(fpOut);
	EVP_CIPHER_CTX_cleanup(&ctx);
	printf("Encrypt success\n");
	return 1;
}
