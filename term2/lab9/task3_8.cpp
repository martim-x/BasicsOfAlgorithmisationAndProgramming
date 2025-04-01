#include <iostream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

struct Tree {
    int key;
    int intVal1;
    int intVal2;
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

Tree* createNode(int key, int intVal1, int intVal2) {
    Tree* newNode = new Tree;
    newNode->key = key;
    newNode->intVal1 = intVal1;
    newNode->intVal2 = intVal2;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}

Tree* insertElem(Tree* root, int key, int intVal1, int intVal2) {
    if (root == nullptr) {
        return createNode(key, intVal1, intVal2);
    }

    if (key < root->key) {
        root->Left = insertElem(root->Left, key, intVal1, intVal2);
    }
    else if (key > root->key) {
        root->Right = insertElem(root->Right, key, intVal1, intVal2);
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
Tree* deleteMaxSumNode(Tree* root) {
    if (root == nullptr) {
        return nullptr;
    }

    Tree* maxNode = root;
    int maxSum = root->intVal1 + root->intVal2;
    Tree* parent = nullptr;

    queue<pair<Tree*, Tree*>> q;
    q.push({ root, nullptr });

    while (!q.empty()) {
        auto currentPair = q.front();
        q.pop();

        Tree* currentNode = currentPair.first;
        Tree* currentParent = currentPair.second;

        int currentSum = currentNode->intVal1 + currentNode->intVal2;
        if (currentSum > maxSum || (currentSum == maxSum && currentNode->key > maxNode->key)) {
            maxSum = currentSum;
            maxNode = currentNode;
            parent = currentParent;
        }

        if (currentNode->Left != nullptr) {
            q.push({ currentNode->Left, currentNode });
        }
        if (currentNode->Right != nullptr) {
            q.push({ currentNode->Right, currentNode });
        }
    }

    // Deleting the maxNode
    if (parent == nullptr) { // maxNode is root
        if (maxNode->Left == nullptr && maxNode->Right == nullptr) {
            delete maxNode;
            return nullptr;
        }
        else if (maxNode->Left == nullptr) {
            Tree* newRoot = maxNode->Right;
            delete maxNode;
            return newRoot;
        }
        else if (maxNode->Right == nullptr) {
            Tree* newRoot = maxNode->Left;
            delete maxNode;
            return newRoot;
        }
        else {
            Tree* successorParent = maxNode;
            Tree* successor = maxNode->Right;
            while (successor->Left != nullptr) {
                successorParent = successor;
                successor = successor->Left;
            }
            maxNode->key = successor->key;
            maxNode->intVal1 = successor->intVal1;
            maxNode->intVal2 = successor->intVal2;
            if (successorParent == maxNode) {
                successorParent->Right = successor->Right;
            }
            else {
                successorParent->Left = successor->Right;
            }
            delete successor;
            return root;
        }
    }
    else {
        bool isLeftChild = (parent->Left == maxNode);

        if (maxNode->Left == nullptr && maxNode->Right == nullptr) {
            if (isLeftChild) {
                parent->Left = nullptr;
            }
            else {
                parent->Right = nullptr;
            }
            delete maxNode;
        }
        else if (maxNode->Left == nullptr || maxNode->Right == nullptr) {
            Tree* child = (maxNode->Left != nullptr) ? maxNode->Left : maxNode->Right;
            if (isLeftChild) {
                parent->Left = child;
            }
            else {
                parent->Right = child;
            }
            delete maxNode;
        }
        else {
            Tree* successorParent = maxNode;
            Tree* successor = maxNode->Right;
            while (successor->Left != nullptr) {
                successorParent = successor;
                successor = successor->Left;
            }
            maxNode->key = successor->key;
            maxNode->intVal1 = successor->intVal1;
            maxNode->intVal2 = successor->intVal2;
            if (successorParent == maxNode) {
                successorParent->Right = successor->Right;
            }
            else {
                successorParent->Left = successor->Right;
            }
            delete successor;
        }
    }

    return root;
}
void printTree(Tree* root) {
    if (root != nullptr) {
        printTree(root->Left);
        cout << "Key: " << root->key << ", intVal1: " << root->intVal1 << ", intVal2: " << root->intVal2 << endl;
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
        cout << "4 - Delete node with maximum sum\n";
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
            int intVal1 = inputValidatedInt("Enter first integer: ", INT32_MIN, INT32_MAX);
            int intVal2 = inputValidatedInt("Enter second integer: ", INT32_MIN, INT32_MAX);
            root = insertElem(root, key, intVal1, intVal2);
            cout << "Element inserted.\n";
            break;
        }
        case 3: {
            int key = inputValidatedInt("Enter key to search: ", INT32_MIN, INT32_MAX);
            Tree* result = search(root, key);
            if (result != nullptr) {
                cout << "Found node with key " << key << ": intVal1 = " << result->intVal1 << ", intVal2 = " << result->intVal2 << endl;
            }
            else {
                cout << "Node with key " << key << " not found.\n";
            }
            break;
        }
        case 4: {
            root = deleteMaxSumNode(root);
            cout << "Node with maximum sum deleted.\n";
            break;
        }
        case 5: {
            if (root == nullptr) {
                cout << "Tree is empty.\n";
            }
            else {
                printTree(root);
            }
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
