// trigonometric.cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include "calculator.h"

// Функция для вычисления факториала
long double factorial(int n) {
    long double res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

// Функция для вычисления синуса через ряд Тейлора
long double taylor_sin(double x_rad, double precision = 1e-9) {
    long double sum = 0.0;
    long double term;
    int n = 0;
    do {
        term = pow(-1, n) * pow(x_rad, 2 * n + 1) / factorial(2 * n + 1);
        sum += term;
        n++;
    } while (std::abs(term) > precision);
    return sum;
}

// Функция для вычисления косинуса через ряд Тейлора
long double taylor_cos(double x_rad, double precision = 1e-9) {
    long double sum = 0.0;
    long double term;
    int n = 0;
    do {
        term = pow(-1, n) * pow(x_rad, 2 * n) / factorial(2 * n);
        sum += term;
        n++;
    } while (std::abs(term) > precision);
    return sum;
}

void trigonometric() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало тригонометрических вычислений");

    int choice;

    std::cout << "Выберите тригонометрическую функцию:\n";
    std::cout << "1. Синус (sin)\n";
    std::cout << "2. Косинус (cos)\n";
    std::cout << "3. Тангенс (tg)\n";
    std::cout << "4. Котангенс (ctg)\n";
    std::cout << "Введите номер функции: ";

    while (!(std::cin >> choice) || choice < 1 || choice > 4 || std::cin.peek() != '\n') {
        std::cout << "Ошибка: Введите целое число от 1 до 4. Попробуйте еще раз: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        logger->warn("Некорректный выбор тригонометрической функции");
    }

    double angle_deg;
    double angle_rad;
    const double PI = 3.14159265358979323846;

    std::cout << "Введите угол в градусах: ";
    while (!(std::cin >> angle_deg) || std::cin.peek() != '\n') {
        std::cout << "Ошибка: Введите число. Попробуйте еще раз: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        logger->warn("Некорректный ввод угла");
    }
    
    // Нормализация угла
    while (angle_deg >= 360.0) {
        angle_deg -= 360.0;
    }
    while (angle_deg < 0.0) {
        angle_deg += 360.0;
    }

    // Преобразование градусов в радианы
    angle_rad = angle_deg * PI / 180.0;

    double result = 0.0;
    std::string functionName, resultStr;
    bool error = false;

    switch (choice) {
        case 1:
            result = taylor_sin(angle_rad);
            std::cout << "Значение sin:     " << result << std::endl;
            functionName = "Синус";
            logger->info("sin({}°) = {}", angle_deg, result);
            break;
        case 2:
            result = taylor_cos(angle_rad);
            std::cout << "Значение cos:     " << result << std::endl;
            functionName = "Косинус";
            logger->info("cos({}°) = {}", angle_deg, result);
            break;
        case 3:
            if (angle_deg == 90 || angle_deg == 270) {
                std::cout << "Ошибка: угол является кратным pi/2. Тангенс не определён." << std::endl;
                resultStr = "ОШИБКА: тангенс не определен";
                error = true;
                logger->error("Тангенс не определен для угла {}°", angle_deg);
            } else {
                result = taylor_sin(angle_rad) / taylor_cos(angle_rad);
                std::cout << "Значение tg:     " << result << std::endl;
                functionName = "Тангенс";
                logger->info("tg({}°) = {}", angle_deg, result);
            }
            break;
        case 4:
            if (angle_deg == 0 || angle_deg == 180) {
                std::cout << "Ошибка: угол является кратным pi. Котангенс не определён." << std::endl;
                resultStr = "ОШИБКА: котангенс не определен";
                error = true;
                logger->error("Котангенс не определен для угла {}°", angle_deg);
            } else {
                result = taylor_cos(angle_rad) / taylor_sin(angle_rad);
                std::cout << "Значение ctg:     " << result << std::endl;
                functionName = "Котангенс";
                logger->info("ctg({}°) = {}", angle_deg, result);
            }
            break;
    }
    
    if (!error) {
        resultStr = std::to_string(result);
    }
    
    historyManager->addCommand("Тригонометрия", functionName, 
                              "угол=" + std::to_string(angle_deg) + "°", resultStr);
    
    logger->debug("Тригонометрические вычисления завершены");
}