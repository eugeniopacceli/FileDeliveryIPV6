#ifndef __TCPSOCKET_H
#define __TCPSOCKET_H

#include "ChannelSocket.hpp"

/*class socket to TCP protocol*/
class TCPSocket: public ChannelSocket {

public:
	
	/**
	*
	*/
	TCPSocket() throw(SocketException): ChannelSocket(SOCK_STREAM, 0) {
	}
	
	/**
	*
	*/
	TCPSocket(const string &foreignAddress, int foreignPort) throw(SocketException): ChannelSocket(SOCK_STREAM, 0) {
		connect(foreignAddress, foreignPort);
	}

private:
	
	/**
	*
	*/
	friend class TCPServerSocket;
	TCPSocket(int sockfd): ChannelSocket(sockfd) {
	}
};
#endif
