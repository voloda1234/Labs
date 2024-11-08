//#include <iostream>
//#include <iomanip>
//#include <time.h>
//using namespace std;
//
////Iteration way
//
//void PrintArray(int* a, const int numberOfElements);
//int GetMaxIndex(int* a, int numberOfElements, int maxIndex);
//int GetProductOfElements(int* a, int numberOfElements, int firstZero, int secondZero, int product);
//void EnterArray(int* a, int numberOfElements);
//void SortElements(int* a, int numberOfElements);
//
//int main()
//{
//	const int n = 10;
//	int a[n] = { 1,2,3,4,0,6,7,8,0,10 };
//
//	cout << "Array with elements:" << endl;
//	PrintArray(a, n);
//	cout << endl;
//
//	//1.1
//	cout << "//1.1" << endl;
//	int maxIndex = GetMaxIndex(a, n, 0);
//	cout << "MaxIndex: " << maxIndex << endl;
//	cout << endl;
//	//1.2
//	cout << "//1.2" << endl;
//	int product = GetProductOfElements(a, n, 0, 0, 1);
//	cout << "Product: " << product << endl;
//	cout << endl;
//	//2
//	cout << "//2" << endl << "Enter elements of array:" << endl;
//	int b[n];
//	EnterArray(b, n);
//	SortElements(b, n);
//	PrintArray(b, n);
//
//
//}
//
//void PrintArray(int* a, const int numberOfElements)
//{
//	for (int i = 0; i < numberOfElements; i++) {
//		cout << "a[" << setw(1) << i << "] = " << setw(1) << a[i] << "; ";
//	}
//	cout << endl;
//}
//
//int GetMaxIndex(int* a, int numberOfElements, int maxIndex) {
//
//	int maxValue = a[0];
//	for (int i = 1; i < numberOfElements; i++) {
//		if (a[i] > maxValue) {
//			maxValue = a[i];
//			maxIndex = i;
//		}
//	}
//	return maxIndex;
//}
//
//int GetProductOfElements(int* a, int numberOfElements, int firstZero, int secondZero, int product) {
//
//	bool isPassed = true;
//	for (int i = 0; i < numberOfElements; i++) {
//		if (a[i] == 0) {
//			if (isPassed) {
//				firstZero = i;
//				isPassed = false;
//			}
//			else
//				secondZero = i;
//		}
//	}
//
//	int start = firstZero + 1;
//	int end = secondZero - 1;
//	for (; start <= end; start++) {
//		product *= a[start];
//	}
//	return product;
//}
//
//void EnterArray(int* a, int numberOfElements)
//{
//	for (int i = 0; i < numberOfElements; i++) {
//		int number;
//		cout << "a[" << setw(1) << i << "] = " << setw(1); cin >> number;
//		a[i] = number;
//	}
//	cout << endl;
//}
//
//void SortElements(int* a, int numberOfElements)
//{
//	int arrayP[5] = { 0,0,0,0,0 };
//	int arrayN[5] = { 0,0,0,0,0 };
//
//	int indexP = 0;
//	int indexN = 0;
//
//	int j = 0;
//	int k = 0;
//
//	for (int i = 0; i < numberOfElements; i++) {
//		if (a[i] % 2 != 0) {
//			if (indexN < 5) {
//				arrayN[indexN] = a[i];
//				indexN++;
//			}
//		}
//		else {
//			if (indexP < 5) {
//				arrayP[indexP] = a[i];
//				indexP++;
//			}
//		}
//	}
//
//	for (int i = 0; i < numberOfElements / 2; i++) {
//		a[i] = arrayN[j];
//		j++;
//	}
//
//	for (int i = 5; i < numberOfElements; i++) {
//		a[i] = arrayP[k];
//		k++;
//	}
//
//}
