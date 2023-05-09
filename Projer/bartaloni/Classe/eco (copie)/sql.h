#ifndef SQL
#define SQL

#include <iostream>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

using namespace std;

class Sql
{
	MYSQL *connect;
	string basse;


    public:
        Sql(string);

        void envoyer(char update[]);

        ~Sql();
};

#endif // Sql
