#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

//Recurtion way

void CreateArrayWithRandomElements(int* a, int numberOfElements, int start, int end, int i);
void PrintArray(int* a, const int numberOfElements, int i);
int CountElements(int* a, int numberOfElements, int count, int i);
int SumElements(int* a, int numberOfElements, int sum, int i);
void TurnToZero(int* a, int numberOfElements, int i);

//int main()
//{
//	srand((unsigned)time(NULL)); 
//
//	const int n = 22;
//	int a[n];
//
//	int Low = -10;
//	int High = 35;
//	CreateArrayWithRandomElements(a, n, Low, High, 0);
//	cout << "Array with Random elements:" << endl;
//	PrintArray(a, n, 0);
//	cout << "Number of right elements: " << setw(1) << CountElements(a, n, 0, 0) << endl;
//	cout << "Sum of right elements: " << setw(1) << SumElements(a, n, 0, 0) << endl;
//	TurnToZero(a, n, 0);
//	PrintArray(a, n, 0);
//}

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

int CountElements(int* a, int numberOfElements, int count, int i) {
	if (i < numberOfElements) {
		if (a[i] > 0 || !(a[i]%3 == 0)) {
			count++;
		}
		return CountElements(a, numberOfElements, count, i + 1);
	}
	return count;
}

int SumElements(int* a, int numberOfElements, int sum, int i) {
	if (i < numberOfElements) {
		if (a[i] > 0 || !(a[i] % 3 == 0)) {
			sum += a[i];
		}
		return SumElements(a, numberOfElements, sum, i + 1);
	}
	return sum;
}

void TurnToZero(int* a, int numberOfElements, int i) {
	if (i < numberOfElements) {
		if (a[i] > 0 || !(a[i] % 3 == 0)) {
			a[i] = 0;
		}
		TurnToZero(a, numberOfElements, i + 1);
	}
}
