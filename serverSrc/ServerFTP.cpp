#include <iostream>
#include <fstream>
#include <pthread.h>
#include "../socketAPI/Socket.h"
#include "../socketAPI/CommunicatingService.h"

sing namespace std;

static vector<Files> qList;
static pthread_mutex_t lock;

void HandleTCPClient(TCPSocket *);

/*funcion that show the help information*/
void showhelpinfo(char *s)
{
  cout<<endl;
  cout<<"   Usage:   "<<s<<" <port server> <buffer_size> <directory>"<<endl;
  cout<<"   or   :   "<<s<<" -o [-option] [argument]"<<endl;
  cout<<"   option:  "<<"-h  show help information (this message) and exit"<<endl;
  cout<<"            "<<"-p  port server"<<endl;
  cout<<"            "<<"-b  buffer size"<<endl;
  cout<<"            "<<"-d  directory name"<<endl;
  cout<<"   example: "<<s<<" portserver buffersize dirname"<<endl;
  cout<<"   or     : "<<s<<" -o -p portnumber -t buffersize -d dirname"<<endl;
  cout<<endl;
  exit(1);
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
    while((opt=getopt(argc,argv,"hp:b:d:o"))!=-1)
    {
        switch(opt)
        {
            case 'o':
                optflag = 1;
                break;
            case 'h':
                showhelpinfo(argv[0]);
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
            /*invail input will get the heil infomation*/
            default:
                showhelpinfo(argv[0]);
        }
    }


    if(!optflag) {
		/*if the program is running without options ,it will show the usgage and exit*/
		if(argc  == optind)
		{
			showhelpinfo(argv[0]);
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
    }
    catch(SocketException &e) {
        cout << "erro: " << e.what() << endl;
    }

    return 0;
}

void HandleTCPClient(TCPSocket *newsockfd) {

    cout << newsockfd->getForeignAddress() << endl;
    cout << newsockfd->getForeignPort() << endl;
    delete newsockfd;
}


