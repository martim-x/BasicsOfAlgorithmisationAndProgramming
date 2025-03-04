#include <iostream>
#include "validators.h"
#include <string>

using namespace std;

int main() {
    while (true) {
        string valConName = inputValidatedName("Enter Name: ");
        cout << "DEST IS : " << valConName << endl;
    }
    return 0;
}