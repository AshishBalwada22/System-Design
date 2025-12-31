#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<thread> threads;
    for(int i=0;i<8;i++){
        threads.emplace_back([i](){
            this_thread::sleep_for(10ms);
            cout<<"name : "<<i<<", thread_ id : "<<this_thread::get_id()<<endl;
        });
    }
    for(auto& t:threads) t.join();
    cout<<endl;
}

/*
// lambda
int main(){
   int n=5;
   // launch a thread with a lambda that capture n by value
   thread t1([n](){  // thread name([argument](){function defination});
      cout<<"name "<<n<<endl;
   });
   t1.join();
   cout<<"end"<<endl;
}

*/

/*
void task(int n){
   cout<<"name "<<n<<endl;
}

int main(){
    thread t1(task,5);
    t1.join();
    cout<<"end"<<endl;
}

*/

/*

// can see the race condition
void task(string name){
    for(int i=0;i<3;i++){
        cout<<name<<" hello " <<i<<endl;
        this_thread::sleep_for(10ms); // can see the interleaving(mixing operation) behaviour using sleep_for() func
        // otherwise t1 thread complete all its operation before t2
    }
}
int main(){
  thread t1(task, "T1");
  thread t2(task, "T2");

  t1.join();
  t2.join();

  cout<<"end"<<endl;
}

*/