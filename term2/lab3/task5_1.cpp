#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdio>     
#include <cstdlib>    

using namespace std;


int inputValidatedInt(const string& prompt, int min = 0, int max = INT32_MAX) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}


bool isValidString(const string& str, const string& allowedChars, bool canBeEmpty) {
    if (canBeEmpty && str.empty())
        return true;
    if (str.empty())
        return false;
    char c_prev = str[0];
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        // Если первый или последний символ является допустимым спецсимволом, то считаем ввод недопустимым
        if ((i == 0 || i == str.length() - 1) && allowedChars.find(c) != string::npos)
            return false;
        // Если символ не буква, то он должен присутствовать в списке дополнительных допустимых символов
        if (!isalpha(c)) {
            if (allowedChars.find(c) == string::npos)
                return false;
            // Если спецсимволы идут подряд, то также считаем ввод ошибочным
            if (allowedChars.find(c) != string::npos && c_prev == c)
                return false;
        }
        c_prev = c;
    }
    return true;
}


string inputValidatedString(const string& prompt, const string& allowedChars, bool canBeEmpty, const string& strReplaced = "EMPTY") {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (isValidString(value, allowedChars, canBeEmpty)) {
            if (value.empty())
                return strReplaced;
            return value;
        }
        cout << "Invalid input!" << endl;
    }
}


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


Teacher inputTeacher() {
    Teacher t;
    t.surname = inputValidatedString("Enter teacher's surname: ", " -", false);
    t.examName = inputValidatedString("Enter exam name: ", " -", false);

    int day = inputValidatedInt("Enter exam day (1-31): ", 1, 31);
    int month = inputValidatedInt("Enter exam month (1-12): ", 1, 12);
    int year = inputValidatedInt("Enter exam year (1900-2100): ", 1900, 2100);


    sprintf(t.examDate.dateStr, "%02d/%02d/%04d", day, month, year);
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
