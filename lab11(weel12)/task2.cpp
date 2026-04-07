#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class FormatType {
private:
    string font;
    int size;
    string color;

    public:
    FormatType(const string& f, int s, const string& c) : font(f), size(s), color(c) {}

    void print() {
        cout << "Font: " << font << ", Size: " << size << ", Color: " << color << endl;
    }
};

class FormatFactory {
    private:
    static map<string, FormatType*> formats;

    public:
    static FormatType* getFormat(const string& f, int s, const string& c) {
        string key = f + "_" + to_string(s) + "_" + c;

        if (formats.find(key) == formats.end()) {
            formats[key] = new FormatType(f, s, c);
        }

        return formats[key];
    }

    static int getTotalFormats() { return formats.size(); }
};

map<string, FormatType*> FormatFactory::formats;

// Simple character with formatting - stores all properties individually
class FormattedCharacter {
private:
    char character;
    FormatType* format;

public:
    FormattedCharacter(char c, const string& f, int s, const string& col)
        : character(c), format(FormatFactory::getFormat(f, s, col)) {}

    void print() const {
        cout << "Character: " << character << " with properties: ";
        format->print();
    }
};

// Client code - creates formatted text
int main() {
    vector<FormattedCharacter> document;
    // Add characters to our document
    document.emplace_back('H', "Arial", 12, "Red");
    document.emplace_back('e', "Arial", 12, "Red");
    document.emplace_back('l', "Arial", 12, "Red");
    document.emplace_back('l', "Arial", 12, "Red");
    document.emplace_back('o', "Arial", 12, "Red");

    document.emplace_back('_', "Times New Roman", 12, "Black");

    document.emplace_back('W', "Arial", 14, "Blue");
    document.emplace_back('o', "Arial", 14, "Blue");
    document.emplace_back('r', "Arial", 14, "Blue");
    document.emplace_back('l', "Arial", 14, "Blue");
    document.emplace_back('d', "Arial", 14, "Blue");

    document.emplace_back('!', "Arial", 16, "Green");

    // Print all characters
    cout << "Document content:\n";
    for (const auto& fc : document) {
        fc.print();
    }

    // Memory analysis
    cout << "\nMemory Usage Analysis:\n";
    cout << "Total characters: " << document.size() << endl;
    cout << "Unique format objects: " << FormatFactory::getTotalFormats() << endl;
    cout << "Now characters with the same formatting share one FormatType object.\n";
    cout << "This is much more memory-efficient than creating a new format for every character.\n";

    return 0;
}