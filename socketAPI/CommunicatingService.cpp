#include "CommunicatingService.h"

using namespace std;

void sendInt(ChannelSocket *sock, uint32_t val) throw(SocketException) {
	val = htonl(val);
	// Convert val to network byte order
	sock->send(&val, sizeof(val));
	// Send the value through the socket
}

void sendString(ChannelSocket *sock, const string &str)
throw(SocketException) {
	sendInt(sock, str.length());
	// Send the length of string
	sock->send(str.c_str(), str.length()); // Send string contents
}

uint32_t recvInt(ChannelSocket *sock) throw(runtime_error) {

	uint32_t val;

	// Try to read a 32-bit int into val
	if (sock->recvFully(&val, sizeof(val)) != sizeof(val))
	throw runtime_error("Socket closed while reading int");
	return ntohl(val);
	// Convert to host byte order, return
}

string recvString(ChannelSocket *sock) throw(runtime_error) {

	uint32_t len = recvInt(sock);

	// Read string length
	char *buffer = new char [len + 1];

	// Temp buffer to hold string
	if (sock->recvFully(buffer, len) != len) { // Try to read whole string
			delete [] buffer;
			throw runtime_error("Socket closed while reading string");
	}

	buffer[len] = '\0';
	string result(buffer);
	delete [] buffer;
	return result;
	// Null terminate the received string
	// Convert to an std::string
	// Free temporary buffer
}

//must be implemented
bool readDir(istream &stream, std::vector<Files> &qList) {
/*
	int count = 0;

	stream >> count;
	// See how many questions there are

	stream.ignore();
	// Skip past newline

	qList = vector< Question >(count);
	// Parse each question.

	for (unsigned int q = 0; q < qList.size(); q++ ) {
		getline(stream, qList[q].qText);
	// Get the text of the question

	count = 0;
	stream >> count;
	stream.ignore();
	// Read number of responses
	// Skip past newline
	// Initialize the response list and populate it.
	qList[q].rList = vector< string >(count);
	for (unsigned int r = 0; r < qList[q].rList.size(); r++)
		getline(stream, qList[q].rList[r]);
	}
	return stream;
	// Return true if stream is still good
*/
}
