#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

int FindCountOfWordsWithTheSameEndingAndBeginning(const string s)
{
    int count = 0;
    stringstream spliter(s);
    string word;

    while (spliter >> word) {
        if (!word.empty() && word.front() == word.back()) {
            count++;
        }
    }

    return count;
}
int main()
{
	string str;
	cout << "Enter string:" << endl;
	getline(cin, str);
	cout << "Count Of Words With The Same Ending And Beginning: " << FindCountOfWordsWithTheSameEndingAndBeginning(str) << endl;
	return 0;
}