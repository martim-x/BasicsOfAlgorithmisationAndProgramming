#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

struct Student {
    string name;
    vector<vector<int>> grades;
};

struct SchoolClass {
    string className;
    vector<string> subjects;
    vector<Student> students;
};

struct School {
    vector<SchoolClass> classes;
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


void inputSchool(School& school) {
    int numClasses = inputValidatedInt("Enter number of classes: ", 1);

    for (int i = 0; i < numClasses; ++i) {
        SchoolClass cls;
        cls.className = inputValidatedString("Enter class name (e.g. 10-A): ");

        int numSubjects = inputValidatedInt("Enter number of subjects: ", 1);
        for (int j = 0; j < numSubjects; ++j) {
            cls.subjects.push_back(
                inputValidatedString("Enter subject #" + to_string(j + 1) + ": ")
            );
        }

        int numStudents = inputValidatedInt("Enter number of students: ", 1);
        for (int s = 0; s < numStudents; ++s) {
            Student student;
            student.name = inputValidatedString("Enter student name: ");

            student.grades.resize(numSubjects);
            for (int subjIdx = 0; subjIdx < numSubjects; ++subjIdx) {
                int numGrades = inputValidatedInt(
                    "How many grades for " + cls.subjects[subjIdx] + "? ", 1
                );

                for (int g = 0; g < numGrades; ++g) {
                    student.grades[subjIdx].push_back(
                        inputValidatedInt("Enter grade #" + to_string(g + 1) + ": ", 1, 12)
                    );
                }
            }
            cls.students.push_back(student);
        }
        school.classes.push_back(cls);
    }
}


void printSchool(const School& school) {
    for (const auto& cls : school.classes) {
        cout << "\nClass: " << cls.className << endl;
        cout << "Subjects: ";
        for (const auto& subj : cls.subjects) {
            cout << subj << ", ";
        }

        cout << "\nStudents:\n";
        for (const auto& stud : cls.students) {
            cout << "- " << stud.name << "\nGrades:\n";
            for (size_t i = 0; i < stud.grades.size(); ++i) {
                cout << "  " << cls.subjects[i] << ": ";
                for (int grade : stud.grades[i]) {
                    cout << grade << " ";
                }
                cout << endl;
            }
        }
    }
}


void editGrades(School& school) {
    if (school.classes.empty()) {
        cout << "No classes available!" << endl;
        return;
    }

    // Выбор класса
    cout << "\nAvailable classes:\n";
    for (int i = 0; i < school.classes.size(); ++i) {
        cout << i + 1 << ". " << school.classes[i].className << endl;
    }
    int classIdx = inputValidatedInt("Select class: ", 1, school.classes.size()) - 1;

    // Выбор студента
    auto& students = school.classes[classIdx].students;
    cout << "\nStudents in class:\n";
    for (int i = 0; i < students.size(); ++i) {
        cout << i + 1 << ". " << students[i].name << endl;
    }
    int studentIdx = inputValidatedInt("Select student: ", 1, students.size()) - 1;

    // Выбор предмета
    auto& subjects = school.classes[classIdx].subjects;
    cout << "\nSubjects:\n";
    for (int i = 0; i < subjects.size(); ++i) {
        cout << i + 1 << ". " << subjects[i] << endl;
    }
    int subjIdx = inputValidatedInt("Select subject: ", 1, subjects.size()) - 1;

    // Редактирование оценок
    auto& grades = students[studentIdx].grades[subjIdx];
    cout << "\nCurrent grades: ";
    for (int grade : grades) cout << grade << " ";

    cout << "\n1. Add grade\n2. Remove grade\n3. Edit grade\nChoose action: ";
    int action = inputValidatedInt("", 1, 3);

    switch (action) {
    case 1:
        grades.push_back(inputValidatedInt("Enter new grade: ", 1, 10));
        break;
    case 2: {
        if (grades.empty()) {
            cout << "No grades to remove!" << endl;
            break;
        }
        int gradeIdx = inputValidatedInt("Enter grade position to remove: ", 1, grades.size()) - 1;
        grades.erase(grades.begin() + gradeIdx);
        break;
    }
    case 3: {
        if (grades.empty()) {
            cout << "No grades to edit!" << endl;
            break;
        }
        int gradeIdx = inputValidatedInt("Enter grade position to edit: ", 1, grades.size()) - 1;
        grades[gradeIdx] = inputValidatedInt("Enter new value: ", 1, 10);
        break;
    }
    }
}


void saveToFile(const School& school, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error opening file!";
        return;
    }

    fout << school.classes.size() << endl;
    for (const auto& cls : school.classes) {
        fout << cls.className << endl;

        fout << cls.subjects.size() << endl;
        for (const auto& subj : cls.subjects)
            fout << subj << endl;

        fout << cls.students.size() << endl;
        for (const auto& stud : cls.students) {
            fout << stud.name << endl;
            for (const auto& subjectGrades : stud.grades) {
                fout << subjectGrades.size() << " ";
                for (int grade : subjectGrades) fout << grade << " ";
                fout << endl;
            }
        }
    }
}


void loadFromFile(School& school, const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file!" << endl;
        return;
    }

    school.classes.clear();
    int classCount;
    fin >> classCount;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');  // Пропустить всё до новой строки

    for (int i = 0; i < classCount; ++i) {
        SchoolClass cls;
        getline(fin, cls.className);  // Считываем имя класса

        int subjCount;
        fin >> subjCount;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');  // Пропустить всё до новой строки

        cls.subjects.resize(subjCount);
        for (int j = 0; j < subjCount; ++j) {
            getline(fin, cls.subjects[j]);  // Считываем предметы
        }

        int studCount;
        fin >> studCount;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');  // Пропустить всё до новой строки

        for (int s = 0; s < studCount; ++s) {
            Student stud;
            getline(fin, stud.name);  // Считываем имя студента

            stud.grades.resize(subjCount);  // Инициализируем вектор оценок

            for (int g = 0; g < subjCount; ++g) {
                int gradeCount;
                fin >> gradeCount;  // Количество оценок

                stud.grades[g].resize(gradeCount);
                for (int k = 0; k < gradeCount; ++k) {
                    fin >> stud.grades[g][k];  // Считываем оценки
                }
                // Пропустить оставшиеся символы до конца строки
                fin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cls.students.push_back(stud);  // Добавляем студента
        }

        school.classes.push_back(cls);  // Добавляем класс в школу
    }
}


void showMenu() {
    cout << "\n1. Add class\n"
        << "2. Show data\n"
        << "3. Save to file\n"
        << "4. Load from file\n"
        << "5. Edit grades\n"
        << "6. Exit\n"
        << "Choice: ";
}


int main() {
    School school;
    while (true) {
        showMenu();
        int choice = inputValidatedInt("", 1, 6);

        switch (choice) {
        case 1: inputSchool(school); break;
        case 2: printSchool(school); break;
        case 3: saveToFile(school, "school.txt"); break;
        case 4: loadFromFile(school, "school.txt"); break;
        case 5: editGrades(school); break;
        case 6: return 0;
        }
    }
}
