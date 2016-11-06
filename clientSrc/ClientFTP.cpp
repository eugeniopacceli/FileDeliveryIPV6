#include <iostream>
#include <iomanip>
#include "../socketAPI/TCPSocket.hpp"
#include "../socketAPI/SocketException.hpp"
#include "../socketAPI/CommunicatingService.h"
#include "../socketAPI/GlobalErrorTable.hpp"

using namespace std;


int main(int argc, char *argv[]) {

    /*set default options*/
    struct {
        string          command;
        string          server;
        unsigned short  port;
        int             buffer;
        string          file;
    } options;

    char opt;
    int  optflag = 0;

    /*use function getopt to get the arguments with option."hu:p:s:v" indicate 
    that option h,v are the options without arguments while u,p,s are the
    options with arguments*/
    while((opt=getopt(argc,argv,"hs:p:t:f:o"))!=-1)
    {
        switch(opt)
        {
            case 'o':
                optflag = 1;
                break;
            case 'h':
                GlobalErrorTable::showClientHelpAndExit(argv[0]);
                break;
            case 's':
                options.server = optarg;
                break;
            case 'p':
                options.port = (unsigned short)atoi(optarg);
                break;
            case 'b':
                options.buffer = atoi(optarg);
                break;
            case 'f':
                options.file = optarg;
                break;
            /*invail input will get the heil infomation*/
            default:
                GlobalErrorTable::showClientHelpAndExit(argv[0]);
        }
    }

    /*if the program is running without options ,it will show the usgage and exit*/
	if(argc  == optind)
	{
		GlobalErrorTable::showClientHelpAndExit(argv[0]);
	}

	options.command = argv[optind];

    if(!optflag) {

		options.server = argv[optind+1];
		options.port = (unsigned short)atoi(argv[optind+2]);
		options.buffer = atoi(argv[optind+3]);
		options.file = argv[optind+4];
    }


	try {
		// Connect to the server.
		TCPSocket socket(options.server, options.port);
/*
		int qCount = recvInt(&sock);

		for (int q = 0; q < qCount; q++) {
			cout << "Q" << q << ": " << recvString(&sock) << endl;

			int rCount = recvInt(&sock);

			for (int r = 0; r < rCount; r++)
				cout << setw(2) << r << " " << recvString(&sock) << endl;

			// Send the server the user's response
			sendInt(&sock, response);
		}
	} catch(runtime_error &e) {
		cerr << e.what() << endl;
	return 1;
}
	// Report errors to the console.
*/
	return 0;
}
