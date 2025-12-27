// singelton design pattern
// ensure exactly one instance of class exists, and provide a global access point to it.
// can become a god object, too many responsibilites -> leads to violate SRP
// Hide the concrete singleton behind an interface and let dependency injection framework inject it.


#include<bits/stdc++.h>
using namespace std;
/*
class Logger{
    private : 
    Logger() = default; //prevent direct instantiation from outside.
    Logger(const Logger&) = delete; // prevent creating copies of singleton instance.
    Logger& operator=(const Logger&) = delete; // prevent assigning of singleton instance to another.

    public:
    static Logger& getInstance(){
        static Logger instance; // ensure thread safe in c++11
        return instance;
    }

    void info(string message){
        cout<<"message = "<<message<<endl;
    }
};

int main(){
    Logger::getInstance().info("welcome to singleton design pattern");
}

*/


// Hide the concrete singleton behind an interface and let dependency injection framework inject it.

class ILogger{
    public:
    virtual ~ILogger() = default;
    virtual void info(string message) = 0;
};

class Logger: public ILogger{
    private : 
    Logger() = default; //prevent direct instantiation from outside.
    Logger(const Logger&) = delete; // prevent creating copies of singleton instance.
    Logger& operator=(const Logger&) = delete; // prevent assigning of singleton instance to another.

    public:
    static Logger& getInstance(){
        static Logger instance; // ensure thread safe in c++11
        return instance;
    }

    void info(string message) override{
        cout<<"message = "<<message<<endl;
    }
};

class LoggingService{
    private : 
    ILogger& logger;
    public :
    LoggingService(ILogger& loginstance){
        logger = loginstance;
    }
    void service(const string& message){
        logger.info(message);
    }
};

int main(){
    ILogger& loggerobj = Logger::getInstance();
    LoggingService log(loggerobj);
    log.service("welcome to singleton design pattern using interface");
}