#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For windows
// export LANG=en_US.UTF-8 For Linux
int main()
{
    int num;
    bitset<4> bt;
    cin >> num;
    string str = to_string(num);

    for (int i = 0; i < 4; i++)
    {
        if (bt[str[i] - '0'])
        {
            cout << "Цифры не различны" << endl;
            return 0;
        }
        else
        {
            bt[str[i] - '0'] = 1;
        }
    }
    cout << "Цифры различны" << endl;
    return 0;
}
