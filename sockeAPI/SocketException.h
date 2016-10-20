/* vim: set noet ts=4 sw=4 
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

#ifndef __SOCKETEXCEPTION_H
#define __SOCKETEXCEPTION_H

#include <string>
#include <exception>

using namespace std;

class SocketException: public exception {

public:
        /*  
        *       Construct a inherits from exception with explanatory message
        *       @param message show message erro from exception
        *       @param inclSysMsg if there is message from strerror(errno) is true
        */
        SocketException(const string& message, bool inclSysMsg = false) throw();

        /*  
        *       
        */
        ~SocketException() throw();

        /** 
        *       @return the exception message in c style
        */
        const char* what() const throw();

private:
        string errorMessage;    // keep exception erro messages
};

#endif
