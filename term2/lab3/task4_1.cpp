#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <bitset>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "validators.h"


using namespace std;


enum BodyType {
    SEDAN,
    UNIVERSAL,
    HATCHBACK,
    COUPE,
    SUV,
    MINIVAN,
    PICKUP,
    BODYTYPE_COUNT
};


const char* bodyTypeNames[] = {
    "Sedan",
    "Universal",
    "Hatchback",
    "Coupe",
    "SUV",
    "Minivan",
    "Pickup"
};


struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;
};


ostream& operator<<(ostream& os, const Date& d) {
    os << d.day << "/" << d.month << "/" << d.year;
    return os;
}


struct Car {
    string brand;
    string color;
    string serialNumber;
    Date manufactureDate;
    BodyType bodyType;
    Date lastInspection;
    string owner;
};


BodyType inputBodyType();
Date inputDate(const string& prompt);
void printCar(const Car& c);
void addCar(vector<Car>& cars);
void deleteCar(vector<Car>& cars);
void searchByOwner(const vector<Car>& cars);
void saveToFile(const vector<Car>& cars, const string& filename);
void loadFromFile(vector<Car>& cars, const string& filename);
int inputValidatedInt(const string& prompt, int min, int max);
bool validateString(const string& input, const string& pattern);
string inputValidatedString(const string& prompt, const string& pattern, size_t exactLength = 0);

vector<Car> cars;

int main() {
    const string filename = "task5_11.txt";

    while (true) {
        cout << "\nCar Management System\n"
            << "1. Add Car\n"
            << "2. Show All Cars\n"
            << "3. Delete Car\n"
            << "4. Search by Owner\n"
            << "5. Save to File\n"
            << "6. Load from File\n"
            << "7. Exit\n"
            << "Enter choice: ";

        int choice = inputValidatedInt("", 1, 7);

        switch (choice) {
        case 1: addCar(cars); break;
        case 2:
            for (const auto& c : cars) printCar(c);
            break;
        case 3: deleteCar(cars); break;
        case 4: searchByOwner(cars); break;
        case 5: saveToFile(cars, filename); break;
        case 6: loadFromFile(cars, filename); break;
        case 7: return 0;
        }
    }
}

int inputValidatedInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && value >= min && value <= max && ss.eof())
            return value;
        cout << "Invalid input! Enter integer between " << min << " and " << max << endl;
    }
}


bool validateString(const string& input, const string& pattern, size_t exactLength) {
    if (exactLength != 0 && input.length() != exactLength)
        return false;
    for (char c : input) {
        if (pattern.find(c) == string::npos)
            return false;
    }
    return !input.empty();
}


string inputValidatedString(const string& prompt, const string& pattern, size_t exactLength) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (validateString(value, pattern, exactLength))
            return value;
        if (exactLength != 0)
            cout << "Invalid input! Must be exactly " << exactLength << " characters. Allowed: " << pattern << endl;
        else
            cout << "Invalid input! Allowed characters: " << pattern << endl;
    }
}


BodyType inputBodyType() {
    cout << "Select body type:\n"
        << "1. Sedan\n2. Universal\n3. Hatchback\n4. Coupe\n"
        << "5. SUV\n6. Minivan\n7. Pickup\n";
    return static_cast<BodyType>(inputValidatedInt("Choice (1-7): ", 1, 7) - 1);
}


bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


bool isValidDate(int day, int month, int year) {
    const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month < 1 || month > 12) return false;
    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear(year)) {
        maxDays = 29;
    }
    return day >= 1 && day <= maxDays;
}


Date inputValidatedDate(const string& prompt) {
    cout << prompt << endl;
    Date d;

    while (true) {
        d.day = inputValidatedInt("Day: ", 1, 31);
        d.month = inputValidatedInt("Month: ", 1, 12);
        d.year = inputValidatedInt("Year: ", 1900, 2099);

        if (isValidDate(d.day, d.month, d.year)) {
            return d;
        }
        else {
            cout << "Invalid date! Please enter a valid date.\n";
        }
    }
}


void addCar(vector<Car>& cars) {
    Car c;
    c.brand = inputValidatedString("Brand: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -", 0);
    c.color = inputValidatedString("Color: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 0);
    c.serialNumber = inputValidatedString("Serial number (exactly 10 characters): ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 10);
    c.manufactureDate = inputDate("Manufacture date:");
    c.bodyType = inputBodyType();
    c.lastInspection = inputDate("Last inspection date:");
    c.owner = inputValidatedString("Owner: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ", 0);

    cars.push_back(c);
}


void printCar(const Car& c) {
    cout << "------------------------------------------------------" << endl;
    cout << "| Brand: " << c.brand << endl;
    cout << "| Color: " << c.color << endl;
    cout << "| Serial: " << c.serialNumber << endl;
    cout << "| Body: " << bodyTypeNames[c.bodyType] << endl;
    cout << "| Manufactured: " << c.manufactureDate << endl;
    cout << "| Last inspection: " << c.lastInspection << endl;
    cout << "| Owner: " << c.owner << endl;
    cout << "------------------------------------------------------" << endl;
}


void searchByOwner(const vector<Car>& cars) {
    string owner = inputValidatedString("Enter owner name: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ", 0);
    bool found = false;

    for (const auto& c : cars) {
        if (c.owner == owner) {
            printCar(c);
            found = true;
        }
    }

    if (!found) {
        cout << "No cars found for owner: " << owner << endl;
    }
}


void deleteCar(vector<Car>& cars) {
    string serial = inputValidatedString("Enter serial number to delete: ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 10);

    auto it = remove_if(cars.begin(), cars.end(),
        [serial](const Car& c) { return c.serialNumber == serial; });

    if (it != cars.end()) {
        cars.erase(it, cars.end());
        cout << "Car deleted\n";
    }
    else {
        cout << "Car not found\n";
    }
}


void saveToFile(const vector<Car>& cars, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error saving file!\n";
        return;
    }

    for (const auto& c : cars) {
        size_t brandSize = c.brand.size();
        file.write(reinterpret_cast<const char*>(&brandSize), sizeof(brandSize));
        file.write(c.brand.c_str(), brandSize);

        size_t colorSize = c.color.size();
        file.write(reinterpret_cast<const char*>(&colorSize), sizeof(colorSize));
        file.write(c.color.c_str(), colorSize);

        file.write(c.serialNumber.c_str(), 10);

        file.write(reinterpret_cast<const char*>(&c.manufactureDate), sizeof(c.manufactureDate));
        file.write(reinterpret_cast<const char*>(&c.bodyType), sizeof(c.bodyType));
        file.write(reinterpret_cast<const char*>(&c.lastInspection), sizeof(c.lastInspection));

        size_t ownerSize = c.owner.size();
        file.write(reinterpret_cast<const char*>(&ownerSize), sizeof(ownerSize));
        file.write(c.owner.c_str(), ownerSize);
    }

    cout << "Data saved to " << filename << endl;
}


void loadFromFile(vector<Car>& cars, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error loading file!\n";
        return;
    }

    cars.clear();
    while (file) {
        Car c;
        size_t size;

        if (!file.read(reinterpret_cast<char*>(&size), sizeof(size))) break;
        c.brand.resize(size);
        file.read(&c.brand[0], size);

        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        c.color.resize(size);
        file.read(&c.color[0], size);

        char serialBuffer[10];
        file.read(serialBuffer, 10);
        c.serialNumber.assign(serialBuffer, 10);

        file.read(reinterpret_cast<char*>(&c.manufactureDate), sizeof(c.manufactureDate));
        file.read(reinterpret_cast<char*>(&c.bodyType), sizeof(c.bodyType));
        file.read(reinterpret_cast<char*>(&c.lastInspection), sizeof(c.lastInspection));

        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        c.owner.resize(size);
        file.read(&c.owner[0], size);

        if (file) cars.push_back(c);
    }

    cout << "Data loaded from " << filename << endl;
}