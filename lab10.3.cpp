#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

struct Route
{
    string startPoint;
    string destination;

    int routeNumber;
};

void Create(Route* r, const int N);
void Print(Route* r, const int N);
void PrintOneRoute(Route r);
void Sort(Route* r, const int N);
int* IndexSort(Route* r, const int N);
void PrintIndexSorted(Route* r, int* I, const int N);
Route BinSearch(Route* r, const int N, const int RouteNumber);
bool SaveToFile(Route* r, const int N, const char* filename);
bool LoadFromFile(Route*& r, int& N, const char* filename);
bool FileExists(const string& filename);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N = 0;
    Route* r = nullptr;
    char filename[100];
    Route foundRoute;
    int menuItem;
    int routeNumber;

    do {
        cout << "\n\nMenu:\n";
        cout << " [1] - Enter route data\n";
        cout << " [2] - Display routes\n";
        cout << " [3] - Sort routes (physical)\n";
        cout << " [4] - Sort routes (index)\n";
        cout << " [5] - Binary search by route number\n";
        cout << " [6] - Save to file\n";
        cout << " [7] - Load from file\n";
        cout << " [0] - Exit\n";
        cout << "Enter your choice: "; cin >> menuItem;
        cout << endl;

        switch (menuItem) {
        case 1:
            if (r != nullptr) {
                delete[] r;
                r = nullptr;
            }
            do {
                cout << "Enter number of routes (1-100): ";
                cin >> N;
            } while (N <= 0 || N > 100);

            r = new Route[N];
            Create(r, N);
            break;

        case 2:
            if (r == nullptr) {
                cout << "No data available! Please load or enter data first.\n";
                break;
            }
            Print(r, N);
            break;

        case 3:
            if (r == nullptr) {
                cout << "No data available! Please load or enter data first.\n";
                break;
            }
            Sort(r, N);
            Print(r, N);
            break;

        case 4:
            if (r == nullptr) {
                cout << "No data available! Please load or enter data first.\n";
                break;
            }
            PrintIndexSorted(r, IndexSort(r, N), N);
            break;

        case 5:
            if (r == nullptr) {
                cout << "No data available! Please load or enter data first.\n";
                break;
            }
            cout << "Enter route number to search: "; cin >> routeNumber;
            foundRoute = BinSearch(r, N, routeNumber);
            if (foundRoute.routeNumber == routeNumber)
                PrintOneRoute(foundRoute);
            else
                cout << "Route not found!\n";
            break;

        case 6:
            if (r == nullptr) {
                cout << "No data to save! Please load or enter data first.\n";
                break;
            }
            cin.ignore();
            cout << "Enter filename to save: ";
            cin.getline(filename, 99);
            if (!SaveToFile(r, N, filename)) {
                cout << "Failed to save data to file!\n";
            }
            break;

        case 7:
            cin.ignore();
            cout << "Enter filename to load: ";
            cin.getline(filename, 99);
            if (!FileExists(filename)) {
                cout << "File doesn't exist!\n";
                break;
            }
            if (!LoadFromFile(r, N, filename)) {
                cout << "Failed to load data from file!\n";
            }
            break;

        case 0:
            break;

        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (menuItem != 0);

    if (r != nullptr) {
        delete[] r;
    }
    return 0;
}

void Create(Route* r, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Route # " << i + 1 << ":" << endl;

        cin.ignore();
        cout << " Start Poit: "; getline(cin, r[i].startPoint);
        cout << "Destination: ";  getline(cin, r[i].destination);
        cout << "Route Number: "; cin >> r[i].routeNumber;

        cout << endl;
    }
}

void Print(Route* r, const int N)
{
    cout << "=============================================================" << endl;
    cout << "| #  |  Start Point   |     Destination     | Route Number  |" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(15) << left << r[i].startPoint;
        cout << "| " << setw(20) << left << r[i].destination;
        cout << "| " << setw(13) << right << r[i].routeNumber;
        cout << " |" << endl;
    }

    cout << "=============================================================" << endl;
    cout << endl;
}


void PrintOneRoute(Route r)
{
    cout << "========================================================" << endl;
    cout << "|  Start Point   |     Destination     | Route Number  |" << endl;
    cout << "--------------------------------------------------------" << endl;

    cout << "| " << setw(15) << left << r.startPoint;
    cout << "| " << setw(20) << left << r.destination;
    cout << "| " << setw(13) << right << r.routeNumber;
    cout << " |" << endl;

    cout << "========================================================" << endl;
    cout << endl;
}

void Sort(Route* r, const int N) {
    Route tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            if (r[i1].routeNumber < r[i1 + 1].routeNumber) {
                tmp = r[i1];
                r[i1] = r[i1 + 1];
                r[i1 + 1] = tmp;
            }
        }
    }
}

int* IndexSort(Route* r, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) {
        I[i] = i;
    }

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (r[j].routeNumber > r[value].routeNumber)
            {
                break;
            }
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Route* r, int* I, const int N) {
    cout << "=============================================================" << endl;
    cout << "| #  |  Start Point   |     Destination     | Route Number  |" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(15) << left << r[I[i]].startPoint;
        cout << "| " << setw(20) << left << r[I[i]].destination;
        cout << "| " << setw(13) << right << r[I[i]].routeNumber;
        cout << " |" << endl;
    }
    cout << "=============================================================" << endl;
}

Route BinSearch(Route* r, const int N, const int routeNumber) {
    int L = 0, R = N - 1, m;
    Route notFound;
    notFound.routeNumber = -1;

    do {
        m = (L + R) / 2;
        if (r[m].routeNumber == routeNumber) {
            return r[m];
        }
        if (r[m].routeNumber < routeNumber) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);

    return notFound;
}

bool FileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool SaveToFile(Route* r, const int N, const char* filename)
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        return false;
    }

    fout << N << endl;
    for (int i = 0; i < N; i++) {
        fout << r[i].startPoint << endl;
        fout << r[i].destination << endl;
        fout << r[i].routeNumber << endl;
    }
    fout.close();
    cout << "Data saved to file: " << filename << endl;
    return true;
}

bool LoadFromFile(Route*& r, int& N, const char* filename)
{
    ifstream fin(filename);
    delete[] r;
    r = nullptr;

    if (!(fin >> N) || N <= 0) {
        fin.close();
        return false;
    }

    r = new Route[N];
    fin.ignore();

    for (int i = 0; i < N; i++) {
        if (!getline(fin, r[i].startPoint)) 
        {
            delete[] r;
            r = nullptr;
            fin.close();
            return false;
        }
        if (!getline(fin, r[i].destination)) 
        {
            delete[] r;
            r = nullptr;
            fin.close();
            return false;
        }
        if (!(fin >> r[i].routeNumber)) 
        {
            delete[] r;
            r = nullptr;
            fin.close();
            return false;
        }
        fin.ignore();
    }
    fin.close();
    cout << "Data loaded from file: " << filename << endl;
    return true;
}