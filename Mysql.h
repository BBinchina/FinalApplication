#ifndef MYSQL_H
#define MYSQL_H
#include <mysql/mysql.h>

void FindAndStore(char *);

//enum {Field_Length = 20};

//const char User[] = "root";
//const char Passwd[] = "";
//const char Host[] = "localhost";
//const char Database[] = "CipherText";
//const char Table[] = "CipherTextTable";
//unsigned int Port = 3306;

MYSQL one_connection;	//one connect with database;

#endif	//MYSQL_H
