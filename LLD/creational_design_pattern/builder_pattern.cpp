//Builder pattern

// builder separates how you construct a complex object from the final object itself, usually with step by step method + a final build()
// you use it when -
// object has many fields, many are optional.
// you want readable object creation instead of huge constructor.
// sometimes, to create immutable object(value set only via builder)
// to get rid of telescoping constructor.
// user is immutable (no setter functionality, value of fields or member variable cannot be changed)
// builder is mutable, used only to assemble and call build().

#include<bits/stdc++.h>
using namespace std;

class User{
    private:
    string name;
    string email;
    string phone;
    public:
    // this should be private
    User(string name, string email, string phone) : name(name), email(email), phone(phone) {}
    void print(){
        cout<<"name = "<<name<<endl;
        cout<<"email = "<<email<<endl;
        cout<<"phone = "<<phone<<endl;
    } 

    class Builder{
        private:
        string _name;
        string _email;
        string _phone;
        public:
        Builder& setname(string name){
            _name = name;
            return *this;
        }
        Builder& setemail(string email){
            _email = email;
            return *this;
        }
        Builder& setphone(string phone){
            _phone = phone;
            return *this;
        }
        User build(){
            return User(_name,_email,_phone);
        }
    };
};

int main(){
    User user = User::Builder().setname("Ashish").setphone("9968....22").build();
    user.print();
}
