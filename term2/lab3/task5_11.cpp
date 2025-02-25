#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>

using namespace std;

// Перечисление для типов кузова
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

const string bodyTypes[] = { "Sedan", "Universal", "Hatchback", "Coupe",
                           "SUV", "Minivan", "Pickup" };

// Структура для даты (без битовых полей для упрощения)
struct Date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

struct Car {
    string brand;
    string color;
    string serialNumber;
    Date manufactureDate;
    BodyType bodyType;
    Date lastInspection;
    string owner;
};

// Прототипы функций
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
string formatDate(const Date& d);

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

string formatDate(const Date& d) {
    stringstream ss;
    ss << setfill('0')
        << setw(2) << d.day << "/"
        << setw(2) << d.month << "/"
        << d.year;
    return ss.str();
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

bool validateString(const string& input, const string& pattern) {
    for (char c : input) {
        if (pattern.find(c) == string::npos)
            return false;
    }
    return !input.empty();
}

string inputValidatedString(const string& prompt, const string& pattern) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (validateString(value, pattern))
            return value;
        cout << "Invalid input! Allowed characters: " << pattern << endl;
    }
}

BodyType inputBodyType() {
    cout << "Select body type:\n"
        << "1. Sedan\n2. Universal\n3. Hatchback\n4. Coupe\n"
        << "5. SUV\n6. Minivan\n7. Pickup\n";
    return static_cast<BodyType>(inputValidatedInt("Choice (1-7): ", 1, 7) - 1);
}

Date inputDate(const string& prompt) {
    cout << prompt << endl;
    Date d;
    d.day = inputValidatedInt("Day (1-31): ", 1, 31);
    d.month = inputValidatedInt("Month (1-12): ", 1, 12);
    d.year = inputValidatedInt("Year (1900-2099): ", 1900, 2099);
    return d;
}

void addCar(vector<Car>& cars) {
    Car c;
    c.brand = inputValidatedString("Brand: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -");
    c.color = inputValidatedString("Color: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    c.serialNumber = inputValidatedString("Serial number: ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    c.manufactureDate = inputDate("Manufacture date:");
    c.bodyType = inputBodyType();
    c.lastInspection = inputDate("Last inspection date:");
    c.owner = inputValidatedString("Owner: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ");

    cars.push_back(c);
}

void printCar(const Car& c) {
    cout << "------------------------------------------------------\n"
        << "| Brand: " << c.brand << "\n"
        << "| Color: " << c.color << "\n"
        << "| Serial: " << c.serialNumber << "\n"
        << "| Body: " << bodyTypes[c.bodyType] << "\n"
        << "| Manufactured: " << formatDate(c.manufactureDate) << "\n"
        << "| Last inspection: " << formatDate(c.lastInspection) << "\n"
        << "| Owner: " << c.owner << "\n"
        << "------------------------------------------------------\n";
}

void searchByOwner(const vector<Car>& cars) {
    string owner = inputValidatedString("Enter owner name: ", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ");
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
    string serial = inputValidatedString("Enter serial number to delete: ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

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
    ofstream file(filename);
    if (!file) {
        cerr << "Error saving file!\n";
        return;
    }

    file << cars.size() << "\n";
    for (const auto& c : cars) {
        file << c.brand << "\n"
            << c.color << "\n"
            << c.serialNumber << "\n"
            << c.manufactureDate.day << " "
            << c.manufactureDate.month << " "
            << c.manufactureDate.year << "\n"
            << static_cast<int>(c.bodyType) << "\n"
            << c.lastInspection.day << " "
            << c.lastInspection.month << " "
            << c.lastInspection.year << "\n"
            << c.owner << "\n";
    }
    cout << "Data saved to " << filename << endl;
}

void loadFromFile(vector<Car>& cars, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error loading file!\n";
        return;
    }

    cars.clear();
    int count;
    if (!(file >> count)) {
        cerr << "Error reading count!\n";
        return;
    }
    file.ignore(INT32_MAX, '\n');

    for (int i = 0; i < count; ++i) {
        Car c;

        getline(file, c.brand);
        getline(file, c.color);
        getline(file, c.serialNumber);

        if (!(file >> c.manufactureDate.day >> c.manufactureDate.month >> c.manufactureDate.year)) {
            cerr << "Error reading manufacture date!\n";
            break;
        }

        int bodyType;
        if (!(file >> bodyType)) {
            cerr << "Error reading body type!\n";
            break;
        }
        c.bodyType = static_cast<BodyType>(bodyType);

        if (!(file >> c.lastInspection.day >> c.lastInspection.month >> c.lastInspection.year)) {
            cerr << "Error reading inspection date!\n";
            break;
        }

        file.ignore(INT32_MAX, '\n');
        getline(file, c.owner);

        cars.push_back(c);
    }
    cout << "Data loaded from " << filename << endl;
}