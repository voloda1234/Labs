#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <windows.h>

using namespace std;

const int MAX_SPECIALITIES = 10;
const int MAX_FACULTIES = 5;
const int MAX_NAME_LENGTH = 50;

struct Speciality {
    char name[MAX_NAME_LENGTH];
    int seats;
};

struct Faculty {
    char name[MAX_NAME_LENGTH];
    Speciality specialities[MAX_SPECIALITIES];
    int specialityCount;
};

struct Institute {
    char city[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];
    int admissionPlan;
    Faculty faculties[MAX_FACULTIES];
    int facultyCount;
};

void InputInstitute(Institute& inst);
void PrintInstitute(const Institute& inst);
void WriteToFile(const char* filename, const Institute& inst);
void ReadFromFile(const char* filename);
void AppendToFile(const char* filename);
void ReplaceInFile(const char* filename, int index, const Institute& newInst);
void DeleteFromFile(const char* filename, int index);
void FindByKeyword(const char* filename);
void FindBySpeciality(const char* filename, const char* search);
void FindMaxSeatsSpeciality(const char* filename, const char* search);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char filename[100];
    cout << "Enter file name: ";
    cin.getline(filename, 100);

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1 - Create institute and write to file\n";
        cout << "2 - Show all records from file\n";
        cout << "3 - Append to file\n";
        cout << "4 - Replace record in file\n";
        cout << "5 - Delete record from file\n";
        cout << "6 - Search for specialities with keywords\n";
        cout << "7 - Institutes offering a specific speciality\n";
        cout << "8 - Speciality with max number of seats\n";
        cout << "0 - Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Institute inst;
            InputInstitute(inst);
            WriteToFile(filename, inst);
        }
        else if (choice == 2) {
            ReadFromFile(filename);
        }
        else if (choice == 3) {
            AppendToFile(filename);
        }
        else if (choice == 4) {
            int index;
            cout << "Enter record index to replace: ";
            cin >> index;
            cin.ignore();
            Institute inst;
            InputInstitute(inst);
            ReplaceInFile(filename, index, inst);
        }
        else if (choice == 5) {
            int index;
            cout << "Enter record index to delete: ";
            cin >> index;
            cin.ignore();
            DeleteFromFile(filename, index);
        }
        else if (choice == 6) {
            FindByKeyword(filename);
        }
        else if (choice == 7) {
            char speciality[MAX_NAME_LENGTH];
            cout << "Enter speciality name: ";
            cin.getline(speciality, MAX_NAME_LENGTH);
            FindBySpeciality(filename, speciality);
        }
        else if (choice == 8) {
            char speciality[MAX_NAME_LENGTH];
            cout << "Enter speciality name: ";
            cin.getline(speciality, MAX_NAME_LENGTH);
            FindMaxSeatsSpeciality(filename, speciality);
        }
    } while (choice != 0);

    return 0;
}

void InputInstitute(Institute& inst) {
    cout << "City: ";
    cin.getline(inst.city, MAX_NAME_LENGTH);

    cout << "Institute name: ";
    cin.getline(inst.name, MAX_NAME_LENGTH);

    cout << "Admission plan: ";
    cin >> inst.admissionPlan;
    cin.ignore();

    cout << "Number of faculties: ";
    cin >> inst.facultyCount;
    cin.ignore();

    for (int i = 0; i < inst.facultyCount; ++i) {
        cout << "Faculty " << i + 1 << " name: ";
        cin.getline(inst.faculties[i].name, MAX_NAME_LENGTH);

        cout << "Number of specialities: ";
        cin >> inst.faculties[i].specialityCount;
        cin.ignore();

        for (int j = 0; j < inst.faculties[i].specialityCount; ++j) {
            cout << "Speciality " << j + 1 << " name: ";
            cin.getline(inst.faculties[i].specialities[j].name, MAX_NAME_LENGTH);

            cout << "Number of seats: ";
            cin >> inst.faculties[i].specialities[j].seats;
            cin.ignore();
        }
    }
}

void PrintInstitute(const Institute& inst) {
    cout << "\nCity: " << inst.city << "\nInstitute: " << inst.name
        << "\nAdmission plan: " << inst.admissionPlan << "\n";

    for (int i = 0; i < inst.facultyCount; ++i) {
        cout << "  Faculty: " << inst.faculties[i].name << "\n";
        for (int j = 0; j < inst.faculties[i].specialityCount; ++j) {
            cout << "    Speciality: " << inst.faculties[i].specialities[j].name
                << " (seats: " << inst.faculties[i].specialities[j].seats << ")\n";
        }
    }
}

void WriteToFile(const char* filename, const Institute& inst) {
    ofstream fout(filename, ios::binary | ios::trunc);
    fout.write((char*)&inst, sizeof(Institute));
    fout.close();
}

void AppendToFile(const char* filename) {
    Institute inst;
    InputInstitute(inst);
    ofstream fout(filename, ios::binary | ios::app);
    fout.write((char*)&inst, sizeof(Institute));
    fout.close();
}

void ReadFromFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    Institute inst;
    int i = 0;
    while (fin.read((char*)&inst, sizeof(Institute))) {
        cout << "\n--- Record #" << i++ << " ---";
        PrintInstitute(inst);
    }
    fin.close();
}

void ReplaceInFile(const char* filename, int index, const Institute& newInst) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    file.seekp(index * sizeof(Institute), ios::beg);
    file.write((char*)&newInst, sizeof(Institute));
    file.close();
}

void DeleteFromFile(const char* filename, int index) {
    ifstream fin(filename, ios::binary);
    ofstream fout("temp.dat", ios::binary);

    Institute inst;
    int i = 0;
    while (fin.read((char*)&inst, sizeof(Institute))) {
        if (i != index)
            fout.write((char*)&inst, sizeof(Institute));
        ++i;
    }
    fin.close();
    fout.close();

    remove(filename);
    rename("temp.dat", filename);
}


bool ContainsKeyword(const char* text) {
    return strstr(text, "comp") || strstr(text, "auto");
}

void FindByKeyword(const char* filename) {
    ifstream fin(filename, ios::binary);
    Institute inst;
    while (fin.read((char*)&inst, sizeof(Institute))) {
        for (int i = 0; i < inst.facultyCount; ++i) {
            for (int j = 0; j < inst.faculties[i].specialityCount; ++j) {
                if (ContainsKeyword(inst.faculties[i].specialities[j].name)) {
                    cout << inst.faculties[i].specialities[j].name << endl;
                }
            }
        }
    }
    fin.close();
}

void FindBySpeciality(const char* filename, const char* search) {
    ifstream fin(filename, ios::binary);
    Institute inst;
    while (fin.read((char*)&inst, sizeof(Institute))) {
        for (int i = 0; i < inst.facultyCount; ++i) {
            for (int j = 0; j < inst.faculties[i].specialityCount; ++j) {
                if (strcmp(inst.faculties[i].specialities[j].name, search) == 0) {
                    cout << "Institute: " << inst.name
                        << ", Faculty: " << inst.faculties[i].name << endl;
                }
            }
        }
    }
    fin.close();
}

void FindMaxSeatsSpeciality(const char* filename, const char* search) {
    ifstream fin(filename, ios::binary);
    Institute maxInst;
    Faculty maxFac;
    Speciality maxSpec;
    int maxSeats = -1;

    Institute inst;
    while (fin.read((char*)&inst, sizeof(Institute))) {
        for (int i = 0; i < inst.facultyCount; ++i) {
            for (int j = 0; j < inst.faculties[i].specialityCount; ++j) {
                Speciality& s = inst.faculties[i].specialities[j];
                if (strcmp(s.name, search) == 0 && s.seats > maxSeats) {
                    maxSeats = s.seats;
                    maxInst = inst;
                    maxFac = inst.faculties[i];
                    maxSpec = s;
                }
            }
        }
    }

    if (maxSeats != -1) {
        cout << "City: " << maxInst.city << "\nInstitute: " << maxInst.name
            << "\nFaculty: " << maxFac.name
            << "\nSpeciality: " << maxSpec.name
            << " (seats: " << maxSpec.seats << ")\n";
    }
    else {
        cout << "Speciality \"" << search << "\" not found.\n";
    }
    fin.close();
}

