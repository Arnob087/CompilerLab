#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("number.txt");

    if (!inputFile.is_open()) {
        cout << "File doesn't exist!" << endl;
        return 1;
    }

    string x;
    while (getline(inputFile, x)) {
        if (x.empty()) {
            continue;
        }

        bool isReal = false;

        for (int i = 0; i < x.length(); i++) {
            if (x[i] == '-') {
                cout << x << " is a real number." << endl;
                isReal = true;
                break;
            } else if (x[i] == '.') {
                cout << x << " is a real number." << endl;
                isReal = true;
                break;
            }
        }

        if (!isReal) {
            cout << x << " is an integer number." << endl;
        }
    }

    inputFile.close();
    return 0;
}
