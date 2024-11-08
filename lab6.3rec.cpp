#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
using namespace std;

void PrintArray(int* a, const int numberOfElements, int i);
void PrintArray(double* a, const int numberOfElements, int i);
void PrintArray(string* a, const int numberOfElements, int i);

void Sort(int* a, const int size, int i);

template <typename T>
void Sort(T* a, const int size, int i);

//int main()
//{
//	const int n = 10;
//	int a[n] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	cout << "Started Array" << endl;
//	PrintArray(a, n, 0);
//	cout << endl;
//
//	cout << "Sort(a, n)" << endl;
//	Sort(a, n, 0);
//	PrintArray(a, n, 0);
//	cout << endl;
//
//	cout << "Sort<int>(a, n)" << endl;
//	Sort<int>(a, n, 0);
//	PrintArray(a, n, 0);
//	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
//
//	double b[n] = { 1.1, 2.2, 3.3, 4.3, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0 };
//	cout << "Started Array" << endl;
//	PrintArray(b, n, 0);
//	cout << endl;
//
//	cout << "Sort<double>(a, n)" << endl;
//	Sort<double>(b, n, 0);
//	PrintArray(b, n, 0);
//	cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
//
//	string c[n] = { "-3 ", "-2 ", "-1 ", "0 ", "1 ", "2 ", "3 ", "4 ", "5 ", "6 " };
//	cout << "Started Array" << endl;
//	PrintArray(c, n, 0);
//	cout << endl;
//
//	cout << "Sort<string>(c, n)" << endl;
//	Sort<string>(c, n, 1);
//	PrintArray(c, n, 0);
//	return 0;
//}
void Sort(int* a, const int size, int i)
{
	int k = 0;
	for (int j = 0; j < size - i; j++)
		if (a[j] < a[j + 1])
		{
			int tmp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = tmp;
			k = 1;
		}
	if (k == 0)
		return; 
	if (i < size - 1)
		Sort(a, size, i + 1);
}

template <typename T>
void Sort(T* a, const int size, int i)
{
	bool empty = false;
	for (int j = 0; j < size - i; j++)
		if (a[j] < a[j + 1])
		{
			T tmp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = tmp;
			empty = true;
		}
	if (!empty)
		return;
	if (i < size - 1)
		Sort(a, size, i + 1);
}

void PrintArray(int* a, const int numberOfElements, int i)
{
	cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
	if (i < numberOfElements - 1)
		PrintArray(a, numberOfElements, i + 1);
	else
		cout << endl;
}


void PrintArray(double* a, const int numberOfElements, int i)
{
	cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
	if (i < numberOfElements - 1)
		PrintArray(a, numberOfElements, i + 1);
	else
		cout << endl;
}

void PrintArray(string* a, const int numberOfElements, int i)
{
	cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
	if (i < numberOfElements - 1)
		PrintArray(a, numberOfElements, i + 1);
	else
		cout << endl;
}