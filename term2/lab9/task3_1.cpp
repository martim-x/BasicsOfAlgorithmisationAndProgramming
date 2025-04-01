#include <iostream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;


struct Tree {
    int key;
    int intVal1;
    int intVal2;
    int intVal3;
    Tree* Left;
    Tree* Right;
};


int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}


Tree* createNode(int key, int intVal1, int intVal2, int intVal3) {
    Tree* newNode = new Tree;
    newNode->key = key;
    newNode->intVal1 = intVal1;
    newNode->intVal2 = intVal2;
    newNode->intVal3 = intVal3;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}


Tree* insertElem(Tree* root, int key, int intVal1, int intVal2, int intVal3) {
    if (root == nullptr) {
        return createNode(key, intVal1, intVal2, intVal3);
    }

    if (key < root->key) {
        root->Left = insertElem(root->Left, key, intVal1, intVal2, intVal3);
    }
    else if (key > root->key) {
        root->Right = insertElem(root->Right, key, intVal1, intVal2, intVal3);
    }

    return root;
}


Tree* deleteMinSumNode(Tree* root) {
    if (root == nullptr) return nullptr;

    Tree* minNode = root;
    int minSum = root->intVal1 + root->intVal2 + root->intVal3;
    Tree* parent = nullptr;

    queue<pair<Tree*, Tree*>> q;
    q.push({ root, nullptr });

    while (!q.empty()) {
        auto currentPair = q.front();
        q.pop();

        Tree* current = currentPair.first;
        Tree* currentParent = currentPair.second;

        int currentSum = current->intVal1 + current->intVal2 + current->intVal3;
        if (currentSum < minSum || (currentSum == minSum && current->key < minNode->key)) {
            minSum = currentSum;
            minNode = current;
            parent = currentParent;
        }

        if (current->Left) q.push({ current->Left, current });
        if (current->Right) q.push({ current->Right, current });
    }


    if (parent == nullptr) {
        if (minNode->Left == nullptr && minNode->Right == nullptr) {
            delete minNode;
            return nullptr;
        }
        if (minNode->Left == nullptr) {
            Tree* newRoot = minNode->Right;
            delete minNode;
            return newRoot;
        }
        if (minNode->Right == nullptr) {
            Tree* newRoot = minNode->Left;
            delete minNode;
            return newRoot;
        }

        Tree* successorParent = minNode;
        Tree* successor = minNode->Right;
        while (successor->Left != nullptr) {
            successorParent = successor;
            successor = successor->Left;
        }

        minNode->key = successor->key;
        minNode->intVal1 = successor->intVal1;
        minNode->intVal2 = successor->intVal2;
        minNode->intVal3 = successor->intVal3;

        if (successorParent == minNode) {
            successorParent->Right = successor->Right;
        }
        else {
            successorParent->Left = successor->Right;
        }
        delete successor;
        return root;
    }
    else {
        bool isLeft = (parent->Left == minNode);

        if (minNode->Left == nullptr && minNode->Right == nullptr) {
            if (isLeft) parent->Left = nullptr;
            else parent->Right = nullptr;
        }
        else if (minNode->Left == nullptr || minNode->Right == nullptr) {
            Tree* child = minNode->Left ? minNode->Left : minNode->Right;
            if (isLeft) parent->Left = child;
            else parent->Right = child;
        }
        else {
            Tree* successorParent = minNode;
            Tree* successor = minNode->Right;
            while (successor->Left != nullptr) {
                successorParent = successor;
                successor = successor->Left;
            }

            minNode->key = successor->key;
            minNode->intVal1 = successor->intVal1;
            minNode->intVal2 = successor->intVal2;
            minNode->intVal3 = successor->intVal3;

            if (successorParent == minNode) {
                successorParent->Right = successor->Right;
            }
            else {
                successorParent->Left = successor->Right;
            }
            delete successor;
        }
        delete minNode;
    }
    return root;
}


Tree* search(Tree* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->Left, key);
    }
    else {
        return search(root->Right, key);
    }
}


void printTree(Tree* root) {
    if (root != nullptr) {
        printTree(root->Left);
        cout << "Key: " << root->key
            << ", Values: " << root->intVal1 << ", "
            << root->intVal2 << ", " << root->intVal3 << endl;
        printTree(root->Right);
    }
}


int main() {
    Tree* root = nullptr;
    int choice;

    while (true) {
        cout << "\nBinary Tree Operations Menu:\n";
        cout << "1 - Create tree\n";
        cout << "2 - Insert element\n";
        cout << "3 - Search by key\n";
        cout << "4 - Delete node with minimum sum\n";
        cout << "5 - Print tree\n";
        cout << "6 - Exit\n";

        choice = inputValidatedInt("Enter your choice: ", 1, 6);

        switch (choice) {
        case 1: {
            root = nullptr;
            cout << "Tree created.\n";
            break;
        }
        case 2: {
            int key = inputValidatedInt("Enter key: ", INT32_MIN, INT32_MAX);
            int v1 = inputValidatedInt("Enter first value: ", INT32_MIN, INT32_MAX);
            int v2 = inputValidatedInt("Enter second value: ", INT32_MIN, INT32_MAX);
            int v3 = inputValidatedInt("Enter third value: ", INT32_MIN, INT32_MAX);
            root = insertElem(root, key, v1, v2, v3);
            cout << "Element inserted.\n";
            break;
        }
        case 3: {
            int key = inputValidatedInt("Enter key to search: ", INT32_MIN, INT32_MAX);
            Tree* result = search(root, key);
            if (result != nullptr) {
                cout << "Found node with key " << key << ": intVal1 = " << result->intVal1 << ", intVal2 = " << result->intVal2 <<  ", intVal3 = " << result->intVal3 <<endl;
            }
            else {
                cout << "Node with key " << key << " not found.\n";
            }
            break;
        }
        case 4: {
            root = deleteMinSumNode(root);
            cout << "Node with minimum sum deleted.\n";
            break;
        }
        case 5: {
            if (root == nullptr) cout << "Tree is empty.\n";
            else printTree(root);
            break;
        }
        case 6: {
            cout << "Exiting program.\n";
            return 0;
        }
        }
    }
    return 0;
}