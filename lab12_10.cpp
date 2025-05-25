#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    string word;
    int count;
};

Node* CreateNode(const string& word);
Node* InsertWord(Node* root, const string& word);
void PrintTree(Node* root, int level);
int CountNodes(Node* root);
int CountLevels(Node* root);
Node* SearchWord(Node* root, const string& word);
void ReadWordsFromFile(Node*& root, const string& filename);
void SaveTreeToFile(Node* root, ofstream& file);
void SaveToFile(Node* root, const string& filename);
void DeleteTree(Node* root);

int main() {
    Node* root = nullptr;
    string filename, searchWord;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Load words from file\n";
        cout << "2. Add word manually\n";
        cout << "3. Print tree\n";
        cout << "4. Search for a word\n";
        cout << "5. Show node count\n";
        cout << "6. Show tree depth\n";
        cout << "7. Save tree to file\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter filename to load from: ";
            cin >> filename;
            ReadWordsFromFile(root, filename);
            break;
        }
        case 2: {
            cout << "Enter word to add: ";
            cin >> searchWord;
            root = InsertWord(root, searchWord);
            break;
        }
        case 3: {
            cout << "Tree:\n";
            PrintTree(root, 0);
            break;
        }
        case 4: {
            cout << "Enter word to search: ";
            cin >> searchWord;
            Node* found = SearchWord(root, searchWord);
            if (found != nullptr) {
                cout << "Word '" << searchWord << "' found. Occurrences: " << found->count << endl;
            }
            else {
                cout << "Word '" << searchWord << "' not found in the tree.\n";
            }
            break;
        }
        case 5: {
            cout << "Number of nodes in the tree: " << CountNodes(root) << endl;
            break;
        }
        case 6: {
            cout << "Tree depth: " << CountLevels(root) << endl;
            break;
        }
        case 7: {
            cout << "Enter filename to save to: ";
            cin >> filename;
            SaveToFile(root, filename);
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

    DeleteTree(root);
    return 0;
}

Node* CreateNode(const string& word) {
    Node* newNode = new Node;
    newNode->word = word;
    newNode->count = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* InsertWord(Node* root, const string& word) {
    if (root == nullptr) {
        return CreateNode(word);
    }

    if (word == root->word) {
        root->count++;
    }
    else if (word < root->word) {
        root->left = InsertWord(root->left, word);
    }
    else {
        root->right = InsertWord(root->right, word);
    }

    return root;
}

void PrintTree(Node* root, int level) {
    if (root != nullptr) {
        PrintTree(root->right, level + 1);
        for (int i = 0; i < level; i++) cout << "    ";
        cout << root->word << " (" << root->count << ")" << endl;
        PrintTree(root->left, level + 1);
    }
}

int CountNodes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

int CountLevels(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = CountLevels(root->left);
    int rightHeight = CountLevels(root->right);
    return max(leftHeight, rightHeight) + 1;
}

Node* SearchWord(Node* root, const string& word) {
    if (root == nullptr || root->word == word) {
        return root;
    }

    if (word < root->word) {
        return SearchWord(root->left, word);
    }
    else {
        return SearchWord(root->right, word);
    }
}

void ReadWordsFromFile(Node*& root, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    string word;
    while (file >> word) {
        root = InsertWord(root, word);
    }

    file.close();
    cout << "Words successfully loaded from file.\n";
}

void SaveTreeToFile(Node* root, ofstream& file) {
    if (root != nullptr) {
        SaveTreeToFile(root->left, file);
        file << root->word << " " << root->count << endl;
        SaveTreeToFile(root->right, file);
    }
}

void SaveToFile(Node* root, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error creating file!\n";
        return;
    }

    SaveTreeToFile(root, file);
    file.close();
    cout << "Tree successfully saved to file.\n";
}

void DeleteTree(Node* root) {
    if (root == nullptr) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}