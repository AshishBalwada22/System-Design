#include<bits/stdc++.h>
using namespace std;

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