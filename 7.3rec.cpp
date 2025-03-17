#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < colCount - 1)
		PrintRow(a, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}
void PrintRows(int** a, const int n, int rowNo)
{
	PrintRow(a, rowNo, n, 0);
	if (rowNo < n - 1)
		PrintRows(a, n, rowNo + 1);
	else
		cout << endl;
}
void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
	cout << "a[" << rowNo << "][" << colNo << "] = ";
	cin >> a[rowNo][colNo];
	if (colNo < colCount - 1)
		InputRow(a, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}
void InputRows(int** a, const int n, int rowNo)
{
	InputRow(a, rowNo, n, 0);
	if (rowNo < n - 1)
		InputRows(a, n, rowNo + 1);
	else
		cout << endl;
}
void CreateRow(int** a, const int rowNo, const int colCount,
	const int Low, const int High, int colNo)
{
	a[rowNo][colNo] = Low + rand() % (High - Low + 1);
	if (colNo < colCount - 1)
		CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}
void CreateRows(int** a, const int n,
	const int Low, const int High, int rowNo)
{
	CreateRow(a, rowNo, n, Low, High, 0);
	if (rowNo < n - 1)
		CreateRows(a, n, Low, High, rowNo + 1);
}

bool isLocalMinimum(int** a, int n, int i, int j, int di, int dj) {
	if (di > 1) {
		return true;
	}

	if (di == 0 && dj == 0) {
		return isLocalMinimum(a, n, i, j, di, dj + 1);
	}

	if (dj > 1) {
		return isLocalMinimum(a, n, i, j, di + 1, -1);
	}

	int ni = i + di;
	int nj = j + dj;

	if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
		if (a[i][j] >= a[ni][nj]) {
			return false;
		}
	}
	return isLocalMinimum(a, n, i, j, di, dj + 1);
}

void CountLocalMins(int** a, int n, int i, int j, int& count) {
	if (i >= n) {
		return;
	}

	if (j >= n) {
		CountLocalMins(a, n, i + 1, 0, count);
		return;
	}

	if (isLocalMinimum(a, n, i, j, -1, -1)) {
		count++;
	}

	CountLocalMins(a, n, i, j + 1, count);
}

int SumAboveMainDiagonalRec(int** a, const int n, int i, int j, int& sum)
{
	if (i >= n) {
		return sum;
	}

	if (j >= n) {
		return SumAboveMainDiagonalRec(a, n, i + 1, i + 2, sum);
	}

	sum += abs(a[i][j]);

	return SumAboveMainDiagonalRec(a, n, i, j + 1, sum);
}

int main()
{
	srand((unsigned)time(NULL));
	int Low = 0;
	int High = 20;
	int n;
	cout << "n = "; cin >> n;

	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];

	CreateRows(a, n, Low, High, 0);
	/*InputRows(a, n, 0);*/
	PrintRows(a, n, 0);
	int count = 0;
	CountLocalMins(a, n, 0, 0, count);
	cout << "Number of local mins: " << count << endl;
	int sum = 0;
	SumAboveMainDiagonalRec(a, n, 0, 1, sum);
	cout << "SumAboveMainDiagonal: " << sum << endl;
	
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
	return 0;
}
