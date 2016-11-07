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

#ifndef __OSSERVICES_H
#define __OSSERVICES_H
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "../socketAPI/GlobalErrorTable.hpp"

using namespace std;

class OSServices {
private:

public:
	static string getDirectoryFilesList(string directory) {
	    char buffer[4096];
	    string dirProcess = "dir -A -l -h " + directory;
	    string result = "";
	    FILE* pipe = popen(dirProcess.c_str(), "r");
	    if (!pipe) throw std::runtime_error(GlobalErrorTable::GENERIC_ERROR);
	    while (!feof(pipe)) {
	        if (fgets(buffer, 4096, pipe) != NULL)
	            result += buffer;
	    }
	    pclose(pipe);
	    return result;
	}

	static string trimDirString(string& str){
		if (str.length() == 0) return "";
	    size_t first = str.find_first_not_of(' ');
	    size_t last = str.find_last_not_of(' ');
	    str = str.substr(first, (last-first+1));
	    if(str.at(str.length() - 1) != '/'){
	    	str += '/';
	    }
	    return str;
	}

};

#endif
