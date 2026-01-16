// arithmetic.cpp
#include "calculator.h"

// Функция для арифметических действий
void arithmetic() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало арифметической операции");
    
    double num1, num2;
    char operation;
    std::string inputStr;

    std::cout << "Введите первое число: ";
    while (!(std::cin >> num1) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка: Некорректный ввод. Пожалуйста, введите число: ";
        logger->warn("Некорректный ввод первого числа в арифметике");
    }
    
    std::cout << "Введите операцию (+, -, *, /): ";
    std::cin >> operation;
    while ((operation != '+' && operation != '-' && operation != '*' && operation != '/') || std::cin.peek() != '\n') {
        std::cout << "Ошибка: Некорректная операция. Введите +, -, * или /: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> operation;
        logger->warn("Некорректный ввод операции в арифметике");
    }

    std::cout << "Введите второе число: ";
    while (!(std::cin >> num2) || (std::cin.peek() != '\n')) {
        std::cout << "Ошибка: Некорректный ввод. Пожалуйста, введите число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        logger->warn("Некорректный ввод второго числа в арифметике");
    }

    std::string resultStr;
    
    switch (operation) {
        case '+': {
            double result = num1 + num2;
            resultStr = std::to_string(result);
            std::cout << "Результат: " << result << std::endl;
            logger->info("Сложение: {} + {} = {}", num1, num2, result);
            historyManager->addCommand("Арифметика", "+", 
                                      std::to_string(num1) + " " + std::to_string(num2), 
                                      resultStr);
            break;
        }
        case '-': {
            double result = num1 - num2;
            resultStr = std::to_string(result);
            std::cout << "Результат: " << result << std::endl;
            logger->info("Вычитание: {} - {} = {}", num1, num2, result);
            historyManager->addCommand("Арифметика", "-", 
                                      std::to_string(num1) + " " + std::to_string(num2), 
                                      resultStr);
            break;
        }
        case '*': {
            double result = num1 * num2;
            resultStr = std::to_string(result);
            std::cout << "Результат: " << result << std::endl;
            logger->info("Умножение: {} * {} = {}", num1, num2, result);
            historyManager->addCommand("Арифметика", "*", 
                                      std::to_string(num1) + " " + std::to_string(num2), 
                                      resultStr);
            break;
        }
        case '/': {
            if (num2 == 0) {
                std::cout << "Ошибка: Деление на ноль!" << std::endl;
                logger->error("Попытка деления на ноль: {} / {}", num1, num2);
                historyManager->addCommand("Арифметика", "/", 
                                          std::to_string(num1) + " " + std::to_string(num2), 
                                          "ОШИБКА: деление на ноль");
            } else {
                double result = num1 / num2;
                resultStr = std::to_string(result);
                std::cout << "Результат: " << result << std::endl;
                logger->info("Деление: {} / {} = {}", num1, num2, result);
                historyManager->addCommand("Арифметика", "/", 
                                          std::to_string(num1) + " " + std::to_string(num2), 
                                          resultStr);
            }
            break;
        }
    }
    
    logger->debug("Арифметическая операция завершена");
}