#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int CountRec(char* str, int i, int count)
{
    if (i >= strlen(str) - 1)
        return count;

    if ((str[i] == 'a' && str[i + 1] == 'a') || (str[i] == 'b' && str[i + 1] == 'b') || (str[i] == 'c' && str[i + 1] == 'c'))
        return CountRec(str, i + 1, count + 1);
    else
        return CountRec(str, i + 1, count);
}
char* ChangeRec(char* str, size_t i, char* tmp, char* t)
{
    size_t len = strlen(str);
    if (len < 2)
        return str;

    if (i >= len)
    {
        *t = '\0'; 
        return tmp;
    }

    if ((str[i] == 'a' && str[i + 1] == 'a') ||
        (str[i] == 'b' && str[i + 1] == 'b') ||
        (str[i] == 'c' && str[i + 1] == 'c'))
    {
        strcat(t, "***");
        t += 3; 
        return ChangeRec(str, i + 2, tmp, t);
    }
    else
    {
        *t++ = str[i]; 
        return ChangeRec(str, i + 1, tmp, t); 
    }
}
int main()
{
    char str[101];
    cout << "Enter string:" << endl;
    cin.getline(str, 100);
    cout << "String contained |aa or bb or cc|:" << CountRec(str, 0, 0) << endl;

    char* tmp = new char[strlen(str) * 3 / 2 + 1];
    char* t = tmp; 

    ChangeRec(str, 0, tmp, t);

    cout << "Modified string (param) : " << str << endl;
    cout << "Modified string1 (result): " << tmp << endl;
    return 0;
}