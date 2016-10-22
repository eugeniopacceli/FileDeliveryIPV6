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

#ifndef __SOCKET_H
#define __SOCKET_H
#include "SocketException.h"
#include <string>

using namespace std;

/*general class representing a socket*/
class Socket {

public:
	/**
	*
	*/
	~Socket();	

	/**
	*
	*/
	unsigned short getLocalPort() throw(SocketException);

	/**
	*
	*/
	string getLocalAddress() throw(SocketException);

	/**
	*
	*/
	void bind() throw(SocketException);

	/**
	*
	*/
	void bind(unsigned short localPort) throw(SocketException);	

	/**
	*
	*/
	void bind(const string& address, unsigned short localPort) throw(SocketException);	


	/**
	*mudar para protected
	*/
	Socket(int domain, int type, int protocol) throw(SocketException);
	
private:

	/**
	*
	*/
	Socket(const Socket& socket);

	/**
	*
	*/
	void operator=(const Socket& socket);

protected:

	/**
	*
	*/
	int sockfd;

	/**
	*
	*/
	Socket(int sockfd);


};

/*class enable to communicate with by send and receive function*/
class ChannelSocket: public Socket {

public:

	/**
	*
	*/
	void connect(const string &destAddress, unsigned short desPort)	throw(SocketException);	

	/**
	*
	*/
	void send(const void *buffer, int bufferLen) throw(SocketException);

	/**
	*
	*/
	int receive(const void *buffer, int bufferLen) throw(SocketException);

	/**
	*
	*/
	unsigned short getForeignPort() throw(SocketException);

	/**
	*
	*/
	string getForeignAddress() throw(SocketException);


protected:

	/**
	*
	*/
	ChannelSocket(int domain, int type, int protocol) throw(SocketException);

	/**
	*
	*/
	ChannelSocket(int sockfd);

};

/*class socket to TCP protocol*/
class TCPSocket: public ChannelSocket {

public:
	
	/**
	*
	*/
	TCPSocket() throw(SocketException);
	
	/**
	*
	*/
	TCPSocket(const string &foreignAddress, unsigned short foreignPort) throw(SocketException);

private:
	
	/**
	*
	*/
	friend class TCPServerSocket;
	TCPSocket(int sockfd);
};

/*class socket to TCP protocol from server side*/
class TCPServerSocket: public Socket {

public:
	
	/**
	*
	*/
	TCPServerSocket(unsigned short port, int queueLen = 5)
		throw(SocketException);

	/**
	*
	*/
	TCPServerSocket(const string &localAddress, unsigned short port, int queueLen = 5)
		throw(SocketException);
	/**
	*
	*/
	TCPSocket *accept() throw(SocketException);

private:

	/**
	*
	*/
	void listen(int queueLen) throw(SocketException);
};

#endif
