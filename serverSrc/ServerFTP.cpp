#include <iostream>
#include <fstream>
#include <pthread.h>
#include "../socketAPI/TCPServerSocket.hpp"
#include "../socketAPI/CommunicatingService.h"
#include "../socketAPI/GlobalErrorTable.hpp"

using namespace std;

static vector<Files> qList;
static pthread_mutex_t lock;

void HandleTCPClient(TCPSocket *newsockfd) {

    cout << newsockfd->getForeignAddress() << endl;
    cout << newsockfd->getForeignPort() << endl;
    delete newsockfd;
}

int main(int argc, char *argv[]) {

    /*set default options*/
    struct {
        unsigned short   port;
        int              buffer;
        string           dir;
    } options;

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
        for(;;) {
            HandleTCPClient(serverSocket.accept());
        }
    }catch(SocketException &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}