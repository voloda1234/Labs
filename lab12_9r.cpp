#include <iostream>
#include <climits>
using namespace std;

typedef int Info;

struct Node {
    Node* left;
    Node* right;
    Info info;
};

Node* CreateTree(int nodeCount);
void PrintTree(Node* root, int level, Node* highlight = NULL);
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
void PostfixOrder(Node* root, Info& minVal, Node*& minNode);

int main() {
    Node* root = NULL;
    int choice, N;
    Info value;
    bool found;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create binary tree\n";
        cout << "2. Create binary search tree\n";
        cout << "3. Add element to BST\n";
        cout << "4. Print tree\n";
        cout << "5. Find first min element (postfix order)\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter number of nodes: ";
            cin >> N;
            root = CreateTree(N);
            break;
        }
        case 2: {
            cout << "Enter number of nodes: ";
            cin >> N;
            root = NULL;
            for (int i = 0; i < N; i++) {
                cout << "Enter value " << i + 1 << ": ";
                cin >> value;
                BinarySearchInsert(root, value, found);
            }
            break;
        }
        case 3: {
            cout << "Enter value to add: ";
            cin >> value;
            BinarySearchInsert(root, value, found);
            break;
        }
        case 4: {
            cout << "Tree:\n";
            PrintTree(root, 0, NULL);
            break;
        }
        case 5: {
            Info minVal = INT_MAX;
            Node* minNode = NULL;
            PostfixOrder(root, minVal, minNode);

            if (minNode != NULL) {
                cout << "First min element in postfix order: " << minVal << endl;
                cout << "Tree with highlighted element:\n";
                PrintTree(root, 0, minNode);
            }
            else {
                cout << "Tree is empty!\n";
            }
            break;
        }
        case 0: {
            cout << "Exiting...\n";
            break;
        }
        default: {
            cout << "Invalid choice!\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}

Node* CreateTree(int nodeCount) {
    if (nodeCount == 0)
        return NULL;
    else {
        Node* newNode = new Node;
        cout << "Enter node value: ";
        cin >> newNode->info;

        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

void PrintTree(Node* root, int level, Node* highlight = NULL) {
    if (root != NULL) {
        PrintTree(root->right, level + 1, highlight);
        for (int i = 1; i <= level; i++)
            cout << " ";

        if (root == highlight)
            cout << "[" << root->info << "]" << endl;
        else
            cout << root->info << endl;

        PrintTree(root->left, level + 1, highlight);
    }
}

Node* BinarySearchInsert(Node*& root, Info value, bool& found) {
    if (root == NULL) {
        root = new Node;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        found = false;
        return root;
    }
    else if (value == root->info) {
        found = true;
        return root;
    }
    else if (value < root->info)
        return BinarySearchInsert(root->left, value, found);
    else
        return BinarySearchInsert(root->right, value, found);
}

void PostfixOrder(Node* root, Info& minVal, Node*& minNode) {
    if (root != NULL) {
        PostfixOrder(root->left, minVal, minNode);
        PostfixOrder(root->right, minVal, minNode);

        if (root->info < minVal) {
            minVal = root->info;
            minNode = root;
        }
    }
}