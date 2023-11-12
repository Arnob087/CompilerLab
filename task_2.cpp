
#include <iostream>
#include <fstream>

using namespace std;

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isalnum(char c) {
    return isAlpha(c) || isDigit(c);
}

bool isOperator(char ch) {
    char operators[14] = {
        '-', '+', '*', '/', '%', '=',
        '>', '<',
        '!', '?',
        '&', '^', '|', '~'
    };

    for (char i : operators) {
        if (ch == i) {
            return true;
        }
    }
    return false;
}

bool isKeyword(const string& token) {
    string keywords[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while","using","namespace","endl"
    };

    for (const string a : keywords) {
        if (token == a) {
            return true;
        }
    }

    return false;
}

bool isValidIdentifier(const string str) {
    if (str.empty() || !(isAlpha(str[0]) || str[0] == '_')) {
        return false;
    }

   for (char c : str) {
        if (!(isalnum(c) || c == '_')) {
            return false;
        }
    }

    return true;
}

bool isDelimiter(char ch) {
    char delimiters[9] = {
        '(', ')',
        '.',
        ':', ';',
        '[', ']',
        '{', '}'
    };

    for (char i : delimiters) {
        if (ch == i) {
            return true;
        }
    }

    return false;
}

bool isStringLiteral(const string line) {
    bool inString = false;
    string content;

    for (char c : line) {
        if (c == '"') {
            inString = !inString;
            if (!inString) {
                cout << "Found a string literal: " << content << endl;
                content.clear();
            }
        }
        if (inString) {
            content += c;
        }
    }

    return inString;
}

void processStringLiterals(const string line, int& i) {
    bool inString = false;
    string content;

    for (; i < line.length(); i++) {
        char c = line[i];

        if (c == '"') {
            if (inString) {

                cout << "    -string literal: " << content << endl;
                content.clear();
            } else {

                inString = true;
            }
        } else if (inString) {

            content += c;
        }
    }

    if (inString) {

    } else {

        i++;
    }
}

int startCharType(char ch) {
    if (isDigit(ch)) {
        return 1;
    } else if (isAlpha(ch) || ch == '_') {
        return 2;
    } else if (isOperator(ch)) {
        return 4;
    } else if (isDelimiter(ch)) {
        return 3;
    } else if (ch == '"') {
        return 5; // String literal
    }
}
void processCodeBlock(ifstream& inputFile) {
    string line;
    bool inCodeBlock = false;

    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (!inCodeBlock) {
            cout << "Line: " << line << endl;
            if (line.find('#') == 0) {
                cout << "  Found a preprocessor directive: " << line << endl;
            } else {
                cout << "  Syntactical error: " << line << endl;
            }
        } else {
            cout << "Line: " << line << endl;
            string token = "";
            int i = 0;

            while (i < line.length()) {
                char ch = line[i];
                int type = startCharType(ch);

                while (i < line.length() && type == 2) { // It's an identifier or a keyword
                    token += line[i];
                    i++;
                    ch = line[i];
                    type = startCharType(ch);
                }

                if (isKeyword(token)) {
                    cout << "    - Keyword: " << token << endl;
                } else if (isValidIdentifier(token)) {
                    cout << "    - Identifier: " << token << endl;
                }

                token = "";

                if (i < line.length()) {
                    if (type == 1) { // It's a digit
                        while (i < line.length() && isDigit(line[i])) {
                            token += line[i];
                            i++;
                        }
                        cout << "    - Digit: " << token << endl;
                           token = "";
                    } else if (type == 4) { // It's an operator
                        while (i < line.length() && isOperator(line[i])) {
                            token += line[i];
                            i++;
                        }
                        cout << "    - Operator: " << token << endl;
                           token = "";
                    } else if (type == 3) { // It's a delimiter
                        while (i < line.length() && isDelimiter(line[i])) {
                            token += line[i];
                            i++;
                        }
                        cout << "    - Delimiter: " << token << endl;
                           token = "";
                    } else if (type == 5) { // It's a string literal
                        processStringLiterals(line, i);
                           token = "";

                    } else {

                        i++;
                    }
                }
            }
        }

        if (line.find('#') < line.length()) {
            inCodeBlock = true;
        } else if (line.find('}') < line.length()) {
            inCodeBlock = false;
        }
    }
}


int main() {
    ifstream inputFile("Arnob.txt");
    if (!inputFile) {
        cout << "Error opening the input file." << endl;
        return 1;
    }

    processCodeBlock(inputFile);

    inputFile.close();
}
