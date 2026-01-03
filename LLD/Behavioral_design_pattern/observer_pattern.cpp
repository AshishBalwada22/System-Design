// observer pattern
// one to many dependency. when subject changes, all observer get notified
// one to many dependency between object, when one object(subject) changes its state, then it would notify all other objects(observer).

//flow
// newsAgency(subject) can registered newsChannel(observer) or unregistered newsChannel
// newsAgency set news, then will call notifyObserver() to notify all the newsChannel(observer) that there is new update came.

// where it is used - GUIS, event systems, push notifications, messaging, "notify me" on restock, anytime multiple object needs live update from single resource.

#include<bits/stdc++.h>
using namespace std;

// observer interface or abstract class
class Iobserver{
    public:
    virtual ~Iobserver() = default;
    virtual void update(const string& name) = 0;
};

// subject interface or abstract class
class Isubject{
    public:
    virtual ~Isubject() = default;
    virtual void addObserver(shared_ptr<Iobserver> observer) = 0;
    virtual void removeObserver(shared_ptr<Iobserver> observer) = 0;
    virtual void notifyAllObserver() = 0;
};

// subject concrete class - newsAgency(subject change - setNews -> then notify all observer about new state of news)
class newsAgency : public Isubject{
    vector<shared_ptr<Iobserver>> observers;
    string newsName;
    struct comparator{
        shared_ptr<Iobserver> target;
        bool operator()(const shared_ptr<Iobserver>& other) const{
            return target == other;
        }
    };
    public:
    void addObserver(shared_ptr<Iobserver> observer) override{
        observers.push_back(observer);
        cout<<"Agency register news channel"<<endl;
    }
    void removeObserver(shared_ptr<Iobserver> observer) override{
        observers.erase(remove_if(observers.begin(),observers.end(),comparator{observer}),observers.end());
        // comparator{observer} -> this will create temporary comparator object and intialize its target member with the observer
        // remove_if() -> if element doesn't match then put it into the beginning with maintained sequence
        // if element doesn't match then it skip, and element come to the end
        // erase -> remove element of range from (first_argument,second_argument)
        cout<<"Agency unregister news channel"<<endl;
    }
    void setNews(const string& name){
        newsName=name;
        cout<<"new News is set : "<<name<<endl;
        notifyAllObserver();
    }
    void notifyAllObserver() override{
        for(auto& observer:observers){
            observer->update(newsName);
        }
    }
};

// observer concrete class - newschannel
class newschannel : public Iobserver{
    string name_;
    public:
    newschannel(const string& newschannel) : name_(newschannel){}
    void update(const string& name) override{
        cout<<"channel name "<<name_<<" recieved news : "<<name<<endl;
    }
};

int main(){
    auto agency = make_shared<newsAgency>();
    auto channel1 = make_shared<newschannel>("A"); // one shared pointer(channel1) is pointed to the newsChannel type object, reference_count increase by 1 
    auto channel2 = make_shared<newschannel>("B");
    agency->addObserver(channel1); // when we call addObserver, another shared pointer(in vector<shared_pointer>) will point to the same object and its reference_count becomes to 2
    // now there are two shared pointer object points to the same object
    // once we call removeObserver, then delete the observer from the vector, second shared pointer goes out of scope and its reference count reduced to 1
    // why we used shared pointer (shared ownership) as subject depends upon observer
    // observer can live independently but subject cannot
    agency->addObserver(channel2);
    agency->setNews("welcome to observer pattern");
    agency->removeObserver(channel2);
    agency->setNews("stranger things finale");
}