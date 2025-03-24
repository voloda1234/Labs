#include <iostream>
#include <string>
using namespace std;

int Count(const string& s, size_t pos) {
    if (pos >= s.length() - 1) {
        return 0;
    }

    if ((s[pos] == 'a' && s[pos + 1] == 'a') ||
        (s[pos] == 'b' && s[pos + 1] == 'b') ||
        (s[pos] == 'c' && s[pos + 1] == 'c')) {
        return 1 + Count(s, pos + 2);
    }
    else {
        return Count(s, pos + 1);
    }
}

string Change(string& s, size_t pos) {
    if (pos >= s.length() - 1) {
        return s;
    }

    if ((s[pos] == 'a' && s[pos + 1] == 'a') ||
        (s[pos] == 'b' && s[pos + 1] == 'b') ||
        (s[pos] == 'c' && s[pos + 1] == 'c')) {
        s.replace(pos, 2, "***");
        return Change(s, pos + 3);
    }
    else {
        return Change(s, pos + 1);
    }
}

int main() {
    string str;
    cout << "Enter string:" << endl;
    getline(cin, str);

    cout << "String contained " << Count(str, 0) << " groups of 'aa', 'bb', or 'cc'" << endl;

    string dest = Change(str, 0);
    cout << "Modified string (param) : " << str << endl;
    cout << "Modified string (result): " << dest << endl;

    return 0;
}