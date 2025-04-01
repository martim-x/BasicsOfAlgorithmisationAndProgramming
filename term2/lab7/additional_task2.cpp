#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>
#include "validators.h"

using namespace std;

struct Student {
    string lastName;
    string firstName;
    string patronymic;
    int birthYear;
    int course;
    string group;
    vector<int> grades;
};

struct GroupStats {
    map<string, vector<double>> subjectAverages;
    Student* bestStudent = nullptr;
};

struct SchoolClass {
    vector<string> subjects;
    vector<Student> students;
};

bool compareStudents(const Student& a, const Student& b) {
    if (a.course != b.course) return a.course < b.course;
    if (a.lastName != b.lastName) return a.lastName < b.lastName;
    if (a.firstName != b.firstName) return a.firstName < b.firstName;
    return a.patronymic < b.patronymic;
}

Student inputStudent(const vector<string>& subjects) {
    Student s;
    s.lastName = inputValidatedName("Enter last name: ", true);
    s.firstName = inputValidatedName("Enter first name: ", false);
    s.patronymic = inputValidatedCountryOrTownName("Enter patronymic: ", true);
    s.birthYear = inputValidatedInt("Enter birth year (1999 - 2010): ", 1999, 2010);
    s.course = inputValidatedInt("Enter course (1 - 6): ", 1, 6);
    s.group = inputValidatedInt("Enter group (1 - 10): ", 1, 10);

    cout << "Enter 5 grades:\n";
    for (int i = 0; i < 5; ++i) {
        s.grades.push_back(
            inputValidatedInt(subjects[i] + " grade (1 - 10): ", 1, 10)
        );
    }
    return s;
}

void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), compareStudents);
}

map<string, GroupStats> calculateStatistics(vector<Student>& students, const vector<string>& subjects) {
    map<string, GroupStats> stats;

    for (auto& student : students) {
        string group = student.group;
        GroupStats& groupStat = stats[group];

        double total = accumulate(student.grades.begin(), student.grades.end(), 0.0);
        double avg = total / student.grades.size();

        if (!groupStat.bestStudent || (avg > accumulate(
            groupStat.bestStudent->grades.begin(),
            groupStat.bestStudent->grades.end(), 0.0) / groupStat.bestStudent->grades.size())) {
            groupStat.bestStudent = &student;
        }

        for (size_t i = 0; i < subjects.size(); ++i) {
            groupStat.subjectAverages[subjects[i]].push_back(student.grades[i]);
        }
    }

    for (auto& entry : stats) {
        GroupStats& stat = entry.second;
        for (auto& subjectEntry : stat.subjectAverages) {
            vector<double>& grades = subjectEntry.second;
            if (!grades.empty()) {
                double sum = accumulate(grades.begin(), grades.end(), 0.0);
                size_t count = grades.size();
                grades.clear();
                grades.push_back(sum / count);
            }
        }
    }

    return stats;
}

pair<Student*, Student*> findAgeExtremes(vector<Student>& students) {
    if (students.empty()) return { nullptr, nullptr };

    auto minmax = minmax_element(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.birthYear < b.birthYear; });

    return { &*minmax.second, &*minmax.first };
}

void printStatistics(const map<string, GroupStats>& stats) {
    for (const auto& entry : stats) {
        const string& group = entry.first;
        const GroupStats& data = entry.second;
        cout << "\nGroup: " << group << "\nAverage grades:\n";
        for (const auto& subjectEntry : data.subjectAverages) {
            cout << subjectEntry.first << ": " << subjectEntry.second[0] << endl;
        }

        if (data.bestStudent) {
            cout << "\nBest student: " << data.bestStudent->lastName << " "
                << data.bestStudent->firstName << " (Average: "
                << accumulate(data.bestStudent->grades.begin(),
                    data.bestStudent->grades.end(), 0.0) / 5.0 << ")\n";
        }
    }
}

void showMenu() {
    cout << "\n1. Add student\n"
        << "2. Show students\n"
        << "3. Sort students\n"
        << "4. Show statistics\n"
        << "5. Show age extremes\n"
        << "6. Exit\n"
        << "Choice: ";
}

int main() {
    SchoolClass database;
    database.subjects = { "Math", "Physics", "Chemistry", "Literature", "History" };

    while (true) {
        showMenu();
        int choice = inputValidatedInt("", 1, 6);

        switch (choice) {
        case 1:
            database.students.push_back(inputStudent(database.subjects));
            break;
        case 2:
            for (const auto& s : database.students) {
                cout << s.lastName << " " << s.firstName << " Course: " << s.course
                    << " Group: " << s.group << endl;
            }
            break;
        case 3:
            sortStudents(database.students);
            break;
        case 4:
            printStatistics(calculateStatistics(database.students, database.subjects));
            break;
        case 5: {
            pair<Student*, Student*> ageExtremes = findAgeExtremes(database.students);
            Student* youngest = ageExtremes.first;
            Student* oldest = ageExtremes.second;
            if (oldest) {
                cout << "\nOldest student: " << oldest->patronymic << " " << oldest->firstName << " ("
                    << oldest->birthYear << ")";
                cout << "\nYoungest student: " << youngest->patronymic << " " << youngest->firstName << " ("
                    << youngest->birthYear << ")\n";
            }
            break;
        }
        case 6:
            return 0;
        }
    }
}