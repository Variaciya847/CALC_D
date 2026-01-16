// calculator - обязательно включение С++ 20
#define _CRT_SECURE_NO_WARNINGS
#include "calculator.h"
#include "conversion.h"
#include "data.h"
#include "string.h"
#include "balans.h"

#include <iostream>
#include <cstdlib>
#include <filesystem>

int main() {
    int choice = 1;
    UnitConverter converter;
    
    // Инициализация логгера
    std::filesystem::create_directory("logs");
    Logger::init();
    
    auto logger = Logger::get();
    logger->info("========== КАЛЬКУЛЯТОР ЗАПУЩЕН ==========");
    
    do {
        // Вывод меню
        std::cout << "\n========== ГЛАВНОЕ МЕНЮ ==========" << std::endl;
        std::cout << "1.  Арифметические операции" << std::endl;
        std::cout << "2.  Тригонометрические функции" << std::endl;
        std::cout << "3.  Логарифмы" << std::endl;
        std::cout << "4.  Логические функции" << std::endl;
        std::cout << "5.  Бухгалтерский баланс" << std::endl;
        std::cout << "6.  Конвертация единиц" << std::endl;
        std::cout << "7.  Дата/время" << std::endl;
        std::cout << "8.  Строковые функции" << std::endl;
        std::cout << "9.  Прочие функции" << std::endl;
        std::cout << "10. История операций" << std::endl;
        std::cout << "11. Отменить операцию (Undo)" << std::endl;
        std::cout << "12. Повторить операцию (Redo)" << std::endl;
        std::cout << "13. Выход из программы" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "Выберите операцию (1-13): ";

        while (!(std::cin >> choice) || choice < 1 || choice > 13 || (std::cin.peek() != '\n')) {
            std::cout << "Ошибка: Введите целое число от 1 до 13. Попробуйте еще раз: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            logger->warn("Некорректный ввод в главном меню");
        }

        // Обработка выбора 
        switch (choice) {
        case 1:
            logger->info("Выбраны арифметические операции");
            arithmetic();
            break;
        case 2:
            logger->info("Выбраны тригонометрические функции");
            trigonometric();
            break;
        case 3:
            logger->info("Выбраны логарифмы");
            logarithms();
            break;
        case 4:
            logger->info("Выбраны логические функции");
            logic();
            break;
        case 5:
            logger->info("Выбран бухгалтерский баланс");
            balans();
            break;
        case 6:
            logger->info("Выбрана конвертация единиц");
            conversion(converter);
            break;
        case 7:
            logger->info("Выбрана работа с датой/временем");
            data();
            break;
        case 8:
            logger->info("Выбраны строковые функции");
            string();
            break;
        case 9:
            logger->info("Выбраны прочие функции");
            other();
            break;
        case 10:
            showHistory();
            break;
        case 11:
            undoOperation();
            break;
        case 12:
            redoOperation();
            break;
        case 13:
            logger->info("========== ВЫХОД ИЗ ПРОГРАММЫ ==========");
            std::cout << "Выход из программы" << std::endl;
            break;
        }
        
    } while (choice != 13);

    return 0;
}