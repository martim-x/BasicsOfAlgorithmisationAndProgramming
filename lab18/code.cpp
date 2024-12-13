#include <iostream> 
int sum(int n, ...);
using namespace std;

int main()
{
    cout << sum(6, 4, 5, 1, 2, 3, 0) << endl;
    cout << sum(2, 34, 4445);
    return 0;
}

int sum(int n, ...)
{
    int* p = &n;
    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += *(++p);
    return sum;
}