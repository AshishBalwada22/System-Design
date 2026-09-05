/*
1) SRP (single responsibility principle) - documentEditor class has only one responsibility which is to interact with client and use document and persistence classes to add elements, render and save the document.
Dicate all the services to other classes like document and persistence classes. So it has only one responsibility.
2) OCP (open closed principle) - if we want to add new element like video, we can create a new class videoElement which will implement documentElement interface and override render method.
3) DIP (dependency inversion principle) - documentEditor class is dependent on abstraction like document and persistence classes. Not directly dependent on low level module like file handling.
Principle of least knowledge -> you should always talk to your immediate friend.
*/


#include<bits/stdc++.h>
using namespace std;

// abstract class, render any document element at run time
class documentElement{
    public : 
    virtual string render() = 0;
};

// concrete class for text element
class textElement : public documentElement{
    private:
    string text;
    public:
    textElement(string text){
        this->text = text;
    }
    string render() override{
        return text + "\n";
    }
};

// concrete class for image element
class imageElement : public documentElement{
    private:
    string path;
    public:
    imageElement(string path){
        this->path = path;
    }
    string render() override{
        return "Image = " + path + "\n";
    }
};

// concrete class for new line element
class newLineElement : public documentElement{
    public:
    string render() override{
        return "\n";
    }
};

// document class which will hold all the document elements and render them at run time
// responsible for holding a collection of element
class document{
    private:
    vector<documentElement*> elements;
    public:
    void addElement(documentElement* ele){
        elements.push_back(ele);
    }
    string render(){
        string result = "";
        for(auto ele : elements){
            result+=ele->render();
        }
        return result;
    }
};


class persistence{
    public:
    virtual void save(string data)=0;
};

// fileStorage implementation of persistence
class fileStorage : public persistence{
    public:
    void save(string data) override{
        ofstream out("output.txt");
        if(out.is_open()){
            out<<data;
            out.close();
            cout<<"successfully stored to file"<<endl;
        }else{
            cout<<"file can't be opened to write"<<endl;
        }
    }
};

class dbStorage : public persistence{
    public:
    void save(string data) override{
        //save to db
    }
};

// documentEditor class which will use document and persistence classes to add elements, render and save the document
// documentEditor class is responsible for interaction with client

class documentEditor{
    private:
    document* doc;
    persistence* persist;
    string renderdoc;
    public:
    documentEditor(document* doc, persistence* persist){
        this->doc = doc;
        this->persist = persist;
    }
    void addText(string text){
        doc->addElement(new textElement(text));
    }
    void addImage(string path){
        doc->addElement(new imageElement(path));
    }
    string renderDocument(){
        if(renderdoc.empty()){
            renderdoc = doc->render();
        }
        return renderdoc;
    }
    void saveToPersistance(){
        persist->save(renderDocument());
    }

};


int main(){
    document* doc = new document();
    persistence* persist = new fileStorage();
    documentEditor* editor = new documentEditor(doc,persist);
    editor->addText("Bhagwan ji blesses a pure heart");
    editor->addImage("image.jpg");
    cout<<editor->renderDocument()<<endl;
    editor->saveToPersistance(); 
}