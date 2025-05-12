#include <iostream>
using namespace std;

typedef int Info;

struct Elem {
    Elem* next;
    Elem* prev;
    Info info;
};

void enqueue(Elem*& first, Elem*& last, Info value) {
    if (first == NULL) {
        first = new Elem;
        first->info = value;
        first->next = NULL;
        first->prev = NULL;
        last = first;
    }
    else {
        enqueue(first->next, last, value);
        if (first->next != NULL) {
            first->next->prev = first;
            if (first->next->next == NULL) {
                last = first->next;
            }
        }
    }
}

void printList(Elem* L) {
    if (L == NULL) {
        cout << endl;
        return;
    }
    cout << L->info << " ";
    printList(L->next);
}

int countOccurrences(Elem* L, Info value) {
    if (L == NULL) return 0;
    return (L->info == value ? 1 : 0) + countOccurrences(L->next, value);
}

bool isSubset(Elem* L1, Elem* L2) {
    if (L1 == NULL) return true;

    int countL1 = countOccurrences(L1, L1->info);
    int countL2 = countOccurrences(L2, L1->info);

    if (countL2 < countL1) return false;

    Info current = L1->info;
    while (L1 != NULL && L1->info == current) {
        L1 = L1->next;
    }

    return isSubset(L1, L2);
}

void deleteList(Elem*& first) {
    if (first == NULL) return;
    Elem* next = first->next;
    delete first;
    first = next;
    deleteList(first);
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