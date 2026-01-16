// string.h
#ifndef STRING_H    // Исключение повторного вкл. заголовочного файла
#define STRING_H

#include <iostream> // Для ввода/вывода
#include <string>   // Для работы со строками
#include <sstream>  // Для потоков (парсинга строк)
#include <vector>   // Для хранения токенов (чисел и операторов)
#include <stdexcept> // Для исключений (ошибок)

// Класс Калькулятор
class Calculator_String {
public:
    std::string expression; // Строка с выражением
    std::vector<std::string> tokens; // Токены (числа и операторы)
    double result; // Результат вычисления

    // Метод для парсинга выражения на токены
    void parseExpression() {
        std::stringstream ss(expression);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
    }

    // Метод для выполнения простых операций (считаем, что токены уже распарсены и их 3)
    double calculateSimpleExpression(const std::string& num1Str, const std::string& op, const std::string& num2Str) {
        double num1 = std::stod(num1Str); // Преобразуем строку в число
        double num2 = std::stod(num2Str);
        if (op == "+") return num1 + num2;
        if (op == "-") return num1 - num2;
        if (op == "*") return num1 * num2;
        if (op == "/") {
            if (num2 == 0) throw std::runtime_error("Деление на ноль!");
            return num1 / num2;
        }
        throw std::runtime_error("Неизвестный оператор: " + op);
    }

    // Конструктор: принимает выражение и сразу парсит его
    Calculator_String(const std::string& expr) : expression(expr), result(0.0) {
        parseExpression(); // Парсим выражение при создании объекта
    }

    // Метод для вычисления результата
    void compute() {
        if (tokens.size() == 3) { // Ожидаем формат: число оператор число
            try {
                result = calculateSimpleExpression(tokens[0], tokens[1], tokens[2]);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "Ошибка вычисления: " << e.what() << std::endl;
                result = 0.0; // Сбрасываем результат в случае ошибки
            }
        }
        else {
            std::cerr << "Некорректный формат выражения. Ожидается 'число оператор число'." << std::endl;
            result = 0.0;
        }
    }

    // Метод для получения результата
    double getResult() const {
        return result;
    }

    // Метод для вывода результата
    void displayResult() const {
        std::cout << "Результат: " << result << std::endl;
    }
};

void string();

#endif STRING_H