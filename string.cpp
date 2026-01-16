// string.cpp
#include "string.h"
#include "calculator.h"

void string() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало строковых операций");
    
    std::string userInput;
    std::cout << "Введите простое математическое выражение в формате: \n";
    std::cout << "число операция число (пример: 5 + 3 Enter) : ";
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, userInput);
    
    logger->info("Получено строковое выражение: {}", userInput);

    // Создаем объект калькулятора, передавая ему ввод пользователя
    Calculator_String calc(userInput);

    // Выполняем вычисление
    calc.compute();

    // Выводим результат
    calc.displayResult();
    
    // Логирование и добавление в историю
    double result = calc.getResult();
    logger->info("Строковое вычисление: {} = {}", userInput, result);
    
    historyManager->addCommand("Строковые операции", "Вычисление выражения", 
                              userInput, std::to_string(result));
    
    logger->debug("Строковые операции завершены");
}