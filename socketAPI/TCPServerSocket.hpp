#ifndef __TCPSERVERSOCKET_H
#define __TCPSERVERSOCKET_H

#include "TCPSocket.hpp"

/*class socket to TCP protocol from server side*/
class TCPServerSocket: public Socket {

public:
    
    /**
    *
    */
    TCPServerSocket(int port, int queue = 5) 
        throw(SocketException): Socket(SOCK_STREAM, 0) {
        bind(port);
        listen(queue);
    }

    /**
    *
    */
    TCPServerSocket(const string &localAddress, int port, int queue = 5)
        throw(SocketException): Socket(SOCK_STREAM, 0) {
        bind(localAddress, port);
        listen(queue);
    }

    /**
    *
    *///ok ipv6 
    TCPSocket *accept()
        throw(SocketException) {

        int newsockfd;
        sockaddr_in6 addr;
        socklen_t addr_len = sizeof(addr);
        if((newsockfd = ::accept(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len)) < 0) {
            throw SocketException("Failed of accept (accept())", true);
        }

        inet_ntop(AF_INET6, &(addr.sin6_addr),client_addr_ipv6, sizeof(client_addr_ipv6));
        
        return new TCPSocket(newsockfd);
    }

private:

    /**
    *
    */
    char client_addr_ipv6[INET6_ADDRSTRLEN];

    /**
    *
    *///ok ipv6
    void listen(int queueLen)
        throw(SocketException) {
        if(::listen(sockfd, queueLen) < 0) {
            throw SocketException("listen in socket failed (listen())", true);
        }
    }
    
};
#endif
