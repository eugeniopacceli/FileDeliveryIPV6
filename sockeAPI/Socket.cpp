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
	if((sockfd = socket(domain, type, protocol) < 0)) {
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

	

void Socket::bind(unsigned short localPort)
	throw(SocketException) {
	
	sockaddr_in localAddr;
	memset(&localAddr,'\0' , sizeof(localAddr));
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(localPort);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Socket::bind(const string& address , unsigned short localPort)
	throw(SocketException) {
}

void Socket::shutdown(int how)
	throw(SocketException) {

	if(::shutdown(this->sockdf, how) < 0) {
		throw SocketException("failed to shutdown (shutdown())", true);
	}

}
/***********************************************************************/

//ChannelSocket
/***********************************************************************/

/***********************************************************************/

//TCPSocket
/***********************************************************************/

/***********************************************************************/

//TCPServer
/***********************************************************************/

/***********************************************************************/
