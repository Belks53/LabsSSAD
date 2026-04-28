#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Memento: holds editor state
class Memento {
public:
    Memento(const string& state) : state(state) {}

    string getState() const {
        return state;
    }

private:
    string state;
};

// Originator: the text editor
class TextEditor {
public:
    TextEditor() : text("") {}

    void appendText(const string& newText) {
        text += newText;
    }

    string getText() const {
        return text;
    }

    Memento save() const {
        return Memento(text);
    }

    void restore(const Memento& memento) {
        text = memento.getState();
    }

private:
    string text;
};

// Caretaker: manages undo/redo stacks
class UndoRedoManager {
public:
    UndoRedoManager() {}

    void saveState(TextEditor& editor) {
        undoStack.push(editor.save());

        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo(TextEditor& editor) {
        if (undoStack.size() <= 1) {
            return;
        }

        Memento currentState = undoStack.top();
        undoStack.pop();

        redoStack.push(currentState);

        Memento previousState = undoStack.top();
        editor.restore(previousState);
    }

    void redo(TextEditor& editor) {
        if (redoStack.empty()) {
            return;
        }

        Memento nextState = redoStack.top();
        redoStack.pop();

        undoStack.push(nextState);
        editor.restore(nextState);
    }

private:
    stack<Memento> undoStack;
    stack<Memento> redoStack;
};

int main() {
    TextEditor editor;
    UndoRedoManager undoRedoManager;

    // Initial text
    cout << "Initial text: " << editor.getText() << endl;

    // Append some text and save state
    editor.appendText("Hello");
    undoRedoManager.saveState(editor);
    cout << "After appending 'Hello': " << editor.getText() << endl;

    // Append more text and save state
    editor.appendText(" World");
    undoRedoManager.saveState(editor);
    cout << "After appending ' World': " << editor.getText() << endl;

    // Undo and show state
    undoRedoManager.undo(editor);
    cout << "After undoing: " << editor.getText() << endl;

    // Redo and show state
    undoRedoManager.redo(editor);
    cout << "After redoing: " << editor.getText() << endl;

    return 0;
}