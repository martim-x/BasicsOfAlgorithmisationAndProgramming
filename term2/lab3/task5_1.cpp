// УДОСТОВЕРИТЬСЯ НА НУЖНОСТЬ ИМПРОТОВ ЗАВИСИМОСТЕЙ
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdio>     
#include <cstdlib>
#include "validators.h"

using namespace std;


union ExamDate {
    struct {
        int day;
        int month;
        int year;
    } parts;
    char dateStr[11];
};


struct Teacher {
    string surname;
    string examName;
    ExamDate examDate;
};


bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


bool isValidDate(const ExamDate& date) {
    int day = date.parts.day;
    int month = date.parts.month;
    int year = date.parts.year;

    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDay = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year)) {
        maxDay = 29;
    }

    return day >= 1 && day <= maxDay;
}


ExamDate inputExamDate(const string& prompt) {
    ExamDate date;
    while (true) {
        cout << prompt << endl;
        date.parts.day = inputValidatedInt("Day (1-31): ", 1, 31);
        date.parts.month = inputValidatedInt("Month (1-12): ", 1, 12);
        date.parts.year = inputValidatedInt("Year (2000-2099): ", 2000, 2099);

        if (isValidDate(date)) {
            sprintf(date.dateStr, "%02d/%02d/%04d", date.parts.day, date.parts.month, date.parts.year);
            return date;
        }
        cout << "Invalid date! Please enter a valid date." << endl;
    }
}



Teacher inputTeacher() {
    Teacher t;
    t.surname = inputValidatedName("Enter teacher's surname: ", false);
    t.examName = inputValidatedString("Enter exam name: ", " -,.0123456789",false);
    t.examDate = inputExamDate("Enter exam date: ");
    return t;
}


void printTeacher(const Teacher& t) {
    cout << "Teacher Surname: " << t.surname << "\n"
        << "Exam Name      : " << t.examName << "\n"
        << "Exam Date      : " << t.examDate.dateStr << "\n";
}


void saveToFile(const vector<Teacher>& teachers, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    fout << teachers.size() << "\n";
    for (const auto& t : teachers) {
        fout << t.surname << "\n"
            << t.examName << "\n"
            << t.examDate.dateStr << "\n";
    }
    fout.close();
    cout << "Data saved to " << filename << endl;
}


void loadFromFile(vector<Teacher>& teachers, const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }
    teachers.clear();
    size_t count;
    fin >> count;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < count; i++) {
        Teacher t;
        getline(fin, t.surname);
        getline(fin, t.examName);

        fin.getline(t.examDate.dateStr, sizeof(t.examDate.dateStr));
        teachers.push_back(t);
    }
    fin.close();
    cout << "Data loaded from " << filename << endl;
}


void printAllTeachers(const vector<Teacher>& teachers) {
    if (teachers.empty()) {
        cout << "No teacher records available." << endl;
        return;
    }
    for (const auto& t : teachers) {
        cout << "--------------------------\n";
        printTeacher(t);
    }
}


void searchTeacherBySurname(const vector<Teacher>& teachers) {
    string searchSurname = inputValidatedString("Enter teacher's surname to search: ", " -", false);
    bool found = false;
    for (const auto& t : teachers) {
        if (t.surname == searchSurname) {
            printTeacher(t);
            cout << "--------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No teacher found with surname: " << searchSurname << endl;
    }
}


void showMenu() {
    cout << "\n=== Teacher Exam Information System ===\n"
        << "1. Add Teacher Record\n"
        << "2. Save to File\n"
        << "3. Load from File\n"
        << "4. Display All Records\n"
        << "5. Search by Surname\n"
        << "6. Exit\n"
        << "Choice: ";
}

int main() {
    vector<Teacher> teachers;
    const string filename = "task5_1.txt";

    while (true) {
        showMenu();
        int choice = inputValidatedInt("", 1, 6);
        switch (choice) {
        case 1:
            teachers.push_back(inputTeacher());
            break;
        case 2:
            saveToFile(teachers, filename);
            break;
        case 3:
            loadFromFile(teachers, filename);
            break;
        case 4:
            printAllTeachers(teachers);
            break;
        case 5:
            searchTeacherBySurname(teachers);
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
}
