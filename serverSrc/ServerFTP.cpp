#include <iostream>
#include <fstream>
#include <pthread.h>
#include <csignal>
#include "../socketAPI/TCPServerSocket.hpp"
#include "../socketAPI/GlobalErrorTable.hpp"
#include "FileDeliveryIPV6Server.hpp"
//#include "../socketAPI/CommunicatingService.h"

using namespace std;

//thread main function
static void *HandleTCPClient(void *arg);

typedef struct {
        unsigned short   port;
        int              buffer;
        string           dir;
    } Options;

TCPServerSocket* serverSocket;
FileDeliveryIPV6Server* globalServer;
Options globalOptions;

void signalHandler( int signum ) {
    cout << "Interrupt signal (" << signum << ") received.\n";
    if(serverSocket) delete serverSocket;
    exit(signum);
}

int main(int argc, char *argv[]) {

	signal( SIGINT, signalHandler);

    /*set default options*/

    char opt;
    int  optflag = 0;

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
                globalOptions.port = (unsigned short)atoi(optarg);
                break;
            case 'b':
                globalOptions.buffer = atoi(optarg);
                break;
            case 'd':
                globalOptions.dir = optarg;
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

        globalOptions.port = (unsigned short)atoi(argv[optind]);
        globalOptions.buffer = atoi(argv[optind+1]);
        globalOptions.dir = argv[optind+2];
    }

   try {
        serverSocket = new TCPServerSocket(globalOptions.port);
        globalServer = new FileDeliveryIPV6Server(globalOptions.buffer, globalOptions.dir);
        for(;;) {
			TCPSocket *sock = serverSocket->accept();
			pthread_t newThread; // Give client in a separate thread
			if (pthread_create(&newThread, NULL, HandleTCPClient, sock) != 0) {
				cerr << GlobalErrorTable::GENERIC_ERROR << endl;
                delete sock;
			}
        }
    }catch(SocketException &e) {
        cerr << GlobalErrorTable::SOCKET_ERROR << " :: " << e.what() << endl;
    }

    delete globalServer;
    return 0;
}

static void *HandleTCPClient(void *arg) {
	TCPSocket *sock = (TCPSocket *)arg;
    char* buffer = new char[globalOptions.buffer]();
    PackageFormat package;
    string request;
	try {
        package = sock->receiveFormatted(buffer,globalOptions.buffer);
        request = string(package.buffer);
        if(request == "list"){
            globalServer->sendDirectoryFileList(sock);
        }else if(request.substr(0,3) == "get"){
            // get FILE_NAME, the first letter of the file is the 4th character.
            globalServer->sendFile(request.substr(4,string::npos),sock);
        }
	} catch (exception &e) {
		cerr << GlobalErrorTable::GENERIC_ERROR << " :: " << e.what() << endl;
	}
    delete[] buffer;
	pthread_exit(0);
}
