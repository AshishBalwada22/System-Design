/*
promise and future
- promise and future provide a safe and efficient way to transfer a single result between different threads without needing explicitly locks or shared memory.
- promise set the value, future retrieve the value
- taken care of mutex + shared_variable

async (task based concurrency)
- combination of thread, promise and future
- return future object and manages threading details
*/

/*
// without future and promise
// mutex + shared variable 
#include<bits/stdc++.h>
using namespace std;

int result = 0; //shared variable
mutex m;

void compute(){
    int r = 22*22;
    lock_guard<mutex> obj(m); // to prevent from race condition
    result = r;
}

int main(){
    thread t(compute);
    t.join(); // wait for thread to finish its execution
    cout<<"result : "<<result<<endl;
}
*/

/*
// with promise and future
#include<bits/stdc++.h>
using namespace std;

void compute(promise<int>p){
    int r = 22*22;
    p.set_value(r); // set the result into the promise
}

int main(){
    promise<int>p;  // create a promise object that store int value
    future<int>f = p.get_future(); // get a future object from the promise
    thread t(compute,move(p)); // as promise is not a copyable, so movable only
    int result = f.get(); // block until promise set the value, once the value is set, future retrieves the value
    cout<<"result : "<<result<<endl;
    t.join(); // waiting for thead t to be finished
    cout<<"main end here"<<endl;
}
*/

//async (task based concurrency)
#include<bits/stdc++.h>
using namespace std;

int compute(){
    return 22*22;
}
int main(){
    future<int> f = async(launch::async,compute); // return future object, also handle promise internally
    cout<<"result : "<<f.get()<<endl;
}