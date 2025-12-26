// abstract factory design pattern
// it provides an interface for creating families of related or dependent objects without specifying the concrete classes.
// factory pattern creates one type of product(notification), abstract factory creates mulitple product(button, checkbox, theme).

#include<bits/stdc++.h>
using namespace std;

// abstract product interface
class Ibutton{
    public:
    virtual ~Ibutton() = default;
    virtual void render() = 0;
};

// abstract product interface
class Icheckbox{
    public:
    virtual ~Icheckbox() = default;
    virtual void render() = 0;
};

// concrete or product classes

class Lightbutton : public Ibutton{
    public:
    void render() override{
        cout<<"rendering light button"<<endl;
    }
};

class DarkButton : public Ibutton{
    public:
    void render() override{
        cout<<"rendering dark button"<<endl;
    }
};

class Lightcheckbox : public Icheckbox{
    public:
    void render() override{
        cout<<"rendering light checkbox"<<endl;
    }
};

class Darkcheckbox : public Icheckbox{
    public:
    void render() override{
        cout<<"rendering dark checkbox"<<endl;
    }
};

class IUIFactory{
    public:
    virtual ~IUIFactory() = default;
    virtual unique_ptr<Ibutton> createButton() = 0;
    virtual unique_ptr<Icheckbox> createCheckbox() = 0;
};

class LightThemeFactory : public IUIFactory{
    public:
    unique_ptr<Ibutton> createButton() override{
        return make_unique<Lightbutton>();
    }
    unique_ptr<Icheckbox> createCheckbox() override{
        return make_unique<Lightcheckbox>();
    }
};

class DarkThemeFactory : public IUIFactory{
    public:
    unique_ptr<Ibutton> createButton() override{
        return make_unique<DarkButton>();
    }
    unique_ptr<Icheckbox> createCheckbox() override{
        return make_unique<Darkcheckbox>();
    }
};

int main(){
    bool darktheme = true;
    unique_ptr<IUIFactory> UiObject;
    if(darktheme)
    UiObject = make_unique<DarkThemeFactory>();
    else 
    UiObject = make_unique<LightThemeFactory>();
    unique_ptr<Ibutton> buttonObj = UiObject->createButton();
    unique_ptr<Icheckbox> checkboxObj = UiObject->createCheckbox();
    buttonObj->render();
    checkboxObj->render();
}