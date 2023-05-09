CFLAGS=-lmysqlclient
LDFLAGS=-I/usr/include/mysql


main: main.o client_tcp.o sql.cpp
	g++ -o ecoconteur ecoconteur.o -Wall $(CFLAGS) $(LDFLAGS)

sql.o: sql.cpp
	g++ -c sql.cpp -Wall $(CFLAGS) $(LDFLAGS)

client_tcp.o: client_tcp.cpp
	g++ -c client_tcp.cpp -Wall

main.o: main.cpp client_tcp.h sql.h
	g++ -c main.cpp -Wall $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o