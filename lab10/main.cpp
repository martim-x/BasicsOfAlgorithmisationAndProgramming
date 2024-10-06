#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;


void task6() {
    int size;
    cout << "Введите размер массива" << endl;
    cin >> size;
    vector<int> vec;
    srand(time(0));
    for (int i = 0; i < size; i++)
        vec.push_back(rand());

    cout << "Элементы массива" << endl;
    for (int num : vec) {
        cout << num << " ";
    }

    int max = *max_element(vec.begin(), vec.end());
    cout << "Максимальный элемент массива: " << max << endl;
    for (int i = 1; i <= size; i++)
        if (i % 2 == 0)
            vec[i-1] = max;

    cout << "Элементы массива" << endl;
    for (int num : vec) {
        cout << num << " ";
    }
}


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    task6();
    return 0;
}

