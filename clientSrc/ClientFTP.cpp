#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

#include "../socketAPI/GlobalErrorTable.hpp"
#include "ClientSocket.hpp"

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
		cerr << "missing commands" << endl;
		GlobalErrorTable::showClientHelpAndExit(argv[0]);
	}

	options.command = argv[optind];
	int idx = 1;

	if(!options.command.compare("get")) {
		if((optflag && (argc-optind < 2)) || (!optflag && (argc-optind < 5)))
		{
			cerr << "missing filename" << endl;
			GlobalErrorTable::showClientHelpAndExit(argv[0]);
		}
		options.file = argv[optind+1];
		idx = 2;
	} else {
		//checking if command is valid, if different from list exit
		if(options.command.compare("list")) {
			cerr << "error in command passed" << endl;
			GlobalErrorTable::showClientHelpAndExit(argv[0]);
		}
	}		

    if(!optflag) {
		if((argc-optind) < 4 || (argc-optind) > 5) {	 
			cerr << "wrong number of command passed" << endl;
			GlobalErrorTable::showClientHelpAndExit(argv[0]);
		}

		options.server = argv[optind+idx];
		idx++;
		options.port = (unsigned short)atoi(argv[optind+idx]);
		idx++;
		options.buffer = atoi(argv[optind+idx]);
    }

#if 0
	//testing input
	cout << options.command << endl;
	cout << options.file << endl;
	cout << options.server << endl;
	cout << options.port << endl;
	cout << options.buffer << endl;
#endif

	try {
		// Connect to the server.
		FileDeliveryIPV6Client client(options.server, options.port, options.buffer);

		if(!options.command.compare("list")) {
			//send commad list to server
			client << "list";
			//put the list of files in cout
			client >> cout;
		} else {
			client << "get " + options.file;
		}
	}
	catch(SocketException &e) {
		cerr << e.what() << endl;
	}

	return 0;
}
