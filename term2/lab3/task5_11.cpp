#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>
#include <regex>
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


const string bodyTypes[] = { "Sedan", "Universal", "Hatchback", "Coupe",
                           "SUV", "Minivan", "Pickup" };


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
    string first_name;
    string sur_name;
    string last_name;
};


BodyType inputBodyType();
void printCar(const Car& c);
void addCar(vector<Car>& cars);
void deleteCar(vector<Car>& cars);
void searchByOwner(const vector<Car>& cars);
void saveToFile(const vector<Car>& cars, const string& filename);
void loadFromFile(vector<Car>& cars, const string& filename);
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


string inputValidatedSerialNumber(const string& prompt) {
    string serial;
    while (true) {
        cout << prompt;
        getline(cin, serial);
        regex pattern("^[0-9]{4}[A-Z]{2}-[0-9]{1}$");

        if (regex_match(serial, regex(pattern)))
            return serial;

        cout << "Invalid format! Required format: 1234AB-5\n";
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
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year)) {
        maxDay = 29;
    }

    return day >= 1 && day <= maxDay;
}


Date inputDate(const string& prompt) {
    while (true) {
        cout << prompt << endl;
        int day = inputValidatedInt("Day (1-31): ", 1, 31);
        int month = inputValidatedInt("Month (1-12): ", 1, 12);
        int year = inputValidatedInt("Year (2000-2099): ", 2000, 2099);

        if (isValidDate(day, month, year)) {
            Date d;
            d.day = day;
            d.month = month;
            d.year = year - 2000;
            return d;
        }

        cout << "Invalid date! Please enter a valid date." << endl;
    }
}


bool isDateLater(const Date& date1, const Date& date2) {
    int year1 = date1.year + 2000;
    int year2 = date2.year + 2000;
    if (year1 != year2) return year1 > year2;
    if (date1.month != date2.month) return date1.month > date2.month;
    return date1.day > date2.day;
}


void addCar(vector<Car>& cars) {
    Car c;
    c.brand = inputValidatedString("Brand: ", " -", false);
    c.color = inputValidatedString("Color: ", " -", false);
    c.serialNumber = inputValidatedSerialNumber("Serial number (1234AB-5): ");
    c.manufactureDate = inputDate("Manufacture date (DD/MM/YYYY): ");
    c.bodyType = inputBodyType();

    do {
        c.lastInspection = inputDate("Last inspection date (DD/MM/YYYY): ");
        if (!isDateLater(c.lastInspection, c.manufactureDate)) {
            cout << "Last inspection must be after manufacture date!\n";
        }
    } while (!isDateLater(c.lastInspection, c.manufactureDate));

    c.first_name = inputValidatedName("Enter owner first name: ", false);
    c.sur_name = inputValidatedName("Enter owner sur name: ", false);
    c.last_name = inputValidatedName("Enter owner last name: ", true);
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
        << "| Owner first name: " << c.first_name << "\n"
        << "| Owner sur name: " << c.sur_name << "\n"
        << "| Owner last name: " << c.last_name << "\n"
        << "------------------------------------------------------\n";
}


void searchByOwner(const vector<Car>& cars) {
    string owner = inputValidatedName("Enter owner name: ", true);
    bool found = false;

    for (const auto& c : cars) {
        if (c.sur_name == owner) {
            printCar(c);
            found = true;
        }
    }

    if (!found) {
        cout << "No cars found for owner: " << owner << endl;
    }
}


void deleteCar(vector<Car>& cars) {
    string serial = inputValidatedSerialNumber("Enter serial number (1234AB-5): ");

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
            << c.first_name << "\n"
            << c.sur_name << "\n"
            << c.last_name << "\n";
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
        getline(file, c.first_name);


        file.ignore(INT32_MAX, '\n');
        getline(file, c.sur_name);


        file.ignore(INT32_MAX, '\n');
        getline(file, c.last_name);

        cars.push_back(c);
    }
    cout << "Data loaded from " << filename << endl;
}