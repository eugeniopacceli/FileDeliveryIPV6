#include <iostream>
#include <iomanip>
#include "../socketAPI/Socket.h"
#include "../socketAPI/SocketException.h"
#include "../socketAPI/CommunicatingService.h"

using namespace std;

/*funcion that show the help information*/
void showhelpinfo(char *s) 
{
    cerr<<endl;
    cerr<<"   Usage:   "<<s<<" { list | get <file> } <server> <port> <buffer_size>"<<endl;
    cerr<<"   or     :   "<<s<<" { list | get <file> } -o [-option] [argument]"<<endl;
    cerr<<"   option:  "<<"-h  show help information (this message) and exit"<<endl;
    cerr<<"            "<<"-s  server"<<endl;
    cerr<<"            "<<"-p  port"<<endl;
    cerr<<"            "<<"-b  buffer size"<<endl;
    cerr<<"            "<<"-f  file name"<<endl;
    cerr<<"   example: "<<s<<" get filename -s server -p portnumber -t buffersize"<<endl;
    cerr<<"   or       : "<<s<<" get filename server portnumber buffersize"<<endl;
    cerr<<"   or       : "<<s<<" list -s server -p portnumber -t buffersize"<<endl;
    cerr<<"   or       : "<<s<<" list server portnumber buffersize"<<endl;
    cerr<<endl;
    exit(1);
}


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
                showhelpinfo(argv[0]);
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
                showhelpinfo(argv[0]);
        }
    }

    /*if the program is running without options ,it will show the usgage and exit*/
	if(argc  == optind)
	{
		showhelpinfo(argv[0]);
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
