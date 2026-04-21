#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};


class TextEditor {
private:
    string text;
    string clipboard;

public:
    void addText(const string& newText) {
        text += newText;
    }

    void replaceText(const string& newText) {
        text = newText;
    }

    string getText() const {
        return text;
    }

    void setClipboard(const string& text) {
        clipboard = text;
    }

    string getClipboard() const {
        return clipboard;
    }
};


class CopyCommand : public Command {
private:
    TextEditor* editor;
    string backup;

public:
    CopyCommand(TextEditor* editor) : editor(editor) {}

    void execute() override {
        backup = editor->getText();
        editor->setClipboard(editor->getText());
        cout << "Copied" << endl;
    }

    void undo() override {
        editor->replaceText(backup);
        cout << "Restored" << endl;
    }
};


class PasteCommand : public Command {
private:
    TextEditor* editor;
    string backup;

public:
    PasteCommand(TextEditor* editor) : editor(editor) {}

    void execute() override {
        backup = editor->getText();

        string currentText = editor->getText();
        string clipboardText = editor->getClipboard();

        if (clipboardText.empty()) {
            cout << "Nothing to paste." << endl;
        } else {
            editor->replaceText(currentText + clipboardText);
            cout << "Pasted" << endl;
        }
    }

    void undo() override {
        editor->replaceText(backup);
        cout << "Restored" << endl;
    }
};

class CommandHistory {
private:
    vector<unique_ptr<Command>> history;


public:
    void push(Command* cmd) {
        history.emplace_back(cmd);
    }

    Command* pop() {
        if (history.empty()) return nullptr;
        auto cmd = history.back().release();
        history.pop_back();
        return cmd;
    }

    bool isEmpty() const {
        return history.empty();
    }
};

int main() {
    TextEditor editor;
    CommandHistory history;

    cout << "Enter text: ";
    string input;
    getline(cin, input);
    editor.addText(input);

    // Assume user wants to copy and then paste
    Command* copy = new CopyCommand(&editor);
    Command* paste = new PasteCommand(&editor);

    copy->execute(); // Copy current text
    paste->execute(); // Paste text
    history.push(copy);
    history.push(paste);

    cout << "Current text: " << editor.getText() << endl;

    // Undo last command
    if (!history.isEmpty()) {
        Command* cmd = history.pop();
        cmd->undo();
        delete cmd;
        cout << "Text after undo: " << editor.getText() << endl;
    }

    // Cleanup remaining commands
    while (!history.isEmpty()) {
        delete history.pop();
    }

    return 0;
}