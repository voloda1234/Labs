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
void SaveToFile(Route* r, const int N, const char* filename);
void LoadFromFile(Route*& r, int& N, const char* filename);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Enter the number of routes N: "; cin >> N;

    int routeNumber;
    char filename[100];
    Route foundRoute;

    Route* r = new Route[N];
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose an action:" << endl << endl;
        cout << " [1] - Enter data for student" << endl;
        cout << " [2] - Display data on screen" << endl;
        cout << " [3] - Physical data sorting" << endl;
        cout << " [4] - Index Sourt" << endl;
        cout << " [5] - Binery Sourt" << endl;
        cout << " [6] - Save to File" << endl;
        cout << " [7] - Load from File" << endl;
        cout << " [0] - Exit and finish the program" << endl << endl;
        cout << "Enter your choice: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(r, N);
            break;
        case 2:
            Print(r, N);
            break;
        case 3:
            Sort(r, N);
            Print(r, N);
            break;
        case 4:
            PrintIndexSorted(r, IndexSort(r, N), N);
            break;
        case 5:
            cin.get();
            cin.sync();
            cout << "Enter Route Number to search: "; cin >> routeNumber;
            foundRoute = BinSearch(r, N, routeNumber);
            if (foundRoute.routeNumber == routeNumber)
                PrintOneRoute(foundRoute);
            else
                cout << "Route not found" << endl;
            break;
        case 6:
            cin.get();
            cin.sync();

            cout << "Enter file name to save in: "; cin.getline(filename, 99);
            SaveToFile(r, N, filename);
            break;
        case 7:
            cin.get(); 
            cin.sync();

            cout << "Enter file name to load from: "; cin.getline(filename, 99);
            LoadFromFile(r, N, filename);
            break;

        case 0:
            break;
        default:
            cout << "You entered an incorrect value! "
                "Please enter a number corresponding to the menu item" << endl;
        }
    } while (menuItem != 0);

    delete[] r;
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
    cout << "=======================================================" << endl;
    cout << "|  Start Point   |     Destination     | Route Number |" << endl;
    cout << "-------------------------------------------------------" << endl;

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

void SaveToFile(Route* r, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary);
    fout.write((char*)&N, sizeof(N)); 
    for (int i = 0; i < N; i++)
        fout.write((char*)&r[i], sizeof(Route));
    fout.close(); 
}
void LoadFromFile(Route*& r, int& N, const char* filename)
{
    delete[] r; 
    ifstream fin(filename, ios::binary); 
    fin.read((char*)&N, sizeof(N));
    r = new Route[N];
    for (int i = 0; i < N; i++)
        fin.read((char*)&r[i], sizeof(Route));
    fin.close();
}
