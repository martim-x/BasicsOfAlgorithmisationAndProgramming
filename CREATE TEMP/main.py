import os

# Список файлов, которые нужно создать
filenames = [
    "input1_1.txt",
    "output1_1.txt",
    "input1_2.txt",
    "output1_2.txt",
    "input8_1.txt",
    "output8_1.txt",
    "input8_2.txt",
    "output8_2.txt",
    "input11_1.txt",
    "output11_1.txt",
    "input11_2.txt",
    "output11_2.txt",
    "input14_1.txt",
    "output14_1.txt",
    "input14_2.txt",
    "output14_2.txt",
]

# Создаем папку resource, если её нет
os.makedirs("resource", exist_ok=True)

# Создаем пустые файлы
for filename in filenames:
    filepath = os.path.join("resource", filename)
    with open(filepath, "w") as file:
        pass  # Просто создаем файл без записи данных
    print(f"Создан файл: {filename}")

print("Все файлы успешно созданы!")
