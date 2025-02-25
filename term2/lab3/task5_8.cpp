#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Перечисление для пунктов назначения
enum Destination {
    MOSCOW, PARIS, LONDON, NEW_YORK,
    TOKYO, DUBAI, BEIJING, SYDNEY, DESTINATION_COUNT
};

const string destinations[] = {
    "Moscow", "Paris", "London", "New York",
    "Tokyo", "Dubai", "Beijing", "Sydney"
};

// Объединение для номера рейса
union FlightNumber {
    struct {
        char airline[3];
        unsigned int number;
    } coded;
    unsigned int numeric;
};

// Битовая структура для даты
struct Date {
    unsigned int day : 5;    // 1-31
    unsigned int month : 4;  // 1-12
    unsigned int year : 14;  // 2000-2099
};

struct Flight {
    FlightNumber number;
    Destination destination;
    string departureTime;
    Date date;
    double price;
    int seats;
};

// Прототипы функций
void addFlight(vector<Flight>& flights);
void printFlights(const vector<Flight>& flights);
void saveToFile(const vector<Flight>& flights, const string& filename);
void loadFromFile(vector<Flight>& flights, const string& filename);
void searchByDestination(const vector<Flight>& flights);
int inputInt(const string& prompt, int min, int max);
double inputDouble(const string& prompt, double min, double max);
string inputTime();
Date inputDate();
Destination inputDestination();
bool validateFlightNumber(const string& input);

int main() {
    vector<Flight> flights;
    const string filename = "task5_8.dat";

    while (true) {
        cout << "\nAirline Management System\n"
            << "1. Add Flight\n"
            << "2. Show All Flights\n"
            << "3. Save to File\n"
            << "4. Load from File\n"
            << "5. Search by Destination\n"
            << "6. Exit\n"
            << "Enter choice: ";

        int choice = inputInt("", 1, 6);

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

// Реализация функций

bool validateFlightNumber(const string& input) {
    if (input.empty()) return false;

    // Проверка формата AAA-123
    if (input.size() == 7 &&
        isalpha(input[0]) && isalpha(input[1]) && isalpha(input[2]) &&
        input[3] == '-' &&
        isdigit(input[4]) && isdigit(input[5]) && isdigit(input[6]))
        return true;

    // Проверка числового формата
    if (all_of(input.begin(), input.end(), ::isdigit))
        return true;

    return false;
}

void addFlight(vector<Flight>& flights) {
    Flight f;
    string numberInput;

    // Ввод номера рейса
    while (true) {
        cout << "Enter flight number (AAA-123 or 12345): ";
        getline(cin, numberInput);
        transform(numberInput.begin(), numberInput.end(), numberInput.begin(), ::toupper);

        if (validateFlightNumber(numberInput)) break;
        cout << "Invalid flight number format!\n";
    }

    // Обработка номера рейса
    if (numberInput.find('-') != string::npos) {
        sscanf(numberInput.c_str(), "%3c-%3u",
            f.number.coded.airline,
            &f.number.coded.number);
    }
    else {
        f.number.numeric = stoi(numberInput);
    }

    f.destination = inputDestination();
    f.departureTime = inputTime();
    f.date = inputDate();
    f.price = inputDouble("Enter ticket price (50-10000): ", 50, 10000);
    f.seats = inputInt("Enter available seats (1-500): ", 1, 500);

    flights.push_back(f);
}

void printFlights(const vector<Flight>& flights) {
    cout << "\nList of flights:\n";
    for (const auto& f : flights) {
        cout << "------------------------------------------------------\n"
            << "Flight: ";

        if (isalpha(f.number.coded.airline[0])) {
            cout << f.number.coded.airline[0]
                << f.number.coded.airline[1]
                << f.number.coded.airline[2]
                << "-" << f.number.coded.number;
        }
        else {
            cout << f.number.numeric;
        }

        cout << "\nDestination: " << destinations[f.destination]
            << "\nDate: " << (int)f.date.day << "/"
            << (int)f.date.month << "/" << (f.date.year + 2000)
            << "\nTime: " << f.departureTime
            << "\nPrice: $" << fixed << setprecision(2) << f.price
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
        file.write(reinterpret_cast<const char*>(&f.destination), sizeof(f.destination));
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
        file.read(reinterpret_cast<char*>(&flights[i].number), sizeof(FlightNumber));
        file.read(reinterpret_cast<char*>(&flights[i].destination), sizeof(Destination));
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

Destination inputDestination() {
    cout << "Select destination:\n";
    for (int i = 0; i < DESTINATION_COUNT; ++i)
        cout << i + 1 << ". " << destinations[i] << "\n";
    return static_cast<Destination>(inputInt("Enter choice (1-8): ", 1, 8) - 1);
}

Date inputDate() {
    Date d;
    d.day = inputInt("Enter day (1-31): ", 1, 31);
    d.month = inputInt("Enter month (1-12): ", 1, 12);
    d.year = inputInt("Enter year (2000-2099): ", 2000, 2099) - 2000;
    return d;
}

string inputTime() {
    string time;
    while (true) {
        cout << "Enter departure time (HH:MM): ";
        getline(cin, time);

        if (time.size() == 5 &&
            isdigit(time[0]) && isdigit(time[1]) &&
            time[2] == ':' &&
            isdigit(time[3]) && isdigit(time[4])) {
            int hours = stoi(time.substr(0, 2));
            int minutes = stoi(time.substr(3, 2));
            if (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60)
                return time;
        }
        cout << "Invalid time format! Use HH:MM\n";
    }
}

int inputInt(const string& prompt, int min, int max) {
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

double inputDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        replace(line.begin(), line.end(), ',', '.');
        stringstream ss(line);

        if (ss >> value && value >= min && value <= max && ss.eof())
            return value;
        cout << "Invalid input! Enter value between " << min << " and " << max << endl;
    }
}

void searchByDestination(const vector<Flight>& flights) {
    Destination target = inputDestination();
    bool found = false;

    cout << "\nFlights to " << destinations[target] << ":\n";
    for (const auto& f : flights) {
        if (f.destination == target) {
            cout << "Flight: ";
            if (isalpha(f.number.coded.airline[0])) {
                cout << f.number.coded.airline[0]
                    << f.number.coded.airline[1]
                    << f.number.coded.airline[2]
                    << "-" << f.number.coded.number;
            }
            else {
                cout << f.number.numeric;
            }
            cout << " | Date: " << (int)f.date.day << "/"
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