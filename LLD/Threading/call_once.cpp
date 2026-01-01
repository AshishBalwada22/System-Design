// call_once -> execute function only once, no matter how many threads calling that function concurrently
// call_once for one-time init

#include<bits/stdc++.h>
using namespace std;

class config{
    public:
    int value;
};

void init(){
    config *p = new config();
    p->value = 6;
    cout<<"Initialization done"<<endl; 
}

once_flag flag;

void task(int n){
   call_once(flag, init);
   cout<<"thread = "<<n<<endl;
}
int main(){
    vector<thread> threads;
    for(int i=0;i<6;i++){
        threads.emplace_back(task,i);
    }
    for(auto& t:threads) t.join();
    cout<<"main thread end here"<<endl;
}