#include "Socket.h"
#include "SocketException.h"
#include <iostream>

#include <sys/socket.h>

using namespace std;

void function(void) {
	throw SocketException("exception was done");
}

int main() {
	try {

		Socket sock(AF_INET, SOCK_STREAM, 0);
		sock.bind();
		cout << sock.getLocalPort() << endl;
		cout << sock.getLocalAddress() << endl;

	}catch(exception& e) {
		cout << "exception: " << e.what() << endl;
	}
	
	return 0;
}
