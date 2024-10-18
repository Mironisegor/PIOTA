#pragma once

/**
* @file Header.h
* @brief Заголовочный файл
*/

#include <string>
#include <iostream>
#include <map>
#include <deque>
#include <utility>
#include <fstream>
#include <set>
#include <windows.h>
#include <vector>

using namespace std;

/**
* @brief Структура, описывающая машину Тьюринга
* @details Cтруктура, которая моделирует машину Тьюринга с её текущим лентой, состоянием, положением головки, флагом для отображения заключительного состояния, системой команд, множеством входных символов, множеством заключительных состояний
*/
typedef struct Transition {
    //! Лента машины Тьюринга
    string lenta;
    //! Текущее состояние
    string nowCondition;
    //! Положение головки
    int indexForNowSym;
    //! Флаг для отображения заключительного состояния
    bool isWorking;
    //! Система команд
    map<pair<string, char>, tuple<char, char, string>> commands;
    //! Множество входных символов
    set<char> Alphabet_input = { 'a', 'b', 'c', '!'};
    //! Множество заключительных состояний
    set<string> endConditions = { "q0" };
} Transition;

/**
* @brief Функция инициализации системы команд машины Тьюринга
* @return 1 - если файл успешно открыт\n 0 - в противном случае
* @details Функция считывает таблицу команд машины Тьюринга из файла "TXT_FOR_PIOTA" и сохраняет её в структуру данных "Turing.commands"
*/
int init();
/**
 * @brief Функция, реализующая работу машины Тьюринга
 * @param chain Входная цепочка символов
 * @return 0 - если работа завершена успешно\n 1 - если команда не найдена\n 2 - если превышено максимальное количество шагов
 * @details Функция выполняет шаги машины Тьюринга, используя таблицу команд, и возвращает результат работы
 */
int turing(std::string chain);
/**
 * @brief Функция для проверки правильности входной цепочки
 * @param chain Входная цепочка символов
 * @return true - если цепочка корректна\n false - в противном случае
 * @details Функция проверяет, состоит ли входная цепочка только из символов, допустимых в алфавите машины Тьюринга
 */
bool checkInputString(std::string chain);
