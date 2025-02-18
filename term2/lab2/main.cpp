#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

class Student {
public:
    string surname;
    string first_name;
    string last_name;
    map<string, vector<int>> subjects;

    Student() : surname(""), first_name(""), last_name("") {}

    Student(const string& sn, const string& fn, const string& pt)
        : surname(sn), first_name(fn), last_name(pt) {
    }

    void add_subject(const string& subject_name, const vector<int>& grades) {
        for (auto grade : grades)
            subjects[subject_name].push_back(grade);
    }

    double calculate_average(const string& subject_name) const {  // Marked const because it does not modify the object
        int total = 0;
        int count = 0;
        if (subject_name == "ALL") {
            for (const auto& subj : subjects) {
                for (int grade : subj.second) {
                    total += grade;
                    count++;
                }
            }
        }
        else {
            for (int grade : subjects.at(subject_name)) {  // Using at() to safely access the element
                total += grade;
                count++;
            }
        }

        return (count > 0) ? double(total) / count : 0.0;
    }

    void print_info() const {  // Marked const because it does not modify the object
        cout << "Surname: " << surname << endl;
        cout << "First Name: " << first_name << endl;
        cout << "Last_name: " << last_name << endl;
        for (const auto& subject : subjects) {
            cout << subject.first << ": ";
            for (int grade : subject.second) {
                cout << grade << " ";
            }
            cout << endl;
        }
        cout << "Average Grade: " << calculate_average("ALL") << endl;
    }
};

class Form {
public:
    string form_name;
    map<string, Student> students;

    Form(const string& name) : form_name(name) {}

    void add_student(const string& full_name, const Student& student) {
        students[full_name] = student;
    }

    void remove_student(const string& full_name) {
        students.erase(full_name);
    }

    void print_all_students() const {  // Marked const because it does not modify the object
        if (students.empty()) {
            cout << "No students in form " << form_name << "." << endl;
            return;
        }
        cout << "Students in form " << form_name << ":\n";
        for (const auto& student : students) {
            student.second.print_info();
            cout << "----------------------\n";
        }
    }
};

void show_menu() {
    cout << "======================\n";
    cout << "1. Add Form\n";
    cout << "2. Add Student to Form\n";
    cout << "3. View All Students in Form\n";
    cout << "4. Delete Student from Form\n";
    cout << "5. Search by Average Grade\n";
    cout << "6. Save Data to Files\n";
    cout << "7. Load Data from Files\n";
    cout << "8. Exit\n";
    cout << "======================\n";
    cout << "Select an option: ";
}

int main() {
    map<string, Form> forms;
    int choice;

    while (true) {
        show_menu();
        cin >> choice;
        cin.ignore();
    }
}
