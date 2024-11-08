#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

//Iteration way

void CreateArrayWithRandomElements(int* a, int numberOfElements, int start, int end);
void PrintArray(int* a, const int numberOfElements);
int CountElements(int* a, int numberOfElements);
int SumElements(int* a, int numberOfElements);
void TurnToZero(int* a, int numberOfElements);

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
	cout << "Number of right elements: " << setw(1) << CountElements(a, n) << endl;
	cout << "Sum of right elements: " << setw(1) << SumElements(a, n) << endl;
	TurnToZero(a, n);
	PrintArray(a, n);
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

int CountElements(int* a, int numberOfElements) {
	int count = 0;
	for (int i = 0; i < numberOfElements; i++) {
		if (a[i] > 0 || !(a[i] % 3 == 0)) {
			count++;
		}
	}
	return count;
}

int SumElements(int* a, int numberOfElements) {
	int sum = 0;
	for (int i = 0; i < numberOfElements; i++) {
		if (a[i] > 0 || !(a[i] % 3 == 0)) {
			sum += a[i];
		}
	}
	return sum;
}

void TurnToZero(int* a, int numberOfElements) {
	for (int i = 0; i < numberOfElements; i++) {
		if (a[i] > 0 || !(a[i] % 3 == 0)) {
			a[i] = 0;
		}
	}
}