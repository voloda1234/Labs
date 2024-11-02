#include <iostream>
#include <cmath>
using namespace std;

double s(const double x);

int main()
{
	double tp, tk, res;
	int n;

	cout << "tp = "; cin >> tp;
	cout << "tk = "; cin >> tk;
	cout << "n = "; cin >> n;
	cout << endl;

	double dt = (tk - tp) / n;

	double t = tp;

	while (t <= tk)
	{
		res = s(2 * t + 1) + 2 * s(pow(t, 2) + sqrt(s(1)));

		cout << t << " " << res << endl;
		t += dt;
	}
	return 0;
}
double s(const double x)
{
	if (abs(x) >= 1 && x == 0)
		return (pow(cos(x), 2) + 1.0) / exp(x);
	else
	{
		double S = 0;
		int k = 0;
		double a = 1;
		S = a;
		do
		{
			k++;
			double R = pow(2, 2 * k + 1) * pow(x, 2 * k + 1) / (2 * k - 1) * (2 * k) * (2 * k + 1);
			a *= R;
			S += a;
		} while (k < 4);

		return 1 / sin(2*x) + S;
	}
}