#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateTestFile(const string& filename, int count) {
    ofstream file(filename);
    for (int i = 0; i < count; ++i) {
        file << rand() % 1000 << " ";
    }
}

void testSearch(const HashTable& ht, const vector<int>& nums) {
    for (int num : nums) {
        pair<bool, size_t> result = ht.search(num);
        cout << "Number " << num << ": "
            << (result.first ? "Found" : "Not found")
            << ", Comparisons: " << result.second << "\n";
    }
}

int main() {
    srand(time(nullptr));

    generateTestFile("random.txt", 1000);
    generateTestFile("unique.txt", 500);
    generateTestFile("duplicates.txt", 2000);

    HashTable htRandom(101);
    HashTable htUnique(101);
    HashTable htDuplicates(101);

    htRandom.loadFromFile("random.txt");
    htUnique.loadFromFile("unique.txt");
    htDuplicates.loadFromFile("duplicates.txt");

    const vector<int> testNumbers = { 42, 317, 999, 123, 777 };

    cout << "===== Random Numbers =====\n";
    testSearch(htRandom, testNumbers);

    cout << "\n===== Unique Numbers =====\n";
    testSearch(htUnique, testNumbers);

    cout << "\n===== Duplicates =====\n";
    testSearch(htDuplicates, testNumbers);


    return 0;
}