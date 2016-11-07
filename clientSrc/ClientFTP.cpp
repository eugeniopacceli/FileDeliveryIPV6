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

#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include "../socketAPI/GlobalErrorTable.hpp"
#include "FileDeliveryIPV6Client.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    /*set default options*/
    struct {
        string          command;
        string          server;
        int                port;
        int             buffer;
        string          file;
    } options;

    char opt;
    int  optflag = 0;

    /*use function getopt to get the arguments with option."hu:p:s:v" indicate 
    that option h,v are the options without arguments while u,p,s are the
    options with arguments*/
    while((opt=getopt(argc,argv,"hs:p:t:f:o"))!=-1)
    {
        switch(opt)
        {
            case 'o':
                optflag = 1;
                break;
            case 'h':
                GlobalErrorTable::showClientHelpAndExit(argv[0]);
                break;
            case 's':
                options.server = optarg;
                break;
            case 'p':
                options.port = atoi(optarg);
                break;
            case 'b':
                options.buffer = atoi(optarg);
                break;
            case 'f':
                options.file = optarg;
                break;
            /*invail input will get the heil infomation*/
            default:
                GlobalErrorTable::showClientHelpAndExit(argv[0]);
        }
    }

    /*if the program is running without options ,it will show the usgage and exit*/
    if(argc  == optind)
    {
        cerr << GlobalErrorTable::ARG_ERROR << " :: " << GlobalErrorTable::ARG_ERROR_DESC << endl;
        GlobalErrorTable::showClientHelpAndExit(argv[0]);
    }

    options.command = argv[optind];
    int idx = 1;

    if(!options.command.compare("get")) {
        if((optflag && (argc-optind < 2)) || (!optflag && (argc-optind < 5)))
        {
            cerr << GlobalErrorTable::ARG_ERROR << " :: " << GlobalErrorTable::ARG_ERROR_DESC << endl;
            GlobalErrorTable::showClientHelpAndExit(argv[0]);
        }
        options.file = argv[optind+1];
        idx = 2;
    } else {
        //checking if command is valid, if different from list exit
        if(options.command.compare("list")) {
            cerr << GlobalErrorTable::ARG_ERROR << " :: " << GlobalErrorTable::ARG_ERROR_DESC << endl;
            GlobalErrorTable::showClientHelpAndExit(argv[0]);
        }
    }        

    if(!optflag) {
        if((argc-optind) < 4 || (argc-optind) > 5) {     
            cerr << GlobalErrorTable::ARG_ERROR << " :: " << GlobalErrorTable::ARG_ERROR_DESC << endl;
            GlobalErrorTable::showClientHelpAndExit(argv[0]);
        }

        options.server = argv[optind+idx];
        idx++;
        options.port = atoi(argv[optind+idx]);
        idx++;
        options.buffer = atoi(argv[optind+idx]);
    }

    try {
        // Connect to the server.
        FileDeliveryIPV6Client client(options.server, options.port, options.buffer);

        if(!options.command.compare("list")) {
            //send commad list to server
            client << "list";
            client.listDir();
        } else {
            client << "get " + options.file;
            client.writeFile(options.file);
        }

    }
    catch(SocketException &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
