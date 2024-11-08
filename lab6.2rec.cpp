#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

//Recurtion way

void CreateArrayWithRandomElements(int* a, int numberOfElements, int start, int end, int i);
void PrintArray(int* a, const int numberOfElements, int i);
int FindIndexOfTheMinElement(int* a, int numberOfElements, int firstIndex, int i);
int IFirst(int* a, const int numberOfElements, int i);


int main()
{
	srand((unsigned)time(NULL)); 

	const int n = 22;
	int a[n];

	int Low = -10;
	int High = 35;
	CreateArrayWithRandomElements(a, n, Low, High, 0);
	cout << "Array with Random elements:" << endl;
	PrintArray(a, n, 0);

	int firstIndex = IFirst(a, n, 0);
	int minIndex = FindIndexOfTheMinElement(a, n, firstIndex, 1);
	cout << endl;
	cout << "MinIndex:" << endl;
	cout << "a[" << setw(1) << minIndex << "] = " << setw(1) << a[minIndex] << "; ";

	//PrintArray(a, n, 0);
}

void CreateArrayWithRandomElements(int* a, int numberOfElements, int start, int end, int i) {
	a[i] = start + rand() % (end - start + 1);
	if (i < numberOfElements - 1) {
		CreateArrayWithRandomElements(a, numberOfElements, start, end, i + 1);
	}
}
void PrintArray(int* a, const int numberOfElements, int i)
{
	cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
	if (i < numberOfElements - 1)
		PrintArray(a, numberOfElements, i + 1);
	else
		cout << endl;
}

int FindIndexOfTheMinElement(int* a, int numberOfElements, int firstIndex, int i) {

	int min = a[firstIndex];
	if (firstIndex == -1)
	{
		cout << "немає елементів, які задовольняють умові" << endl;
		return 0;
	}

	if (firstIndex + i < numberOfElements) {
		if (a[i] < min && a[i] % 2 != 0) {
			min = a[i];
			firstIndex = i;
		}
		return FindIndexOfTheMinElement(a, numberOfElements, firstIndex , i + 1);
	}
	return firstIndex;
}

int IFirst(int* a, const int numberOfElements, int i)
{
	if (i < numberOfElements) {
		if (a[i] % 2 != 0) {
			return i;
		}
		return IFirst(a, numberOfElements, i + 1);
	}
	return -1;
}