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

#include "SocketException.hpp"
#include "GlobalErrorTable.hpp"
#include <string>
#include <sys/types.h>      
#include <sys/socket.h>     
#include <netdb.h>          
#include <arpa/inet.h>       
#include <unistd.h>          
#include <netinet/in.h>      
#include <errno.h>           
#include <cstring>
#include <iostream>

using namespace std;

/*general class representing a socket*/
class Socket {

public:
    /**
    *
    */
    ~Socket() {
        ::close(sockfd);
        sockfd = -1;
    }

#if 0
    /**
    *
    */
    unsigned short getLocalPort() throw(SocketException) {

        sockaddr_in addr;
        unsigned int addr_len = sizeof(addr);
        if(getsockname(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
            throw SocketException("Fetching local port failed (getsockname())", true);
        } 
        
        return ntohs(addr.sin_port);    
    }

    /**
    *
    */
    string getLocalAddress() throw(SocketException) {

        sockaddr_in addr;
        unsigned int addr_len = sizeof(addr);
        if(getsockname(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
            throw SocketException("Fetching local address failed (getsockname())", true);
        } 
        
        return inet_ntoa(addr.sin_addr);    
    }
#endif

    /**
    *
    *///ok ipv6
    void bind() throw(SocketException) {
        
        struct sockaddr_in6 localAddr;
        //memset(&localAddr,'\0' , sizeof(localAddr));
        bzero((char *) &localAddr, sizeof(localAddr));
        localAddr.sin6_flowinfo = 0;
        localAddr.sin6_family = AF_INET6;
        localAddr.sin6_addr = in6addr_any;
        localAddr.sin6_port = htons(0);
        //localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if(::bind(sockfd, (sockaddr *) &localAddr, sizeof(sockaddr)) < 0) {
            throw SocketException("Set of port failed (bind())", true);
        }    
    }
    /**
    *
    *///ok ipv6
    void bind(int localPort) throw(SocketException) {

        struct sockaddr_in6 localAddr;
        //bzero((char *) &localAddr, sizeof(localAddr));
        memset(&localAddr,'\0' , sizeof(localAddr));
        localAddr.sin6_flowinfo = 0;
        localAddr.sin6_family = AF_INET6;
           localAddr.sin6_addr = in6addr_any;
         localAddr.sin6_port = htons(localPort);

        if (::bind(sockfd, (struct sockaddr *) &localAddr, sizeof(localAddr)) < 0) {
            throw SocketException("Set of local port failed (bind())", true);
        }    
    }

    /**
    *
    *///ok ipv6
    void bind(const string& address , int localPort) throw(SocketException) {

        struct sockaddr_in6 localAddr;
        //memset(&localAddr,'\0' , sizeof(localAddr));
        bzero((char *) &localAddr, sizeof(localAddr));
        localAddr.sin6_flowinfo = 0;
        localAddr.sin6_family = AF_INET6;
        struct hostent *host;

        if((host = gethostbyname2(address.c_str(),AF_INET6)) == NULL) {
            throw SocketException("Failed to resolve name (gethostbyname())");
        }

        localAddr.sin6_port = htons(localPort);
        memmove((char *) &localAddr.sin6_addr.s6_addr, (char *) host->h_addr, host->h_length);
        //localAddr.sin_addr = *((struct in_addr *)host->h_addr_list[0]);

        if(::bind(sockfd, (sockaddr *) &localAddr, sizeof(sockaddr)) < 0) {
            throw SocketException("Set of local port and address failed (bind())", true);
        }
    }

    /**
    *mudar para protected
    */
    Socket(int type, int protocol) throw(SocketException) {
        //create a new socket
        if(((sockfd = socket(AF_INET6, type, protocol)) < 0)) {
            throw SocketException("socket creation failed (socket())", true);
        }
    }
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
    Socket(int sockfd) {
        //assign the already exist socket descriptor
        this->sockfd = sockfd;
    }

};

#endif
