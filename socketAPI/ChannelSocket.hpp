#ifndef __CHANNELSOCKET_H
#define __CHANNELSOCKET_H

#include "Socket.hpp"

typedef struct{
    size_t packageLen;
    bool isFinal;
    char* buffer;
} PackageFormat;

/*class enable to communicate with by send and receive function*/
class ChannelSocket: public Socket {

public:

    /**
    *
    *///ok ipv6
    void connect(const string &destAddress, int destPort) throw(SocketException) {

        struct sockaddr_in6 foreignAddr;
        memset(&foreignAddr,'\0' , sizeof(foreignAddr));
		foreignAddr.sin6_flowinfo = 0;
        foreignAddr.sin6_family = AF_INET6;
        struct hostent *host;

        if((host = gethostbyname2(destAddress.c_str(),AF_INET6)) == NULL) {
            throw SocketException("Failed to resolve name (gethostbyname())");
        }

        foreignAddr.sin6_port = htons(destPort);
		memmove((char *) &foreignAddr.sin6_addr.s6_addr, (char *) host->h_addr, host->h_length);
        //foreignAddr.sin_addr = *((struct in_addr *)host->h_addr_list[0]);

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
    int sendall(const void *buffer, int bufferLen) throw(SocketException) {
        
        int total = 0;
        int bytesleft = bufferLen;
        int n;

        while(total < bufferLen) {
            if((n = ::send(sockfd, (void *) (((char *) buffer) + total), bytesleft, 0)) < 0) {
                break;
            }
            total += n;
            bytesleft -= n;
        }

        return n == -1?-1:total;
    }

    /**
    *
    */
    int sendFormatted(const void *buffer, int bufferLen, bool isFinal) throw(SocketException) {
        size_t firstOffset = sizeof(size_t);
        size_t secondOffset = sizeof(bool);
        size_t bufferSize = bufferLen;
        size_t totalSize = bufferSize + firstOffset + secondOffset;

        char* totalBuffer = new char[totalSize]();
        
        memcpy(totalBuffer, &bufferSize, firstOffset);
        memcpy(totalBuffer + firstOffset, &isFinal, secondOffset);
        memcpy(totalBuffer + firstOffset + secondOffset, buffer, bufferSize);
        int sndl;

        if((sndl = send((void *)totalBuffer, totalSize) < 0)) {
            throw SocketException(GlobalErrorTable::SOCKET_ERROR, true);
        } 

        return sndl;
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
    PackageFormat receiveFormatted(const void *buffer, int bufferLen) throw(SocketException) {
        int rcvt;
        size_t firstOffset = sizeof(size_t);
        size_t secondOffset = sizeof(bool);
        size_t bufferSize;
        bool isFinal;
        char* receivedBuffer;

        if((rcvt = recv((void *)buffer, bufferLen)) < 0) {
            throw SocketException(GlobalErrorTable::SOCKET_ERROR, true);
        }

        bufferSize = *((size_t*)buffer);
        isFinal = *((bool*)buffer+firstOffset);
        receivedBuffer = (char*)buffer + firstOffset + secondOffset;
        
        return { bufferSize, isFinal, receivedBuffer};
    }

#if 0
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
#endif

protected:

    /**
    *
    */
    ChannelSocket(int type, int protocol) throw(SocketException): Socket(type, protocol) {
    }

    /**
    *
    */
    ChannelSocket(int sockfd): Socket(sockfd) {
    }

};
#endif
