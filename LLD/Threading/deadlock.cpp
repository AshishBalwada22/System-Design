// deadlock - two thread, two mutexes, each grab one, then waits for the other - no one can proceed.
// how to resolve this
// 1) consistent order - everywher acquire m1 before m2 or m2 before m1
// 2) scoped_lock(lock + adopt_lock)(C++ 17+) - whenever you try to hold multiple lock at once.
// 3) try_lock - back off instead of waiting forever
// 
#include<bits/stdc++.h>
using namespace std;

mutex m1,m2;

void func1(){
    lock_guard<mutex> obj1(m1);
    this_thread::sleep_for(10ms);
    lock_guard<mutex> obj2(m2);
    cout<<"func1 completed"<<endl;
}

void func2(){
    lock_guard<mutex> obj1(m2);
    this_thread::sleep_for(10ms);
    lock_guard<mutex> obj2(m1);
    cout<<"func2 completed"<<endl;
}

int main(){
    thread t1(func1), t2(func2);
    t1.join();
    t2.join();
    cout<<"main thread ends here"<<endl;
}