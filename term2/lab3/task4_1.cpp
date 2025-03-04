#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ctime>
#include "validators.h"

using namespace std;

enum Position {
    DIRECTOR,
    MANAGER,
    ENGINEER,
    TECHNICIAN,
    ACCOUNTANT,
    POSITION_COUNT
};

const string positionNames[] = {
    "Director", "Manager", "Engineer", "Technician", "Accountant"
};


struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 14;
};


struct Employee {
    string first_name;
    string sur_name;
    string last_name;
    string education;
    string specialty;
    string department;
    Position position;
    double salary;
    Date hireDate;
};


Date inputDate(const string& prompt);
void printEmployee(const Employee& e);
void addEmployee(vector<Employee>& employees);
void deleteEmployee(vector<Employee>& employees);
void searchByExperience(const vector<Employee>& employees);
string formatDate(const Date& d);


int main() {
    vector<Employee> employees;

    while (true) {
        cout << "\nHR Management System\n"
            << "1. Add Employee\n"
            << "2. Show All Employees\n"
            << "3. Delete Employee\n"
            << "4. Search by Experience\n"
            << "5. Exit\n"
            << "Enter choice: ";

        int choice = inputValidatedInt("", 1, 5);

        switch (choice) {
        case 1:
            addEmployee(employees);
            break;
        case 2:
            for (const auto& e : employees) {
                printEmployee(e);
            }
            break;
        case 3:
            deleteEmployee(employees);
            break;
        case 4:
            searchByExperience(employees);
            break;
        case 5:
            return 0;
        }
    }
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


string formatDate(const Date& d) {
    stringstream ss;
    ss << setfill('0')
        << setw(2) << d.day << "/"
        << setw(2) << d.month << "/"
        << (d.year + 2000);
    return ss.str();
}


void printEmployee(const Employee& e) {
    cout << "------------------------------------------------------\n"
        << "| Full Name: " << e.first_name << "\n"
        << "| Sur Name: " << e.sur_name << "\n"
        << "| Last Name: " << e.last_name << "\n"
        << "| Education: " << e.education << "\n"
        << "| Specialty: " << e.specialty << "\n"
        << "| Department: " << e.department << "\n"
        << "| Position: " << positionNames[e.position] << "\n"
        << "| Salary: " << e.salary << "\n"
        << "| Hire Date: " << formatDate(e.hireDate) << "\n"
        << "------------------------------------------------------\n";
}


void addEmployee(vector<Employee>& employees) {
    Employee e;

    e.first_name = inputValidatedName("Enter first name: ", false);
    e.sur_name = inputValidatedName("Enter sur name: ", false);
    e.last_name = inputValidatedName("Enter last name: ", true);

    e.education = inputValidatedString("Enter education: ", " .,-0123456789", false, "");
    e.specialty = inputValidatedString("Enter specialty: ", " .,-0123456789", false, "");
    e.department = inputValidatedString("Enter department: ", " .,-0123456789", false, "");

    cout << "Select position:\n";
    for (int i = 0; i < POSITION_COUNT; ++i) {
        cout << i + 1 << ". " << positionNames[i] << "\n";
    }
    int posChoice = inputValidatedInt("Enter position (1-" + to_string(POSITION_COUNT) + "): ", 1, POSITION_COUNT);
    e.position = static_cast<Position>(posChoice - 1);

    e.salary = inputValidatedDouble("Enter salary (0.0-1000000.0): ", 0.0, 1000000.0);

    e.hireDate = inputDate("Enter hire date: ");

    employees.push_back(e);
}


void deleteEmployee(vector<Employee>& employees) {
    if (employees.empty()) {
        cout << "No employees to delete.\n";
        return;
    }

    cout << "Employees list:\n";
    for (size_t i = 0; i < employees.size(); ++i) {
        cout << i + 1 << ". " << employees[i].first_name << " ";
        cout << i + 1 << ". " << employees[i].sur_name << " ";
        cout << i + 1 << ". " << employees[i].last_name << "\n";
    }

    int index = inputValidatedInt("Enter employee number to delete: ", 1, employees.size()) - 1;
    employees.erase(employees.begin() + index);
    cout << "Employee deleted.\n";
}


void searchByExperience(const vector<Employee>& employees) {
    int required = inputValidatedInt("Enter minimum experience (years): ", 0, 100);

    time_t now = time(nullptr);
    tm* currentTm = localtime(&now);
    int currentYear = currentTm->tm_year + 1900;
    int currentMonth = currentTm->tm_mon + 1;
    int currentDay = currentTm->tm_mday;

    bool found = false;
    for (const auto& e : employees) {
        int hireYear = e.hireDate.year + 2000;
        int expYears = currentYear - hireYear;

        if (currentMonth < e.hireDate.month || (currentMonth == e.hireDate.month && currentDay < e.hireDate.day)) {
            expYears--;
        }

        if (expYears >= required) {
            printEmployee(e);
            found = true;
        }
    }

    if (!found) {
        cout << "No employees with " << required << "+ years experience.\n";
    }
}