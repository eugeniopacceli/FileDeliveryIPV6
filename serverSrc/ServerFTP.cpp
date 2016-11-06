#include <iostream>
#include <fstream>
#include <pthread.h>
#include "../socketAPI/TCPServerSocket.hpp"
#include "../socketAPI/CommunicatingService.h"
#include "../socketAPI/GlobalErrorTable.hpp"
#include "FileDeliveryIPV6Server.hpp"

using namespace std;

//thread main function
static void *HandleTCPClient(void *arg);
 
FileDeliveryIPV6Server* globalServer;

typedef struct {
        unsigned short   port;
        int              buffer;
        string           dir;
    } Options;

int main(int argc, char *argv[]) {

    /*set default options*/

    char opt;
    int  optflag = 0;
    Options options;
    /*use function getopt to get the arguments with option."hp:b:d:o" indicate 
    that option h,o are the options without arguments while p,b,d are the
    options with arguments*/
    while((opt=getopt(argc,argv,"hp:b:d:o"))!=-1){
        switch(opt){
            case 'o':
                optflag = 1;
                break;
            case 'h':
                GlobalErrorTable::showServerHelpAndExit(argv[0]);
                break;
            case 'p':
                options.port = (unsigned short)atoi(optarg);
                break;
            case 'b':
                options.buffer = atoi(optarg);
                break;
            case 'd':
                options.dir = optarg;
                break;
            default:
                GlobalErrorTable::showServerHelpAndExit(argv[0]);
        }
    }


    if(!optflag) {
		/*if the program is running without options ,it will show the usgage and exit*/
		if(argc  == optind){
			GlobalErrorTable::showServerHelpAndExit(argv[0]);
		}

        options.port = (unsigned short)atoi(argv[optind+1]);
        options.buffer = atoi(argv[optind+2]);
        options.dir = argv[optind+3];
    }

   try {
        TCPServerSocket serverSocket(options.port);
        globalServer = new FileDeliveryIPV6Server(options.buffer, options.dir);
        for(;;) {
			TCPSocket *sock = serverSocket.accept();
			pthread_t newThread; // Give client in a separate thread
			if (pthread_create(&newThread, NULL, HandleTCPClient, sock) != 0) {
				cerr << GlobalErrorTable::GENERIC_ERROR << endl;
				delete sock;
			}
        }
    }catch(SocketException &e) {
        cerr << GlobalErrorTable::SOCKET_ERROR << " :: " << e.what() << endl;
    }

    return 0;
}

static void *HandleTCPClient(void *arg) {
	TCPSocket *sock = (TCPSocket *)arg;
	try {
        // RECEIVE REQUEST PACKAGE
        // PARSE
        string clientAddr = sock->getForeignAddress();
        int clientPort = sock->getForeignPort(); 
        // CHOOSE BETWEEN sendDirectoryFileList(clientAddr,clientPort)
        // OR             sendFile(fileName,clientAddr,clientPort)
	} catch (exception &e) {
		cerr << GlobalErrorTable::GENERIC_ERROR << " :: " << e.what() << endl;
	}
	delete sock;
	return NULL;
	// Report errors to the console.
	// Free the socket object (and close the connection)
}
