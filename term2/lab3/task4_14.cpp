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

// Перечисление для типа размещения
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

// Битовая структура для даты
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
    string passport;
    Date arrivalDate;
    Date departureDate;
    int roomNumber;
    AccommodationType accommodation;
};

// Прототипы функций
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
        << (d.year + 2000); // Восстанавливаем полный год
    return ss.str();
}

Date inputDate(const string& prompt) {
    cout << prompt << endl;
    Date d;
    d.day = inputValidatedInt("Day (1-31): ", 1, 31);
    d.month = inputValidatedInt("Month (1-12): ", 1, 12);
    d.year = inputValidatedInt("Year (2000-2099): ", 2000, 2099) - 2000;
    return d;
}

bool validatePassport(const string& input) {
    // Формат: 4 буквы, 6 цифр (с пробелом или без)
    if (input.length() != 10 && input.length() != 11) return false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (i < 4 && !isalpha(input[i])) return false;
        if (i == 4 && input[i] != ' ' && input.length() == 11) return false;
        if (i >= 4 + (input.length() == 11) && !isdigit(input[i])) return false;
    }
    return true;
}

string inputPassport() {
    string passport;
    while (true) {
        cout << "Passport (AAAA 123456 or AAAA123456): ";
        getline(cin, passport);

        // Преобразование в верхний регистр
        transform(passport.begin(), passport.end(), passport.begin(), ::toupper);

        // Удаление пробелов для проверки
        string cleanPassport = passport;
        cleanPassport.erase(remove(cleanPassport.begin(), cleanPassport.end(), ' '), cleanPassport.end());

        if (cleanPassport.size() == 10 &&
            all_of(cleanPassport.begin(), cleanPassport.begin() + 4, ::isalpha) &&
            all_of(cleanPassport.begin() + 4, cleanPassport.end(), ::isdigit)) {
            // Форматирование с пробелом
            return cleanPassport.substr(0, 4) + " " + cleanPassport.substr(4);
        }

        cout << "Invalid passport format! Examples: ABCD 123456 or ABCD123456\n";
    }
}

bool validateDates(const Date& arrival, const Date& departure) {
    return !(departure < arrival);
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

void addGuest(vector<HotelGuest>& guests) {
    HotelGuest g;

    g.passport = inputPassport();

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