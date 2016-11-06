#ifndef __TCPSERVERSOCKET_H
#define __TCPSERVERSOCKET_H

#include "TCPSocket.hpp"

/*class socket to TCP protocol from server side*/
class TCPServerSocket: public Socket {

public:
    
    /**
    *
    */
    TCPServerSocket(unsigned short port, int queue = 5) 
        throw(SocketException): Socket(AF_INET, SOCK_STREAM, 0) {
        bind(port);
        listen(queue);
    }

    /**
    *
    */
    TCPServerSocket(const string &localAddress, unsigned short port, int queue = 5)
        throw(SocketException): Socket(AF_INET, SOCK_STREAM, 0) {
        bind(localAddress, port);
        listen(queue);
    }

    /**
    *
    */
    TCPSocket *accept()
        throw(SocketException) {

        int newsockfd;
        sockaddr_in addr;
        int addr_len = sizeof(addr);
        if((newsockfd = ::accept(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len)) < 0) {
            throw SocketException("Failed of accept (accept())", true);
        }
        
        return new TCPSocket(newsockfd);
    }

private:

    /**
    *
    */
    void listen(int queueLen)
        throw(SocketException) {
        if(::listen(sockfd, queueLen) < 0) {
            throw SocketException("listen in socket failed (listen())", true);
        }
    }
};
#endif
