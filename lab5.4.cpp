#include <iostream>
#include <cmath>
using namespace std;

double Interaction(const int K, const int N)
{
	double S = 0;
	for (int i = K; i <= N; i++)
		S += pow(i, 2) / (pow(K,2) + pow(N, 2));
	return S;
}
double Rec1(const int K, const int N, const int i)
{
	if (i > N)
		return 0;
	else
		return pow(i, 2) / (pow(K, 2) + pow(N, 2)) + Rec1(K, N, i + 1);
}
double Rec2(const int K, const int N, const int i)
{
	if (i < K)
		return 0;
	else
		return pow(i, 2) / (pow(K, 2) + pow(N, 2)) + Rec2(K, N, i - 1);
}
double Rec3(const int K, const int N, const int i, double t)
{
	t = t + pow(i, 2) / (pow(K, 2) + pow(N, 2));
	if (i >= N)
		return t;
	else
		return Rec3(K, N, i + 1, t);
}
double Rec4(const int K, const int N, const int i, double t)
{
	t = t + pow(i, 2) / (pow(K, 2) + pow(N, 2));
	if (i <= K)
		return t;
	else
		return Rec4(K, N, i - 1, t);
}
int main()
{
	int K, N;
	cout << "K = "; cin >> K;
	cout << "N = "; cin >> N;
	cout << "(iter) S0 = " << Interaction(K, N) << endl;
	cout << "(rec up ++) S1 = " << Rec1(K, N, K) << endl;
	cout << "(rec up --) S2 = " << Rec2(K, N, N) << endl;
	cout << "(rec down ++) S3 = " << Rec3(K, N, K, 0) << endl;
	cout << "(rec down --) S4 = " << Rec4(K, N, N, 0) << endl;
	return 0;
}