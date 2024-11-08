#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

//Recurtion way

void PrintArray(int* a, const int numberOfElements, int i);
int GetMaxIndex(int* a, int numberOfElements, int maxIndex, int i);
int GetProductOfElements(int* a, int numberOfElements, int firstZero, int secondZero, int product, bool isPassed, int i);
void EnterArray(int* a, int numberOfElements, int i);
void SortElements(int* a, int numberOfElements, int i, int indexP, int indexN, int j, int k, int* arrayP, int* arrayN);

int main()
{
	const int n = 10;
	int a[n] = { 1,2,3,4,0,6,7,8,0,10 };

	cout << "Array with elements:" << endl;
	PrintArray(a, n, 0);
	cout << endl;

	//1.1
	cout << "//1.1" << endl;
	int maxIndex = GetMaxIndex(a, n, 0, 0);
	cout << "MaxIndex: " << maxIndex << endl;
	cout << endl;
	//1.2
	cout << "//1.2" << endl;
	int product = GetProductOfElements(a, n, 0, 0, 1, true, 0);
	cout << "Product: " << product << endl;
	cout << endl;
	//2
	cout << "//2" << endl << "Enter elements of array:" << endl;
	int b[n];
	EnterArray(b, n, 0);
	int arrayN[n / 2];
	int arrayP[n / 2];
	SortElements(b, n, 0, 0, 0, 0, 0, arrayP, arrayN);
	PrintArray(b, n, 0);


}

void PrintArray(int* a, const int numberOfElements, int i)
{
	cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
	if (i < numberOfElements - 1) {
		PrintArray(a, numberOfElements, i + 1);
	}
	else
		cout << endl;
}

int GetMaxIndex(int* a, int numberOfElements, int maxIndex, int i) {

	int maxValue = a[0];
	if (i < numberOfElements) {
		if (a[i] > maxValue) {
			maxValue = a[i];
			maxIndex = i;
		}
		return GetMaxIndex(a, numberOfElements, maxIndex, i + 1);
	}
	return maxIndex;
}

int GetProductOfElements(int* a, int numberOfElements, int firstZero, int secondZero, int product, bool isPassed, int i) {
	if (i < numberOfElements) {
		if (a[i] == 0) {
			if (isPassed) {
				firstZero = i;
				isPassed = false;
			}
			else
				secondZero = i;
		}
		return GetProductOfElements(a, numberOfElements, firstZero, secondZero, product,isPassed, i + 1);
	}

	int start = firstZero + 1;
	int end = secondZero - 1;
	for (; start <= end; start++) {
		product *= a[start];
	}
	return product;
}

void EnterArray(int* a, int numberOfElements, int i)
{
	if (i < numberOfElements) {
		int number;
		cout << "a[" << setw(1) << i << "] = " << setw(1); cin >> number;
		a[i] = number;
		EnterArray(a, numberOfElements, i + 1);
	}
	else 
		cout << endl;
}

void SortElements(int* a, int numberOfElements, int i, int indexP, int indexN, int j, int k, int* arrayP, int* arrayN)
{
	if (i < numberOfElements) {
		if (a[i] % 2 != 0) {
			if (indexN < 5) {
				arrayN[indexN] = a[i];
				indexN++;
			}
		}
		else {
			if (indexP < 5) {
				arrayP[indexP] = a[i];
				indexP++;
			}
		}
		SortElements(a, numberOfElements, i + 1, indexP, indexN, j, k, arrayP, arrayN);
	}

	for (int i = 0; i < numberOfElements / 2; i++) {
		a[i] = arrayN[j];
		j++;
	}

	for (int i = 5; i < numberOfElements; i++) {
		a[i] = arrayP[k];
		k++;
	}

}