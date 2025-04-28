#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialty { ComputerScience, Informatics, MathematicsandEconomics, PhysicsandInformatics, WorkbasedLearning };
const string specialtyNames[] = { "Computer Science","Informatics","Math and Economics","Physics and IT","Work-based Learning" };
enum Course { I = 1, II = 2, III = 3, IV = 4 };

struct Student {
    string lastName;
    Specialty specialty;
    Course course;
    int mathGrade;
    int physicsGrade;
    union {
        int ITGrade;
        int UnitMethod;
        int Pedagogy;
    } otherGrade;
};

void WriteStudent(fstream& file, const Student& s);
bool ReadStudent(fstream& file, Student& s);
int GetAverage(const Student& s);

void CreateFile(const string& filename);
void PrintFile(const string& filename);
double CalculateExcellentStudentsPercent(const string& filename);
int CountGoodGrades(const string& filename);
void Sort(const string& filename);
void PrintSortedByIndex(const string& filename);
int BinarySearch(const string& filename, const string& lastName, Course course, int averageGrade);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename;
    cout << "Enter filename: ";
    getline(cin, filename);

    int menuItem;
    do {
        cout << "\n\nChoose an action:\n\n";
        cout << " [1] - Enter data for students\n";
        cout << " [2] - Display data from file\n";
        cout << " [3] - Find percentage of excellent students (grade 5)\n";
        cout << " [4] - Count good grades (grade 4)\n";
        cout << " [5] - Sort file by criteria\n";
        cout << " [6] - Display sorted by index\n";
        cout << " [7] - Binary search\n";
        cout << " [0] - Exit\n\n";
        cout << "Enter your choice: ";
        cin >> menuItem;
        cin.ignore();

        switch (menuItem) {
        case 1:
            CreateFile(filename);
            break;
        case 2:
            PrintFile(filename);
            break;
        case 3:
        {
            double percent = CalculateExcellentStudentsPercent(filename);
            cout << "Percentage of excellent students: " << fixed << setprecision(2) << percent << "%\n";
            break;
        }
        case 4:
            cout << "Number of good grades: " << CountGoodGrades(filename) << "\n";
            break;
        case 5:
            Sort(filename);
            cout << "File sorted successfully!\n";
            break;
        case 6:
            PrintSortedByIndex(filename);
            break;
        case 7: {
            string lastName;
            int course, avgGrade;
            cout << "Enter search keys:\n";
            cout << " LastName: "; getline(cin, lastName);
            cout << " Course: "; cin >> course;
            cout << " Average grade: "; cin >> avgGrade;
            cin.ignore();

            int pos = BinarySearch(filename, lastName, static_cast<Course>(course), avgGrade);
            if (pos != -1)
                cout << "Found at position " << pos + 1 << endl;
            else
                cout << "Not found\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (menuItem != 0);

    return 0;
}

void WriteStudent(fstream& file, const Student& s) {
    size_t lastNameSize = s.lastName.size();
    file.write((char*)&lastNameSize, sizeof(lastNameSize));
    file.write(s.lastName.c_str(), lastNameSize);
    file.write((char*)&s.specialty, sizeof(s.specialty));
    file.write((char*)&s.course, sizeof(s.course));
    file.write((char*)&s.mathGrade, sizeof(s.mathGrade));
    file.write((char*)&s.physicsGrade, sizeof(s.physicsGrade));
    file.write((char*)&s.otherGrade, sizeof(s.otherGrade));
}

bool ReadStudent(fstream& file, Student& s) {
    size_t lastNameSize;
    file.read((char*)&lastNameSize, sizeof(lastNameSize));
    if (file.eof()) return false;

    char* buffer = new char[lastNameSize + 1];
    file.read(buffer, lastNameSize);
    buffer[lastNameSize] = '\0';
    s.lastName = buffer;
    delete[] buffer;

    file.read((char*)&s.specialty, sizeof(s.specialty));
    file.read((char*)&s.course, sizeof(s.course));
    file.read((char*)&s.mathGrade, sizeof(s.mathGrade));
    file.read((char*)&s.physicsGrade, sizeof(s.physicsGrade));
    file.read((char*)&s.otherGrade, sizeof(s.otherGrade));
    return true;
}

int GetAverage(const Student& p) {
    return (int)((p.mathGrade + p.physicsGrade + p.otherGrade.ITGrade) / 3);
}

void CreateFile(const string& filename) {
    fstream file(filename, ios::out | ios::binary);

    Student s;
    char choice;
    do {
        cout << "Enter student data:\n";
        cout << " Last name: "; getline(cin, s.lastName);
        cout << " Specialty (0-4): ";
        int spec; cin >> spec;
        s.specialty = static_cast<Specialty>(spec);
        cout << " Course (1-4): ";
        int crs; cin >> crs;
        s.course = static_cast<Course>(crs);
        cout << " Math grade: "; cin >> s.mathGrade;
        cout << " Physics grade: "; cin >> s.physicsGrade;

        switch (s.specialty) {
        case ComputerScience: cout << " IT grade: "; cin >> s.otherGrade.ITGrade; break;
        case Informatics: cout << " Unit method grade: "; cin >> s.otherGrade.UnitMethod; break;
        default: cout << " Pedagogy grade: "; cin >> s.otherGrade.Pedagogy;
        }

        WriteStudent(file, s);
        cout << "Add another student? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (tolower(choice) == 'y');

    file.close();
}

void PrintFile(const string& filename) {
    fstream file(filename, ios::in | ios::binary);
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    cout << "==========================================================================================================" << endl;
    cout << "| # |    Last Name     |     Specialty     | Course | Math |  Phys |  ITGrade  | UnitMethod |  Pedagogy  |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

    Student s;
    int counter = 1;

    while (ReadStudent(file, s))
    {
        cout << "| " << setw(2) << right << counter + 1 << " ";
        cout << "| " << setw(16) << left << s.lastName;
        cout << "| " << setw(18) << left << specialtyNames[s.specialty];
        cout << "| " << setw(7) << right << s.course;
        cout << "| " << setw(5) << right << s.mathGrade;
        cout << "| " << setw(6) << right << s.physicsGrade;

        switch (s.specialty)
        {
        case ComputerScience:
            cout << "| " << setw(10) << right << s.otherGrade.ITGrade;
            cout << "| " << setw(11) << right << "-";
            cout << "| " << setw(9) << right << "-";
            break;
        case Informatics:
            cout << "| " << setw(10) << right << "-";
            cout << "| " << setw(11) << right << s.otherGrade.UnitMethod;
            cout << "| " << setw(9) << right << "-";
            break;
        default:
            cout << "| " << setw(10) << right << "-";
            cout << "| " << setw(11) << right << "-";
            cout << "| " << setw(9) << right << s.otherGrade.Pedagogy;
        }
        cout << " |" << endl;
    }

    cout << "==========================================================================================================\n";
    file.close();
}

double CalculateExcellentStudentsPercent(const string& filename) {
    fstream file(filename, ios::in | ios::binary);
    if (!file) return 0.0;

    int total = 0, excellent = 0;
    Student s;

    while (ReadStudent(file, s)) {
        total++;
        if (s.mathGrade == 5 || s.physicsGrade == 5) excellent++;
    }

    file.close();
    return total ? (100.0 * excellent / total) : 0.0;
}

int CountGoodGrades(const string& filename) {
    fstream file(filename, ios::in | ios::binary);
    if (!file) return 0;

    int count = 0;
    Student s;

    while (ReadStudent(file, s)) 
    {
        if (s.mathGrade == 4) count++;
        if (s.physicsGrade == 4) count++;
        if (s.otherGrade.ITGrade == 4) count++;
    }

    file.close();
    return count;
}

void Sort(const string& filename) {
    fstream file(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    file.seekg(0, ios::end);
    int studentCount = file.tellg() / sizeof(Student);
    file.seekg(0, ios::beg);

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            file.seekg(j * sizeof(Student));
            Student current;
            ReadStudent(file, current);

            Student next;
            ReadStudent(file, next);

            bool shouldSwap = false;
            if (GetAverage(current) < GetAverage(next)) {
                shouldSwap = true;
            }
            else if (GetAverage(current) == GetAverage(next)) {
                if (current.course > next.course) {
                    shouldSwap = true;
                }
                else if (current.course == next.course) {
                    if (current.lastName > next.lastName) {
                        shouldSwap = true;
                    }
                }
            }

            if (shouldSwap) {
                file.seekp(j * sizeof(Student));
                WriteStudent(file, next);
                WriteStudent(file, current);
            }
        }
    }

    file.close();
}

void PrintSortedByIndex(const string& filename) {
    fstream file(filename, ios::in | ios::binary);
    if (!file) {
        cerr << "Error opening file!\n";
        return;
    }

    file.seekg(0, ios::end);
    int studentCount = file.tellg() / sizeof(Student);
    file.seekg(0, ios::beg);

    if (studentCount == 0) {
        cout << "No students in file!\n";
        file.close();
        return;
    }

    int* indexes = new int[studentCount];
    int* avgGrades = new int[studentCount];
    Course* courses = new Course[studentCount];
    string* lastNames = new string[studentCount];

    Student s;
    for (int i = 0; i < studentCount; i++) {
        indexes[i] = i;
        file.seekg(i * sizeof(Student));
        avgGrades[i] = GetAverage(s);
        courses[i] = s.course;
        lastNames[i] = s.lastName;
    }

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            bool shouldSwap = false;

            if (avgGrades[indexes[j]] < avgGrades[indexes[j + 1]]) {
                shouldSwap = true;
            }
            else if (avgGrades[indexes[j]] == avgGrades[indexes[j + 1]] &&
                courses[indexes[j]] > courses[indexes[j + 1]]) {
                shouldSwap = true;
            }
            else if (avgGrades[indexes[j]] == avgGrades[indexes[j + 1]] &&
                courses[indexes[j]] == courses[indexes[j + 1]] &&
                lastNames[indexes[j]] > lastNames[indexes[j + 1]]) {
                shouldSwap = true;
            }

            if (shouldSwap) {
                swap(indexes[j], indexes[j + 1]);
            }
        }
    }

    cout << "==========================================================================================================" << endl;
    cout << "| # |    Last Name     |     Specialty     | Course | Math |  Phys |  ITGrade  | UnitMethod |  Pedagogy  |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

    int counter = 1;

    while (ReadStudent(file, s))
    {
        cout << "| " << setw(2) << right << counter + 1 << " ";
        cout << "| " << setw(16) << left << s.lastName;
        cout << "| " << setw(18) << left << specialtyNames[s.specialty];
        cout << "| " << setw(7) << right << s.course;
        cout << "| " << setw(5) << right << s.mathGrade;
        cout << "| " << setw(6) << right << s.physicsGrade;

        switch (s.specialty)
        {
        case ComputerScience:
            cout << "| " << setw(10) << right << s.otherGrade.ITGrade;
            cout << "| " << setw(11) << right << "-";
            cout << "| " << setw(9) << right << "-";
            break;
        case Informatics:
            cout << "| " << setw(10) << right << "-";
            cout << "| " << setw(11) << right << s.otherGrade.UnitMethod;
            cout << "| " << setw(9) << right << "-";
            break;
        default:
            cout << "| " << setw(10) << right << "-";
            cout << "| " << setw(11) << right << "-";
            cout << "| " << setw(9) << right << s.otherGrade.Pedagogy;
        }
        cout << " |" << endl;
    }

    cout << "==========================================================================================================\n";

    delete[] indexes;
    delete[] avgGrades;
    delete[] courses;
    delete[] lastNames;
    file.close();
}

int BinarySearch(const string& filename, const string& lastName, Course course, int averageGrade) {
    fstream file(filename, ios::in | ios::binary);
    if (!file) return -1;

    int left = 0;
    file.seekg(0, ios::end);
    int right = file.tellg() / sizeof(Student) - 1;
    file.seekg(0);

    while (left <= right) {
        int mid = (left + right) / 2;
        file.seekg(mid * sizeof(Student));

        Student s;
        if (!ReadStudent(file, s)) break;

        if (s.lastName == lastName && s.course == course && GetAverage(s) == averageGrade) {
            file.close();
            return mid;
        }
        else if (GetAverage(s) < averageGrade ||
            (GetAverage(s) == averageGrade && s.course < course) ||
            (GetAverage(s) == averageGrade && s.course == course && s.lastName < lastName)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    file.close();
    return -1;
}