#include <iostream>

using namespace std;

// Abstract Product A
class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() {}
};

// Abstract Product B
class Checkbox {
public:
    virtual void paint() = 0;
    virtual ~Checkbox() {}
};

// Concrete Product A1
class WinButton : public Button {
public:
    void paint() override {
        cout << "Windows button created" << endl;
    }
};

// Concrete Product B1
class WinCheckbox : public Checkbox {
public:
    void paint() override {
        cout << "Windows checkbox created" << endl;
    }
};

// Concrete Product A2
class MacButton : public Button {
public:
    void paint() override {
        cout << "Mac button created" << endl;
    }
};

// Concrete Product B2
class MacCheckbox : public Checkbox {
public:
    void paint() override {
        cout << "Mac checkbox created" << endl;
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factory 1
class WinFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WinButton();
    }

    Checkbox* createCheckbox() override {
        return new WinCheckbox();
    }
};

// Concrete Factory 2
class MacFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new MacButton();
    }

    Checkbox* createCheckbox() override {
        return new MacCheckbox();
    }
};

// Client code
class Application {
private:
    GUIFactory* factory;
    Button* button;
    Checkbox* checkbox;

public:
    Application(GUIFactory* factory) {
        this->factory = factory;
        button = nullptr;
        checkbox = nullptr;
    }

    void createUI() {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void paint() {
        button->paint();
        checkbox->paint();
    }

    ~Application() {
        delete button;
        delete checkbox;
    }
};

int main() {
    GUIFactory* factory = new WinFactory();

    Application app(factory);
    app.createUI();
    app.paint();

    delete factory;

    return 0;
}