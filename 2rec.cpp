#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int Count(const char* s, int k) {
    const char* pos = strstr(s, "aa");
    if (pos != NULL) {
        k++; 
        return Count(pos + 2, k); 
    }

    pos = strstr(s, "bb");
    if (pos != NULL) {
        k++; 
        return Count(pos + 2, k); 
    }

    pos = strstr(s, "cc");
    if (pos != NULL) {
        k++; 
        return Count(pos + 2, k); 
    }

    return k; 
}

char* Change(char* s, char* t = nullptr, size_t len = 0, int pos1 = 0) {
    if (t == nullptr) {
        len = strlen(s);
        t = new char[len * 3 + 1]; 
        t[0] = '\0'; 
    }

    char* p = nullptr;
    int pos2 = 0;

    if ((p = strstr(s + pos1, "aa")) || (p = strstr(s + pos1, "bb")) || (p = strstr(s + pos1, "cc"))) {
        pos2 = p - s; 
        strncat(t, s + pos1, pos2 - pos1);
        strcat(t, "***");
        return Change(s, t, len, pos2 + 2); 
    }

    strcat(t, s + pos1);

    strcpy(s, t);
    delete[] t; 

    return s;
}

//int main() {
//    char str[101];
//
//    cout << "Enter string:" << endl;
//    cin.getline(str, 100);
//
//    cout << "String contained " << Count(str, 0) << " groups of 'aa', 'bb', 'cc'" << endl;
//
//    Change(str, 0, 0);
//
//    cout << "Modified string: " << str << endl;
//
//    return 0;
//}