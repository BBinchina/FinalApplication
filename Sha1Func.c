#include "Sha1.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int shaFile(const char* fileName,char *des)
{
	assert(fileName != NULL);

	FILE* fpIn = fopen(fileName,"rb");
	if(fpIn == NULL)
	{
		printf("The %s can't be Sha1 processing\n",fileName);
		return 0;
	}

	size_t nRead;
	
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	while(1)
	{
		nRead = fread(buffIn,1,File_Buffer_Size,fpIn);
		if(nRead)
		{
			SHA1_Update(&ctx,buffIn,nRead);//Multiple Execution
		}
		else
			break;
	}
	SHA1_Final(hash,&ctx);//To get the final result and put it into hash
	fclose(fpIn);

	int i=0,j=0;
	for(;i < SHA_DIGEST_LENGTH;j += 2, ++i)
	{
		sprintf(des + j,"%02x",hash[i]);
	}

	return 1;
}
