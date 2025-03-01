#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <bitset>
#include <algorithm>
#include <cctype>
#include "validators.h"

using namespace std;


enum Destination {
    MOSCOW,
    PARIS,
    LONDON,
    NEW_YORK,
    TOKYO,
    DUBAI,
    BEIJING,
    SYDNEY,
    DESTINATION_COUNT
};


struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;
};


struct Flight {
    int number;
    Destination destination;
    string departureTime;
    Date date;
    double ticketPrice;
    int seatsAvailable;
};


Destination inputDestination();
Date inputDate();
void printFlight(const Flight& f);
void addFlight(vector<Flight>& flights);
void deleteFlight(vector<Flight>& flights);
void searchByDate(const vector<Flight>& flights);
vector<Flight> flights;

int main() {
    while (true) {
        cout << "\nAirline Management System\n"
            << "1. Add Flight\n"
            << "2. Show All Flights\n"
            << "3. Delete Flight\n"
            << "4. Search by Date\n"
            << "5. Exit\n"
            << "Enter choice: ";

        int choice = inputValidatedInt("", 1, 5);

        switch (choice) {
        case 1:
            addFlight(flights);
            cout<<endl;
            break;
        case 2:
            for (const auto& f : flights) printFlight(f);
            cout<<endl;
            break;
        case 3:
            deleteFlight(flights);
            cout<<endl;
            break;
        case 4:
            searchByDate(flights);
            cout<<endl;
            break;
        case 5:
            return 0;
        }
    }
}


Date inputDate() {
    Date d;
    while (true) {
        int day = inputValidatedInt("Enter day (1-31): ", 1, 31);
        int month = inputValidatedInt("Enter month (1-12): ", 1, 12);
        int year = inputValidatedInt("Enter year (1900-2099): ", 1900, 2099);

        d.day = day;
        d.month = month;
        d.year = year;
        return d;
    }
}


Destination inputDestination() {
    cout << "\nSelect destination:\n"
        << "1. Moscow\n2. Paris\n3. London\n4. New York\n"
        << "5. Tokyo\n6. Dubai\n7. Beijing\n8. Sydney\n";
    return static_cast<Destination>(inputValidatedInt("Choice (1-8): ", 1, 8) - 1);
}


void addFlight(vector<Flight>& flights) {
    Flight f;
    f.number = inputValidatedDouble("Enter flight number (0.1-9999.99999): ", 0.1, 9999.99999);
    f.destination = inputDestination();
    f.departureTime = inputTime("Enter deportation time: ");

    f.date = inputDate();
    f.ticketPrice = inputValidatedDouble("Ticket price (50.0-10000.0): ", 50, 10000);
    f.seatsAvailable = inputValidatedInt("Available seats (1-500): ", 1, 500);

    flights.push_back(f);
}


void printFlight(const Flight& f) {
    const string destinations[] = { "Moscow", "Paris", "London", "New York",
                                   "Tokyo", "Dubai", "Beijing", "Sydney" };
    cout << "Flight " << f.number << " to " << destinations[f.destination]
        << "\nDeparture: " << f.date.day << "/" << f.date.month << "/" << f.date.year
        << " at " << f.departureTime << "\nPrice: $" << fixed << setprecision(2)
        << f.ticketPrice << "\nSeat: " << f.seatsAvailable << "\n";
}


void searchByDate(const vector<Flight>& flights) {
    cout << "Enter search date:\n";
    Date searchDate = inputDate();

    for (const auto& f : flights) {
        if (f.date.day == searchDate.day &&
            f.date.month == searchDate.month &&
            f.date.year == searchDate.year) {
            printFlight(f);
        }
    }
}


void deleteFlight(vector<Flight>& flights) {
    int num = inputValidatedInt("Enter flight number to delete: ", 1, 9999);

    auto it = std::remove_if(flights.begin(), flights.end(),
        [num](const Flight& f) { return f.number == num; });

    if (it != flights.end()) {
        flights.erase(it, flights.end());
        cout << "Flight deleted\n";
    }
    else {
        cout << "Flight not found\n";
    }
}