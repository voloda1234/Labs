#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int n, const int Low, const int High);
void Input(int** a, const int n);
void Print(int** a, const int n);
void CountLocalMins(int** a, const int n);
int SumAboveMainDiagonal(int** a, const int n);

//int main()
//{
//	srand((unsigned)time(NULL));
//	int Low = 1;
//	int High = 50;
//	int n;
//	cout << "n = "; cin >> n;
//
//	int** a = new int* [n];
//	for (int i = 0; i < n; i++)
//		a[i] = new int[n];
//
//	Create(a, n, Low, High);
//	/*Input(a, n);*/
//	Print(a, n);
//
//	CountLocalMins(a, n);
//
//	cout << "SumAboveMainDiagonal:" << SumAboveMainDiagonal(a, n);
//
//	for (int i = 0; i < n; i++)
//		delete[] a[i];
//	delete[] a;
//	return 0;
//}
void Create(int** a, const int n, const int Low,
	const int High)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = Low + rand() % (High - Low + 1);
}
void Input(int** a, const int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "a[" << i << "][" << j << "] = ";
			cin >> a[i][j];
		}
		cout << endl;
	}
}
void Print(int** a, const int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(4) << a[i][j];
		cout << endl;
	}
	cout << endl;
}

void CountLocalMins(int** a, const int n)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			bool isLocalMin = true;

			for (int di = -1; di <= 1; di++)
			{
				for (int dj = -1; dj <= 1; dj++)
				{
					if (di == 0 && dj == 0) continue;

					int ni = i + di;
					int nj = j + dj;

					if (ni >= 0 && ni < n && nj >= 0 && nj < n)
					{
						if (a[i][j] >= a[ni][nj])
						{
							isLocalMin = false;
							break;
						}
					}
				}
				if (!isLocalMin) break;
			}
			if (isLocalMin)
				count++;
		}
	}

	cout << "Number of local mins: " << count << endl;
}

int SumAboveMainDiagonal(int** a, const int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++) 
		{
			sum += abs(a[i][j]);
		}
	}
	return sum;
}