#include<bits/stdc++.h>
using namespace std;

int counter = 0;

void task(int n){
    for(int i=0;i<n;i++){
        counter++;
        // Increment a counter involves multiple steps at lower level (i.e assembly code)
        // read, increment, write
        // current value of counter is loaded into register
        // value in the register is incremented
        // value from register written back to counter
        // if multiple thread trying to execute counter++ concurrently, their operations can interleave  
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