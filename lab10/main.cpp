#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;


void task6() {
    int size;
    cout << "Input the size of the array: " << endl;
    cin >> size;
    vector<int> vec;
    srand(time(0));
    for (int i = 0; i < size; i++)
        vec.push_back(rand() % 100);

    cout << "Elements of the array:  " << endl;
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    int max = *max_element(vec.begin(), vec.end());
    cout << "Max element of the array: " << max << endl;
    for (int i = 1; i <= size; i++)
        if (i % 2 == 0)
            vec[i - 1] = max;

    cout << "Elements of the array: " << endl;
    for (int num : vec)
        cout << num << " ";
    cout << endl;

    cout << "Input the size (k): " << endl;
    cin >> size;
    int num, buffer = INT_MAX, counter = 0;
    for (int i = 0; i < size; i++) {
        num = rand() % 100;
        cout << num << ", " << buffer;
        if (num > buffer)
            cout << " id " << ++counter << endl;
        buffer = num;
        cout << endl;
    }
    cout << "amount of invers: " << counter << endl;

}


void task7_2AND7_3() {
    vector<int> nums;
    vector<int> repeats(101, 0);
    srand(time(0));
    for (int i = 0; i < 100; i++)
        nums.push_back(rand() % 21 - 10);

    int currentEl, nextEL;

    for (int i = 0; i < nums.size() - 1; i++) {
        cout << nums[i] << endl;
        currentEl = nums[i];
        nextEL = nums[i + 1];
        if (currentEl == nextEL)
            repeats[currentEl + 10]++;
    }

    for (int i = 0; i < 21; i++) {
        if (repeats[i])
            cout << i - 10 << ": " << repeats[i] << endl;
    }
}


void task7_6() {
    vector<int> vec, bufferVec;
    set<int, greater<int>> sums;
    map<int, vector<int>> paths;
    int buffer = 0;
    int num;

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        num = rand() % (21) - 10;
        vec.push_back(num);
        cout << num << endl;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            for (int k = i; k <= j; k++) {
                if (vec[k] > 0) {
                    buffer += vec[k];
                    bufferVec.push_back(vec[k]);
                }
                else {
                    buffer = 0;
                    bufferVec.clear();

                }
            }
            paths.insert(make_pair(buffer, bufferVec));
            sums.insert(buffer);
            buffer = 0;
            bufferVec.clear();

        }
    }

    set<int>::iterator it;
    it = sums.begin();
    cout << "Max sum: " << *it << endl;

    cout << endl;
    for (auto el : paths[*it])
        cout << el << endl;
    cout << endl;

    it = --sums.end();
    cout << "Min sum: " << *it << endl;

}


int main() {
    task6();
    task7_2AND7_3();
    task7_6();
    return 0;
}

