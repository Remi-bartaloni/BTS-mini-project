CFLAGS=-lmysqlclient
LDFLAGS=-I/usr/include/mysql


ecoconteur: ecoconteur.o
	g++ -o ecoconteur ecoconteur.o -Wall $(CFLAGS) $(LDFLAGS)


ecoconteur.o: ecoconteur.cpp
	g++ -c ecoconteur.cpp -Wall $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o