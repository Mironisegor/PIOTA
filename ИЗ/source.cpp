/**
* @file Source.cpp
* @brief Файл реализации
*/

#include "Header.h"

using namespace std;

Transition Turing; ///< Глобальная переменная для хранения состояния машины Тьюринга

/**
 * @brief Функция для смены цвета в консоли для отображения головки МТ.
 * @param color Цвет текста в консоли.
 */
static void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

/**
* @brief Функция инициализации системы команд машины Тьюринга
* @return 1 - если файл успешно открыт\n 0 - в противном случае
* @details Функция считывает таблицу команд машины Тьюринга из файла "TXT_FOR_PIOTA" и сохраняет её в структуру данных "Turing.commands"
*/
int init() {
    ifstream inputFile("TXT_FOR_PIOTA.txt");
    vector <char> vec = { 'a', 'b', 'c', 'd', 'e', 'f', '#' , '*', '1', '!', '@' };
    if (!inputFile) {
        return 0;
    }
    else {
        // Здесь можно добавить логику для чтения файла и инициализации Turing
        for (int i = 1; i < 31; i++) {
            for (int j = 0; j < 11; j++) {
                char s1, s2;
                string s3;
                inputFile >> s1;
                if (s1 == 'n') {
                    continue;
                }
                inputFile >> s2 >> s3;
                auto para = make_pair("q" + to_string(i), vec[j]);
                Turing.commands[para] = { s1, s2, s3 };
            }
        }
        return 1;
    }
}

/**
 * @brief Функция для вывода ленты и текущего состояния МТ.
 */
static void print() {
    for (size_t i = 0; i < Turing.indexForNowSym; i++) {
        cout << Turing.lenta[i];
    }
    setColor(4);
    cout << Turing.lenta[Turing.indexForNowSym];
    setColor(7);
    for (size_t i = Turing.indexForNowSym + 1; i < Turing.lenta.length(); i++) {
        cout << Turing.lenta[i];
    }
    cout << ' ' << Turing.nowCondition << endl;
}

/**
 * @brief Статическая функция, которая ищет команду по текущему символу и состоянию.
 * @return tuple с командой или "NO_COMMAND", если команда не найдена.
 */
static auto findCommand() {
    pair <string, char> key = make_pair(Turing.nowCondition, Turing.lenta[Turing.indexForNowSym]);
    auto it = Turing.commands.find(key);
    if (it != Turing.commands.end()) {
        return it->second;
    }
    else {
        tuple<char, char, string> NO_COMMAND = { ' ', ' ', "NO_COMMAND" };
        return NO_COMMAND;
    }
}

/**
 * @brief Статическая функция для добавления пробелов слева и справа.
 */
static void addEmptySymbols() {
    if (Turing.lenta[0] != '@') {
        Turing.lenta = '@' + Turing.lenta;
    }
    if (Turing.lenta.back() != '@') {
        Turing.lenta += '@';
    }
    if (Turing.lenta == "@") {
        Turing.lenta = '@' + Turing.lenta;
        Turing.lenta += '@';
    }
}

/**
 * @brief Функция для перемещения головки МТ.
 * @param direction Направление перемещения ('>' или '<').
 */
static void movePtr(char direction) {
    if (direction == '>') {
        Turing.indexForNowSym++;
    }
    else if (direction == '<') {
        Turing.indexForNowSym--;
    }
}

/**
 * @brief Функция, реализующая один шаг работы МТ.
 * @return true, если команда не найдена, иначе false.
 */
static bool turingStep() {
    auto it = findCommand();
    if (get<2>(it) == "NO_COMMAND") {
        return true;
    }
    char firstElemInTuple = get<0>(it);
    char secondElemInTuple = get<1>(it);
    string thirdElemInTuple = get<2>(it);
    Turing.lenta[Turing.indexForNowSym] = firstElemInTuple;
    Turing.nowCondition = thirdElemInTuple;
    movePtr(secondElemInTuple);
    if (Turing.endConditions.count(Turing.nowCondition)) {
        Turing.isWorking = false;
    }
    return false;
}

/**
 * @brief Функция, реализующая работу машины Тьюринга
 * @param chain Входная цепочка символов
 * @return 0 - если работа завершена успешно\n 1 - если команда не найдена\n 2 - если превышено максимальное количество шагов
 * @details Функция выполняет шаги машины Тьюринга, используя таблицу команд, и возвращает результат работы
 */
int turing(string chain) {
    int count = 0;
    bool flagForNoCommand = false;
    Turing.isWorking = true;
    Turing.indexForNowSym = 1;
    Turing.nowCondition = "q1";
    Turing.lenta = chain;

    while (Turing.isWorking and count < 10001 and !flagForNoCommand) {
        addEmptySymbols();
        print();
        flagForNoCommand = turingStep();
        count++;
    }
    if (flagForNoCommand) {
        return 1;
    }
    else if (count > 10001) {
        return 2;
    }
    else {
        cout << "Ответ: ";
        print();
        cout << "Работа машины Тьюринга завершилась корректно" << endl;
        return 0;
    }
}

/**
 * @brief Функция для проверки правильности входной цепочки
 * @param chain Входная цепочка символов
 * @return true - если цепочка корректна\n false - в противном случае
 * @details Функция проверяет, состоит ли входная цепочка только из символов, допустимых в алфавите машины Тьюринга
 */
bool checkInputString(string chain) {
    for (auto sym : chain) {
        if (!Turing.Alphabet_input.count(sym)) {
            return 0;
        }
    }
    return 1;
}
