#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void display(const string& indent = "") const = 0;
    virtual string getName() const = 0;
};

class File: public FileSystemComponent {
private:
    string name;

public:
    File(string name) : name(name) {}

    void display(const string& indent = "") const override {
        cout << indent << "File: " << name << endl;
    }

    string getName() const override {
        return name;
    }
};

class Directory: public FileSystemComponent {
private:
    string name;
    vector<FileSystemComponent*> components;

public:
    Directory(string name) : name(name) {}

    ~Directory() {
        for (auto component : components) {
            delete component;
        }
    }

    void addComponent(FileSystemComponent* component) {
        components.push_back(component);
    }

    void display(const string& indent = "") const override {
        cout << indent << "Directory: " << name << endl;

        string newIndent = indent + "  ";
        for (const auto& component : components) {
            component->display(newIndent);
        }
    }

    string getName() const override {
        return name;
    }
};

int main()
{
    Directory* root = new Directory("Root");
    File* file1 = new File("File1.txt");
    File* file2 = new File("File2.txt");
    Directory* dir1 = new Directory("Dir1");
    File* file3 = new File("File3.txt");
    File* file4 = new File("File4.txt");
    Directory* dir2 = new Directory("Dir2");

    root->addComponent(file1);
    root->addComponent(file2);
    root->addComponent(dir1);
    dir1->addComponent(file3);
    dir1->addComponent(file4);
    dir1->addComponent(dir2);

    root->display();

    delete root;
    return 0;
}

// EXAMPLE OUTPUT:
// Directory: Root
// File: File1.txt
// File: File2.txt
// Directory: Dir1
// File: File3.txt
// File: File4.txt
// Directory: Dir2