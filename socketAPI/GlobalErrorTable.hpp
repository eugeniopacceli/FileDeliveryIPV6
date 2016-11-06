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
#ifndef __GLOBALERRORTABLE_H
#define __GLOBALERRORTABLE_H
#include<string>
#include<iostream>

using namespace std;

class GlobalErrorTable{
public:
    static const string ARG_ERROR;
    static const string SOCKET_ERROR;
    static const string BIND_ERROR;
    static const string LISTEN_ERROR;
    static const string ACCEPT_ERROR;
    static const string CONNECT_ERROR;
    static const string COMMUNICATION_ERROR;
    static const string FILE_NOT_FOUND_ERROR;
    static const string POINTER_ERROR;
    static const string COMMAND_ERROR;
    static const string GENERIC_ERROR;

    static const string ARG_ERROR_DESC;
    static const string SOCKET_ERROR_DESC;
    static const string BIND_ERROR_DESC;
    static const string LISTEN_ERROR_DESC;
    static const string ACCEPT_ERROR_DESC;
    static const string CONNECT_ERROR_DESC;
    static const string COMMUNICATION_ERROR_DESC;
    static const string FILE_NOT_FOUND_ERROR_DESC;
    static const string POINTER_ERROR_DESC;
    static const string COMMAND_ERROR_DESC;
    static const string GENERIC_ERROR_DESC;

    static void showServerHelpAndExit(char *s){
        cerr << endl;
        cerr << "   Usage:   " << s << " <port server> <buffer_size> <directory>" << endl;
        cerr << "   or     :   " << s << " -o [-option] [argument]" << endl;
        cerr << "   option:  " << "-h  show help information (this message) and exit" << endl;
        cerr << "            " << "-p  port server" << endl;
        cerr << "            " << "-b  buffer size" << endl;
        cerr << "            " << "-d  directory name" << endl;
        cerr << "   example: " << s << " portserver buffersize dirname" << endl;
        cerr << "   or       : " << s << " -o -p portnumber -t buffersize -d dirname" << endl;
        cerr << endl;
        exit(1);
    }

    static void showClientHelpAndExit(char *s){
	    cerr << endl;
	    cerr << "   Usage:   " << s << " { list | get <file> } <server> <port> <buffer_size>" << endl;
	    cerr << "   or     :   " << s << " { list | get <file> } -o [-option] [argument]" << endl;
	    cerr << "   option:  " << "-h  show help information (this message) and exit" << endl;
	    cerr << "            " << "-s  server" << endl;
        cerr << "            " << "-p  port" << endl;
        cerr << "            " << "-b  buffer size" << endl;
        cerr << "            " << "-f  file name" << endl;
        cerr << "   example: " << s << " get filename -s server -p portnumber -t buffersize" << endl;
        cerr << "   or       : " << s << " get filename server portnumber buffersize" << endl;
        cerr << "   or       : " << s << " list -s server -p portnumber -t buffersize" << endl;
        cerr << "   or       : " << s << " list server portnumber buffersize" << endl;
        cerr << endl;
        exit(1);
    }

};

const string GlobalErrorTable::ARG_ERROR = "-1";
const string GlobalErrorTable::SOCKET_ERROR = "-2";
const string GlobalErrorTable::BIND_ERROR = "-3";
const string GlobalErrorTable::LISTEN_ERROR = "-4";
const string GlobalErrorTable::ACCEPT_ERROR = "-5";
const string GlobalErrorTable::CONNECT_ERROR = "-6";
const string GlobalErrorTable::COMMUNICATION_ERROR = "-7";
const string GlobalErrorTable::FILE_NOT_FOUND_ERROR = "-8";
const string GlobalErrorTable::POINTER_ERROR = "-9";
const string GlobalErrorTable::COMMAND_ERROR = "-10";
const string GlobalErrorTable::GENERIC_ERROR = "-999";

const string GlobalErrorTable::ARG_ERROR_DESC = "Erro nos argumentos de entrada";
const string GlobalErrorTable::SOCKET_ERROR_DESC = "Erro de criação de socket";
const string GlobalErrorTable::BIND_ERROR_DESC = "Erro de bind";
const string GlobalErrorTable::LISTEN_ERROR_DESC = "Erro de listen";
const string GlobalErrorTable::ACCEPT_ERROR_DESC = "Erro de accept";
const string GlobalErrorTable::CONNECT_ERROR_DESC = "Erro de connect";
const string GlobalErrorTable::COMMUNICATION_ERROR_DESC = "Erro de comunicação com servidor/cliente";
const string GlobalErrorTable::FILE_NOT_FOUND_ERROR_DESC = "Arquivo solicitado não encontrado";
const string GlobalErrorTable::POINTER_ERROR_DESC = "Erro em ponteiro";
const string GlobalErrorTable::COMMAND_ERROR_DESC = "Comando de clienteFTP não existente";
const string GlobalErrorTable::GENERIC_ERROR_DESC = "Outros erros (não listados)";

#endif