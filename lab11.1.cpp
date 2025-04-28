#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void CreateBIN(char* fname) {
	ofstream fout(fname, ios::binary);
	int number;
	char choice;

	do {
		cout << "Enter a number: ";
		cin >> number;                  
		fout.write((char*)&number, sizeof(number)); 
		cout << "Add another number? (y/n): ";
		cin >> choice;       
	} while (choice == 'y' || choice == 'Y');

	fout.close();
}

void PrintBIN(char* fname) 
{
	ifstream fin(fname, ios::binary); 
	int number;
	while (fin.read((char*)&number , sizeof(number)))
	{
		cout << number << ",";
	}
	cout << endl;
}

void SplitEvenOdd(char* fname, char* evenFile, char* oddFile) {
	ifstream fin(fname, ios::binary);
	ofstream feven(evenFile, ios::binary);
	ofstream fodd(oddFile, ios::binary);
	int number;

	while (fin.read((char*)&number, sizeof(number))) {
		if (number % 2 == 0)
			feven.write((char*)&number, sizeof(number));
		else
			fodd.write((char*)&number, sizeof(number));
	}

	fin.close();
	feven.close();
	fodd.close();
}int main()
{
	char fname[100];
	char evenName[100];
	char oddName[100];

	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname); 
	PrintBIN(fname);
	cout << "enter file name 2: "; cin >> evenName;
	cout << endl;
	cout << "enter file name 3: "; cin >> oddName;

	SplitEvenOdd(fname, evenName, oddName);
	cout << "Even: " << endl;
	PrintBIN(evenName);
	cout << "Odd: " << endl;
	PrintBIN(oddName);
	return 0;
}