#include "client_tcp.h"
#include "sql.h"

#include <stdio.h>
#include <string.h>

using namespace std;

#define SQL_BASSE "test"

#define IP_ecocompteur "172.16.1.28"
#define PORT_ecocompteur 80

int main()
{
	int position = 0;
	char valeur[255];

	string tram;
	string conso_base = "conso_base";
	string conso_hc = "conso_hc";
	string conso_hp = "conso_hp";
	string Date_Time = "Date_Time";

	string evoi = "GET /data.json HTTP/1.1\r\n";
	string evoi2 = "GET /inst.json HTTP/1.1\r\n";

	Client_tcp *client;
    client = new Client_tcp(PORT_ecocompteur, IP_ecocompteur);

    Client_tcp *client2;
    client2 = new Client_tcp(PORT_ecocompteur, IP_ecocompteur);

    Sql *sql;
    sql = new Sql(SQL_BASSE);



    client->envoyer(evoi);

    client->recevoir(tram);

    position = tram.find(conso_base);
	position = position + conso_base.size() + 4;
	conso_base = tram.substr(position, 1);


	position = tram.find(conso_hc);
	position = position + conso_hc.size() + 6;
	conso_hc = tram.substr(position, 9);


	position = tram.find(conso_hp);
	position = position + conso_hp.size() + 6;
	conso_hp = tram.substr(position, 9);	

	tram.clear();

	client2->envoyer(evoi2);

    client2->recevoir(tram);

    position = tram.find(Date_Time);
    position = position + Date_Time.size() + 2;
    Date_Time = tram.substr(position, 10);


    printf("Conso_base = %s\n", conso_base.c_str());
	sprintf(valeur, "UPDATE t SET t.conso_base=%s", conso_base.c_str());
	sql->envoyer(valeur);

	printf("Conso_hc = %s\n", conso_hc.c_str());
	sprintf(valeur, "UPDATE t SET t.conso_hc=%s", conso_hc.c_str());
	sql->envoyer(valeur);
	
	printf("Conso_hp = %s\n", conso_hp.c_str());
	sprintf(valeur, "UPDATE t SET t.conso_hp=%s", conso_hp.c_str());
	sql->envoyer(valeur);

	printf("Date_Time = %s\n", Date_Time.c_str());
	sprintf(valeur, "UPDATE t SET t.Date_Time=%s", Date_Time.c_str());
	sql->envoyer(valeur);


	delete(client2);	
	delete(client);
	return 0;
}