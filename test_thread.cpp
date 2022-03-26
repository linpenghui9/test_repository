/*************************************************************************
	> File Name: test_thread.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 26 Mar 2022 11:08:07 AM PDT
 ************************************************************************/
#include <thread>
#include <iostream>
#include <unistd.h>
using namespace std;
void print(){
    for (int i = 1; i <= 10; ++i) {
        cout << i << endl;
        sleep(1);
    }
}
int main(){
    thread t1(print), t2(print);
    t1.join();
    t2.join();
    
}
