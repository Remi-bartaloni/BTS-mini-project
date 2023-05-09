#include "sql.h"

using namespace std;


Sql::Sql(string basse):basse(basse)
{
    connect=mysql_init(NULL);
    if (!connect)
    {
        cout<<"MySQL Initialization failed";
    }
    connect=mysql_real_connect(connect, "127.0.0.1", "root", "pi" , basse.c_str() ,0,NULL,0);
    
    if (connect)
    {
        cout<<"connection Succeeded\n";
    }
    else
    {
        cout<<"connection failed\n";
    }

}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Sql::envoyer(char update[])
{
    if(mysql_query(connect, update) != 0)
    {
        cout<<"Errur";
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Sql::~Sql()
{
    mysql_close (connect);
}
