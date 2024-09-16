#include <bits/stdc++.h>
using namespace std;
// chcp 65001 For Windows
// export LANG=en_US.UTF-8 For Linux


int task5(){
    int num;
    bitset<4> bt;
    cin >> num;
    string str = to_string(num);

    for (int i = 0; i < 4; i++){
        if (bt[str[i] - '0']){
            cout << "Цифры не различны" << endl;
            return 0;
        }
        else{
            bt[str[i] - '0'] = 1;
        }
    }
    cout << "Цифры различны" << endl;
}


void task6(){
    int choice;

    cout << "Выберите тему для разговора:\n";
    cout << "1. Погода\n";
    cout << "2. Спорт\n";
    cout << "3. Музыка\n";
    cout << "4. Выход\n";
    cout << "Введите номер вашего выбора: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Сегодня отличная погода! Солнечно и тепло.\n";
        break;
    case 2:
        cout << "Вы любите спорт? Какой ваш любимый вид спорта?\n";
        break;
    case 3:
        cout << "Музыка - это прекрасно! Какую музыку вы предпочитаете?\n";
        break;
    case 4:
        cout << "До свидания!\n";
        break;
    default:
        cout << "Неверный выбор. Попробуйте снова.\n";
        break;
    }
}


void task7(){
    int num1, num2, num3, result = 0;
    cin >> num1 >> num2 >> num3;
    result;
    result += (num1 % 5 == 0) ? num1 : 0;
    result += (num2 % 5 == 0) ? num2 : 0;
    result += (num3 % 5 == 0) ? num3 : 0;
    if (result)
        cout << result << endl;
    else
        cout << "error" << endl;
}


void task7_1(){
    double r,p,q;
    cout<<"Введите r: "<<endl;
    cout<<"Введите p: "<<endl;
    cout<<"Введите q: "<<endl;
    if (r<=p*q/(sqrt(pow(p,2)+pow(q,2)))){
        cout<<"Шарик пройдет в ромбированное отверстие"<<endl;
    }
    else{
        cout<<"Шарик не пройдет в ромбированное отверстие"<<endl;
    }
}


int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    task5();
    task6();
    task7();
    return 0;
}
