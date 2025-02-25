#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdio>    // Для sprintf
#include <cstdlib>

using namespace std;

//===============================
// Валидаторы ввода
//===============================

// Валидация целого числа
int inputValidatedInt(const string& prompt, int min = 0, int max = numeric_limits<int>::max()) {
    int value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max)
            return value;
        cout << "Invalid input! Please try again." << endl;
    }
}

// Валидация вещественного числа
double inputValidatedDouble(const string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max)
            return value;
        cout << "Invalid input! Please try again." << endl;
    }
}

// Проверка строки на допустимые символы (разрешены буквы, пробел и дефис)
bool isValidString(const string& str, const string& allowedChars, bool canBeEmpty) {
    if (canBeEmpty && str.empty())
        return true;
    if (str.empty())
        return false;
    // Допускаем буквы (isalpha) и символы из allowedChars
    for (char c : str) {
        if (!isalpha(c) && allowedChars.find(c) == string::npos)
            return false;
    }
    return true;
}

// Валидация ввода строки с проверкой на пустоту и допустимые символы
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
        cout << "Invalid input! Allowed characters: letters and these symbols: " << allowedChars << endl;
    }
}

//===============================
// Структура данных
//===============================

// Объединение для хранения даты поступления.
// Реализовано двумя способами:
// - как структура с полями day, month, year
// - как символьный массив dateStr для хранения даты в формате "DD/MM/YYYY"
union AdmissionDate {
    struct {
        int day;
        int month;
        int year;
    } parts;
    char dateStr[11];  // Формат: "DD/MM/YYYY" (10 символов + завершающий ноль)
};

struct StudentRecord {
    string fullName;         // Ф.И.О.
    AdmissionDate admitDate; // Дата поступления
    string specialization;   // Специальность
    string group;            // Группа
    string faculty;          // Факультет
    double averageGrade;     // Средний балл
};

//===============================
// Функции работы с данными
//===============================

// Ввод данных о студенте
StudentRecord inputStudent() {
    StudentRecord s;
    // Разрешаем буквы, пробел и дефис (allowedChars: " -")
    s.fullName = inputValidatedString("Enter student's full name (letters, space, hyphen): ", " -", false);

    // Ввод даты поступления (вводим отдельно день, месяц, год, затем форматируем)
    int day = inputValidatedInt("Enter admission day (1-31): ", 1, 31);
    int month = inputValidatedInt("Enter admission month (1-12): ", 1, 12);
    int year = inputValidatedInt("Enter admission year (e.g. 2000-2100): ", 1900, 2100);
    // Форматирование даты в строку
    sprintf(s.admitDate.dateStr, "%02d/%02d/%04d", day, month, year);

    s.specialization = inputValidatedString("Enter specialization: ", " -", false);
    s.group = inputValidatedString("Enter group: ", " -", false);
    s.faculty = inputValidatedString("Enter faculty: ", " -", false);
    s.averageGrade = inputValidatedDouble("Enter average grade (0.0 - 10.0): ", 0.0, 10.0);
    return s;
}

// Вывод информации о студенте
void printStudent(const StudentRecord& s) {
    cout << "Full Name      : " << s.fullName << "\n"
        << "Admission Date : " << s.admitDate.dateStr << "\n"
        << "Specialization : " << s.specialization << "\n"
        << "Group          : " << s.group << "\n"
        << "Faculty        : " << s.faculty << "\n"
        << "Average Grade  : " << s.averageGrade << "\n";
}

// Вывод всех записей
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

// Запись данных в файл
void saveToFile(const vector<StudentRecord>& students, const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    // Сначала записываем количество записей
    fout << students.size() << "\n";
    for (const auto& s : students) {
        fout << s.fullName << "\n";
        fout << s.admitDate.dateStr << "\n";
        fout << s.specialization << "\n";
        fout << s.group << "\n";
        fout << s.faculty << "\n";
        fout << s.averageGrade << "\n";
    }
    fout.close();
    cout << "Data saved to " << filename << endl;
}

// Чтение данных из файла
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
        getline(fin, s.fullName);
        // Чтение даты поступления в массив символов
        fin.getline(s.admitDate.dateStr, sizeof(s.admitDate.dateStr));
        getline(fin, s.specialization);
        getline(fin, s.group);
        getline(fin, s.faculty);
        fin >> s.averageGrade;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        students.push_back(s);
    }
    fin.close();
    cout << "Data loaded from " << filename << endl;
}

// Поиск студентов по среднему баллу (выводятся все записи, у которых средний балл >= введённого порога)
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

//===============================
// Меню программы
//===============================
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
