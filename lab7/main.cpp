#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux

vector<long long> searchPrimes(long long num)
{
    bitset<10000000> bs;
    bs.set();

    vector<long long> primes;

    long long sqrtOfnum = sqrt(num);
    for (long long i = 2; i < sqrtOfnum; i++)
        if (bs[i])
        {
            for (long long j = i; j < sqrtOfnum; j += i)
            {
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    return primes;
}

int main()
{
    long long num;
    cin >> num;
    vector<long long> primes = searchPrimes(num);
    for (auto el : primes)
        cout << el << endl;
    return 0;
}