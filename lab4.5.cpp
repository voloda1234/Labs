#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
int main()
{
	double x, y, R;

	srand((unsigned)time(NULL));

	cout << "R = "; cin >> R;
	for (int i = 0; i < 10; i++)
	{
		cout << "x = "; cin >> x;
		cout << "y = "; cin >> y;

		if (pow((x + R), 2) + pow((y - R), 2) <= pow(R, 2) || 
			y <= 0 && y >= -R && x >= 0 && x <= 2 * R)
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	cout << endl << fixed;

	for (int i = 0; i < 10; i++)
	{
		x = 2 * R + rand() * (- 2 * R - 2 * R) / RAND_MAX;
		y = 2 * R + rand() * (-2 * R - 2 * R) / RAND_MAX;
		if (pow((x + R), 2) + pow((y - R), 2) <= pow(R, 2) ||
		y <= 0 && y >= -R && x >= 0 && x <= 2 * R)
			cout << setw(8) << setprecision(4) << x << " "
			<< setw(8) << setprecision(4) << y << " " << "yes" << endl;
			else
			cout << setw(8) << setprecision(4) << x << " "
			<< setw(8) << setprecision(4) << y << " " << "no" << endl;
	}
	return 0;
}