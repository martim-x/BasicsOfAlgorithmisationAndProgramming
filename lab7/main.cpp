#include <bits/stdc++.h>
// #include <Windows.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux


void task6() {
    double d, b, k = 6, a = 1.33 * pow(10, 3);
    vector<double> x = { 0.2 , -3, -6,1 };
    for (auto el : x) {
        d = exp(-el) + (el - a) / log(el);
        if (d >= k * sqrt(a))
            b = 6 * d * el;
        if (d < k * sqrt(a))
            b = sin(a / el);
        cout<<"b: "<<b<<endl;
    }

}


vector<long long> searchPrimes(long long num) {
    bitset<10000000> bs;
    bs.set();

    vector<long long> primes;

    long long sqrtOfnum = sqrt(num);
    for (long long i = 2; i <= sqrtOfnum; i++)
        if (bs[i]) {
            for (long long j = i; j < sqrtOfnum; j += i)
            {
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    return primes;
}


set<long long> searchDeviders(vector<long long> primes, long long num) {
    set<long long> deviders;
    for (auto dev : primes)
        while (num % dev == 0) {
            num /= dev;
            deviders.insert(dev);
        }

    for (auto dev : deviders)
        cout << dev << endl;
    return deviders;
}


void task8_3() {
    double C1, C2;
    cout << "task8_3" << endl;
    cout << "Введите C1 и C2: " << endl;
    cin >> C1 >> C2;
    for (int i = 0; i < 12; i++) {
        C2 += C1 / 2;
        C1 = C1 / 2;
        C1 += C2 / 2;
        C2 = C2 / 2;
    }
    cout << "C1 = " << C1 << ", C2 = " << C2 << endl;
}


void task8_1() {
    vector<long long> ultraprimes = searchPrimes(999);

    vector<long long> megaultraprimes;

    ultraprimes.erase(ultraprimes.begin(), ultraprimes.begin() + 4);

    string strPrime;
    for (auto prime : ultraprimes) {
        strPrime = to_string(prime * prime);
        if (strPrime[0] - '0' < strPrime[1] - '0' && strPrime[2] - '0' < strPrime[1] - '0')
            megaultraprimes.push_back(prime);
    }
    cout << "task 8_1  ultraprimes" << endl;

    for (auto prime : megaultraprimes) {
        cout << prime << endl;
    }
}


void subtask8_2(set<pair<int, vector<int>>>& summary, set<pair<int, vector<int>>>& buffers, vector<int> coins, bool executable) {
    for (auto sum : summary) {

        for (auto coin : coins) {

            if (sum.first >= coin || sum.first == 0) {
                vector<int> newCombination = sum.second;
                pair<int, vector<int> > pairForBuffers;

                if (sum.first) {
                    newCombination.push_back(coin);
                    sort(newCombination.begin(), newCombination.end());
                    pairForBuffers = make_pair(sum.first - coin, newCombination);
                    executable = true;
                }

                else {
                    pairForBuffers = make_pair(sum.first, newCombination);
                }
                buffers.insert(pairForBuffers);
            }
        }
    }

    if (executable) {
        summary.clear();
        subtask8_2(buffers, summary, coins, false);
    }
}

void task8_2() {
    vector<int> coins = { 50, 20, 5, 2 };
    set<pair<int, vector<int>>> buffers;
    set<pair<int, vector<int>>> summary;

    summary.insert(make_pair(100, vector<int>()));

    subtask8_2(summary, buffers, coins, false);

    cout << "Amount of cases: " << buffers.size() << endl;
    for (auto el : buffers) {
        cout << el.first << ": ";
        for (auto coin : el.second) {
            cout << coin << " ";
        }
        cout << endl;
    }
}

int main() {
    system("chcp 65001");
    task6();
    // SetConsoleCP(65001);
    // SetConsoleOutputCP(65001);
    long long num;
    cout << "Введите число: " << endl;
    cin >> num;

    vector<long long> primes = searchPrimes(num);
    set<long long> deviders = searchDeviders(primes, num);

    task8_3();

    task8_1();

    task8_2();
    return 0;
}
