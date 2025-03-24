#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int Count(const char* s)
{
	int k = 0;
	const char* pos = s;

	while ((pos = strstr(pos, "aa")) != NULL) {
		k++;
		pos++;
	}

	pos = s;
	while ((pos = strstr(pos, "bb")) != NULL) {
		k++;
		pos++;
	}
	
	pos = s;
	while ((pos = strstr(pos, "cc")) != NULL) {
		k++;
		pos++;
	}

	return k;
}
char* Change(char* s) {
	size_t len = strlen(s);
	char* t = new char[len * 3 + 1];
	t[0] = '\0'; 

	char* p;
	int pos1 = 0, pos2 = 0;

	while ((p = strstr(s + pos1, "aa")) || (p = strstr(s + pos1, "bb")) || (p = strstr(s + pos1, "cc"))) {
		pos2 = p - s;
		strncat(t, s + pos1, pos2 - pos1);
		strcat(t, "***");
		pos1 = pos2 + 2;
	}
	strcat(t, s + pos1);

	strcpy(s, t);
	delete[] t;

	return s;
}


int main()
{
	char str[101];

	cout << "Enter string:" << endl;
	cin.getline(str, 100);
	cout << "String contained " << Count(str) << " groups of 'aa' 'bb' 'cc'" << endl;

	char* dest = new char[151];
	dest = Change(str);
	cout << "Modified string (param) : " << str << endl;
	cout << "Modified string (result): " << dest << endl;
	return 0;
}