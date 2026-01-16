// data.h
#ifndef DATA_H    // Исключение повторного вкл. заголовочного файла
#define DATA_H

#include <iostream>
#include <string>
#include <chrono> // Для получения времени
#include <ctime>  // Для преобразования времени
#include <iomanip> // Для форматирования (put_time)
#include <map> // Для ассоциативного контейнер из стандартной библиотеки STL:  
               // для хранения данных в виде упорядоченных пар «ключ-значение».
#include <format> // Для удобного форматирования вывода (C++20)

// Класс для представления даты

#include <iostream>
#include <iomanip> // Для форматирования вывода

// Класс для представления даты
class Date {
public:
    int day;
    int month;
    int year;

    // Конструктор для инициализации
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Конструктор по умолчанию (для удобства)
    Date() : day(1), month(1), year(2000) {}

    // Метод для ввода даты с клавиатуры
    void inputDate() {
        std::cout << "Введите день, месяц, год (например, 15 10 2024): ";
        std::cin >> day >> month >> year;
        // Простая валидация
        if (day < 1 || day > 31 || month < 1 || month > 12) {
            std::cout << "Некорректные данные. Установлена дата по умолчанию (1/1/2000).\n";
            day = 1; month = 1; year = 2000;
        }
    }
    // Метод для вывода даты
    void printDate() const {
        std::cout << std::setfill('0') << std::setw(2) << day << "."
            << std::setfill('0') << std::setw(2) << month << "."
            << year;
    }

    // Перегрузка оператора сложения (добавление дней к дате)
    Date operator+(int days) const {
        // Очень упрощенный подход, без учета високосных годов и реального числа дней в месяце
        // Для полноценного калькулятора дней требуется более сложная логика
        Date newDate = *this;
        newDate.day += days;
        // Простая коррекция месяца и года (упрощенно)
        if (newDate.day > 30) { // Предполагаем 30 дней для простоты
            newDate.day -= 30;
            newDate.month++;
            if (newDate.month > 12) {
                newDate.month = 1;
                newDate.year++;
            }
        }
        return newDate;
    }

    // Перегрузка оператора вычитания (вычитание дней)
    Date operator-(int days) const {
        Date newDate = *this;
        newDate.day -= days;
        // Простая коррекция (упрощенно)
        if (newDate.day < 1) {
            newDate.month--;
            newDate.day += 30; // Предполагаем 30 дней
            if (newDate.month < 1) {
                newDate.month = 12;
                newDate.year--;
            }
        }
        return newDate;
    }
};

void data();

#endif DATA_H