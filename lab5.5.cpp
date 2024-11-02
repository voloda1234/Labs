#include <iostream>
using namespace std;

double GetBinomial(int n, int k, int level, int& depth);

int main()
{
    int n, k;

    cout << "n = "; cin >> n;
    cout << "k = "; cin >> k;

    int depth = 0;
    double coefficient = GetBinomial(n, k, 1, depth);

    cout << "coefficient = " << coefficient << endl;
    cout << "depth = " << depth << endl;

    return 0;
}

double GetBinomial(int n, int k, int level, int& depth)
{
    if (level > depth)
        depth = level;

    if (k == 0 || k == n)
        return 1;
    if(n > 0)
        return (n * 0.1 / (k * (n - k))) * GetBinomial(n - 1, k - 1, level + 1, depth) + (n * 0.1 / (k * (n - k))) * GetBinomial(n - 1, k, level+1, depth);
}
