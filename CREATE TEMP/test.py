import os
import random

# Путь к директории с данными студентов
base_path = "C:\\Users\\timof\\Documents\\Visual Studio Code\\BasicsOfAlgorithmisationAndProgramming\\term2\\lab2\\student_data\\11A"

# Список студентов
students = [
    "Ivanov_John_Smith",
    "Petrov_Andrey_Petrovich",
    "Sidorov_Paul_Ivanovich",
    "Orlov_Alexander_Mikhailovich",
    "Fedorov_Maxim_Vladimirovich",
    "Mikhailov_Dmitry_Viktorovich",
    "Aleksandrov_Sergei_Aleksandrovich",
    "Belov_Vladislav_Sergeevich",
    "Makarov_Artem_Valerievich",
    "Kuznetsov_Egor_Petrovich",
]

# Список предметов
subjects = ["Math", "History", "Literature"]


# Функция для создания случайных отметок
def generate_grades():
    return [random.randint(2, 10) for _ in range(random.randint(5, 9))]


# Функция для записи отметок в файл
def write_grades(student_name, subject, grades):
    student_dir = os.path.join(base_path, "students", student_name, "subjects")
    os.makedirs(student_dir, exist_ok=True)
    file_path = os.path.join(student_dir, f"{subject}.txt")

    with open(file_path, "w") as file:
        file.write(" ".join(map(str, grades)))


# Генерация и запись случайных отметок для всех студентов
for student in students:
    for subject in subjects:
        grades = generate_grades()
        write_grades(student, subject, grades)
        print(f"Записаны оценки для {student} по предмету {subject}: {grades}")
