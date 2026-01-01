// producer and consumer donot talk to each other directly
// they communicate only through the queue api's 

#include<bits/stdc++.h>
using namespace std;

class threadSafeQueue{
    private:
    queue<int>q;
    mutex m;
    condition_variable cv;
    public:
    void push(int val){
        lock_guard<mutex> obj(m);
        q.push(val);
        cv.notify_one();
    }
    int pop(){
        unique_lock<mutex> obj(m);
        cv.wait(obj,[this](){
            if(!q.empty()) return true;
            return false;
        });
        int val = q.front();
        q.pop();
        return val;
    }
};

int main(){
    threadSafeQueue tsq;
    thread producer([&](){
       for(int i=0;i<6;i++){
        tsq.push(i);
        cout<<"producer produces "<<i<<endl;
        this_thread::sleep_for(10ms);
       }
    });
    thread consumer([&](){
        for(int i=0;i<6;i++){
            int val = tsq.pop();
            cout<<"consumer consumes "<<val<<endl;
            this_thread::sleep_for(10ms);
        }
    });
    producer.join();
    consumer.join();
}