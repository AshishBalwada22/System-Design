#include<bits/stdc++.h>
using namespace std;

void task(){
    cout<<"task started"<<endl;
    cout<<"thread_id : "<<this_thread::get_id()<<endl;
    this_thread::sleep_for(20ms);
    cout<<"task ends here"<<endl;
}

int main(){
    thread t(task); // from here, thread task and main will be starting working concurrently

    cout<<"Is my task thread task joinable or not : "<<t.joinable()<<endl;
    // joinable return true if it is active thread that has not been joined or detached yet.
    this_thread::sleep_for(20ms);
    cout<<"main is working"<<endl;

    t.join(); // main thread wait here until the completion of task thread
    // if not join, then main thread might be completed before task thread and leaving zoombie thread

    cout<<"Is my task thread joinable or not : "<<t.joinable()<<endl;

    cout<<"ends here"<<endl;
}

/*
void task(){
    this_thread::sleep_for(20ms);
    cout<<"task started"<<endl;
    cout<<"thread_id : "<<this_thread::get_id()<<endl;
    cout<<"task ends here"<<endl;
}

int main(){
    thread t(task); // from here, thread task and main will be starting working concurrently

    t.detach(); // now run independently
    // main thread doesnot wait for t to complete 
    // it might be possible that main thread will be completed and exit before t thread
    
    cout<<"ends here"<<endl;
}
*/