#include <iostream>
#include <cmath>

using namespace std;
int main()
{
	int k;
	int N;
	int i;
	double S;

	cout << "k = "; cin >> k;
	cout << "N = "; cin >> N;
	S = 0;
	i = k;
	//1
	while (i <= N)
	{
		S += sin(0.1 * pow(i, 2) /(pow(k, 2) + pow(N, 2)));
		i++;
	}
	cout << S << endl;
	//2
	S = 0;
	i = k;
	do {
		S += sin(0.1 * pow(i, 2) / (pow(k, 2) + pow(N, 2)));
		i++;
	} while (i <= N);
	cout << S << endl;
	//3
	S = 0;
	for (i = k; i <= N; i++)
	{
		S += sin(0.1 * pow(i, 2) / (pow(k, 2) + pow(N, 2)));
	}
	cout << S << endl;
	//4
	S = 0;
	for (i = N; i >= k; i--)
	{
		S += sin(0.1 * pow(i, 2) / (pow(k, 2) + pow(N, 2)));
	}
	cout << S << endl;
	return 0;
}