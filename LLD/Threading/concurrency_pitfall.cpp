// detach + local variable + reference -> danger

#include<bits/stdc++.h>
using namespace std;

int main(){
    /*
    string mesg = "Hello world";
    thread t([&](){
        cout<<"thread task starting"<<endl;
        cout<<"message = "<<mesg<<endl;
        // using detach, reference, local variable
        // mesg can be goes out of scope after main thread exit, lead to thread will try to access local variable mesg
        // that result in dangling pointer or crash
        cout<<"thread task ends here"<<endl;
    });
    */

    // using shared pointer
    auto mesg = make_shared<string>("Hello world");
    thread t([sp=mesg](){
        cout<<"thread task starting"<<endl;
        cout<<"message = "<<*sp<<endl;
        cout<<"thread task ends here"<<endl;
    }); 
    t.detach();

    cout<<"main thread end here"<<endl;
}