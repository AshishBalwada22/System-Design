1) class 
user defined data type that define what object will contain, what object will do

2) access modifier

access modifier         same class         derived class        outside class
private                    yes                 no                    no
public                     yes                 yes                   yes
protected                  yes                 yes                   no

3) can you initialize private data member outside the class?
- using getter and setter
- using constructor

4) copy constructor
copy constructor used to copy the object
syntax -  class_name(const class_name& obj){ }

example -
demo(const demo& d3){
    x = d3.x;
}

main(){
    demo d1(10);
    demo d2 = d1; // call the copy constructor or demo d2(d1)
}

- why we used reference while defining the copy constructor?
if we use demo(demo d3) , then when demo d2 = d1 hit the line, it call the copy constructor demo(demo d3)
then demo(demo d3) -> need to copy the d3 which call demo(demo d3) copy constructor again to copy -> it will go infinetly loop
so we should pass by reference instead of pass by value


------------------------------------------------------------------------------------------
this pointer
- pointer to current object
- use for non-static member function

1) resolve name conflict

class student{
    private:
    string name;
    int age;
    public:
    student(string name, int age){
        this->name = name;
        this->age = age;
    }
    void display(){
        cout<<name<<" "<<age<<endl;
    }
};

int main(){
    student obj("Ashish",27);
    obj.display();
}

2) returning the current object (function chaining)

class counter{
    private:
    int count;
    public:
    counter(){
        count = 0;
    }
    counter& increment(){
        count++;
        return *this; // return current object
    }
    void display(){
        cout<<"count = "<<count<<endl;
    }
};

int main(){
    counter c1;
    c1.increment().increment().display(); // function chaining
}

-------------------------------------------------------------------------------------
static keyword
- member that below to class rather than individual object
- static data member is shared data member amoung all objects

// if we want to find the number of object created, then we can use static data member
class student{
    private:
    string name;
    public:
    static int count; // static data member
    student(string name){
        this->name = name;
        count++;
        //this->count++; // static data member can be called by this pointer or by class name
    }
    void display(){
        cout<<"name = "<<name<<endl;
    }
    // static member function can access only static data member and function
    // static member function can be called using class name
    
    static void show(){ // static member function
        cout<<"number of object created = "<<count<<endl;
    }
    // static member can only access static data member
    /*
    static void show2(){
        cout<<name<<endl; // error: cannot access non-static data member
    }
    */
};

int student::count = 0; // definition of static data member

int main(){
    student s1("Ashish");
    student s2("Satyam");
    student s3("Rahul");
    s1.display();
    s2.display();
    s3.display();
    student::count++;
    student::show();
}

------------------------------------------------------------------------------------

const keyword

1) constant variable
- value cannot be changed after initialization
const int x = 10; // constant variable
x++; // error: cannot modify a constant variable

2) constant member object
- object that cannot modify the data member of the class
- only allow to call constant member function

class student{
    private:
    string name;
    public:
    student(string name){   
        this->name = name;
    }
    void display(){
        cout<<"name = "<<name<<endl;
    }
};

int main(){
    const student s1("Ashish"); // constant member object
    s1.display();
    //s1.name = "Satyam"; // error: cannot modify a constant member object
}

3) constant member variable
- member variable that cannot be modified after initialization
class student{
    private:
    const string name; // constant member variable
    public:
    student(string name){   
        this->name = name; // error: cannot modify a constant member variable
    }
    void display(){         
        cout<<"name = "<<name<<endl;
    }
};

then how to assigned value to constant member variable?
- using initializer list in constructor
class student{
    private:
    const string name; // constant member variable
    public:
    student(string name) : name(name){ // using initializer list to assign value to constant member variable
    }
    void display(){         
        cout<<"name = "<<name<<endl;
    }
};

4) constant member function
- member function that cannot modify the data member of the class   
class student{
    private:
    string name;
    public:
    student(string name){   
        this->name = name;
    }
    void display() const{ // constant member function
        cout<<"name = "<<name<<endl;
        // name = "Satyam"; // error: cannot modify a data member in constant member function
    }
};

5) const reference variable
- reference variable that cannot modify the value of the variable it refer to
int main(){
    int x = 10;
    const int &y = x; // const reference variable
    //y++; // error: cannot modify a const reference variable

what is const correctness?
use const whenever modification is not required

-----------------------------------------------------------------------------------
new and delete keyword

class student{
    private:
    string name;
    public:
    student(string name){
        this->name = name;
        cout<<"constructor called"<<endl;
    }
    void display(){
        cout<<"name = "<<name<<endl;
    }
    ~student(){
        cout<<"destructor called"<<endl;
    }
};

int main(){
    student* s1 = new student("Ashish");
    s1->display();
    delete s1;  
}

what is the difference between stack and heap memory allocation?
stack memory allocation is done at compile time, automatically deallocated memory when object goes out of scope
heap memory allocation is done at runtime, manually deallocated using delete operator
new used to allocate memory on heap and return pointer to the allocated memory

-----------------------------------------------------------------------------------
Abstract class
- with atleast one pure virtual function
- cannot create object of abstract class

class payment{
    protected:
    double amount;
    public: 
    payment(double amount){
        this->amount = amount;
    }
    virtual void pay() = 0; // pure virtual function    
};

class upipayment : public payment{
    private:
    string id;
    public:
    upipayment(double amount, string id) : payment(amount){
        this->id = id;
    }
    void pay(){
        cout<<amount<<" "<<id<<endl;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------
Inheritance
1) multiple inheritance
- derived class can inherit from multiple base class
- java does not support multiple inheritance
i.e printer,scanner -> smart pointer
i.e sms(send), email(send) -> push_notification(send)

- use scope resolution operator to call the function, object.class_name::function_name()

--------------------------------------------------------------------------------------------------------------------------------------------------
constructor

1) copy constructor
- to create new object from existing object
i.e student s2=s1;
    student s3(s2);

class_name(const class_name& obj){
    // copy data members from obj to current object
}  
- if not use &, then infinite recursion will occur, because copy constructor will be called again and again to copy the object

---------------------------------------------------------------------------------------------------------------------------------------------------
shallow copy and deep copy
1) shallow copy
- address get copied

class student{
    private:
    char* name;
    public:
    student(char* n){
        name = new char[strlen(n)+1];
        strcpy(name,n);
    }
    void display(){
        cout<<name<<endl;
    }
    ~student(){
        delete[] name;
    }
};

int main(){
    student s1("Ashish");
    student s2 = s1; // shallow copy, address get copied
    s1.display();
    s1.name[0]='B';
    s2.display(); // Bshish, because both s1 and s2 point to same address, this happens only when we use pointer(we allocate memory using new keyword dynamically))
}


- change in one object will affect the other object
- double delete problem
- undefined behavior


2) Deep copy
- allocate new memory and copy the value from one object to another -> for this we define custom copy constructor

class student{
    private:
    char* name;
    public:
    student(char* n){
        name = new char[strlen(n)+1];
        strcpy(name,n);
    }
    student(const student& s){
        name = new char[strlen(s.name)+1];
        strcpy(name,s.name);
        cout<<"deep copy constructor called"<<endl;
    }
    void display(){
        cout<<name<<endl;
    }
    ~student(){
        delete[] name;
    }
};

int main(){
    student s1("Ashish");
    student s2 = s1; // deep copy, new memory get allocated and value get copied
    s1.display();
    s1.name[0]='B';
    s2.display(); // Ashish, because both s1 and s2 point to different address
}

- we write custom copy constructor to do deep copy

------------------------------------------------------------------------------------------------------------------------------------------------
copy constructor vs assignment operator
1) copy constructor
student s2 = s1; // copy constructor called , while creating new object 

2) assignment operator
student s2;
s2 = s1; // assignment operator called, when we assign value to existing object

-------------------------------------------------------------------------------------------------------------------------------------------------
constructor member intializer list
- student(string n) : name(n){} // here don't need to make copy, directly assignment

student(string n){
    name = n; // first we make copy and then assignment
}

- we need intializer list when we use const key because we cannot assign value to const variable after initialization

order of initialization 
- depend upon data member define in a class

--------------------------------------------------------------------------------------------------------------------------------------------------

Rule of 3
- if we do manually resource management in case of raw pointer, then we need to define destructor, copy constructor and copy assignment operator.
if we need any one of them, then we need to define all three of them otherwise we will get shallow copy and double delete problem

Rule of 5
- if we do manually resource management in case of raw pointer, then we need to define destructor, copy constructor, copy assignment operator, move constructor and move assignment operator.
if we need any one of them, then we need to define all five of them otherwise we will get shallow copy and double delete problem    

Rule of 0 - modern c++
- vector, string, smart pointer manage the resource automatically

-----------------------------------------------------------------------------------
Encapsulation
- binding data and function together in a single unit called class
- restrict direct access to data member

-----------------------------------------------------------------------------------






