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

#include "ClientSocket.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

/*funcion that show the help information*/
void showhelpinfo(char *s)
{
  cerr<<endl;
  cerr<<"   Usage:   "<<s<<" { list | get <file> } <server> <port> <buffer_size>"<<endl;
  cerr<<"   or	 :   "<<s<<" { list | get <file> } -o [-option] [argument]"<<endl;
  cerr<<"   option:  "<<"-h  show help information (this message) and exit"<<endl;
  cerr<<"            "<<"-s  server"<<endl;
  cerr<<"            "<<"-p  port"<<endl;
  cerr<<"            "<<"-b  buffer size"<<endl;
  cerr<<"            "<<"-f  file name"<<endl;
  cerr<<"   example: "<<s<<" get filename -s server -p portnumber -t buffersize"<<endl;
  cerr<<"   or	   : "<<s<<" get filename server portnumber buffersize"<<endl;
  cerr<<"   or	   : "<<s<<" list -s server -p portnumber -t buffersize"<<endl;
  cerr<<"   or	   : "<<s<<" list server portnumber buffersize"<<endl;
  cerr<<endl;
  exit(1);
}

int main (int argc,char *argv[])
{
  /*set default options*/
  struct {
    string command;
    string server; 
    string port;
    string buffer;
    string file;
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
        showhelpinfo(argv[0]);
        break;
      case 's':
	options.server = optarg; 
        break;
      case 'p':
	options.port = optarg;
        break;
      case 'b':
	options.buffer = optarg;
        break;
      case 'f':
	options.file = optarg;
      	break;
      /*invail input will get the heil infomation*/
      default:
        showhelpinfo(argv[0]);
      break;
    }
  }

  if(!optflag) {
    /*if the program is ran witout options ,it will show the usgage and exit*/
    if(argc  == optind)
    {
      showhelpinfo(argv[0]);
    }
    for(int i = optind; i < argc ; i++) {
      cout << argv[i] << endl;
    }
  }
  
  return 0;
}

