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

#include "Socket.h"
#include "SocketException.h"

#include <sys/types.h>      
#include <sys/socket.h>     
#include <netdb.h>          
#include <arpa/inet.h>       
#include <unistd.h>          
#include <netinet/in.h>      
#include <errno.h>           
#include <cstring>
#include <iostream>

//SocketException code
/***********************************************************************/

SocketException::SocketException(const string& message, bool inclSysMsg) 
	throw(): errorMessage(message) {
	if(inclSysMsg) {
		errorMessage.append(": ");
		errorMessage.append(strerror(errno));
	}
}

SocketException::~SocketException() throw() {}

const char* SocketException::what() const throw() {
	return errorMessage.c_str();
} 

/***********************************************************************/

//Socket code
/***********************************************************************/

Socket::Socket(int domain, int type, int protocol) 
	throw(SocketException) {
	//create a new socket
	if(((sockfd = socket(domain, type, protocol)) < 0)) {
		throw SocketException("socket creation failed (socket())", true);
	}
}

Socket::Socket(int sockfd) {
	//assign the already exist socket descriptor
	this->sockfd = sockfd;
}

Socket::~Socket() {
	::close(sockfd);
	sockfd = -1;
}

unsigned short Socket::getLocalPort()
	throw(SocketException) {

	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);
	if(getsockname(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetching local port failed (getsockname())", true);
	} 
	
	return ntohs(addr.sin_port);	
}

string Socket::getLocalAddress()
	throw(SocketException) {

	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);
	if(getsockname(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetching local address failed (getsockname())", true);
	} 
	
	return inet_ntoa(addr.sin_addr);	
}

void Socket::bind() 
	throw(SocketException) {
	
	sockaddr_in localAddr;
	memset(&localAddr,'\0' , sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(0);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(::bind(sockfd, (sockaddr *) &localAddr, sizeof(sockaddr)) < 0) {
		throw SocketException("Set of port failed (bind())", true);
	}	
}

void Socket::bind(unsigned short localPort)
	throw(SocketException) {
	
	sockaddr_in localAddr;
	memset(&localAddr,'\0' , sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(localPort);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(::bind(sockfd, (sockaddr *) &localAddr, sizeof(sockaddr)) < 0) {
		throw SocketException("Set of local port failed (bind())", true);
	}	
}

void Socket::bind(const string& address , unsigned short localPort)
	throw(SocketException) {

	sockaddr_in localAddr;
	memset(&localAddr,'\0' , sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	hostent *host;

	if((host = gethostbyname(address.c_str())) == NULL) {
		throw SocketException("Failed to resolve name (gethostbyname())");
	}

	localAddr.sin_port = htons(localPort);
	localAddr.sin_addr = *((struct in_addr *)host->h_addr_list[0]);

	if(::bind(sockfd, (sockaddr *) &localAddr, sizeof(sockaddr)) < 0) {
		throw SocketException("Set of local port and address failed (bind())", true);
	}	
}

/***********************************************************************/

//ChannelSocket
/***********************************************************************/

ChannelSocket::ChannelSocket(int domain, int type, int protocol)
	throw(SocketException): Socket(domain, type, protocol) {
}

ChannelSocket::ChannelSocket(int sockfd): Socket(sockfd) {
}

void ChannelSocket::connect(const string &destAddress, unsigned short destPort)
	throw(SocketException) {

	sockaddr_in foreignAddr;
	memset(&foreignAddr,'\0' , sizeof(foreignAddr));
	foreignAddr.sin_family = AF_INET;
	hostent *host;

	if((host = gethostbyname(destAddress.c_str())) == NULL) {
		throw SocketException("Failed to resolve name (gethostbyname())");
	}

	foreignAddr.sin_port = htons(destPort);
	foreignAddr.sin_addr = *((struct in_addr *)host->h_addr_list[0]);

	if((::connect(sockfd, (sockaddr *) &foreignAddr, sizeof(foreignAddr))) < 0) {
		throw SocketException("Failed in trying to connect", true);
	}
}

int ChannelSocket::send(const void *buffer, int bufferLen)
	throw(SocketException) {
	
	int sndl;
	if((sndl = ::send(sockfd, (void *)buffer, bufferLen, 0) < 0)) {
		throw SocketException("Failed in send (send())", true);
	} 

	return sndl;
}

int ChannelSocket::sendall(const void *buffer, int *bufferLen)
	throw(SocketException) {
	
	int total = 0;
	int bytesleft = *bufferLen;
	int n;

	while(total < *bufferLen) {
		if((n = ::send(sockfd, (void *)(buffer+total), *bufferLen, 0)) < 0) {
			throw SocketException("Failed in sendall (send())", true);
		}
		total += n;
		bytesleft -= n;
	}

	*bufferLen = total;

	return n == -1?-1:0;
}

int ChannelSocket::receive(const void *buffer, int bufferLen)
	throw(SocketException) {
	
	int rcvt;
	if((rcvt = ::recv(sockfd, (void *)buffer, bufferLen, 0)) < 0) {
		throw SocketException("Failed in receive (recv())", true);
	} 
	
	return rcvt;
}

unsigned short ChannelSocket::getForeignPort()
	throw(SocketException) {

	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);
	if(getpeername(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetching foreign port failed (getpeername())", true);
	} 
	
	return ntohs(addr.sin_port);	
}

string ChannelSocket::getForeignAddress()
	throw(SocketException) {

	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);
	if(getpeername(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
		throw SocketException("Fetching foreign address failed (getpeername())", true);
	} 
	
	return inet_ntoa(addr.sin_addr);	
}

/***********************************************************************/

//TCPSocket
/***********************************************************************/

TCPSocket::TCPSocket() 
	throw(SocketException): ChannelSocket(AF_INET, SOCK_STREAM, 0) {
}

TCPSocket::TCPSocket(int sockfd): ChannelSocket(sockfd) {
}

TCPSocket::TCPSocket(const string &foreignAddress, unsigned short foreignPort) 
	throw(SocketException): ChannelSocket(AF_INET, SOCK_STREAM, 0) {
	connect(foreignAddress, foreignPort);
}

/***********************************************************************/

//TCPServer
/***********************************************************************/

TCPServerSocket::TCPServerSocket(unsigned short port, int queue) 
	throw(SocketException): Socket(AF_INET, SOCK_STREAM, 0) {
	bind(port);
	listen(queue);
}

TCPServerSocket::TCPServerSocket(const string &localAddress, unsigned short port, int queue)
	throw(SocketException): Socket(AF_INET, SOCK_STREAM, 0) {
	bind(localAddress, port);
	listen(queue);
}

TCPSocket *TCPServerSocket::accept()
	throw(SocketException) {

	int newsockfd;
	sockaddr_in addr;
	int addr_len = sizeof(addr);
	if((newsockfd = ::accept(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len)) < 0) {
		throw SocketException("Failed of accept (accept())", true);
	}
	
	return new TCPSocket(newsockfd);
}

void TCPServerSocket::listen(int queueLen)
	throw(SocketException) {
	if(::listen(sockfd, queueLen) < 0) {
		throw SocketException("listen in socket failed (listen())", true);
	}
}
/***********************************************************************/