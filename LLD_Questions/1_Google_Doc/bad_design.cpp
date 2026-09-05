// we will follow bottom up approach

// we have class document editor
/*
1) violate SRP (single responsibility principle) - documentEditor class has addText, addImage, renderDocument, saveToFile methods. So it has multiple responsibilities.
2) violate OCP (open closed principle) - if we want to add new element like video, we have to modify the renderDocument method. So it is not open for extension and closed for modification.
3) violate DIP (dependency inversion principle) - documentEditor class is dependent on low level module like file handling. So it is not following dependency inversion principle.
*/

#include<bits/stdc++.h>
using namespace std;

class documentEditor{
    private:
    vector<string> elements; // element can be text, image, video, newline, tab space
    string renderdoc;
    public:
    void addText(string text){
        elements.push_back(text);
    }
    void addImage(string path){
        elements.push_back(path);
    }
    string renderDocument(){
        if(renderdoc.empty()){
            string result = "";
            for(auto str:elements){
                if(str.length()>4 && (str.substr(str.length()-4) == ".jpg" || str.substr(str.length()-4) == ".png")){
                    result+="Image = " + str + "\n";
                }else{
                    result+=str + "\n";
                }
            }
            renderdoc = result;
        }
        return renderdoc;
    }

    void saveToFile(){
        ofstream file("output.txt");
        if(file.is_open()){
            file<<renderDocument();
            file.close();
            cout<<"successfully save to file"<<endl;
        }else{
            cout<<"file can't be open to write"<<endl;
        }
    }
};

int main(){
    documentEditor obj;
    obj.addText("Bhagwan ji blesses a pure heart");
    obj.addImage("image.jpg");
    cout<<obj.renderDocument()<<endl;
    obj.saveToFile();
}