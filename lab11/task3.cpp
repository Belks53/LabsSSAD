#include <iostream>
#include <string>

using namespace std;

class Document {
public:
    virtual void display() = 0;
    virtual ~Document() {}
};

class RealDocument : public Document {
private:
    string content;

public:
    RealDocument(const string& text) : content(text) {}

    void display() override {
        cout << "Document content: " << content << endl;
    }
};

class SecureDocumentProxy : public Document {
private:
    RealDocument* realDocument;
    string userRole;

public:
    SecureDocumentProxy(const string& content, const string& role) {
        realDocument = new RealDocument(content);
        userRole = role;
    }

    void display() override {
        if (userRole == "admin" || userRole == "manager") {
            cout << "Access granted for role: " << userRole << endl;
            realDocument->display();
        } else {
            cout << "Access denied for role: " << userRole << endl;
        }
    }

    ~SecureDocumentProxy() {
        delete realDocument;
    }
};

int main() {
    SecureDocumentProxy doc1("Top secret financial report", "admin");
    SecureDocumentProxy doc2("Top secret financial report", "manager");
    SecureDocumentProxy doc3("Top secret financial report", "guest");

    cout << "\nAdmin tries to open document:" << endl;
    doc1.display();

    cout << "\nManager tries to open document:" << endl;
    doc2.display();

    cout << "\nGuest tries to open document:" << endl;
    doc3.display();

    return 0;
}