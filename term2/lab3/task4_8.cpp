#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <bitset>
#include <algorithm>  // Добавлено
#include <cctype>     // Добавлено

using namespace std;

// Перечисление для пунктов назначения
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

// Битовая структура для даты (5 бит день, 4 бита месяц, 14 бит год)
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

// Прототипы функций
Destination inputDestination();
Date inputDate();
void printFlight(const Flight& f);
void addFlight(vector<Flight>& flights);
void deleteFlight(vector<Flight>& flights);
void searchByDate(const vector<Flight>& flights);
bool validateName(const string& name);
int inputValidatedInt(const string& prompt, int min, int max);
string inputValidatedString(const string& prompt, const string& pattern);
double inputValidatedDouble(const string& prompt, double min, double max);

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

// Валидация строк по регулярному выражению
bool validateString(const string& input, const string& pattern) {
    for (char c : input) {
        if (pattern.find(c) == string::npos)
            return false;
    }
    return !input.empty();
}

double inputValidatedDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);

        // Исправление 1: Явное указание пространства имён для алгоритмов
        std::replace(input.begin(), input.end(), ',', '.');
        input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

        if (input.empty()) {
            cout << "Error: Empty input!\n";
            continue;
        }

        // Исправление 2: Используем std::count
        if (std::count(input.begin(), input.end(), '.') > 1) {
            cout << "Error: Multiple decimal points!\n";
            continue;
        }

        bool valid = true;
        bool digitFound = false;
        for (size_t i = 0; i < input.size(); ++i) {
            char c = input[i];
            if (!isdigit(c) && c != '.' && !(i == 0 && (c == '-' || c == '+'))) {
                valid = false;
                break;
            }
            if (isdigit(c)) digitFound = true;
        }

        if (!valid || !digitFound) {
            cout << "Error: Invalid characters!\n";
            continue;
        }

        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            if (value >= min && value <= max) {
                return value;
            }
            cout << "Error: Value must be between " << min << " and " << max << "!\n";
        }
        else {
            cout << "Error: Invalid numeric format!\n";
        }
    }
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

// Валидация времени
string validateTime(const string& input) {
    // Без изменений
    string time = input;
    if (time.empty()) return "";

    if (time.size() == 4 && time[1] == ':') time = "0" + time;
    if (time.size() == 3 && time[0] == ':') time = "00" + time;
    if (time.size() == 1) time = "0" + time + ":00";

    if (time.size() != 5 || time[2] != ':' ||
        !isdigit(time[0]) || !isdigit(time[1]) ||
        !isdigit(time[3]) || !isdigit(time[4])) return "";

    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));
    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return "";

    return time;
}

// Ввод и валидация даты
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

// Ввод пункта назначения
Destination inputDestination() {
    cout << "Select destination:\n"
        << "1. Moscow\n2. Paris\n3. London\n4. New York\n"
        << "5. Tokyo\n6. Dubai\n7. Beijing\n8. Sydney\n";
    return static_cast<Destination>(inputValidatedInt("Choice (1-8): ", 1, 8) - 1);
}



string inputTime() {
    string time;
    while (true) {
        cout << "Departure time (HH:MM): ";
        getline(cin, time);
        string formatted = validateTime(time);
        if (!formatted.empty()) return formatted;
        cout << "Invalid time! Examples: 04:06, 23:59, 12:00\n";
    }
}

// Добавление рейса
void addFlight(vector<Flight>& flights) {
    Flight f;
    f.number = inputValidatedDouble("Enter flight number (0.1-9999.99999): ", 0.1, 9999.99999);
    f.destination = inputDestination();
    f.departureTime = inputTime();

    f.date = inputDate();
    f.ticketPrice = inputValidatedDouble("Ticket price (50.0-10000.0): ", 50, 10000);
    f.seatsAvailable = inputValidatedInt("Available seats (1-500): ", 1, 500);

    flights.push_back(f);
}

// Вывод информации о рейсе
void printFlight(const Flight& f) {
    const string destinations[] = { "Moscow", "Paris", "London", "New York",
                                   "Tokyo", "Dubai", "Beijing", "Sydney" };
    cout << "Flight " << f.number << " to " << destinations[f.destination]
        << "\nDeparture: " << f.date.day << "/" << f.date.month << "/" << f.date.year
        << " at " << f.departureTime << "\nPrice: $" << fixed << setprecision(2)
        << f.ticketPrice << "\nSeat: " << f.seatsAvailable << "\n\n";
}

// Поиск по дате
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

// Удаление рейса
void deleteFlight(vector<Flight>& flights) {
    int num = inputValidatedInt("Enter flight number to delete: ", 1, 9999);

    // Исправление 3: Добавляем std:: перед remove_if
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