#include <iostream>
#include <string>
using namespace std;

int Count(const string& s) {
	int k = 0;
	size_t pos = 0;

	while (pos < s.length() - 1) {
		if ((s[pos] == 'a' && s[pos + 1] == 'a') ||
			(s[pos] == 'b' && s[pos + 1] == 'b') ||
			(s[pos] == 'c' && s[pos + 1] == 'c')) {
			k++;
			pos += 2; 
		}
		else {
			pos++;
		}
	}

	return k;
}
string Change(string& s) {
    size_t pos = 0;

    while (pos < s.length() - 1) {
        if ((s[pos] == 'a' && s[pos + 1] == 'a') ||
            (s[pos] == 'b' && s[pos + 1] == 'b') ||
            (s[pos] == 'c' && s[pos + 1] == 'c')) {
            s.replace(pos, 2, "***"); 
            pos += 3;
        }
        else {
            pos++;
        }
    }

    return s;
}

//int main() {
//    string str;
//    cout << "Enter string:" << endl;
//    getline(cin, str);
//
//    cout << "String contained |aa or bb or cc|:" << Count(str) << endl;
//
//    string dest = Change(str);
//    cout << "Modified string (param) : " << str << endl;
//    cout << "Modified string (result): " << dest << endl;
//
//    return 0;
//}