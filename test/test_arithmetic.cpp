#include <gtest/gtest.h>
#include <sstream>
#include "calculator.h"
#include "arithmetic.cpp"  // Включаем исходный файл для тестирования

// Моки для тестирования
class MockLogger {
public:
    void debug(const std::string&) {}
    void info(const std::string&, ...) {}
    void warn(const std::string&, ...) {}
    void error(const std::string&, ...) {}
};

class MockHistoryManager {
public:
    static MockHistoryManager* getInstance() {
        static MockHistoryManager instance;
        return &instance;
    }
    
    void addCommand(const std::string&, const std::string&,
                    const std::string&, const std::string&) {}
};

// Тесты для арифметических операций
TEST(ArithmeticTest, Addition) {
    // Подготовка тестовых данных
    std::stringstream input("10\n+\n5\n");
    std::stringstream output;
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    // Вызов функции
    arithmetic();
    
    // Восстановление потоков
    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
    
    // Проверка результата
    ASSERT_TRUE(output.str().find("Результат: 15") != std::string::npos);
}

TEST(ArithmeticTest, DivisionByZero) {
    std::stringstream input("10\n/\n0\n");
    std::stringstream output;
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    
    arithmetic();
    
    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
    
    ASSERT_TRUE(output.str().find("Деление на ноль") != std::string::npos);
}