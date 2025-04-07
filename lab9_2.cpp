#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Specialty { ComputerScience, Informatics, MathematicsandEconomics, PhysicsandInformatics, WorkbasedLearning };
const string specialtyNames[] = { "Computer Science","Informatics","Math and Economics","Physics and IT","Work-based Learning" };
enum Course { I = 1, II = 2, III = 3, IV = 4 };

struct Student
{
    string lastName;
    Specialty specialty;
    Course course;

    int mathGrade;
    int physicsGrade;

    union
    {
        int ITGrade;
        int UnitMethod;
        int Pedagogy;
    } otherGrade;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double FindDeltaOfStudenstWithExellentGrade(Student* p, const int N);
int FindNumberOfGoodGrades(Student* p, const int N);
void Sort(Student* p, const int N);
int GetAvarange(Student p);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string lastName, const Course course, const int averageGrade);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Enter the number of students N: "; cin >> N;

    string lastName;
    int icource;
    Course cource;
    int avarangeGrade;
    int found;

    Student* p = new Student[N];
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose an action:" << endl << endl;
        cout << " [1] - Enter data for student" << endl;
        cout << " [2] - Display data on screen" << endl;
        cout << " [3] - Find percents of students which (5 Grade) with physic and math" << endl;
        cout << " [4] - Find Number Of Good Grades" << endl;
        cout << " [5] - Physical data sorting" << endl;
        cout << " [6] - Index Sourt" << endl;
        cout << " [7] - Binery Sourt" << endl;
        cout << " [0] - Exit and finish the program" << endl << endl;
        cout << "Enter your choice: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            cout << FindDeltaOfStudenstWithExellentGrade(p, N) << "%" << endl;;
            break;
        case 4:
            cout << "Count:" << FindNumberOfGoodGrades(p, N) << endl;;
            break;
        case 5:
            Sort(p, N);
            Print(p, N);
            break;
        case 6:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 7:
            cin.ignore();
            cout << "Enter Keys:" << endl;
            cout << " LastName: "; getline(cin, lastName);
            cout << endl;
            cout << " Cource: "; cin >> icource;
            cout << " AvarangeGrade: "; cin >> avarangeGrade;
            cource = (Course)icource;

            cin.get();
            cin.sync();

            cout << endl;
            if ((found = BinSearch(p, N, lastName, cource, avarangeGrade)) != -1)
                cout << "Found in position " << found + 1 << endl;
            else
                cout << "Not Found" << endl;
            break;

        case 0:
            break;
        default:
            cout << "You entered an incorrect value! "
                "Please enter a number corresponding to the menu item" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Student* p, const int N)
{
    int specialty;
    int course;
    for (int i = 0; i < N; i++)
    {
        cout << "Student # " << i + 1 << ":" << endl;

        cin.ignore();
        cout << " Last name: "; getline(cin, p[i].lastName);
        cout << " Specialty (0 - Computer Science, 1 - Informatics, 2 - Mathematics and Economics, "
            << "3 - Physics and Informatics, 4 - Work-based Learning): ";
        cin >> specialty;
        p[i].specialty = (Specialty)specialty;
        cout << "Course (1, 2, 3, 4): "; cin >> course;
        p[i].course = (Course)course;

        cout << "Math grade: "; cin >> p[i].mathGrade;
        cout << "Physics grade: "; cin >> p[i].physicsGrade;

        switch (p[i].specialty)
        {
        case ComputerScience:
            cout << "ITGrade grade: "; cin >> p[i].otherGrade.ITGrade;
            break;
        case Informatics:
            cout << "UnitMethod grade: "; cin >> p[i].otherGrade.UnitMethod;
            break;
        default:
            cout << "Pedagogy grade: "; cin >> p[i].otherGrade.Pedagogy;
        }

        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "==========================================================================================================" << endl;
    cout << "| # |    Last Name     |     Specialty     | Course | Math |  Phys |  ITGrade  | UnitMethod|  Pedagogy  |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(16) << left << p[i].lastName;
        cout << "| " << setw(18) << left << specialtyNames[p[i].specialty];
        cout << "| " << setw(7) << right << p[i].course;
        cout << "| " << setw(5) << right << p[i].mathGrade;
        cout << "| " << setw(6) << right << p[i].physicsGrade;

        switch (p[i].specialty)
        {
        case ComputerScience:
            cout << "| " << setw(10) << right << p[i].otherGrade.ITGrade;
            cout << "| " << setw(11) << right << "-";
            cout << "| " << setw(9) << right << "-";
            break;
        case Informatics:
            cout << "| " << setw(10) << right << "-";
            cout << "| " << setw(11) << right << p[i].otherGrade.UnitMethod;
            cout << "| " << setw(9) << right << "-";
            break;
        default:
            cout << "| " << setw(10) << right << "-";
            cout << "| " << setw(11) << right << "-";
            cout << "| " << setw(9) << right << p[i].otherGrade.Pedagogy;
        }
        cout << " |" << endl;
    }

    cout << "===============================================================================================================" << endl;
    cout << endl;
}

double FindDeltaOfStudenstWithExellentGrade(Student* p, const int N)
{
    cout << "Percentage of students which have (5 Grade) with physic and math:" << endl;
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].mathGrade == 5 || p[i].physicsGrade == 5)
            k++;
    }
    return 100.0 * k / N;
}

int FindNumberOfGoodGrades(Student* p, const int N)
{
    cout << "Number Of Good Grades:" << endl;
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].mathGrade == 4)
            k++;
        if (p[i].physicsGrade == 4)
            k++;
        if (p[i].otherGrade.ITGrade == 4)
            k++;
    }
    return k;
}

void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) {
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            bool needSwap = false;

            if (GetAvarange(p[i1]) < GetAvarange(p[i1 + 1])) {
                needSwap = true;
            }
            else if (GetAvarange(p[i1]) == GetAvarange(p[i1 + 1]))
            {
                if (p[i1].course > p[i1 + 1].course) {
                    needSwap = true;
                }
                else if (p[i1].course == p[i1 + 1].course) 
                {
                    if (p[i1].lastName < p[i1 + 1].lastName) {
                        needSwap = true;
                    }
                }
            }

            if (needSwap) {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
    }
}

int GetAvarange(Student p)
{
    return (int)((p.mathGrade + p.physicsGrade + p.otherGrade.ITGrade) / 3);
}

int* IndexSort(Student* p, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) {
        I[i] = i;
    }

    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        for (j = i - 1; j >= 0; j--) {
            if (GetAvarange(p[j]) < GetAvarange(p[value]))
            {
                break;
            }
            else if (GetAvarange(p[j]) == GetAvarange(p[value]))
            {
                if (p[I[j]].course > p[value].course) {
                    break;
                }
                else if (p[I[j]].course == p[value].course) 
                {
                    if (p[I[j]].lastName > p[value].lastName) {
                        break;
                    }
                }
            }
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(Student* p, int* I, const int N) {
    cout << "======================================================================" << endl;
    cout << "| № | LastName      | Cource |      Specialty      | Avarange Grade  |" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << p[I[i]].lastName;
        cout << "| " << setw(7) << left << p[I[i]].course;
        cout << "| " << setw(20) << left << specialtyNames[p[I[i]].specialty];
        cout << "| " << setw(12) << fixed << setprecision(2) << GetAvarange(p[I[i]]) << "    |" << endl;
    }
    cout << "======================================================================" << endl;
}

int BinSearch(Student* p, const int N, const string lastName, const Course course, const int averageGrade) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;

        if (p[m].lastName == lastName &&
            p[m].course == course &&
            GetAvarange(p[m]) == averageGrade) {
            return m;
        }

        if ((GetAvarange(p[m]) < averageGrade) ||
            (GetAvarange(p[m]) == averageGrade && p[m].course < course) ||
            (GetAvarange(p[m]) == averageGrade && p[m].course == course &&
                p[m].lastName < lastName)) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    } while (L <= R);

    return -1;
}
