#include<iostream>
#include<string>
using namespace std;

1) SRP (single responsibility principle) 
 - Each class has only one responsibility

 --violation of SRP--

class User{
    public:
    string name;
    string email;
    string number;
    User(string n, string e, string num) : name(n) , email(e), number(num) {}
};

class NotificationService{
    public : 
    // here, class has two responsibility -> sending notification and logic of sending email or sms written in same class
    void sendNotification(const User& user, const string& message, const string& type){
        if(type == "email"){
            cout<<"Email to " <<user.name<< " : " <<message<<endl;
        }else if(type == "sms"){
            cout<<"SMS to "<<user.name<<":"<<message<<endl;
        }
    }
};

int main(){
    User user("Ashish","ashish@gmail.com","xyz");
    NotificationService service;
    service.sendNotification(user,"welcome : Ashish","email");
}


--Resolution--

class User{
    public:
    string name;
    string email;
    string number;
    User(string n, string e, string num) : name(n) , email(e), number(num) {}
};

class EmailSender{
    public :
    void sendingEmail(const User&user, const string&message){
        cout<<"Email to " <<user.name<< " : " <<message<<endl;
    }
};

class SmsSender{
    public:
    void sendingSms(const User&user, const string& message){
        cout<<"SMS to "<<user.name<<":"<<message<<endl;
    }
};

class NotificationService{
    EmailSender emailsender;
    SmsSender smssender;
    public:
    void sendNotification(const User&user, const string&message, const string&type){
        if(type == "email"){
            emailsender.sendingEmail(user,message);
        }else if(type == "sms"){
            smssender.sendingSms(user,message);
        }
    }
};

int main(){
    User user("Ashish","ashish@gmail.com","xyz");
    NotificationService service;
    service.sendNotification(user,"welcome : Ashish","email");
}


2) OCP (open closed principle)
- open for extension but closed for modification
- removal of if else system
- achieved by abstraction and polymorphism



class User{
    public:
    string name;
    string email;
    string number;
    User(string n, string e, string num) : name(n) , email(e), number(num) {}
};

// abstract class or interface
class iNotifier{
    public:
    virtual void send(const User&user, const string&message) = 0;
};

class EmailSender : public iNotifier{
    public:
    void send(const User&user,const string&message) override{
        cout<<"Email to " <<user.name<< " : " <<message<<endl;
    }
};

class SmsSender : public iNotifier{
    public:
    void send(const User&user,const string&message) override{
        cout<<"Sms to " <<user.name<< " : " <<message<<endl;
    }
};

class NotificationService{
    public:
    void sendNotification(iNotifier& notifier,const User&user,const string&message){
        notifier.send(user,message);
    }
};

int main(){
    User user("Ashish Balwada","ashish@gmail.com","xyz");
    EmailSender emailsender;
    SmsSender smssender;
    NotificationService service;
    service.sendNotification(emailsender,user,"welcome : Ashish");
    service.sendNotification(smssender,user,"welcome : Ashish");
}



3) LSP (liskov subsitution principle) - 
- subclasses should be substituable for base class without altering the correctness of the program.
- emailsender and smssender can come in place of iNotifier.
  iNotifier notifier = emailsender;
- violation
  when base class is forcing function to be implemented by derived class, that doesn't want to be implemented.
- To ensure LSP in practice
  write unit testcases using the base class and run them against all the subclasses to ensure none of the subclasses violated the expected behaviour.
Example - 
class bird{
    public: // these function should be implemented by derived class
    virtual void eat()=0;
    virtual void fly()=0;
};
class penguin : public bird{
    public : 
    void eat() override{}
    void fly() overrid{}  // penguin can't fly, so violation of LSP
};
int main(){
    Bird bird = new bird();
    bird.fly();
    Bird bird1 = new penguin();
    bird1.fly(); // violation of LSP as if i replace base class object with derived class, then it should work with same behaviour
}

Resolution

class bird{
    public:
    virtual void eat()=0;
};
class flightbird : public bird{
    public:
    void eat() override{}
    void fly(){}
}
class flightlessbird : public bird{
    public :
    void eat()override{} 
};
class penguin : public flightlessbird{
    public :
};


4) ISP(interface segregation principle)
- No client should be forced to depend on methods, it doesn't use.
- make interface small
- In iNotifier interface, we define only one send method, that should be implemented by emailSender and smsSender.
- ISP is srp of interface


Example -

class iPrinter{
    public:
    virtual void print() = 0;
};
class iScanner{
    public:
    virtual void print() = 0;
};
class iFax{
    public:
    virtual void print() = 0;
};
class simplePrinter{
    public:
    void print() override{
    }
};

5) DIP (Dependency inversion principle) -
- Higher module should not depend upon lower module but it should depend upon abstraction(iNotifier).
- Old design =  NotificationService -> emailSender, smsSender
- New design = NotificationService -> iNotifier,  emailsender/smsSender -> iNotifier.

Detection Framework -
- Any design has CSR methods
C - controller (starter code, runner of the Apis)
S - service (business logic)
R - repository (database interaction)

SRP -> classes have single responsibility. too long code in function.
OCP -> IF-else cannot be there (except if it explicitly does only if-else)
LSP -> look for forced inheritance and override. i.e rectangle -> square
ISP -> Bulky interface, too many function to implement
DIP -> object static creation -> object passed as parameter -> interface type.