/* vim: set noet ts=4 sw=4 
*  The MIT License
*  
*  Copyright (c) 2016 Eugênio Pacceli Reis da Fonseca 
*  
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*  
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*  
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*
* @authors Eugênio Pacceli
*          Otávio Augusto
*
* @discription:
*/

//#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
//testing
#include "../socketAPI/SocketException.hpp"
#include "../socketAPI/TCPServerSocket.hpp"
#include "../socketAPI/GlobalErrorTable.hpp"

using namespace std;

void HandleTCPClient(TCPSocket *);

int main (int argc,char *argv[])
{
	/*set default options*/
	struct {
		unsigned short	 port;
		int				 buffer;
		string 			 dir;
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
			/*invail input will get the heil infomation*/
			default:
				GlobalErrorTable::showServerHelpAndExit(argv[0]);
		}
	}

	if(!optflag) {
	/*if the program is ran witout options ,it will show the usgage and exit*/
		if(argc == optind)
		{
			GlobalErrorTable::showServerHelpAndExit(argv[0]);
		}
		for(int i = optind; i < argc ; i++) {
			cout << argv[i] << endl;
		}
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
