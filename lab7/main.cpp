#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux



vector<long long> searchPrimes(long long num){
    bitset<10000000> bs;
    bs.set();

    vector<long long> primes;

    long long sqrtOfnum = sqrt(num);
    for (long long i = 2; i <= sqrtOfnum; i++)
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


set<long long> searchDeviders(vector<long long> primes, long long num){
    set<long long> deviders;
    for (auto dev : primes)
        while (num % dev == 0)
        {
            num /= dev;
            deviders.insert(dev);
        }

    for (auto dev: deviders)
        cout<<dev<<endl;
    return deviders;
}


void pouring(){
    double C1, C2;
    cout << "Введите C1 и C2: " << endl;
    cin >> C1 >> C2;
    for (int i = 0; i < 12; i++)
    {
        C2 += C1 / 2;
        C1 = C1 / 2;
        C1 += C2 / 2;
        C2 = C2 / 2;
    }
    cout << "C1 = " << C1 << ", C2 = " << C2 << endl;
}


vector<long long> task8_1(){
    vector<long long> ultraprimes = searchPrimes(999);

    vector<long long> megaultraprimes;

    ultraprimes.erase(ultraprimes.begin(), ultraprimes.begin()+4);
    
    string strPrime;
    for(auto prime: ultraprimes){
        strPrime = to_string(prime*prime);
        if(strPrime[0]-'0'<strPrime[1]-'0' && strPrime[2]-'0'<strPrime[1]-'0'){
            megaultraprimes.push_back(prime);
        }
    }
    for(auto prime: megaultraprimes){
        cout<<prime<<endl;
    }
}


int main(){
    long long num;
    cout << "Введите число: " << endl;
    cin >> num;

    vector<long long> primes = searchPrimes(num);
    set<long long> deviders = searchDeviders(primes, num);

    pouring();

    task8_1();


    return 0;
}