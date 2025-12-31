#include<bits/stdc++.h>
using namespace std;

int counter = 0;

void task(int n){
    for(int i=0;i<n;i++){
        counter++;
        // here increment opertion following three steps - read, increment, write
    }
}
int main(){
  int n=100000;
  thread t1(task,n);
  thread t2(task,n);
  t1.join();
  t2.join();
  cout<<"expected value = "<<2*n<<endl;
  cout<<"actual value = "<<counter<<endl;
}