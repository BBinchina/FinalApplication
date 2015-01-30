#include "Mysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*already connected database;*/
void FindAndStore(char *Target)
{
	MYSQL_RES *result;	//the operation result
	MYSQL_ROW sql_row;	//store row
//	MYSQL_FIELD *fd;	//field name
	
	char sql[512];		//sql statement
//	sprintf(sql,"select %s from CipherTextTable","CipherText");
	sprintf(sql,"select CipherText from CipherTextTable where CipherText='%s'",Target);

//	printf("%s\n",sql);	//check the sql

	if( mysql_query(&one_connection,sql) != 0)//execute the sql
	{
		printf("Error %u: %s\n", mysql_errno(&one_connection), mysql_error(&one_connection));
		exit(1);
	}
	result = mysql_store_result(&one_connection);//Obtain data

	//the table has the same of hash-value
	int numRow;
	if( (numRow = mysql_num_rows(result) ) != 0 )
	{
//		printf("numRow:%d\n",numRow);//

		//fd = mysql_fetch_field(result);
		//field separated from data
		sql_row=mysql_fetch_row(result);//we can see
						//it start from first result
		printf("%s\n",sql_row[0]);

		printf("Already existed! please make sure your operation\n");
	}
	else	//no have so we can store the CipherText into tables
	{
		sprintf(sql,"insert into %s(CipherText)values('%s')"
				,"CipherTextTable",Target);

//		printf("%s\n",sql);	//check sql

		if( !( mysql_query(&one_connection,sql) ) )
		{
			perror("insert");
		}
		else
			printf("Store Success\n");
	}

	mysql_free_result(result);//store the result need malloc
					//we should free the memory
	return;
	//one operation end
}
