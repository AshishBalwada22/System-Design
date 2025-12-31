#include<bits/stdc++.h>
using namespace std;

int counter = 0;
mutex m;

void increment(){
    for(int i=0;i<1000000;i++){
        // lock_guard -> smart lock, is a RAII wrapper around a mutex
        // lock_guard locks when created and unlock when destroyed.
        // Exeptions or early returns are safe - RAII does the cleanup.
        lock_guard<mutex> lock(m); // lock_guard object is created, its constructor call lock()
        counter++;
        /*
        // if an exception occurs between m.lock() and m.unlock(), then unlock() might never be reached, leads to deadlock
        // for example - throws the exception, will try to find catch block and in catch block, no unlock is used.
        m.lock();
        counter++;
        m.unlock();
        */
    } // when object goes out of scope, automatically call unlock()
}
int main(){
    thread t1(increment), t2(increment);
    t1.join();
    t2.join();
    cout<<"counter value = "<<counter<<endl;
}