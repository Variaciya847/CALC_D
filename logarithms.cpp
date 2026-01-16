// logarithms.cpp
#include "calculator.h"
#include <iostream>
#include <cmath>
#include <limits>

void logarithms() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало вычисления логарифмов");

    int choice;
    double number, base;

    std::cout << "Выберите тип логарифма:" << std::endl;
    std::cout << "1. Натуральный (ln)" << std::endl;
    std::cout << "2. Десятичный (log10)" << std::endl;
    std::cout << "3. По произвольному основанию (log_b(a))" << std::endl;
    
    while (!(std::cin >> choice) || choice < 1 || choice > 3 || std::cin.peek() != '\n') {
        std::cout << "Ошибка: Введите целое число от 1 до 3. Попробуйте еще раз: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        logger->warn("Некорректный выбор типа логарифма");
    }
   
    std::string operationType, resultStr;
    double result = 0.0;
    bool error = false;
    
    if (choice == 1) {
        std::cout << "Введите число: ";
        std::cin >> number;
        
        if (number <= 0) {
            std::cout << "Ошибка: число должно быть положительным." << std::endl;
            logger->error("Ошибка вычисления ln: число {} не положительное", number);
            resultStr = "ОШИБКА: число должно быть положительным";
            error = true;
        } else {
            result = std::log(number);
            std::cout << "ln(" << number << ") = " << result << std::endl;
            operationType = "Натуральный логарифм";
            resultStr = std::to_string(result);
            logger->info("ln({}) = {}", number, result);
        }
    }
    else if (choice == 2) {
        std::cout << "Введите число: ";
        std::cin >> number;
        
        if (number <= 0) {
            std::cout << "Ошибка: число должно быть положительным." << std::endl;
            logger->error("Ошибка вычисления log10: число {} не положительное", number);
            resultStr = "ОШИБКА: число должно быть положительным";
            error = true;
        } else {
            result = std::log10(number);
            std::cout << "log10(" << number << ") = " << result << std::endl;
            operationType = "Десятичный логарифм";
            resultStr = std::to_string(result);
            logger->info("log10({}) = {}", number, result);
        }
    }
    else if (choice == 3) {
        std::cout << "Введите число: ";
        std::cin >> number;
        std::cout << "Введите основание: ";
        std::cin >> base;
        
        if (number <= 0 || base <= 0 || base == 1) {
            std::cout << "Ошибка: число и основание должны быть положительными, а основание не может быть равно 1." << std::endl;
            logger->error("Ошибка вычисления log: число={}, основание={}", number, base);
            resultStr = "ОШИБКА: некорректные параметры";
            error = true;
        } else {
            result = std::log(number) / std::log(base);
            std::cout << "log_" << base << "(" << number << ") = " << result << std::endl;
            operationType = "Логарифм по основанию";
            resultStr = std::to_string(result);
            logger->info("log_{}({}) = {}", base, number, result);
        }
    }
    
    if (!error) {
        std::string inputStr;
        if (choice == 3) {
            inputStr = "число=" + std::to_string(number) + ", основание=" + std::to_string(base);
        } else {
            inputStr = "число=" + std::to_string(number);
        }
        
        historyManager->addCommand("Логарифмы", operationType, inputStr, resultStr);
    }
    
    logger->debug("Вычисление логарифмов завершено");
}