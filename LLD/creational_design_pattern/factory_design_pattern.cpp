// Factory design pattern is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.
// Encapsulate object creation logic.
// client code doesn't need to know how to create objects or which specific class to instantiate.
// if client code directly create object using new concreteclass(), then it become tightly coupled.
// we use factory when we use if-else to create object.


  #include<bits/stdc++.h>
  using namespace std;

  // Inotifier abstact class
  class Inotifier{
    public:
    virtual ~Inotifier() = default;
    virtual void send(const string& to, const string& message)=0; 
  };

  class emailsender : public Inotifier{
    public:
    void send(const string& to, const string& message) override{
      cout<<"user : "<<to<<", message : "<<message<<endl;
    }
  };

  class smssender : public Inotifier{
    public:
    void send(const string& to, const string& message) override{
      cout<<"user : "<<to<<", message : "<<message<<endl;
    }
  };

class Notificationservice{
  public: 
  static unique_ptr<Inotifier> createobject(const string&channel){
    if(channel=="email") return make_unique<emailsender>();
    else if(channel=="sms") return make_unique<smssender>();
    // return unique_ptr of interface, not concrete class.
    //unique_ptr is a smart pointer, automatically deallocate memory when it goes out of scope.
  }
};

int main(){
    auto emailobj = Notificationservice::createobject("email"); // createobject is static method, can be called without creating object.
    emailobj->send("Ashish", "welcome to factory design pattern");
}
