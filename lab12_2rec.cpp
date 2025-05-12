#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createListRec(int values[], int size, int index = 0) {
    if (index >= size) return nullptr;

    Node* newNode = new Node{ values[index], nullptr };
    newNode->next = createListRec(values, size, index + 1);
    return newNode;
}

void deleteList(Node* head) {
    if (head == nullptr) return;
    deleteList(head->next);
    delete head;
}

void printList(Node* head) {
    if (head == nullptr) {
        cout << endl;
        return;
    }
    cout << head->data << " ";
    printList(head->next);
}

void deleteAfterValueHelper(Node* current, int value) {
    if (current == nullptr || current->next == nullptr) return;

    if (current->data == value) {
        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        deleteAfterValueHelper(current, value);
    }
    else {
        deleteAfterValueHelper(current->next, value);
    }
}

void deleteAfterValue(Node* head, int value) {
    if (head == nullptr) return;
    deleteAfterValueHelper(head, value);
}


int main() {
    int values[] = { 1, 2, 3, 4, 2, 5, 6, 2, 7 };
    int size = sizeof(values) / sizeof(values[0]);

    Node* head = createListRec(values, size, 0);

    cout << "(rec)Original list: ";
    printList(head);

    int target;
    cout << "Enter value after which to delete nodes: ";
    cin >> target;

    deleteAfterValue(head, target);

    cout << "Modified list: ";
    printList(head);

    deleteList(head);

    return 0;
}