#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
	double x, y, xp, xk, dx, R;

	cout << "R = "; cin >> R;
	cout << "xp = "; cin >> xp;
	cout << "xk = "; cin >> xk;
	cout << "dx = "; cin >> dx;

	cout << fixed;
	cout << "----------------------" << endl;
	cout << "|" << setw(4) << "x" << "    |"
		<< setw(6) << "y" << "     |" << endl;
	cout << "----------------------" << endl;
	x = xp;

	while (x <= xk)
	{
		if (x <= -R)
			y = R;
		else
			if (-R < x && x <= R)
				y = R - sqrt(pow(R, 2) - pow(x, 2));
			else
				if (R < x && x <= 6)
					y = (R + (x - R) * (-3 - R)) / (6 - R);
				else
					y = x - 9;
		cout << "|" << setw(7) << setprecision(2) << x
			<< " |" << setw(10) << setprecision(3) << y
			<< " |" << endl;
		x += dx;
	}
	cout << "----------------------" << endl;
	return 0;
}