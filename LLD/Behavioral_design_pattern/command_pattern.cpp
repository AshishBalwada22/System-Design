// command pattern
// create a command and keep it, execute later when needed
// we have receiver(light) object that actually perform the action when command is executed
// light object is used by concrete command class or main, so use shared pointer
// we have command interface, implemented by light on/off
// we have invoker(remote control) which contain command object
// when it is used - GUI buttons, menu actions, undo/redo, macro recording, job queues

#include<bits/stdc++.h>
using namespace std;

// receiver
class light{
    public:
    void on(){
        cout<<"light is on"<<endl;
    }
    void off(){
        cout<<"light is off"<<endl;
    }
};

// command interface or abstract class
class Icommand{
    public:
    virtual ~Icommand() = default; // when we point command class pointer to concrete class object, it ensure concrete class object invoke their destructor
    virtual void execute() = 0;
};

class lightOnCommand : public Icommand{
    shared_ptr<light> light_;
    public:
    lightOnCommand(shared_ptr<light> light) : light_(light){}
    void execute() override{
        light_->on();
    }
};

class lightOffCommand : public Icommand{
    shared_ptr<light> light_;
    public:
    lightOffCommand(shared_ptr<light> light) : light_(light){}
    void execute() override{
        light_->off();
    }
};

class remoteControl{
    shared_ptr<Icommand> cmd_;
    public:
    void setCommand(shared_ptr<Icommand> cmd){
        cmd_ = cmd;
    }
    void pressButton(){
        if(cmd_){
            cmd_->execute();
        }else{
            cout<<"command is not set"<<endl;
        }
    }
};

int main(){
    auto mylight = make_shared<light>();
    auto lightoff = make_shared<lightOffCommand>(mylight);
    auto lighton = make_shared<lightOnCommand>(mylight);
    remoteControl remote;
    remote.pressButton();
    remote.setCommand(lightoff);
    remote.pressButton();
    remote.setCommand(lighton);
    remote.pressButton();
}


