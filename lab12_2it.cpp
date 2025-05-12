#include <iostream>
using namespace std;

typedef int Info;

struct Elem {
    Elem* next;
    Elem* prev;
    Info info;
};

void enqueue(Elem*& first, Elem*& last, Info value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->next = NULL;

    if (last != NULL)
        last->next = tmp;
    tmp->prev = last;
    last = tmp;

    if (first == NULL)
        first = tmp;
}

void printList(Elem* L) {
    while (L != NULL) {
        cout << L->info << " ";
        L = L->next;
    }
    cout << endl;
}

int countOccurrences(Elem* L, Info value) {
    int count = 0;
    while (L != NULL) {
        if (L->info == value)
            count++;
        L = L->next;
    }
    return count;
}

bool isSubset(Elem* L1, Elem* L2) {
    while (L1 != NULL) {
        int countL1 = countOccurrences(L1, L1->info);
        int countL2 = countOccurrences(L2, L1->info);

        if (countL2 < countL1)
            return false;

        Info current = L1->info;
        while (L1 != NULL && L1->info == current)
            L1 = L1->next;
    }
    return true;
}

void deleteList(Elem*& first) {
    while (first != NULL) {
        Elem* tmp = first->next;
        delete first;
        first = tmp;
    }
}

int main() {
    Elem* L1_first = NULL;
    Elem* L2_first = NULL;
    Elem* L1_last = NULL;
    Elem* L2_last = NULL;

    enqueue(L1_first, L1_last, 1);
    enqueue(L1_first, L1_last, 2);
    enqueue(L1_first, L1_last, 3);

    enqueue(L2_first, L2_last, 3);
    enqueue(L2_first, L2_last, 1);
    enqueue(L2_first, L2_last, 2);
    enqueue(L2_first, L2_last, 4);
    enqueue(L2_first, L2_last, 5);

    cout << "List L1: ";
    printList(L1_first);
    cout << "List L2: ";
    printList(L2_first);

    if (isSubset(L1_first, L2_first))
        cout << "All elements of L1 are present in L2" << endl;
    else
        cout << "Not all elements of L1 are present in L2" << endl;

    deleteList(L1_first);
    deleteList(L2_first);

    return 0;
}