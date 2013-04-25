// Copyright (c) 2013 Adobe Systems Inc

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    std::fstream f1,f2,f3,f4;

    f1.open("flascclogo.txt");
    while (f1.good()) {
    	string line;
      	getline (f1,line);
      	cout << line << endl;
    }

    f2.open("rocks.txt");
    while (f2.good()) {
    	string line;
      	getline (f2,line);
      	cout << line << endl;
    }

    f3.open("/web/remote.txt");
    while (f3.good()) {
    	string line;
      	getline (f3,line);
      	cout << line << endl;
    }

    int count = 0;
    f4.open("/local/counter.txt", ios::in);
    if (f4.is_open()) {
        f4 >> count;
        f4.close();
    }
    cout << "You have run this sample " << ++count << " times";
    f4.open("/local/counter.txt", ios::out);
    f4 << count;
    f4.close();

    return 0;
}
