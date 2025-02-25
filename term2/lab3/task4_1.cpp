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

// Битовая структура для даты
struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;
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

// Валидация целых чисел
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

// Валидация строк
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

// Ввод типа кузова
BodyType inputBodyType() {
    cout << "Select body type:\n"
        << "1. Sedan\n2. Universal\n3. Hatchback\n4. Coupe\n"
        << "5. SUV\n6. Minivan\n7. Pickup\n";
    return static_cast<BodyType>(inputValidatedInt("Choice (1-7): ", 1, 7) - 1);
}

// Ввод даты
Date inputDate(const string& prompt) {
    cout << prompt << endl;
    Date d;
    d.day = inputValidatedInt("Day (1-31): ", 1, 31);
    d.month = inputValidatedInt("Month (1-12): ", 1, 12);
    d.year = inputValidatedInt("Year (1900-2099): ", 1900, 2099);
    return d;
}

// Добавление автомобиля
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

// Вывод информации об автомобиле
void printCar(const Car& c) {
    cout << "------------------------------------------------------" << endl;
    cout << "| Brand: " << c.brand << endl;
    cout << "| Color: " << c.color << endl;
    cout << "| Serial: " << c.serialNumber << endl;
    cout << "| Body: " << c.bodyType << endl;
    cout << "| Manufactured: " << c.manufactureDate << endl;
    cout << "| Last inspection: " << c.lastInspection << endl;
    cout << "| Owner: " << c.owner << endl;
    cout << "------------------------------------------------------" << endl;
}

// Поиск по владельцу
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

// Удаление автомобиля
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

        file.write(c.serial.full, 10);

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

        // Чтение бренда
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        c.brand.resize(size);
        file.read(&c.brand[0], size);

        // Чтение цвета
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        c.color.resize(size);
        file.read(&c.color[0], size);

        // Чтение серийного номера
        file.read(c.serial.full, 10);

        // Чтение дат
        file.read(reinterpret_cast<char*>(&c.manufactureDate), sizeof(c.manufactureDate));
        file.read(reinterpret_cast<char*>(&c.bodyType), sizeof(c.bodyType));
        file.read(reinterpret_cast<char*>(&c.lastInspection), sizeof(c.lastInspection));

        // Чтение владельца
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        c.owner.resize(size);
        file.read(&c.owner[0], size);

        if (file) cars.push_back(c);
    }

    cout << "Data loaded from " << filename << endl;
}