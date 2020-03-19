all: edm.server edm.client clean

edm.server: server.o funct.o
	gcc server.o funct.o -o edm.server

edm.client: client.o funct.o
	gcc client.o funct.o -o edm.client

server.o: server.c
	gcc -c server.c

funct.o: funct.c
	gcc -c funct.c

client.o: client.c
	gcc -c client.c

clean:
	rm -rf *.o
