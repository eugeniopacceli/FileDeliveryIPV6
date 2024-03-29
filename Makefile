CC = g++
FLAGS = -std=c++11 -pthread

all: server client

server : socketAPI/* serverSrc/FileDeliveryIPV6Server.hpp
	$(CC) $(FLAGS) serverSrc/ServerFTP.cpp -o bin/servidorFTP

client : socketAPI/* clientSrc/FileDeliveryIPV6Client.hpp
	$(CC) $(FLAGS) clientSrc/ClientFTP.cpp -o bin/clienteFTP