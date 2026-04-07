#include <iostream>
#include <string>

using namespace std;


class Logger {
private:
    static Logger* instance;
    Logger() {}

public:
    static Logger& getInstance() {
        if (instance == nullptr)
        {
            instance = new Logger();
        }
        return *instance;
    }

    void log(const string& message) {
        cout << "[LOG] " << message << endl;
    }
};

Logger* Logger::instance = nullptr;
class Document;

class DocumentState {
public:
    virtual void handleInput(Document& doc, const string& input) = 0;
    virtual string getName() const = 0;
    virtual ~DocumentState() {}
};

class DraftState : public DocumentState {
public:
    void handleInput(Document& doc, const string& input) override;
    string getName() const override
    {
        return "Draft";
    }
};

class ReviewState : public DocumentState {
public:
    void handleInput(Document& doc, const string& input) override;
    string getName() const override {
        return "Review";
    }
};

class FinalState : public DocumentState {
public:
    void handleInput(Document& doc, const string& input) override;
    string getName() const override {
        return "Final";
    }
};

class Document {
private:
    string content;
    DocumentState* state;

public:
    Document(DocumentState* initialState) {
        state = initialState;
        content = "";
        Logger::getInstance().log("Document created in state: " + state->getName());
    }

    void appendContent(const string& text) {
        content += text + "\n";
    }

    void changeState(DocumentState* newState) {
        Logger::getInstance().log("State changed from " + state->getName() + " to " + newState->getName());
        state = newState;
    }

    void handleInput(const string& input) {
        state->handleInput(*this, input);
    }

    void print() const {
        cout << "\n--- Document content ---" << endl;
        cout << content;

    }
};


void DraftState::handleInput(Document& doc, const string& input) {
    Logger::getInstance().log("Draft state: text added");
    doc.appendContent(input);
}

void ReviewState::handleInput(Document& doc, const string& input) {
    Logger::getInstance().log("Review state: reviewed text added");
    doc.appendContent("[REVIEW] " + input);
}

void FinalState::handleInput(Document& doc, const string& input)
{
    Logger::getInstance().log("Final state: editing is not allowed. Input ignored: " + input);
}

class DocumentPrototype {
public:
    virtual DocumentPrototype* clone() const = 0;
    virtual void printInfo() const = 0;
    virtual ~DocumentPrototype() {}
};

class ReportType : public DocumentPrototype {
private:
    string title;
    string format;

public:
    ReportType(string t = "Default Report", string f = "A4") {
        title = t;
        format = f;
    }

    DocumentPrototype* clone() const override {
        Logger::getInstance().log("ReportType prototype cloned");
        return new ReportType(*this);
    }

    void printInfo() const override {
        cout << "ReportType -> title: " << title << ", format: " << format << endl;
    }
};

class InvoiceType : public DocumentPrototype {
private:
    string company;
    string currency;

public:
    InvoiceType(string c = "Default Company", string cur = "USD") {
        company = c;
        currency = cur;
    }

    DocumentPrototype* clone() const override {
        Logger::getInstance().log("InvoiceType prototype cloned");
        return new InvoiceType(*this);
    }

    void printInfo() const override {
        cout << "InvoiceType -> company: " << company << ", currency: " << currency << endl;
    }
};

int main() {
    Logger::getInstance().log("Program started");

    ReportType reportPrototype("Annual Report", "A4");
    InvoiceType invoicePrototype("Tech Corp", "EUR");

    DocumentPrototype* reportCopy = reportPrototype.clone();
    DocumentPrototype* invoiceCopy = invoicePrototype.clone();

    cout << "\nPrototype objects:" << endl;
    reportPrototype.printInfo();
    invoicePrototype.printInfo();

    cout << "\nCloned objects:" << endl;
    reportCopy->printInfo();
    invoiceCopy->printInfo();

    // state demo
    DraftState draftState;
    ReviewState reviewState;
    FinalState finalState;

    Document doc(&draftState);

    doc.handleInput("This is the first draft paragraph.");
    doc.handleInput("This is the second draft paragraph.");

    doc.changeState(&reviewState);
    doc.handleInput("This paragraph was checked by reviewer.");

    doc.changeState(&finalState);
    doc.handleInput("Trying to edit final document.");

    doc.print();

    delete reportCopy;
    delete invoiceCopy;

    Logger::getInstance().log("Program finished");

    return 0;
}
