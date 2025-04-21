#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace std::chrono;

int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);

        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

void fillArray(vector<int>& arr, int size) {
    arr.resize(size);
    for (int i = 0; i < size; i++) {
        arr[i] = getRandomNumber(INT32_MIN, INT32_MAX);
    }
}

void inputArray(vector<int>& arr, int size) {
    arr.resize(size);
    for (int i = 0; i < size; i++) {
        arr[i] = inputValidatedInt("Enter element " + to_string(i+1) + ": ", INT32_MIN, INT32_MAX);
    }
}

void printArray(const vector<int>& arr, int start = 0, int end = -1) {
    if (end == -1) end = arr.size();
    for (int i = start; i < end && i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

vector<int> copyArray(const vector<int>& arr) {
    return arr;
}

// 1. Сортировка пузырьком
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            if (arr[j - 1] > arr[j]) {
                int t = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = t;
            }
        }
    }
}

// 2. Быстрая сортировка Хоара
int getHoarBorder(vector<int>& arr, int sm, int em) {
    int i = sm - 1, j = em + 1;
    int brd = arr[sm], buf;
    while (i < j) {
        while (arr[--j] > brd);
        while (arr[++i] < brd);
        if (i < j) {
            buf = arr[j];
            arr[j] = arr[i];
            arr[i] = buf;
        }
    }
    return j;
}

void sortHoar(vector<int>& arr, int sm, int em) {
    if (sm < em) {
        int hb = getHoarBorder(arr, sm, em);
        sortHoar(arr, sm, hb);
        sortHoar(arr, hb + 1, em);
    }
}

// 3. Пирамидальная сортировка
void heapify(vector<int>& arr, int pos, int n) {
    int t, tm;
    while (2 * pos + 1 < n) {
        t = 2 * pos + 1;
        if (2 * pos + 2 < n && arr[2 * pos + 2] >= arr[t])
            t = 2 * pos + 2;
        if (arr[pos] < arr[t]) {
            tm = arr[pos];
            arr[pos] = arr[t];
            arr[t] = tm;
            pos = t;
        }
        else break;
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 0; i--)
        heapify(arr, i, n);
    while (n > 0) {
        int tm = arr[0];
        arr[0] = arr[n - 1];
        arr[n - 1] = tm;
        n--;
        heapify(arr, 0, n);
    }
}

// 4. Сортировка слиянием (исправленная версия)
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Создаем временные массивы
    vector<int> L(n1);
    vector<int> R(n2);
    
    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Объединяем временные массивы обратно в arr[left..right]
    int i = 0; // Индекс первого подмассива
    int j = 0; // Индекс второго подмассива
    int k = left; // Индекс объединенного подмассива
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Копируем оставшиеся элементы L[], если они есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Копируем оставшиеся элементы R[], если они есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void sortMerge(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находим среднюю точку
        int mid = left + (right - left) / 2;
        
        // Сортируем первую и вторую половины
        sortMerge(arr, left, mid);
        sortMerge(arr, mid + 1, right);
        
        // Объединяем отсортированные половины
        merge(arr, left, mid, right);
    }
}

// 5. Дополнительное задание. Сортировка подсчетом
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    
    int n = arr.size();
    vector<int> result(n);
    vector<int> count(n, 0);
    
    // Для каждого элемента подсчитываем количество элементов, меньших его
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[j] < arr[i]) {
                count[i]++;
            }
        }
    }
    
    // Размещаем элементы в результирующем массиве согласно их счетчикам
    for (int i = 0; i < n; i++) {
        result[count[i]] = arr[i];
    }
    
    // Копируем отсортированный массив обратно в исходный
    for (int i = 0; i < n; i++) {
        arr[i] = result[i];
    }
}

// 6. Дополнительное задание. Сортировка выбором
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        // Находим минимальный элемент в неотсортированной части
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Меняем местами найденный минимальный элемент с первым элементом неотсортированной части
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// 7. Дополнительное задание. Сортировка простой вставкой
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        // Перемещаем элементы arr[0..i-1], которые больше key, на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Функция для измерения времени выполнения сортировки
long long measureSortingTime(vector<int>& arr, void (*sortFunc)(vector<int>&)) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

// Функция для тестирования всех алгоритмов сортировки
void testAllSortingAlgorithms() {
    cout << "\n=== Testing All Sorting Algorithms ===\n";
    
    // Размеры массивов для тестирования
    vector<int> sizes = {100, 1000, 10000, 100000, 1000000};
    
    // Названия алгоритмов сортировки
    vector<string> algorithmNames = {
        "Bubble Sort",
        "Quick Sort (Hoare)",
        "Heap Sort",
        "Merge Sort",
        "Counting Sort",
        "Selection Sort",
        "Insertion Sort"
    };
    
    // Создаем файл для записи результатов
    ofstream outFile("sorting_results.txt");
    outFile << "Array Size,Quick Sort (ms),Heap Sort (ms),Merge Sort (ms),Counting Sort (ms),Selection Sort (ms),Insertion Sort (ms)\n";
    
    // Генерируем один большой массив для всех тестов
    vector<int> originalArray;
    fillArray(originalArray, 1000001); // 10^6 + 1 элементов
    
    // Тестируем каждый размер массива
    for (int size : sizes) {
        cout << "\nTesting with array size: " << size << endl;
        outFile << size << ",";
        
        // Создаем копию нужного размера из оригинального массива
        vector<int> testArray(originalArray.begin(), originalArray.begin() + size);
        
        // Тестируем сортировку пузырьком
        vector<int> arr;
        long long time;
        bool sorted;
        cout << algorithmNames[0] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << ",";
        
        // Тестируем быструю сортировку
        arr = copyArray(testArray);
        time = measureSortingTime(arr, [](vector<int>& arr) { sortHoar(arr, 0, arr.size() - 1); });
        sorted = isSorted(arr);
        cout << algorithmNames[1] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << ",";
        
        // Тестируем пирамидальную сортировку
        arr = copyArray(testArray);
        time = measureSortingTime(arr, heapSort);
        sorted = isSorted(arr);
        cout << algorithmNames[2] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << ",";
        
        // Тестируем сортировку слиянием
        arr = copyArray(testArray);
        time = measureSortingTime(arr, [](vector<int>& arr) { sortMerge(arr, 0, arr.size() - 1); });
        sorted = isSorted(arr);
        cout << algorithmNames[3] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << ",";
        
        // Тестируем сортировку подсчетом
        arr = copyArray(testArray);
        time = measureSortingTime(arr, countingSort);
        sorted = isSorted(arr);
        cout << algorithmNames[4] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << ",";
        
        // Тестируем сортировку выбором
        arr = copyArray(testArray);
        time = measureSortingTime(arr, selectionSort);
        sorted = isSorted(arr);
        cout << algorithmNames[5] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << ",";
        
        // Тестируем сортировку простой вставкой
        arr = copyArray(testArray);
        time = measureSortingTime(arr, insertionSort);
        sorted = isSorted(arr);
        cout << algorithmNames[6] << ": " << time << " ms, ";
        cout << (sorted ? "Sorted correctly" : "Sorting error!") << endl;
        outFile << time << "\n";
    }
    
    outFile.close();
    cout << "\nResults saved to sorting_results.txt\n";
}

// Функция для объединения нечетных элементов из двух массивов
vector<int> combineOddElements(const vector<int>& A, const vector<int>& B) {
    vector<int> C;
    
    // Добавляем нечетные элементы из массива A
    for (int i = 0; i < A.size(); i++) {
        if (A[i] % 2 != 0) {
            C.push_back(A[i]);
        }
    }
    
    // Добавляем нечетные элементы из массива B
    for (int i = 0; i < B.size(); i++) {
        if (B[i] % 2 != 0) {
            C.push_back(B[i]);
        }
    }
    
    return C;
}

// Главное меню программы
void showMenu() {
    cout << "\n=== Sorting Algorithms Menu ===\n";
    cout << "1. Input arrays A and B manually\n";
    cout << "2. Generate arrays A and B randomly\n";
    cout << "3. Combine odd elements into array C\n";
    cout << "4. Sort array C using Quick Sort\n";
    cout << "5. Sort array C using Merge Sort\n";
    cout << "6. Sort array C using Heap Sort\n";
    cout << "7. Sort array C using Counting Sort\n";
    cout << "8. Sort array C using Selection Sort\n";
    cout << "9. Sort array C using Insertion Sort\n";
    cout << "10. Display arrays\n";
    cout << "11. Test all sorting algorithms\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    vector<int> A, B, C;
    bool arraysInitialized = false;
    
    while (true) {
        showMenu();
        int choice = inputValidatedInt("", 0, 11);
        
        switch (choice) {
            case 0: {
                cout << "Exiting program. Goodbye!\n";
                return 0;
            }
            case 1: {
                int sizeA = inputValidatedInt("Enter size of array A: ", 1, 1000);
                int sizeB = inputValidatedInt("Enter size of array B: ", 1, 1000);
                
                cout << "Enter elements for array A:\n";
                inputArray(A, sizeA);
                cout << "Enter elements for array B:\n";
                inputArray(B, sizeB);
                
                cout << "Array A: ";
                printArray(A);
                cout << "Array B: ";
                printArray(B);
                
                arraysInitialized = true;
                break;
            }
            case 2: {
                int sizeA = inputValidatedInt("Enter size of array A: ", 1, 1000);
                int sizeB = inputValidatedInt("Enter size of array B: ", 1, 1000);
                
                fillArray(A, sizeA);
                fillArray(B, sizeB);
                
                cout << "Array A: ";
                printArray(A);
                cout << "Array B: ";
                printArray(B);
                
                arraysInitialized = true;
                break;
            }
            case 3: {
                if (!arraysInitialized) {
                    cout << "Please initialize arrays first (option 1 or 2).\n";
                    break;
                }
                
                C = combineOddElements(A, B);
                cout << "Array C (odd elements from A and B): ";
                printArray(C);
                break;
            }
            case 4: {
                if (C.empty()) {
                    cout << "Array C is empty. Please combine odd elements first (option 3).\n";
                    break;
                }
                
                cout << "Sorting array C using Quick Sort...\n";
                auto start = high_resolution_clock::now();
                sortHoar(C, 0, C.size() - 1);
                auto end = high_resolution_clock::now();
                long long time = duration_cast<microseconds>(end - start).count();
                
                cout << "Sorted array C: ";
                printArray(C);
                cout << "Sorting time: " << time << " ms\n";
                break;
            }
            case 5: {
                if (C.empty()) {
                    cout << "Array C is empty. Please combine odd elements first (option 3).\n";
                    break;
                }
                
                cout << "Sorting array C using Merge Sort...\n";
                auto start = high_resolution_clock::now();
                sortMerge(C, 0, C.size() - 1);
                auto end = high_resolution_clock::now();
                long long time = duration_cast<microseconds>(end - start).count();
                
                cout << "Sorted array C: ";
                printArray(C);
                cout << "Sorting time: " << time << " ms\n";
                break;
            }
            case 6: {
                if (C.empty()) {
                    cout << "Array C is empty. Please combine odd elements first (option 3).\n";
                    break;
                }
                
                cout << "Sorting array C using Heap Sort...\n";
                auto start = high_resolution_clock::now();
                heapSort(C);
                auto end = high_resolution_clock::now();
                long long time = duration_cast<microseconds>(end - start).count();
                
                cout << "Sorted array C: ";
                printArray(C);
                cout << "Sorting time: " << time << " ms\n";
                break;
            }
            case 7: {
                if (C.empty()) {
                    cout << "Array C is empty. Please combine odd elements first (option 3).\n";
                    break;
                }
                
                cout << "Sorting array C using Counting Sort...\n";
                auto start = high_resolution_clock::now();
                countingSort(C);
                auto end = high_resolution_clock::now();
                long long time = duration_cast<microseconds>(end - start).count();
                
                cout << "Sorted array C: ";
                printArray(C);
                cout << "Sorting time: " << time << " ms\n";
                break;
            }
            case 8: {
                if (C.empty()) {
                    cout << "Array C is empty. Please combine odd elements first (option 3).\n";
                    break;
                }
                
                cout << "Sorting array C using Selection Sort...\n";
                auto start = high_resolution_clock::now();
                selectionSort(C);
                auto end = high_resolution_clock::now();
                long long time = duration_cast<microseconds>(end - start).count();
                
                cout << "Sorted array C: ";
                printArray(C);
                cout << "Sorting time: " << time << " ms\n";
                break;
            }
            case 9: {
                if (C.empty()) {
                    cout << "Array C is empty. Please combine odd elements first (option 3).\n";
                    break;
                }
                
                cout << "Sorting array C using Insertion Sort...\n";
                auto start = high_resolution_clock::now();
                insertionSort(C);
                auto end = high_resolution_clock::now();
                long long time = duration_cast<microseconds>(end - start).count();
                
                cout << "Sorted array C: ";
                printArray(C);
                cout << "Sorting time: " << time << " ms\n";
                break;
            }
            case 10: {
                if (!arraysInitialized) {
                    cout << "Arrays not initialized yet.\n";
                    break;
                }
                
                cout << "Array A: ";
                printArray(A);
                cout << "Array B: ";
                printArray(B);
                cout << "Array C: ";
                printArray(C);
                break;
            }
            case 11: {
                testAllSortingAlgorithms();
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    
    return 0;
} 