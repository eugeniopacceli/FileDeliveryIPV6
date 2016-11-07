#ifndef __COMMUNICATINGSERVICE_H__
#define __COMMUNICATINGSERVICE_H__
#include "ChannelSocket.hpp"
#include <string>
#include <vector>

using namespace std;

/** Write an encoding of val to the socket, sock. */
void sendInt(ChannelSocket *sock, uint32_t val) throw(SocketException);

/** Write an encoding of str to the socket, sock. */
void sendString(ChannelSocket *sock, const string &str)
    throw(SocketException);

/** Read from sock an integer encoded by sendInt() and return it */
uint32_t recvInt(ChannelSocket *sock) throw(runtime_error);

/** Read from sock a string encoded by sendString() and return it */
string recvString(ChannelSocket *sock) throw(runtime_error);

/** Representation for a survey question */
struct Files {
    string qText;
    // Text of the question.
    vector<std::string> rList;
    // List of response choices.
};

bool readDir(istream &stream, vector<Files> &qList);

#endif
