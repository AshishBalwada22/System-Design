// strategy design pattern
// encapsulate interchangeable algorithms behind common interface
// client can use different strategies at run time
// used for removal of if-else, for which algorithm to use.

#include<bits/stdc++.h>
using namespace std;

class Ipayment{
    public:
    virtual ~Ipayment() = default;
    virtual void pay(int amount)= 0;
};

class cardPayment : public Ipayment{
    public: 
    void pay(int amount) override{
        cout<<"payment mode is card : "<<amount<<endl; 
    }
};

class upiPayment : public Ipayment{
    public:
    void pay(int amount) override{
        cout<<"payment mode is upi : "<<amount<<endl;
    }
};

class shopping{
    // shopping own Ipayment object
    unique_ptr<Ipayment> payMode_;
    public:
    void setPaymentMode(unique_ptr<Ipayment> payMode){ // change payment method dynamically(at run time)
        payMode_ = move(payMode); // transfer ownership
    }
    void checkout(int amount){
        payMode_->pay(amount);
    }
};

int main(){
    shopping shop;
    unique_ptr<Ipayment> payMode = make_unique<cardPayment>(); 
    shop.setPaymentMode(move(payMode)); // transfer ownership
    shop.checkout(100);
}