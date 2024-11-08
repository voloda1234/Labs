#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

//Iteration way

void CreateArrayWithRandomElements(int* a, int numberOfElements, int start, int end);
void PrintArray(int* a, const int numberOfElements);
int FindIndexOfTheMinElement(int* a, int numberOfElements);
int IFirst(int* a, const int numberOfElements);

int main()
{
	srand((unsigned)time(NULL));

	const int n = 22;
	int a[n];

	int Low = -10;
	int High = 35;
	CreateArrayWithRandomElements(a, n, Low, High);
	cout << "Array with Random elements:" << endl;
	PrintArray(a, n);

	int minIndex = FindIndexOfTheMinElement(a, n);
	cout << endl;
	cout << "MinIndex:" << endl; 
	cout << "a[" << setw(1) << minIndex << "] = " << setw(1) << a[minIndex] << "; ";

	/*PrintArray(a, n);*/
}

void CreateArrayWithRandomElements(int* a, int numberOfElements, int start, int end) {

	for (int i = 0; i < numberOfElements; i++) {
		a[i] = start + rand() % (end - start + 1);
	}
}
void PrintArray(int* a, const int numberOfElements)
{
	for (int i = 0; i < numberOfElements; i++) {
		cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
	}
	cout << endl;
}

int FindIndexOfTheMinElement(int* a, int numberOfElements) {

	int minIndex = IFirst(a, numberOfElements);
	int min = a[minIndex];
	if (minIndex == -1)
	{
		cerr << "немає елементів, які задовольняють умові" << endl;
		return 0;
	}

	for (int i = minIndex + 1; i < numberOfElements; i++)
		if (a[i] < min && a[i] % 2 != 0) {
			min = a[i];
			minIndex = i;
		}
	return minIndex;
}

int IFirst(int* a, const int numberOfElements)
{
	int minIndex = -1; 
	for (int i = 0; i < numberOfElements; i++)
		if (a[i]%2 != 0)
		{
			minIndex = i;
			break;
		}
	return minIndex;
}
