#include<bits/stdc++.h>
using namespace std;

void counter(int &x){
    x++;
}

int main(){
    int cnt=0;
    // thread t(counter,cnt); // pass by value
    //thread t(counter,ref(cnt)); //pass by reference
    thread t([&](){ // & for reference , = for by value 
         cnt++;
    });
    t.join();
    cout<<"cnt = "<<cnt<<endl;
    cout<<"ends here"<<endl;
}