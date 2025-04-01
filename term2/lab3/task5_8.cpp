#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "validators.h"

using namespace std;

const int DESTINATION_COUNT = 8;
const string destinations[] = {
    "Moscow", "Paris", "London", "New York",
    "Tokyo", "Dubai", "Beijing", "Sydney"
};

union Destination {
    int code;
};

struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;
};

struct Flight {
    Destination destination;
    string departureTime;
    Date date;
    int number;
    double price;
    int seats;
};

void addFlight(vector<Flight>& flights);
void printFlights(const vector<Flight>& flights);
void saveToFile(const vector<Flight>& flights, const string& filename);
void loadFromFile(vector<Flight>& flights, const string& filename);
void searchByDestination(const vector<Flight>& flights);
int inputDestination();
Date inputDate(const string& prompt);

int main() {
    vector<Flight> flights;
    const string filename = "task5_8.bin";

    while (true) {
        cout << "\nAirline Management System\n"
            << "1. Add Flight\n"
            << "2. Show All Flights\n"
            << "3. Save to File\n"
            << "4. Load from File\n"
            << "5. Search by Destination\n"
            << "6. Exit\n"
            << "Enter choice: ";

        int choice = inputValidatedInt("", 1, 6);

        switch (choice) {
        case 1: addFlight(flights); break;
        case 2: printFlights(flights); break;
        case 3: saveToFile(flights, filename); break;
        case 4: loadFromFile(flights, filename); break;
        case 5: searchByDestination(flights); break;
        case 6: return 0;
        }
    }
}

void addFlight(vector<Flight>& flights) {
    Flight f;
    f.number = inputValidatedInt("Enter flight number (0-1000000): ", 0, 1000000);
    f.destination.code = inputDestination();
    f.departureTime = inputTime("Enter departure time (HH:MM): ");
    f.date = inputDate("Enter departure date (DD/MM/YYYY): ");
    f.price = inputValidatedDouble("Enter ticket price (50.0-10000.0): ", 50, 10000);
    f.seats = inputValidatedInt("Enter available seats (1-500): ", 1, 500);

    flights.push_back(f);
}

void printFlights(const vector<Flight>& flights) {
    cout << "\nList of flights:\n";
    for (const auto& f : flights) {
        cout << "------------------------------------------------------\n"
            << "Flight: " << f.number
            << "\nDestination: " << destinations[f.destination.code]  // Используем массив строк
            << "\nDate: " << (int)f.date.day << "/"
            << (int)f.date.month << "/" << (f.date.year + 2000)
            << "\nTime: " << f.departureTime
            << "\nPrice: $" << fixed << setprecision(6) << f.price
            << "\nSeats: " << f.seats << "\n";
    }
    cout << "------------------------------------------------------\n";
}

void saveToFile(const vector<Flight>& flights, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error saving file!\n";
        return;
    }

    size_t count = flights.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& f : flights) {
        file.write(reinterpret_cast<const char*>(&f.number), sizeof(f.number));
        file.write(reinterpret_cast<const char*>(&f.destination.code), sizeof(f.destination.code));
        size_t timeSize = f.departureTime.size();
        file.write(reinterpret_cast<const char*>(&timeSize), sizeof(timeSize));
        file.write(f.departureTime.c_str(), timeSize);
        file.write(reinterpret_cast<const char*>(&f.date), sizeof(f.date));
        file.write(reinterpret_cast<const char*>(&f.price), sizeof(f.price));
        file.write(reinterpret_cast<const char*>(&f.seats), sizeof(f.seats));
    }
    cout << "Data saved to " << filename << endl;
}

void loadFromFile(vector<Flight>& flights, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error loading file!\n";
        return;
    }

    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    flights.resize(count);

    for (size_t i = 0; i < count; ++i) {
        file.read(reinterpret_cast<char*>(&flights[i].number), sizeof(int));
        file.read(reinterpret_cast<char*>(&flights[i].destination.code), sizeof(int));
        size_t timeSize;
        file.read(reinterpret_cast<char*>(&timeSize), sizeof(timeSize));
        flights[i].departureTime.resize(timeSize);
        file.read(&flights[i].departureTime[0], timeSize);
        file.read(reinterpret_cast<char*>(&flights[i].date), sizeof(Date));
        file.read(reinterpret_cast<char*>(&flights[i].price), sizeof(double));
        file.read(reinterpret_cast<char*>(&flights[i].seats), sizeof(int));
    }
    cout << "Data loaded from " << filename << endl;
}

int inputDestination() {
    cout << "Select destination:\n";
    for (int i = 0; i < DESTINATION_COUNT; ++i)
        cout << i + 1 << ". " << destinations[i] << "\n";
    return inputValidatedInt("Enter choice (1-8): ", 1, 8) - 1;
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

void searchByDestination(const vector<Flight>& flights) {
    int target = inputDestination();
    bool found = false;

    cout << "\nFlights to " << destinations[target] << ":\n";
    for (const auto& f : flights) {
        if (f.destination.code == target) {
            cout << "Flight: " << f.number
                << " | Date: " << (int)f.date.day << "/"
                << (int)f.date.month << "/" << (f.date.year + 2000)
                << " | Time: " << f.departureTime
                << " | Price: $" << fixed << setprecision(2) << f.price
                << " | Seats: " << f.seats << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No flights found to " << destinations[target] << endl;
    }
}
