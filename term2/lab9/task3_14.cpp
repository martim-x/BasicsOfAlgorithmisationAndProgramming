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


double calculateAverage(Tree* root) {
    if (!root) {
        cout << "Tree is empty!" << endl;
        return 0.0;
    }

    queue<Tree*> q;
    q.push(root);
    double sum = 0;
    int count = 0;

    while (!q.empty()) {
        Tree* current = q.front();
        q.pop();

        sum += current->intVal1;
        sum += current->intVal2;
        count++;

        if (current->Left) q.push(current->Left);
        if (current->Right) q.push(current->Right);
    }

    return sum / (2*count);
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
        cout << "4 - Calculate average\n";
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
            double count = calculateAverage(root);
            cout << "Average of Values: " << count << endl;
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
