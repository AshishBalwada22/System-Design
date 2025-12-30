// Decorator design pattern
// you wrap an object with another object that implements the same interface and add behaviour before/after delegating to the warpped object.
// delegating -> passing the responsibility for performing a task to another object
// add features without modifying the original class

#include<bits/stdc++.h>
using namespace std;

// abstract/interface notification class
class Inotification{
    public:
    virtual ~Inotification() = default;// ensures memory management and clean up of child class object using pointer of base class
    virtual void send(string to, string message) = 0;
};

//concrete notification class
class emailNotification : public Inotification{
    public:
    void send(string to, string message) override{
        cout<<"message to "<<to<<" : "<<message<<endl;
    }
};

// base decorator , wrapper template
class NotificationDecorator : public Inotification{
    unique_ptr<Inotification> wrappee_; // wrappee that needs to be decorate using decorator class
    public:
    NotificationDecorator(unique_ptr<Inotification> wrappee) : wrappee_(move(wrappee)){}
    // takes the Inotification object to be wrapped and move to tranfer ownership to wrappee_
    void send(string to, string message) override{
        wrappee_->send(to,message); // calling emailNotification send()
    }
};

// concrete decorator - add logging functionality before and after sending the notification
class LoggingNotification : public NotificationDecorator{
    public:
    LoggingNotification(unique_ptr<Inotification> wrappee) : NotificationDecorator(move(wrappee)){}
    // calling base class constructor
    void send(string to, string message) override{
        cout<<"Sending notification to "<<to<<endl;
        NotificationDecorator::send(to,message); // call base decorator's send, which call wrappee_->send()
        cout<<"Notification sent"<<endl;
    }
};

int main(){
    unique_ptr<Inotification> emailSender = make_unique<emailNotification>();
    // now wrap the emailSender with a logging notification
    unique_ptr<Inotification> notificationChain = make_unique<LoggingNotification>(move(emailSender));
    // send a notification through decorated object
    // client doesn't need to know it's a LoggingNotification wrapping an emailNotification, it just call send() on an Inotification
    notificationChain->send("bhagwan ji", "mujhe aur strong banana");
}
