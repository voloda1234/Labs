#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createList(int values[], int size) {
    if (size == 0) return nullptr;

    Node* head = new Node{ values[0], nullptr };
    Node* current = head;

    for (int i = 1; i < size; i++) {
        current->next = new Node{ values[i], nullptr };
        current = current->next;
    }

    return head;
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void deleteAfterValue(Node* head, int value) {
    Node* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->data == value) {
            Node* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
        }
        else
            current = current->next;
    }
}


int main() {
    int values[] = { 1, 2, 3, 4, 2, 5, 6, 2, 7 };
    int size = sizeof(values) / sizeof(values[0]);

    Node* head = createList(values, size);

    cout << "Original list: ";
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