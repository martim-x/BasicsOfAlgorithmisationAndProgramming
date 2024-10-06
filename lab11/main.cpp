#include <bits/stdc++.h>
using namespace std;


void task5() {
    int num;
    cout << "Input number: " << endl;
    cin >> num;
    bitset<64> bt(num);
    cout << bt << endl;
    for (int i = 0; i < 32; i++) {
        if ((i + 1) % 3 == 0)
            num &= ~(1 << i);
    }
    bitset<64> bts(num);
    cout<<

}


int main() {
    task5();
    return 0;
}