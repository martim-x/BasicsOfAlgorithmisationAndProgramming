#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <limits>
#include <sstream>
#include <regex>
using namespace std;

struct Student {
    string lastName;
    string firstName;
    string surName;
    vector<int> grades;
};

struct Group {
    string groupName;
    vector<string> subjects;
    vector<Student> students;
};

struct University {
    vector<Group> groups;
};


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


        if ((i == 0 || i == str.length() - 1) && allowedChars.find(c) != string::npos)
            return false;

        if (!isalpha(c)) {
            if (allowedChars.find(c) == string::npos)
                return false;
            if (allowedChars.find(c) != string::npos && c_prev == c)
                return false;
        }
        c_prev = c;
    }
    return true;
}

// Ввод строки с валидацией
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

// Вывод информации об университете
void printUniversity(const University& university) {
    for (const auto& group : university.groups) {
        cout << "\nGroup: " << group.groupName << endl;
        cout << "Subjects: ";
        for (const auto& subj : group.subjects) {
            cout << subj << ", ";
        }
        cout << "\nStudents:\n";
        for (const auto& stud : group.students) {
            cout << "- " << stud.surName << " " << stud.firstName << " " << stud.lastName << "\nGrades:\n";
            for (int i = 0; i < stud.grades.size(); ++i) {
                cout << "  " << group.subjects[i] << ": ";
                cout << stud.grades[i] << endl;
            }
        }
    }
}


// Ввод данных об университете
void inputUniversity(University& university) {
    int numGroups;
    numGroups = inputValidatedInt("Enter number of groups: ", 0, 10);

    for (int i = 0; i < numGroups; ++i) {
        Group group;
        group.groupName = inputValidatedString("Enter group name: ", " ", false);

        int numSubjects;
        numSubjects = inputValidatedInt("Enter number of subjects: ", 0);

        for (int j = 0; j < numSubjects; ++j) {
            group.subjects.push_back(inputValidatedString("Enter subject name: ", " ", false));
        }

        int numStudents;
        numStudents = inputValidatedInt("Enter number of students: ", 0);

        for (int s = 0; s < numStudents; ++s) {
            Student student;
            student.surName = inputValidatedString("Enter surname name: ", " -", false);
            student.firstName = inputValidatedString("Enter first name: ", " -", false);
            student.lastName = inputValidatedString("Enter last name: ", " -", true);


            for (int subjIdx = 0; subjIdx < numSubjects; ++subjIdx) {
                int grade;
                grade = inputValidatedInt("Enter grade for " + group.subjects[subjIdx] + ": ", 1, 10);
                student.grades.push_back(grade);
            }
            group.students.push_back(student);
        }
        university.groups.push_back(group);
    }
}

// Сохранение данных в файл
void saveToFile(const University& university, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error opening file!";
        return;
    }

    fout << university.groups.size() << endl;
    for (const auto& group : university.groups) {
        fout << group.groupName << endl;
        fout << group.subjects.size() << endl;
        for (const auto& subj : group.subjects) fout << subj << endl;
        fout << group.students.size() << endl;
        for (const auto& stud : group.students) {
            fout << stud.surName << endl;
            fout << stud.firstName << endl;
            fout << stud.lastName << endl;
            for (const auto& grade : stud.grades) fout << grade << endl;
        }
    }
}

// Загрузка данных из файла
void loadFromFile(University& university, const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file!" << endl;
        return;
    }

    university.groups.clear();
    int groupCount;
    fin >> groupCount;
    fin.ignore(INT32_MAX, '\n');

    for (int i = 0; i < groupCount; ++i) {
        Group group;
        getline(fin, group.groupName);

        int subjCount;
        fin >> subjCount;
        fin.ignore(INT32_MAX, '\n');

        group.subjects.resize(subjCount);
        for (int j = 0; j < subjCount; ++j) {
            getline(fin, group.subjects[j]);
        }

        int studCount;
        fin >> studCount;
        fin.ignore(INT32_MAX, '\n');

        for (int s = 0; s < studCount; ++s) {
            Student stud;
            getline(fin, stud.surName);
            getline(fin, stud.firstName);
            getline(fin, stud.lastName);

            stud.grades.clear();
            int grade;
            for (int g = 0; g < subjCount; ++g) {
                fin >> grade;
                stud.grades.push_back(grade);
            }
            fin.ignore(INT32_MAX, '\n');
            group.students.push_back(stud);
        }
        university.groups.push_back(group);
    }
}


// Добавляем в меню новый пункт
void showMenu() {
    cout << "\n1. Add group\n"
        << "2. Show data\n"
        << "3. Save to file\n"
        << "4. Load from file\n"
        << "5. Calculate success rate\n"  // Новый пункт
        << "6. Exit\n"
        << "Choice: ";
}

// Функция проверки, сдал ли студент (>= 4)
bool isStudentPassed(const Student& student) {
    for (int grade : student.grades) {
        if (grade < 4) return false;
    }
    return true;
}

// Расчет статистики успешности студентов
void calculateSuccessRate(const University& university) {
    if (university.groups.empty()) {
        cout << "No data available!" << endl;
        return;
    }

    int totalStudents = 0;
    int passedStudents = 0;
    int highAchievers = 0;
    vector<string> passedNames;
    vector<string> failedNames;
    vector<string> highAchieverNames;
    string fio;

    for (const Group& group : university.groups) {
        for (const Student& student : group.students) {
            totalStudents++;
            bool passed = isStudentPassed(student);
            fio = student.surName + " " + student.firstName + " " + student.lastName;
            if (passed) {
                passedStudents++;
                passedNames.push_back(fio);

                int countHighGrades = 0;
                for (int grade : student.grades) {
                    if (grade == 4 || grade == 5) countHighGrades++;
                }
                if (countHighGrades == student.grades.size()) {
                    highAchievers++;
                    highAchieverNames.push_back(fio);
                }
            }
            else {
                failedNames.push_back(fio);
            }
        }
    }

    if (totalStudents == 0) {
        cout << "No students found!" << endl;
        return;
    }

    double successRate = (static_cast<double>(passedStudents) / totalStudents) * 100;
    double highAchieversRate = (static_cast<double>(highAchievers) / passedStudents) * 100;

    cout << "\nSuccess rate: " << successRate << "% (" << passedStudents << "/" << totalStudents << ")\n";
    cout << "High achievers (students with only 4s and 5s): " << highAchieversRate << "% (" << highAchievers << "/" << passedStudents << ")\n";

    cout << "\nPassed students (" << passedNames.size() << "):\n";
    for (const string& name : passedNames) {
        cout << "- " << name << endl;
    }

    cout << "\nFailed students (" << failedNames.size() << "):\n";
    for (const string& name : failedNames) {
        cout << "- " << name << endl;
    }
}


// В main обновляем обработку выбора
int main() {
    University university;
    while (true) {
        showMenu();
        int choice = inputValidatedInt("", 1, 6); 

        switch (choice) {
        case 1: inputUniversity(university); break;
        case 2: printUniversity(university); break;
        case 3: saveToFile(university, "task5_1.txt"); break;
        case 4: loadFromFile(university, "task5_1.txt"); break;
        case 5: calculateSuccessRate(university); break;  
        case 6:
            system("pause");
            return 0;
        }
    }
}