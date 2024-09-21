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


void task8_3(){
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


void subtask8_2(vector<pair<int, vector<int>>> &summary, vector<pair<int, vector<int>>> &buffers, vector<int> &coins, bool cleaningFlagBuf, bool cleaningFlagSum){
    if (buffers.empty()){
        cleaningFlagSum = true;
    }

    if (summary.empty()){
        cleaningFlagBuf = true;
    }


    vector<pair<int, vector<int>>> newBuffers;

    for(auto &sum: summary){
        for(auto &coin: coins){
            if(sum.first >= coin){
                pair<int, vector<int>> newEntry = {sum.first - coin, sum.second};
                newEntry.second.push_back(coin);
                newBuffers.push_back(newEntry);
            }
        }
    }

    buffers.insert(buffers.end(), newBuffers.begin(), newBuffers.end());

    if(cleaningFlagBuf){
        buffers.clear();
        subtask8_2(summary, buffers, coins, false, false);
    }
    
    if(cleaningFlagSum){
        summary.clear();
        subtask8_2(buffers, summary, coins, false, false);
    }
}


void task8_2(){
    vector<int> coins = {50, 20, 5, 2};
    vector<pair<int, vector<int>>> buffers;
    vector<pair<int, vector<int>>> summary = {{100, {}}};


    subtask8_2(summary, buffers, coins, false, false);

    set<vector<int>> uniquePaths; 

    for(auto &entry: buffers){
        sort(entry.second.begin(), entry.second.end());
        uniquePaths.insert(entry.second);
    }

    for(auto &path: uniquePaths){
        for(auto &coin: path){
            cout << coin << " ";
        }
        cout << endl;
    }
}


int main(){
    long long num;
    cout << "Введите число: " << endl;
    cin >> num;

    vector<long long> primes = searchPrimes(num);
    set<long long> deviders = searchDeviders(primes, num);

    task8_3();

    task8_1();


    return 0;
}