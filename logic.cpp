// logic.cpp
#include <iostream>
#include <iomanip>
#include "calculator.h"

void logic() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало логических операций");

    int num1, num2, result;
    char op;

    std::cout << "Введите первое число: ";
    while (!(std::cin >> num1)) {
        std::cout << "Ошибка: Некорректный ввод. Пожалуйста, введите число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        logger->warn("Некорректный ввод первого числа в логических операциях");
    }

    std::cout << "Введите оператор (& - И, | - ИЛИ, ~ - НЕ, ^ - XOR): ";
    std::cin >> op;

    while ((op != '&') && (op != '|') && (op != '^') && (op != '~')) {
        std::cout << "Ошибка: неправильный оператор. Попробуйте еще раз: ";
        std::cin >> op;
        logger->warn("Некорректный ввод логического оператора");
    }

    std::string operationName, inputStr;
    
    if (op != '~') {
        std::cout << "Введите второе число: ";
        while (!(std::cin >> num2)) {
            std::cout << "Ошибка: Некорректный ввод. Пожалуйста, введите число: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            logger->warn("Некорректный ввод второго числа в логических операциях");
        }
    }

    switch (op) {
        case '&':
            result = num1 & num2;
            std::cout << "Результат: " << result << std::endl;
            operationName = "Побитовое И (AND)";
            inputStr = std::to_string(num1) + " & " + std::to_string(num2);
            logger->info("Логическая операция И: {} & {} = {}", num1, num2, result);
            break;
        case '|':
            result = num1 | num2;
            std::cout << "Результат: " << result << std::endl;
            operationName = "Побитовое ИЛИ (OR)";
            inputStr = std::to_string(num1) + " | " + std::to_string(num2);
            logger->info("Логическая операция ИЛИ: {} | {} = {}", num1, num2, result);
            break;
        case '^':
            result = num1 ^ num2;
            std::cout << "Результат: " << result << std::endl;
            operationName = "Побитовое XOR";
            inputStr = std::to_string(num1) + " ^ " + std::to_string(num2);
            logger->info("Логическая операция XOR: {} ^ {} = {}", num1, num2, result);
            break;
        case '~':
            result = ~num1;
            std::cout << "Результат: " << result << std::endl;
            operationName = "Побитовое НЕ (NOT)";
            inputStr = "~" + std::to_string(num1);
            logger->info("Логическая операция НЕ: ~{} = {}", num1, result);
            break;
    }
    
    historyManager->addCommand("Логические операции", operationName, 
                              inputStr, std::to_string(result));
    
    logger->debug("Логические операции завершены");
}