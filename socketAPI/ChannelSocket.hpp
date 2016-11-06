#ifndef __CHANNELSOCKET_H
#define __CHANNELSOCKET_H

#include "Socket.hpp"

/*class enable to communicate with by send and receive function*/
class ChannelSocket: public Socket {

public:

    /**
    *
    */
    void connect(const string &destAddress, unsigned short destPort) throw(SocketException) {

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
    /**
    *
    */
    int send(const void *buffer, int bufferLen) throw(SocketException) {
        
        int sndl;
        if((sndl = ::send(sockfd, (void *)buffer, bufferLen, 0) < 0)) {
            throw SocketException("Failed in send (send())", true);
        } 

        return sndl;
    }
    /**
    *
    */
    int sendall(const void *buffer, int *bufferLen) throw(SocketException) {
        
        int total = 0;
        int bytesleft = *bufferLen;
        int n;

        while(total < *bufferLen) {
            if((n = ::send(sockfd, (void *) (((char *) buffer) + total), *bufferLen, 0)) < 0) {
                throw SocketException("Failed in sendall (send())", true);
            }
            total += n;
            bytesleft -= n;
        }

        *bufferLen = total;

        return n == -1?-1:0;
    }
    /**
    *
    */
    int recv(const void *buffer, int bufferLen)
        throw(SocketException) {
        
        int rcvt;
        if((rcvt = ::recv(sockfd, (void *)buffer, bufferLen, 0)) < 0) {
            throw SocketException("Failed in receive (recv())", true);
        } 
        
        return rcvt;
    }
    /**
    *
    */
    size_t recvFully(void *buffer, int bufferLen) 
	    throw(SocketException) {
	    int rcount = 0;
	    int len = ::recv(sockfd, (void *)buffer, bufferLen, 0);
        while (len > 0 && rcount + len < bufferLen) {
	        rcount += len;
	        len = ::recv(sockfd, (void *) (((char *) buffer) + rcount), 
	                     bufferLen - rcount, 0);
	    }

	    if (len < 0)
	        throw SocketException("Receive failed (recv())");

	    return rcount + len;
    }
    /**
    *
    */
    unsigned short getForeignPort()
        throw(SocketException) {

        sockaddr_in addr;
        unsigned int addr_len = sizeof(addr);
        if(getpeername(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
            throw SocketException("Fetching foreign port failed (getpeername())", true);
        } 
        
        return ntohs(addr.sin_port);    
    }
    /**
    *
    */
    string getForeignAddress()
        throw(SocketException) {

        sockaddr_in addr;
        unsigned int addr_len = sizeof(addr);
        if(getpeername(sockfd, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
            throw SocketException("Fetching foreign address failed (getpeername())", true);
        } 
        
        return inet_ntoa(addr.sin_addr);    
    }

protected:

    /**
    *
    */
    ChannelSocket(int domain, int type, int protocol) throw(SocketException): Socket(domain, type, protocol) {
    }

    /**
    *
    */
    ChannelSocket(int sockfd): Socket(sockfd) {
    }

};
#endif
