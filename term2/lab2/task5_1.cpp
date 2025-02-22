#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

struct Student {
    string name;
    vector<int> grades;  // Массив оценок для студента
};

struct Group {
    string groupName;    // Название группы
    vector<string> subjects;   // Перечень предметов
    vector<Student> students;   // Список студентов в группе
};

struct University {
    vector<Group> groups;   // Перечень групп в университете
};

// Функция для валидации ввода числа в диапазоне
int inputValidatedInt(const string& prompt, int min = 0, int max = numeric_limits<int>::max()) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);

        // Проверка, что введённое значение является числом и в пределах диапазона
        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        }
        cout << "Invalid input! Please try again." << endl;
    }
}

// Функция для валидации ввода строки (проверка на пустоту)
string inputValidatedString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Input cannot be empty! Please try again." << endl;
    }
}

void inputUniversity(University& university) {
    int numGroups = inputValidatedInt("Enter number of groups: ", 1);

    for (int i = 0; i < numGroups; ++i) {
        Group group;
        group.groupName = inputValidatedString("Enter group name: ");

        int numSubjects = inputValidatedInt("Enter number of exam subjects: ", 1);
        for (int j = 0; j < numSubjects; ++j) {
            group.subjects.push_back(
                inputValidatedString("Enter exam subject #" + to_string(j + 1) + ": ")
            );
        }

        int numStudents = inputValidatedInt("Enter number of students: ", 1);
        for (int s = 0; s < numStudents; ++s) {
            Student student;
            student.name = inputValidatedString("Enter student name: ");

            for (int subjIdx = 0; subjIdx < numSubjects; ++subjIdx) {
                student.grades.push_back(
                    inputValidatedInt("Enter grade for " + group.subjects[subjIdx] + ": ", 1, 12)
                );
            }
            group.students.push_back(student);
        }
        university.groups.push_back(group);
    }
}

void printUniversity(const University& university) {
    for (const auto& group : university.groups) {
        cout << "\nGroup: " << group.groupName << endl;
        cout << "Subjects: ";
        for (const auto& subj : group.subjects) {
            cout << subj << ", ";
        }

        cout << "\nStudents:\n";
        for (const auto& stud : group.students) {
            cout << "- " << stud.name << "\nGrades:\n";
            for (size_t i = 0; i < stud.grades.size(); ++i) {
                cout << "  " << group.subjects[i] << ": ";
                cout << stud.grades[i] << endl;
            }
        }
    }
}

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
        for (const auto& subj : group.subjects)
            fout << subj << endl;

        fout << group.students.size() << endl;
        for (const auto& stud : group.students) {
            fout << stud.name << endl;
            for (const auto& grade : stud.grades) {
                fout << grade << " ";
            }
            fout << endl;
        }
    }
}

void loadFromFile(University& university, const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file!" << endl;
        return;
    }

    university.groups.clear();
    int groupCount;
    fin >> groupCount;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < groupCount; ++i) {
        Group group;
        getline(fin, group.groupName);

        int subjCount;
        fin >> subjCount;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');

        group.subjects.resize(subjCount);
        for (int j = 0; j < subjCount; ++j) {
            getline(fin, group.subjects[j]);
        }

        int studCount;
        fin >> studCount;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int s = 0; s < studCount; ++s) {
            Student stud;
            getline(fin, stud.name);

            // Исправлено: считываем ровно subjCount оценок
            stud.grades.clear(); // Очищаем вектор
            for (int g = 0; g < subjCount; ++g) {
                int grade;
                fin >> grade;
                stud.grades.push_back(grade);
            }
            fin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропустить остаток строки

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

// Функция проверки успеваемости студента
bool isStudentPassed(const Student& student) {
    for (int grade : student.grades) {
        if (grade < 4) {
            return false;
        }
    }
    return true;
}

// Основная функция расчета успеваемости
void calculateSuccessRate(const University& university) {
    if (university.groups.empty()) {
        cout << "No data available!" << endl;
        return;
    }

    int totalStudents = 0;
    int passedStudents = 0;
    vector<string> passedNames;
    vector<string> failedNames;

    // Обрабатываем все группы
    for (const Group& group : university.groups) {
        for (const Student& student : group.students) {
            totalStudents++;
            if (isStudentPassed(student)) {
                passedStudents++;
                passedNames.push_back(student.name);
            }
            else {
                failedNames.push_back(student.name);
            }
        }
    }

    if (totalStudents == 0) {
        cout << "No students found!" << endl;
        return;
    }

    // Расчет процента
    double successRate = (static_cast<double>(passedStudents) / totalStudents) * 100;
    cout << "\nSuccess rate: " << successRate << "% ("
        << passedStudents << "/" << totalStudents << ")\n";

    // Вывод списков
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
        int choice = inputValidatedInt("", 1, 6);  // Теперь до 6

        switch (choice) {
        case 1: inputUniversity(university); break;
        case 2: printUniversity(university); break;
        case 3: saveToFile(university, "university.txt"); break;
        case 4: loadFromFile(university, "university.txt"); break;
        case 5: calculateSuccessRate(university); break;  // Новый кейс
        case 6:
            system("pause");
            return 0;
        }
    }
}