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


union AdmissionDate {
    struct {
        int day;
        int month;
        int year;
    } parts;
    char dateStr[11];
};


struct StudentRecord {
    string first_name;
    string sur_name;
    string last_name;
    AdmissionDate admitDate;
    string specialization;
    int group;
    string faculty;
    double averageGrade;
};


bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


bool isValidAdmissionDate(int day, int month, int year) {

    if (year < 1900 || year > 2100) return false;

    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    return (day >= 1 && day <= daysInMonth[month - 1]);
}


StudentRecord inputStudent() {
    StudentRecord s;
    s.first_name = inputValidatedName("Enter first name: ", false);
    s.sur_name = inputValidatedName("Enter sur name: ", false);
    s.last_name = inputValidatedName("Enter last name: ", true);

    int day, month, year;
    do {
        day = inputValidatedInt("Enter admission day (1-31): ", 1, 31);
        month = inputValidatedInt("Enter admission month (1-12): ", 1, 12);
        year = inputValidatedInt("Enter admission year (1900-2100): ", 1900, 2100);

        if (!isValidAdmissionDate(day, month, year)) {
            cout << "Invalid date! Please enter a valid date.\n";
        }
    } while (!isValidAdmissionDate(day, month, year));

    s.admitDate.parts.day = day;
    s.admitDate.parts.month = month;
    s.admitDate.parts.year = year;
    snprintf(s.admitDate.dateStr, sizeof(s.admitDate.dateStr), "%02d/%02d/%04d", day, month, year);

    s.specialization = inputValidatedString("Enter specialization: ", " -0123456789", false);
    s.group = inputValidatedInt("Enter group: ", 1, 10);
    s.faculty = inputValidatedString("Enter faculty: ", " -", false);
    s.averageGrade = inputValidatedDouble("Enter average grade (0.0 - 10.0): ", 0.0, 10.0);
    return s;
}


void printStudent(const StudentRecord& s) {
    cout << "First Name      : " << s.first_name << "\n"
        << "Sur Name      : " << s.sur_name << "\n"
        << "Last Name      : " << s.last_name << "\n"
        << "Admission Date : " << s.admitDate.dateStr << "\n"
        << "Specialization : " << s.specialization << "\n"
        << "Group          : " << s.group << "\n"
        << "Faculty        : " << s.faculty << "\n"
        << "Average Grade  : " << s.averageGrade << "\n";
}


void printAllStudents(const vector<StudentRecord>& students) {
    if (students.empty()) {
        cout << "No student records available." << endl;
        return;
    }
    for (const auto& s : students) {
        cout << "----------------------------------\n";
        printStudent(s);
    }
    cout << "----------------------------------\n";
}


void saveToFile(const vector<StudentRecord>& students, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    fout << students.size() << "\n";
    for (const auto& s : students) {
        fout << s.first_name << "\n";
        fout << s.sur_name << "\n";
        fout << s.last_name << "\n";
        fout << s.admitDate.dateStr << "\n";
        fout << s.specialization << "\n";
        fout << s.group << "\n";
        fout << s.faculty << "\n";
        fout << s.averageGrade << "\n";
    }
    fout.close();
    cout << "Data saved to " << filename << endl;
}


void loadFromFile(vector<StudentRecord>& students, const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }
    students.clear();
    size_t count;
    fin >> count;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < count; i++) {
        StudentRecord s;
        getline(fin, s.first_name);
        getline(fin, s.sur_name);
        getline(fin, s.last_name);

        fin.getline(s.admitDate.dateStr, sizeof(s.admitDate.dateStr));
        getline(fin, s.specialization);
        fin >> s.group;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, s.faculty);
        fin >> s.averageGrade;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        students.push_back(s);
    }
    fin.close();
    cout << "Data loaded from " << filename << endl;
}


void searchByAverageGrade(const vector<StudentRecord>& students) {
    if (students.empty()) {
        cout << "No student records available." << endl;
        return;
    }
    double threshold = inputValidatedDouble("Enter minimum average grade to search (0.0 - 10.0): ", 0.0, 10.0);
    bool found = false;
    cout << "\nStudents with average grade >= " << threshold << ":\n";
    for (const auto& s : students) {
        if (s.averageGrade >= threshold) {
            cout << "----------------------------------\n";
            printStudent(s);
            found = true;
        }
    }
    if (!found) {
        cout << "No records found matching the criteria." << endl;
    }
}


void showMenu() {
    cout << "\n=== Student Information System ===\n"
        << "1. Add Student Record\n"
        << "2. Display All Records\n"
        << "3. Save to File\n"
        << "4. Load from File\n"
        << "5. Search by Average Grade\n"
        << "6. Exit\n"
        << "Choice: ";
}


int main() {
    vector<StudentRecord> students;
    const string filename = "task5_16.txt";

    while (true) {
        showMenu();
        int choice = inputValidatedInt("", 1, 6);
        switch (choice) {
        case 1:
            students.push_back(inputStudent());
            break;
        case 2:
            printAllStudents(students);
            break;
        case 3:
            saveToFile(students, filename);
            break;
        case 4:
            loadFromFile(students, filename);
            break;
        case 5:
            searchByAverageGrade(students);
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    }
}
