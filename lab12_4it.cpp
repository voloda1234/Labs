#include <iostream>
#include <iomanip>
using namespace std;

typedef int Info;

struct Elem {
    Elem* link;
    Info info;
};

void insert(Elem*& L, Info value) {
    Elem* tmp = new Elem;
    tmp->info = value;

    if (L != NULL) {
        Elem* T = L;
        while (T->link != L)
            T = T->link;
        T->link = tmp;
    }
    else {
        L = tmp;
    }
    tmp->link = L;
}

void printList(Elem* L) {
    if (L == NULL) {
        cout << "Список порожній" << endl;
        return;
    }

    Elem* first = L;
    cout << setw(4) << L->info;
    while (L->link != first) {
        L = L->link;
        cout << setw(4) << L->info;
    }
    cout << endl;
}

int countElements(Elem* L, Info value) {
    if (L == NULL)
        return 0;

    int count = 0;
    Elem* first = L;

    do {
        if (L->info == value)
            count++;
        L = L->link;
    } while (L != first);

    return count;
}

void deleteList(Elem*& L) {
    if (L == NULL)
        return;

    Elem* first = L;
    Elem* tmp;

    do {
        tmp = L;
        L = L->link;
        delete tmp;
    } while (L != first);

    L = NULL;
}

int main() {
    Elem* L = NULL;

    for (int i = 1; i <= 10; i++) {
        insert(L, i % 3 + 1);
    }

    cout << "Print: ";
    printList(L);

    int value;
    cout << "Enter search value: ";
    cin >> value;

    int countIter = countElements(L, value);
    cout << "Number of elements with value" << countIter << endl;

    deleteList(L);

    return 0;
}