// command pattern
// create a command and keep it, execute later when needed
// we have receiver(light) object that actually perform the action when command is executed
// we have command interface, implemented by light on/off
// we have invoker(remote control) which contain command object

#include<bits/stdc++.h>
using namespace std;

class light{
    public:
    void on(){
        cout<<"light is on"<<endl;
    }
    void off(){
        cout<<light is off"<<endl;
    }
};

