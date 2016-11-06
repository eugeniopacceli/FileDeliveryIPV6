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

#ifndef __CLEINTSOCKET_H
#define __CLEINTSOCKET_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include "../socketAPI/TCPSocket.hpp"
#include "../socketAPI/SocketException.hpp"
//#include "../socketAPI/CommunicatingService.h"
#include "../socketAPI/GlobalErrorTable.hpp"


using namespace std;

class FileDeliveryIPV6Client {

public:
	FileDeliveryIPV6Client(string server, unsigned short port, int buffersize):
		socket(server, port), sbuffer(buffersize) {
		buffer = new char[sbuffer]();
	}

	~FileDeliveryIPV6Client() {
		delete [] buffer;
	}
	
	void operator<<(string command) {
		//send commad to server
		socket.send(command.c_str(), command.length());
	}

	void operator>>(ostream& file) {
		//output command from server
		socket.recv(buffer, sbuffer); 
		file << buffer;
	}

private:
	TCPSocket socket;
	char *buffer;
    int sbuffer;
};

#endif
