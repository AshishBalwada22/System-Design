#include<bits/stdc++.h>
using namespace std;

queue<int>q; // shared by producer, consumer
bool done = false; // flag that tells producer work is completed, shared
mutex m; // avoid race condition for shared data
condition_variable cv;
// conditional variable notify thread to wake up and consume
// conditional variable allow threads to sleep until a specific condition becomes true

void producer(){
    for(int i=0;i<5;i++){
        {
        lock_guard<mutex> obj(m); // acquired lock once object is created
        q.push(i);
        cout<<"producer produces "<<i<<endl;
        } // unlock when object goes out of scope
        cv.notify_one(); // notify any one thread to wake up and consume
    }
    {
        lock_guard<mutex> obj(m);
        done = true; // telling producer work is completed
    }
    cv.notify_all(); // notify all consumer to wake up that is waiting
}

void consumer(){
    while(true){
        unique_lock<mutex> obj(m); // conditional variable always acquire unique_lock()
        // when coming to cv.wait()
        // mutex is unlocked, thread goes to sleep, producer call notify, thread wakes up, mutex is re-locked
        // check condition, if true then starts consuming otherwise goes to sleep again
        // lock_guard  doesn't do unlock and re-lock
        cv.wait(obj, []{
            if(!q.empty()||done) return true;
            return false;
        });

        if(!q.empty()){
            int data = q.front();
            q.pop();
            obj.unlock();
            cout<<"consumer consume "<<data<<endl;
        }else if(done){ // if no data is produced or already consumed, then check if producer is done at its side or not
            break;
        }
    }
}

int main(){
    thread p(producer), c1(consumer), c2(consumer);
    p.join();
    c1.join();
    c2.join();
}
