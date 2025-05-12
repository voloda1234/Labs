#include <iostream>
#include <iomanip>
using namespace std;

typedef int Info;

struct Node {
    Node* next;
    Info data;
};

void insert(Node*& head, Info value, Node* start = nullptr, bool firstCall = true) {
    if (firstCall) {
        if (head == nullptr) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->next = newNode;
            head = newNode;
            return;
        }
        start = head;
    }

    if (head->next == start) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = start;
        head->next = newNode;
        return;
    }

    insert(head->next, value, start, false);
}

void printList(Node* current, Node* start = nullptr, bool firstCall = true) {
    if (current == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    if (firstCall) {
        start = current;
        cout << setw(4) << current->data;
    }

    if (current->next != start) {
        cout << setw(4) << current->next->data;
        printList(current->next, start, false);
    }
    else {
        cout << endl;
    }
}

int countElements(Node* current, Info value, Node* start = nullptr, bool firstCall = true) {
    if (current == nullptr)
        return 0;

    if (firstCall)
        start = current;

    int count = (current->data == value) ? 1 : 0;

    if (current->next != start)
        return count + countElements(current->next, value, start, false);
    else
        return count;
}

void deleteList(Node*& head, Node* current = nullptr, Node* start = nullptr, bool firstCall = true) {
    if (head == nullptr)
        return;

    if (firstCall) {
        start = head;
        current = head;
    }

    if (current->next != start) {
        Node* nextNode = current->next;
        delete current;
        deleteList(head, nextNode, start, false);
    }
    else {
        delete current;
        head = nullptr;
    }
}

int main() {
    Node* head = nullptr;

    for (int i = 1; i <= 10; i++) {
        insert(head, i % 3 + 1);
    }

    cout << "List: ";
    printList(head);

    int value;
    cout << "Enter value to search: ";
    cin >> value;

    int count = countElements(head, value);
    cout << "Number of elements with value " << value << ": " << count << endl;

    deleteList(head);

    return 0;
}