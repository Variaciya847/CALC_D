// conversion.cpp
#include "conversion.h"
#include "calculator.h"

void conversion(UnitConverter& converter) {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало конвертации единиц измерения");
    
    int num1, num3;
    double num2;
    Unit from;
    Unit to;
    
    std::cout << "Введите номер единицы измерения\n";
    std::cout << "1. Метры;      2. Километры;    3. Сантиметры;\n";
    std::cout << "4. Миллиметры; 5. Дюймы;        6. Футы. \n"; 
    
    while (!(std::cin >> num1) || (num1 < 1) || (num1 > 6) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 6: \n";
        logger->warn("Некорректный ввод исходной единицы измерения");
    }
    
    std::cout << "Введите величину единицы измерения для конвертации:\n";
    while (!(std::cin >> num2) || (std::cin.peek() != '\n')) {
        std::cout << "Ошибка: неправильный ввод величины единицы измерения. Попробуйте еще раз:\n ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        logger->warn("Некорректный ввод величины для конвертации");
    }
    
    std::cout << "Введите номер единицы измерения для конвертации:\n";
    while (!(std::cin >> num3) || (num3 < 1) || (num3 > 6) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 6: \n";
        logger->warn("Некорректный ввод целевой единицы измерения");
    }
    
    // Определение исходной единицы
    std::string fromName, toName;
    switch (num1) {
        case 1: from = Unit::Meters; fromName = "метры"; break;
        case 2: from = Unit::Kilometers; fromName = "километры"; break;
        case 3: from = Unit::Centimeters; fromName = "сантиметры"; break;
        case 4: from = Unit::Millimeters; fromName = "миллиметры"; break;
        case 5: from = Unit::Inches; fromName = "дюймы"; break;
        case 6: from = Unit::Feet; fromName = "футы"; break;
    }
    
    // Определение целевой единицы
    switch (num3) {
        case 1: to = Unit::Meters; toName = "метры"; break;
        case 2: to = Unit::Kilometers; toName = "километры"; break;
        case 3: to = Unit::Centimeters; toName = "сантиметры"; break;
        case 4: to = Unit::Millimeters; toName = "миллиметры"; break;
        case 5: to = Unit::Inches; toName = "дюймы"; break;
        case 6: to = Unit::Feet; toName = "футы"; break;
    }

    double result = converter.convert(num2, from, to);

    std::cout << num2 << " " << fromName << " = "
              << result << " " << toName << std::endl;
    
    // Логирование и добавление в историю
    logger->info("Конвертация: {} {} → {} {}", num2, fromName, result, toName);
    
    historyManager->addCommand("Конвертация", "Конвертировать",
                              std::to_string(num2) + " " + fromName + " → " + toName,
                              std::to_string(result));
    
    logger->debug("Конвертация завершена");
}