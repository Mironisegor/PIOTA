/**
* ЮФУ, ИКТИБ, МОП ЭВМ
* ПИОТА2
* ИЗ, Вариант 25.1
* КТбо2-6, Миронов Егор Сергеевич
* 15.10.2024
*/

#include "Header.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    int flag = 0; ///< Флаг для проверки инициализации таблицы переходов, корректности цепочки, корректной отработки МТ
    bool flagForMainWhile = true; ///< Фдаг для работы цикла while
    string chain; ///< Цепочка, введенная пользователем

    flag = init();
    if (!flag) {
        cout << "Файл не удалось открыть. Проверьте название и расширение" << endl;
        flagForMainWhile = 0;
    }
    else {
        cout << "Файл был успешно открыт" << endl;
    }

    while (flagForMainWhile) {
        cout << "Введите цепочку, состоящую из букв a, b, c: ";
        cin >> chain;
        flag = checkInputString(chain);
        if (flag) {
            cout << "Цепочка была введена корректно" << endl;
            flag = turing(chain);
            if (flag == 1) {
                cout << "Ошибка во время работы машины Тьюринга" << endl;
                cout << "Отсутствует команда для текущей конфигурации" << endl;
            }
            else if (flag == 2) {
                cout << "Превышено максимальное количество шагов(10000)" << endl;
            }
        }
        else {
            cout << "Цепочка некорректна!" << endl;
            cout << "Убедитесь, что цепочка состоит только из букв a, b, c" << endl;
        }
        cout << "Хотите ввести данные еще раз? 1/0: ";
        cin >> flagForMainWhile;
    }
    return 0;
}
