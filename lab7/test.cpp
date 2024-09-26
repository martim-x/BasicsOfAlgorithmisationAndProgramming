#include <bits/stdc++.h>
using namespace std;

void subtask8_2(set<pair<int, vector<int>>> &summary, set<pair<int, vector<int>>> &buffers, vector<int> coins, bool executable)
{
    for (auto sum : summary)
    {
        for (auto coin : coins)
        {
            if (sum.first >= coin || sum.first == 0)
            {
                vector<int> newCombination = sum.second;
                pair<int, vector<int>> pairForBuffers;

                if (sum.first)
                {
                    newCombination.push_back(coin);
                    sort(newCombination.begin(), newCombination.end());
                    pairForBuffers = make_pair(sum.first - coin, newCombination);
                    executable = true;
                }

                else
                {
                    pairForBuffers = make_pair(sum.first, newCombination);
                }
                buffers.insert(pairForBuffers);
            }
        }
    }

    if (executable)
    {
        summary.clear();
        subtask8_2(buffers, summary, coins, false);
    }
}

void task8_2()
{
    vector<int> coins = {50, 20, 5, 2};
    set<pair<int, vector<int>>> buffers;
    set<pair<int, vector<int>>> summary;

    summary.insert(make_pair(100, vector<int>()));

    subtask8_2(summary, buffers, coins, false);

    cout << "Amount of cases: " << buffers.size() << endl;
    for (auto el : buffers)
    {
        cout << el.first << ": ";
        for (auto coin : el.second)
        {
            cout << coin << " ";
        }
        cout << endl;
    }
}

int main()
{
    task8_2();
    return 0;
}
