#include "SocketException.h"
#include <iostream>

using namespace std;

void function(void) {
	throw SocketException("exception was done");
}

int main() {
	try {
		function();
	}catch(exception& e) {
		cout << "exception: " << e.what() << endl;
	}
	
	return 0;
}
