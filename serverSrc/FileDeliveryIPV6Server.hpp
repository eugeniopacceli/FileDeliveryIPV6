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

#ifndef __SERVERSOCKET_H
#define __SERVERSOCKET_H
#include <iostream>
#include <fstream>
#include "../socketAPI/TCPServerSocket.hpp"
#include "../socketAPI/SocketException.hpp"
#include "OSServices.hpp"

class FileDeliveryIPV6Server {
private:
    streamsize bufferSize;
    string directoryAddr;

public:
    FileDeliveryIPV6Server(streamsize bufferSize, string directoryAddr){
        this->bufferSize = bufferSize;
        this->directoryAddr = directoryAddr;
    }

    //void sendDirectoryFileList(string destiny, unsigned short port){
    void sendDirectoryFileList(ChannelSocket *sendSocket){
        //TCPSocket* sendSocket = new TCPSocket(destiny,port);
        string dirContent;
        bool ok = false;
        int offset = 0;
        try{
            dirContent = OSServices::getDirectoryFilesList(directoryAddr);
        }catch(exception& e){
            dirContent = e.what();
        }
        while(!ok){
            ok = bufferSize >= dirContent.length() - offset;
            sendSocket->sendFormatted(dirContent.substr(offset, bufferSize).c_str(), ok ? dirContent.length() - offset : bufferSize, ok);
            offset += bufferSize;
        }
        delete sendSocket;
    }

    //void sendFile(string file,string destiny, unsigned short port){
    void sendFile(string file, ChannelSocket *sendSocket){
        ifstream* input = new ifstream(file, ios::binary);
        //TCPSocket* sendSocket = new TCPSocket(destiny,port);
        bool ok = true;
        streamsize bytesRead;
        char* buffer = new char[bufferSize]();
        while(ok){
            input->read(buffer,bufferSize);
            ok = !input->eof();
            bytesRead = input->gcount();
            sendSocket->sendFormatted(buffer, (size_t)bytesRead, ok);
        }
        input->close();
        delete input;
        delete sendSocket;
        delete[] buffer;
    }

    streamsize getBufferSize(){
    	return this->bufferSize;
    }

    string getDirecoryAddr(){
    	return this->directoryAddr;
    }

    ~FileDeliveryIPV6Server(){
    }
};

#endif
