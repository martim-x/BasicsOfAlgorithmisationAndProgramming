#include <bits/stdc++.h>
using namespace std;


void task6() {

    char s1[] = "asdfghjkksfddsaf\0";
    char s2[] = "asdghhjhgfjkdasa\0";
    char c1, c2;
    for (int i = 0; i < strlen(s1); i++) {
        c1 = s1[i];
        c2 = s2[i];
        if (c2 == c1)
            cout << "c2 equals c1 -- " << "c2: " << c2 << ",c1: " << c1 << endl;
        else
            cout << "c2 doesm't equal c1 -- " << "c2: " << c2 << ",c1: " << c1 << endl;
    }

    char s3[] = "001 11010 10101010 10101 110101 101010101010 10101010";
    char c3;
    set<int> symbols;
    int buffer = 0;
    for (int i = 0; i < strlen(s3); i++) {
        c3 = s3[i];
        if (c3 == ' ' || i == strlen(s3) - 1) {
            symbols.insert(buffer);
            buffer = 0;
        }
        buffer++;
    }

    cout << "max symbols: " << *(--symbols.end()) << endl;
}

int main() {
    task6();
    return 0;
}