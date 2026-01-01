#include<bits/stdc++.h>
using namespace std;

mutex m;
int shared=0;

void task(int id){
    unique_lock<mutex> obj(m,defer_lock);// not lock now
    // do your work
    obj.lock(); // lock when needed
    shared++;
    cout<<"thread : "<<id<<" "<<"shared value : "<<shared<<endl;
    obj.unlock();
}

int main(){
    vector<thread> threads;
    for(int i=0;i<6;i++){
        /* don't use
        thread t(task,i);
        threads.push_back(t); // create object first then copy/moves it to the container
        */
        threads.emplace_back(task,i); // construct the object directly inside the container
    }
    for(auto& t:threads){
        t.join();
    }
    cout<<"main thread ends here"<<endl;
}