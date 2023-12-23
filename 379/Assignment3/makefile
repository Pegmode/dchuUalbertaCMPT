#assignment 3 makefile

default: server client #build all

server:Server/server.c Server/server.h Server/clientsList.c Server/serverStats.c#build server
	gcc Server/server.c -o server -pthread -O -lrt

client:Client/client.c Client/clientStats.c Client/client.h#build client
	gcc Client/client.c -o client -pthread -O

clean:#Remove executables
	rm ./client
	rm ./server

cc: clearScrn default#clear screen the run default

clearScrn:#clear screen
	clear

serverMan: man/serverManSource.ms
	groff -man -Tpdf man/serverManSource.ms > man/serverMan.pdf

clientMan: man/clientManSource.ms
	groff -man -Tpdf man/clientManSource.ms > man/clientMan.pdf