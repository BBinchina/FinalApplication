#include "Encrypt.h"
#include "Sha1.h"
#include "Mysql.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
	printf("Encryp File:\n");
	char EncryptF[20];
	fgets(EncryptF,20,stdin);	//^d
	
	printf("\n---------------------------------\n");
	
	printf("Savation-CipherText file\n");
	char CipherF[20];
	fgets(CipherF,20,stdin);

	if( Encrypt_File(EncryptF,CipherF) == 1)
	{
		char* Target = (char *)malloc(SHA_DIGEST_LENGTH*2 + 1);
		shaFile(CipherF,Target);

		mysql_init(&one_connection);
		if( !(mysql_real_connect(&one_connection,"127.0.0.1","root","","CipherText",3306,NULL,0)))
		{
			fprintf(stderr,"Counln't connect to engine!\n\n");
			perror("");
			exit(1);
		}
		else
			FindAndStore(Target);
		
		mysql_close(&one_connection);

		free(Target);
	}

	return 0;
}
