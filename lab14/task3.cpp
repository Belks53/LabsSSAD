#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

using namespace std;

class File {
public:
    string path;
    File(const string& path) : path(path) {}
};

class EventListener {
public:
    virtual ~EventListener() = default;
    virtual void update(const string& eventType, const File& file) = 0;
};

class EventManager {
private:
    map<string, vector<shared_ptr<EventListener>>> listeners;

public:
    EventManager(const vector<string>& operations) {
        for (const auto& op : operations) {
            listeners[op] = {};
        }
    }

    void subscribe(const string& eventType, shared_ptr<EventListener> listener) {
        listeners[eventType].push_back(listener);
    }

    void unsubscribe(const string& eventType, shared_ptr<EventListener> listener) {
        auto& vec = listeners[eventType];
        vec.erase(remove(vec.begin(), vec.end(), listener), vec.end());
    }

    void notify(const string& eventType, const File& file) {
        for (auto& listener : listeners[eventType]) {
            listener->update(eventType, file);
        }
    }
};

class Editor {
public:
    unique_ptr<EventManager> events;
    unique_ptr<File> file;

    Editor() {
        events = make_unique<EventManager>(
            vector<string>{"open", "save"}
        );
    }

    void openFile(const string& filePath) {
        file = make_unique<File>(filePath);
        cout << "Opening file: " << filePath << endl;
        events->notify("open", *file);
    }

    void saveFile() {
        if (!file) {
            cerr << "No file is open!" << endl;
            return;
        }
        cout << "Saving file: " << file->path << endl;
        events->notify("save", *file);
    }
};

// Concrete Listener 1
class LoggingListener : public EventListener {
public:
    void update(const string& eventType, const File& file) override {
        cout << "[LOG] Event: " << eventType
             << " | File: " << file.path << endl;
    }
};

// Concrete Listener 2
class EmailNotificationListener : public EventListener {
private:
    string email;

public:
    EmailNotificationListener(const string& email) : email(email) {}

    void update(const string& eventType, const File& file) override {
        cout << "[EMAIL to " << email << "] "
             << "Someone performed '" << eventType
             << "' on file: " << file.path << endl;
    }
};

int main() {
    auto editor = make_unique<Editor>();

    auto logger = make_shared<LoggingListener>();
    auto emailer = make_shared<EmailNotificationListener>("admin@example.com");

    editor->events->subscribe("open", logger);
    editor->events->subscribe("save", logger);
    editor->events->subscribe("save", emailer);

    editor->openFile("test.txt");
    editor->saveFile();

    return 0;
}