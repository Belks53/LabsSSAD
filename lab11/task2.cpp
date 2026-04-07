#include <iostream>
#include <string>

using namespace std;

class Text {
public:
    virtual void write() = 0;
    virtual ~Text() {}
};

class PlainText : public Text {
private:
    string content;

public:
    PlainText(const string& text) : content(text) {}

    void write() override {
        cout << content;
    }
};

class TextDecorator : public Text {
protected:
    Text* wrappedText;

public:
    TextDecorator(Text* text) : wrappedText(text) {}

    virtual ~TextDecorator() {}
};

class Bold : public TextDecorator {
public:
    Bold(Text* text) : TextDecorator(text) {}

    void write() override {
        cout << "\033[1m";
        wrappedText->write();
        cout << "\033[0m";
    }
};

class Italic : public TextDecorator {
public:
    Italic(Text* text) : TextDecorator(text) {}

    void write() override {
        cout << "\033[3m";
        wrappedText->write();
        cout << "\033[0m";
    }
};

class Underline : public TextDecorator {
public:
    Underline(Text* text) : TextDecorator(text) {}

    void write() override {
        cout << "\033[4m";
        wrappedText->write();
        cout << "\033[0m";
    }
};

int main() {
    Text* text1 = new PlainText("Hello, world!");
    Text* text2 = new Bold(text1);
    Text* text3 = new Italic(text2);
    Text* text4 = new Underline(text3);

    cout << "Styled text: ";
    text4->write();
    cout << endl;

    delete text4;
    delete text3;
    delete text2;
    delete text1;

    return 0;
}