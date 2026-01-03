// atomic
// to prevent from race condition, instead of using mutex, use atomic
// prefer for single variable or simple data structure where operation are naturally atomic
// faster

#include<bits/stdc++.h>
using namespace std;

atomic<int> counter(0); // initialize with 0
// this tell the compiler that operation on counter must be atomic

void increment(){
    for(int i=0;i<1000;i++){
        counter++;
    }
}

int main(){
    vector<thread> threads;
    for(int i=0;i<10;i++){
        threads.emplace_back(increment);
    }
    for(auto& t : threads){
        t.join();
    }
    cout<<"counter value : "<<counter.load()<<endl;
}