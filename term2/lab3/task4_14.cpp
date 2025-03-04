// УДОСТОВЕРИТЬСЯ НА НУЖНОСТЬ ИМПРОТОВ ЗАВИСИМОСТЕЙ
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

enum AccommodationType {
    LUXURY,
    SINGLE,
    DOUBLE,
    TRIPLE,
    APARTMENT,
    ACCOMMODATION_COUNT
};


const string accommodationTypes[] = {
    "Luxury", "Single", "Double", "Triple", "Apartment"
};


struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};


struct HotelGuest {
    string first_name;
    string sur_name;
    string last_name;
    string passport;
    Date arrivalDate;
    Date departureDate;
    int roomNumber;
    AccommodationType accommodation;
};


Date inputDate(const string& prompt);
void printGuest(const HotelGuest& g);
void addGuest(vector<HotelGuest>& guests);
void searchByArrivalDate(const vector<HotelGuest>& guests);
int inputValidatedInt(const string& prompt, int min, int max);
bool validatePassport(const string& input);
string inputPassport();
bool validateDates(const Date& arrival, const Date& departure);
string formatDate(const Date& d);

vector<HotelGuest> guests;


int main() {
    while (true) {
        cout << "\nHotel Management System\n"
            << "1. Add Guest\n"
            << "2. Show All Guests\n"
            << "3. Search by Arrival Date\n"
            << "4. Exit\n"
            << "Enter choice: ";

        int choice = inputValidatedInt("", 1, 4);

        switch (choice) {
        case 1: addGuest(guests); break;
        case 2:
            for (const auto& g : guests) printGuest(g);
            break;
        case 3: searchByArrivalDate(guests); break;
        case 4: return 0;
        }
    }
}


string formatDate(const Date& d) {
    stringstream ss;
    ss << setfill('0')
        << setw(2) << d.day << "/"
        << setw(2) << d.month << "/"
        << (d.year + 2000);
    return ss.str();
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


string inputPassport(const string& promt) {
    string passport;
    cout << promt << "\n";
    while (true) {
        getline(cin, passport);
        regex pattern("^[A-Z]{2}[0-9]{7}$");
        if (regex_match(passport, pattern)) {
            return passport;
        }
        else {
            cout << "Invalid passport number. Please enter a valid passport number.\n";
        }
    }
}


bool validateDates(const Date& arrival, const Date& departure) {
    return !(departure < arrival);
}


void addGuest(vector<HotelGuest>& guests) {
    HotelGuest g;

    g.first_name = inputValidatedName("Enter first name: ", false);
    g.sur_name = inputValidatedName("Enter sur name: ", false);
    g.last_name = inputValidatedName("Enter last name: ", true);
    g.passport = inputPassport("Enter passport (2 uppercase letters followed by 7 digits): ");

    while (true) {
        g.arrivalDate = inputDate("Arrival date:");
        g.departureDate = inputDate("Departure date:");

        if (validateDates(g.arrivalDate, g.departureDate)) break;
        cout << "Departure date must be after arrival date!\n";
    }

    g.roomNumber = inputValidatedInt("Room number (1-999): ", 1, 999);

    cout << "Select accommodation type:\n"
        << "1. Luxury\n2. Single\n3. Double\n4. Triple\n5. Apartment\n";
    g.accommodation = static_cast<AccommodationType>(inputValidatedInt("Choice (1-5): ", 1, 5) - 1);

    guests.push_back(g);
}


void printGuest(const HotelGuest& g) {
    cout << "------------------------------------------------------\n"
        << "| First name: " << g.first_name << "\n"
        << "| Sur name: " << g.sur_name << "\n"
        << "| Last name: " << g.last_name << "\n"
        << "| Passport: " << g.passport << "\n"
        << "| Arrival: " << formatDate(g.arrivalDate) << "\n"
        << "| Departure: " << formatDate(g.departureDate) << "\n"
        << "| Room: " << g.roomNumber << "\n"
        << "| Accommodation: " << accommodationTypes[g.accommodation] << "\n"
        << "------------------------------------------------------\n";
}


void searchByArrivalDate(const vector<HotelGuest>& guests) {
    Date searchDate = inputDate("Enter search arrival date:");

    bool found = false;
    for (const auto& g : guests) {
        if (g.arrivalDate.day == searchDate.day &&
            g.arrivalDate.month == searchDate.month &&
            g.arrivalDate.year == searchDate.year) {
            printGuest(g);
            found = true;
        }
    }

    if (!found) {
        cout << "No guests found with arrival date "
            << formatDate(searchDate) << endl;
    }
}