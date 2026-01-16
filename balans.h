// balans.h
#ifndef BALANS_H    // Исключение повторного вкл. заголовочного файла
#define BALANS_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class AccountingEntry {
private:
    std::string accountName;
    double debit;
    double credit;

public:
    // Конструктор, инициализируемый вводом с клавиатуры
    AccountingEntry() {
        std::cout << "Введите номер счета: "; // Номер счета может содержать и буквы
        std::getline(std::cin >> std::ws, accountName);
        std::cout << "Введите сумму по дебету: ";
        // std::cin >> debit;
        while (!(std::cin >> debit) || (std::cin.peek() != '\n')) {
            // Обработка ошибки: очистка потока и вывод сообщения
            std::cin.clear(); // Сброс флага ошибки
            std::cin.ignore(10000, '\n'); // Игнорирование оставшихся символов до перевода строки
            std::cout << "Некорректный ввод. Пожалуйста, введите цифровое значение суммы по дебету: \n";
        }
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите сумму по кредиту: ";
        while (!(std::cin >> credit) || (std::cin.peek() != '\n')) {
            // Обработка ошибки: очистка потока и вывод сообщения
            std::cout << "Некорректный ввод. Пожалуйста, введите цифровое значение суммы по кредиту: \n";
            std::cin.clear(); // Сброс флага ошибки
            std::cin.ignore(10000, '\n'); // Игнорирование оставшихся символов до перевода строки
        }
    }
    // Метод для вывода данных
    void display() const {
        std::cout << std::left << std::setw(20) << accountName
            << " | Д: " << std::setw(10) << debit
            << " | К: " << std::setw(10) << credit << std::endl;
    }

    double getDebit() const { return debit; }
    double getCredit() const { return credit; }
};

void balans();

#endif BALANS_H