// Adapter pattern
// Adapter lets you make an existing class works with different interface by wrapping it.
// you don't touch the old class, you write a wrapper that converts from "what the client expects" to "what the existing class provides"

#include<bits/stdc++.h>
using namespace std;

class oldPaymentService{
    public:
    void makePaymentinRupees(long rupee){
        cout<<"payment in rupees = "<<rupee<<endl;
    }
};

// abstract class or interface
class Ipaymentprocessor{
    public:
    virtual ~Ipaymentprocessor() = default;
    virtual void processingPayment(int dollor) = 0;
};

class newProcessPayment : public Ipaymentprocessor{
    unique_ptr<oldPaymentService> service_;
    public:
    newProcessPayment( unique_ptr<oldPaymentService> service) : service_(move(service)){}
    // move -> move function take lvalue and convert into rvalue reference
    // unique pointer is exclusive ownership, means only one unique_ptr instance own a particular dynmically allocated object.
    // without move lead to passing by value, trying to copy the legacy into the service
    // as unique_ptr is non-copyable
    // move is used to transfer the ownership from the temporary unique_ptr parameter(service) to service_ member variable
    // ownership of oldPaymentService object is transferred from "legacy" to "service_" member inside newProcessPayment object.
    void processingPayment(int dollor) override{
        long rupees = dollor*80;
        service_->makePaymentinRupees(rupees);
    }
};

int main(){
    unique_ptr<oldPaymentService> legacy = make_unique<oldPaymentService>();
    unique_ptr<Ipaymentprocessor> process = make_unique<newProcessPayment>(move(legacy));
    process->processingPayment(1);
}


/*
class oldPaymentService{
    public:
    void makePaymentinRupees(long rupee){
        cout<<"payment in rupees = "<<rupee<<endl;
    }
};

// abstract class or interface
class Ipaymentprocessor{
    public:
    virtual ~Ipaymentprocessor() = default;
    virtual void processingPayment(int dollor) = 0;
};

class newProcessPayment : public Ipaymentprocessor{
    oldPaymentService *service_;
    public:
    newProcessPayment( oldPaymentService *service) : service_(service){}

    void processingPayment(int dollor) override{
        long rupees = dollor*80;
        service_->makePaymentinRupees(rupees);
    }
};

int main(){
    oldPaymentService* legacy = new oldPaymentService();
    Ipaymentprocessor* process = new newProcessPayment(legacy);
    process->processingPayment(1);

    delete process; // delete the adapter before adaptee, as adapter depends upon adaptee, and free adaptee first leads to dangling pointer.
    process = nullptr;

    delete legacy;
    legacy = nullptr;
}

*/

/*

class oldPaymentService{
    public:
    void makePaymentinRupees(long rupee){
        cout<<"payment in rupees = "<<rupee<<endl;
    }
};

// int main(){
//     oldPaymentService* legacy = new oldPaymentService();
//     legacy->makePaymentinRupees(100);
//     delete legacy; // using new, memory is allocated in the heap, not deallocate memory when goes out of scope
//     legacy = nullptr; // need to delete memory manually 
// }

int main(){
    // smart pointers are object that "own" a dynamically allocated object and automatically delete memory when it goes out of scope.
    unique_ptr<oldPaymentService> legacy = make_unique<oldPaymentService>();
    legacy->makePaymentinRupees(100);
}

*/
