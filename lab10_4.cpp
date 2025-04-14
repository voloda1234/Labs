#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

void CreateTXT(char* fname)
{
	ofstream fout(fname);
	char ch;
	string s;
	do
	{
		cin.get();
		cin.sync();
		cout << "enter line: "; getline(cin, s);
		fout << s << endl;
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintTXT(char* fname)
{
	ifstream fin(fname);
	string s;
	while (getline(fin, s))
	{
		cout << s << endl;
	}
	cout << endl;
}

int CountVowelsInWord(const string& word) {
    int count = 0;
    for (char c : word) {
        if (tolower(c) == 'a' || tolower(c) == 'e' ||
            tolower(c) == 'i' || tolower(c) == 'o' ||
            tolower(c) == 'u') {
            count++;
        }
    }
    return count;
}

string FindMaxVowelWord(const string& line) {
    istringstream iss(line);
    string word;
    string maxWord;
    int maxCount = -1;

    while (iss >> word) {
        int currentCount = CountVowelsInWord(word);
        if (currentCount > maxCount) {
            maxCount = currentCount;
            maxWord = word;
        }
    }
    return maxWord;
}

void ProcessFile(const char* inputFilename, const char* outputFilename) {
    ifstream fin(inputFilename);
    if (!fin) {
        cerr << "Error opening input file: " << inputFilename << endl;
        return;
    }

    ofstream fout(outputFilename);
    if (!fout) {
        cerr << "Error opening output file: " << outputFilename << endl;
        fin.close();
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(fin, line)) {
        lineNumber++;
        if (lineNumber % 2 == 1) {
            string maxVowelWord = FindMaxVowelWord(line);
            fout << line;
            if (!maxVowelWord.empty()) {
                fout << " " << maxVowelWord;
            }
            fout << endl;
        }
        else { 
            fout << line << endl;
        }
    }

    fin.close();
    fout.close();
    cout << "File processed successfully. Result in " << outputFilename << endl;
}

int main() {
    char inputFilename[100];
    char outputFilename[100];
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create new file\n";
        cout << "2. Show file content\n";
        cout << "3. Process file\n";
        cout << "4. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> inputFilename;
            CreateTXT(inputFilename);
            break;
        case 2:
            cout << "Enter filename: ";
            cin >> inputFilename;
            PrintTXT(inputFilename);
            break;
        case 3:
            cout << "Enter input file: ";
            cin >> inputFilename;
            cout << "Enter output file: ";
            cin >> outputFilename;
            ProcessFile(inputFilename, outputFilename);
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}