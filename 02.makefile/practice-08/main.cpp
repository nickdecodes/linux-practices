/**
@Author  : nickdecodes
@Email   : 
@Usage   : 
@Filename: main.cpp
@DateTime: 2023/10/07 17:29
@Software: vscode
**/

#include <iostream>
#include <thread>
#include "hello.h"
using namespace std;

void thread_main() {
	cout << "thread main" << endl;
}


int main(int argc, char const *argv[]) {
    thread th(thread_main);
	cout<<"test make "<<endl;
    th.join();
    Hello h;
    return 0;
}