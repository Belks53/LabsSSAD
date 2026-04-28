#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Memento: holds editor state
class Memento {
public:
    Memento(const string& state);
    string getState() const;

private:
    string state;
};

// Originator: the text editor
class TextEditor {
public:
    TextEditor();
    void appendText(const string& newText);
    string getText() const;

    Memento save() const;
    void restore(const Memento& memento);

private:
    string text;
};

// Caretaker: manages undo/redo stacks
class UndoRedoManager {
public:
    UndoRedoManager();

    void saveState(TextEditor& editor);
    void undo(TextEditor& editor);
    void redo(TextEditor& editor);

private:
    stack<Memento> undoStack;
    stack<Memento> redoStack;
};

// Memento methods
Memento::Memento(const string& state) {
    this->state = state;
}

string Memento::getState() const {
    return state;
}

// TextEditor methods
TextEditor::TextEditor() {
    text = "";
}

void TextEditor::appendText(const string& newText) {
    text += newText;
}

string TextEditor::getText() const {
    return text;
}

Memento TextEditor::save() const {
    return Memento(text);
}

void TextEditor::restore(const Memento& memento) {
    text = memento.getState();
}

// UndoRedoManager methods
UndoRedoManager::UndoRedoManager() {}

void UndoRedoManager::saveState(TextEditor& editor) {
    undoStack.push(editor.save());

    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void UndoRedoManager::undo(TextEditor& editor) {
    if (undoStack.size() <= 1) {
        return;
    }

    Memento currentState = undoStack.top();
    undoStack.pop();

    redoStack.push(currentState);

    Memento previousState = undoStack.top();
    editor.restore(previousState);
}

void UndoRedoManager::redo(TextEditor& editor) {
    if (redoStack.empty()) {
        return;
    }

    Memento nextState = redoStack.top();
    redoStack.pop();

    undoStack.push(nextState);
    editor.restore(nextState);
}

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