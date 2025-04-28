#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct Route
{
    char startPoint[30];
    char destination[30];
    int routeNumber;
};

void Create(const char* filename);
void Print(const char* filename);
void PrintOneRoute(const Route& r);
void SortFile(const char* filename);
bool BinSearch(const char* filename, int routeNumber, Route& result);
int CountRoutes(const char* filename);
void SwapRoutes(fstream& file, int pos1, int pos2);
Route ReadRoute(fstream& file, int pos);
void WriteRoute(fstream& file, int pos, const Route& r);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char filename[100];
    cout << "Enter file name: ";
    cin.getline(filename, 99);

    int choice;
    do {
        system("cls");

        cout << "\nMenu:\n";
        cout << "1. Create new file\n";
        cout << "2. Display all routes\n";
        cout << "3. Sort routes\n";
        cout << "4. Search route\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            Create(filename);
            break;
        case 2:
            Print(filename);
            break;
        case 3:
            SortFile(filename);
            Print(filename);
            break;
        case 4:
            int num;
            cout << "Enter route number: ";
            cin >> num;
            Route found;
            if (BinSearch(filename, num, found))
                PrintOneRoute(found);
            else {
                cout << "Route not found\n";
            }
            break;
        }
    } while (choice != 0);

    return 0;
}

int CountRoutes(const char* filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) return 0;
    int size = file.tellg();
    file.close();
    return size / sizeof(Route);
}

Route ReadRoute(fstream& file, int pos) {
    Route r;
    file.seekg(pos * sizeof(Route));
    file.read((char*)&r, sizeof(Route));
    return r;
}

void WriteRoute(fstream& file, int pos, const Route& r) {
    file.seekp(pos * sizeof(Route));
    file.write((char*)&r, sizeof(Route));
}

void SwapRoutes(fstream& file, int pos1, int pos2) {
    Route r1 = ReadRoute(file, pos1);
    Route r2 = ReadRoute(file, pos2);
    WriteRoute(file, pos1, r2);
    WriteRoute(file, pos2, r1);
}

void Create(const char* filename) {
    ofstream file(filename, ios::binary);

    int count;
    cout << "Enter number of routes: ";
    cin >> count;
    cin.ignore();

    Route r;
    for (int i = 0; i < count; i++) {
        cout << "\nRoute #" << i + 1 << ":\n";
        cout << "Start point: ";
        cin.getline(r.startPoint, 30);

        cout << "Destination: ";
        cin.getline(r.destination, 30);

        cout << "Route number: ";
        cin >> r.routeNumber;
        cin.ignore();

        file.write((char*)&r, sizeof(Route));
    }
    file.close();
}

void Print(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file\n";
        return;
    }

    system("cls");

    cout << "\nList of routes:\n";
    cout << "===============================================================\n";
    cout << "| # |     Start Point      |     Destination     | Route Num  |\n";
    cout << "---------------------------------------------------------------\n";

    Route r;
    int index = 1;
    while (file.read((char*)&r, sizeof(Route))) {
        cout << "| " << setw(2) << index++ << " | "
            << setw(20) << left << r.startPoint << "| "
            << setw(20) << left << r.destination << "| "
            << setw(10) << right << r.routeNumber << " |\n";
    }
    cout << "===============================================================\n";

    file.close();

    cin.get();
}


void PrintOneRoute(const Route& r) {
    system("cls");
    cout << "==============================================================\n";
    cout << "|   Start Point    |     Destination     |  Route Number     |\n";
    cout << "--------------------------------------------------------------\n";

    cout << "| " << setw(18) << left << r.startPoint;
    cout << "| " << setw(20) << left << r.destination;
    cout << "| " << setw(16) << right << r.routeNumber << " |\n";

    cout << "==============================================================\n";

    cin.ignore();
    cin.get();
}

void SortFile(const char* filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "Error opening file\n";
        return;
    }

    int count = CountRoutes(filename);
    if (count == 0) return;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            Route r1 = ReadRoute(file, j);
            Route r2 = ReadRoute(file, j + 1);

            if (r1.routeNumber < r2.routeNumber) {
                SwapRoutes(file, j, j + 1);
            }
        }
    }
    file.close();
}

bool BinSearch(const char* filename, int routeNumber, Route& result) {
    ifstream file(filename, ios::binary);
    if (!file) return false;

    int left = 0;
    int right = CountRoutes(filename) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        file.seekg(mid * sizeof(Route));
        file.read((char*)&result, sizeof(Route));

        if (result.routeNumber == routeNumber) {
            file.close();
            return true;
        }

        if (result.routeNumber < routeNumber) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    file.close();
    return false;
}
