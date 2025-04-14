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
int ProcessTXT1(char* fname) 
{
	ifstream fin(fname);
	string s;
	int count = 0;

	while (getline(fin, s)) {
		for (size_t i = 0; i + 1 < s.size(); ++i) {
			if ((s[i] == 'a' && s[i + 1] == 'a') || (s[i] == 'b' && s[i + 1] == 'b') || (s[i] == 'c' && s[i + 1] == 'c')) {
				count++;
				i++;
			}
		}
	}

	return count;
}

int ProcessTXT2(char* fname)
{
	ifstream fin(fname);
    string s;

	getline(fin, s);

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
	char fname[100]; 
	cout << "enter file name 1: "; cin >> fname;
	CreateTXT(fname); 
	PrintTXT(fname);

	cout << "Count of |aa bb cc| = " << ProcessTXT1(fname) << endl;
	cout << "Count of words = " << ProcessTXT2(fname) << endl;
	return 0;
}