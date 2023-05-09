#include<iostream>
#include<mysql.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <winsock.h> (sous Windows)
#include <mysql/mysql.h>

using namespace std;




int main()
{
	int test;
	MYSQL *connect;

	connect=mysql_init(NULL);
	if (!connect)
	{
		cout<<"MySQL Initialization failed";
		return 1;
	}
	connect=mysql_real_connect(connect, "127.0.0.1", "root", "pi" , "raspidomo" ,0,NULL,0);
	
	if (connect)
	{
		cout<<"connection Succeeded\n";
	}
	else
	{
		cout<<"connection failed\n";
	}
	
	/*
	test = mysql_query (connect,"SELECT * FROM t");

	cout<<test<<endl;*/

	test = mysql_query(connect,"UPDATE Configuration SET Configuration.id=0");

	//mysql_query(connect,"UPDATE t SET t.entrait=3");

	cout<<test<<endl;
	
	mysql_close (connect);
	return 0;
}