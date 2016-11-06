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
    char* buffer;
    string directoryAddr;
    int port;

public:
    FileDeliveryIPV6Server(streamsize bufferSize, string directoryAddr, int port){
        this->bufferSize = bufferSize;
        this->buffer = new char[bufferSize]();
        this->directoryAddr = directoryAddr;
        this->port = port;
    }

    void sendDirectoryFileList(){
        string dirContent;
        try{
            dirContent = OSServices::getDirectoryFilesList(directoryAddr);
        }catch(exception& e){
            dirContent = e.what();
        }
    }

    void sendFile(string file){
        ifstream* input = new ifstream(file, ios::binary);
        bool ok = true;
        streamsize bytesRead;
        while(ok){
            input->read(buffer,bufferSize);
            ok = !input->eof();
            bytesRead = input->gcount();
            //package->write(bytesRead);
            //package->write(buffer);
            //send(package);
        }
        input->close();
        delete input;
    }

    ~FileDeliveryIPV6Server(){
        delete buffer;
    }
};

#endif
