#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

struct TRAIN {
    string destination;
    double number; // Изменён тип на double
    string departure;
};

// Прототипы функций
string validateTime(const string& input);
string inputTime();
double inputTrainNumber(); // Изменён тип возвращаемого значения
void printAllTrains(const vector<TRAIN>& trains);
void searchTrains(const vector<TRAIN>& trains);
bool compareTrains(const TRAIN& a, const TRAIN& b);
bool validateDestination(const string& dest); // Новая функция валидации

int main() {
    const int NUM_TRAINS = 8;
    vector<TRAIN> trains(NUM_TRAINS);

    // Ввод данных
    cout << "*** DATA INPUT ***" << endl;
    for (int i = 0; i < NUM_TRAINS; ++i) {
        cout << "\nTrain #" << i + 1 << endl;

        // Ввод и валидация названия
        while (true) {
            cout << "Destination: ";
            getline(cin, trains[i].destination);
            if (validateDestination(trains[i].destination)) break;
            cout << "Invalid name! Format examples: Moscow, Saint-Petersburg\n";
        }

        trains[i].number = inputTrainNumber();
        trains[i].departure = inputTime();
    }

    // Сортировка (без изменений)
    sort(trains.begin(), trains.end(), compareTrains);

    // Главное меню (без изменений)
    while (true) {
        cout << "\n1. Show all trains (sorted)"
            << "\n2. Search trains by departure time"
            << "\n3. Exit"
            << "\nEnter choice: ";

        string choice_str;
        int choice;
        getline(cin, choice_str);
        stringstream ss(choice_str);

        if (!(ss >> choice)) {
            cout << "Invalid input! Please enter 1-3\n";
            continue;
        }

        switch (choice) {
        case 1:
            printAllTrains(trains);
            break;
        case 2:
            searchTrains(trains);
            break;
        case 3:
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Invalid choice! Please enter 1-3\n";
        }
    }
}

// Реализация функций

bool validateDestination(const string& dest) {
    if (dest.empty()) return false;

    bool require_upper = true;
    for (size_t i = 0; i < dest.size(); ++i) {
        char c = dest[i];

        if (require_upper) {
            if (!isupper(c)) return false;
            require_upper = false;
        }
        else {
            if (c == ' ' || c == '-') {
                require_upper = true;
            }
            else if (!isalpha(c) && c != '\'') { // Разрешаем апострофы
                return false;
            }
        }
    }
    return true;
}

bool compareTrains(const TRAIN& a, const TRAIN& b) {
    return a.destination < b.destination;
}

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

string inputTime() {
    // Без изменений
    string time;
    while (true) {
        cout << "Departure time (HH:MM): ";
        getline(cin, time);
        string formatted = validateTime(time);
        if (!formatted.empty()) return formatted;
        cout << "Invalid time! Examples: 04:06, 23:59, 12:00\n";
    }
}

double inputTrainNumber() {
    string input;
    double number;
    while (true) {
        cout << "Train number (0.1-9999.9): ";
        getline(cin, input);

        // Замена запятых на точки
        replace(input.begin(), input.end(), ',', '.');

        stringstream ss(input);
        if (ss >> number && number > 0.0 && number < 10000.0) {
            // Проверка на оставшиеся символы
            char remaining;
            if (ss >> remaining) {
                cout << "Invalid! Only digits and decimal point allowed\n";
            }
            else {
                return number;
            }
        }
        else {
            cout << "Invalid! Must be 0.1 to 9999.9\n";
        }
    }
}

void printAllTrains(const vector<TRAIN>& trains) {
    cout << "\n*** ALL TRAINS ***" << endl;
    for (const auto& t : trains) {
        cout << "Destination: " << t.destination
            << " | Train #";
        // Вывод числа без лишних нулей
        if (t.number == static_cast<int>(t.number))
            cout << static_cast<int>(t.number);
        else
            cout << t.number;
        cout << " | Departure: " << t.departure << endl;
    }
}

void searchTrains(const vector<TRAIN>& trains) {
    // Без изменений
    cout << "\n*** SEARCH ***" << endl;
    string searchTime = inputTime();

    bool found = false;
    cout << "\nTrains departing after " << searchTime << ":\n";
    for (const auto& t : trains) {
        if (t.departure > searchTime) {
            cout << "Destination: " << t.destination
                << " | Train #" << t.number
                << " | Departure: " << t.departure << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No trains found departing after " << searchTime << endl;
    }
}