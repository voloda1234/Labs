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

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Enter the number of students N: "; cin >> N;

    Student* p = new Student[N];
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose an action:" << endl << endl;
        cout << " [1] - Enter data for student" << endl;
        cout << " [2] - Display data on screen" << endl;
        cout << " [3] - Find percents of students which (5 Grade) with physic and math" << endl;
        cout << " [4] - Find Number Of Good Grades" << endl;
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
    cout << "========================================================================================================" << endl;
    cout << "| # |    Last Name     |     Specialty     | Course | Math |  Phys |  ITGrade  | UnitMethod  |Pedagogy |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

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
            cout << "| " << setw(9) << right << "-";
            cout << "| " << setw(8) << right << p[i].otherGrade.Pedagogy;
        }
        cout << " |" << endl;
    }

    cout << "========================================================================================================" << endl;
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
        if (p[i].mathGrade == 3)
            k++;
        if (p[i].physicsGrade == 3)
            k++;
        if (p[i].otherGrade.ITGrade == 3 || p[i].otherGrade.UnitMethod == 3 || p[i].otherGrade.Pedagogy == 3)
            k++;
    }
    return k;
}