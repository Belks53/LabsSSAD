#include <iostream>
#include <string>

using namespace std;

class Document {
private:
    string header;
    string body;
    string footer;

public:
    void setHeader(const string& h) {
        header = h;
    }

    void setBody(const string& b) {
        body = b;
    }

    void setFooter(const string& f) {
        footer = f;
    }

    void print() const {
        cout << "\n--- Document ---" << endl;
        cout << "Header: " << header << endl;
        cout << "Body: " << body << endl;
        cout << "Footer: " << footer << endl;
        cout << "----------------" << endl;
    }
};

class DocumentBuilder {
public:
    virtual void buildHeader() = 0;
    virtual void buildBody() = 0;
    virtual void buildFooter() = 0;
    virtual Document* getDocument() = 0;
    virtual ~DocumentBuilder() {}
};


class ReportBuilder : public DocumentBuilder {
private:
    Document* doc;

public:
    ReportBuilder() {
        doc = new Document();
    }

    void buildHeader() override {
        doc->setHeader("=== Report Header ===");
    }

    void buildBody() override {
        doc->setBody("This is the main body of the report.");
    }

    void buildFooter() override {
        doc->setFooter("=== Report Footer ===");
    }

    Document* getDocument() override {
        return doc;
    }
};


class Director {
public:
    void make(DocumentBuilder& builder)
    {
        builder.buildHeader();
        builder.buildBody();
        builder.buildFooter();
    }
};


int main() {
    Director director;
    ReportBuilder builder;

    director.make(builder);

    Document* report = builder.getDocument();
    report->print();

    delete report;

    return 0;
}
