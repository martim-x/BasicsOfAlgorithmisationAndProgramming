#include <iostream>
#include "validators.h"
#include <string>

using namespace std;

int main() {
    string valConName = inputValidatedName("Enter des: ");

    cout << "DEST IS : " << valConName << endl;

    return 0;
}