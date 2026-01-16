// data.cpp
#include "data.h"
#include "calculator.h"
using namespace std::chrono;

void data() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало работы с датами");

    int num, day, month, year;
    Date date1, date2;

    std::cout << "Введите номер операции с датами\n";
    std::cout << "1. Вывод текущей даты и времени; 2. Вывод количества дней в месяце \n";
    std::cout << "3. Добавление дней к введенной дате; 4. Вычитание дней из введенной даты; \n";

    while (!(std::cin >> num) || (num < 1) || (num > 4) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 4: \n";
        logger->warn("Некорректный ввод номера операции с датами");
    }

    auto now = std::chrono::system_clock::now();

    switch (num) {
        case 1: {
            auto current_time = std::format("{:%Y-%m-%d %H:%M:%S}", now);
            std::cout << "Сегодня: " << std::format("{:%Y-%m-%d}", now) << std::endl;
            std::cout << "Дата и время: " << current_time << std::endl;
            
            logger->info("Вывод текущей даты и времени: {}", current_time);
            historyManager->addCommand("Дата/Время", "Текущая дата", "", current_time);
            break;
        }
        case 2: {
            std::cout << "Введите год: ";
            while (!(std::cin >> year) || (year < 0) || (std::cin.peek() != '\n')) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Некорректный ввод. Пожалуйста, введите корректное значение года: \n";
                logger->warn("Некорректный ввод года");
            }
            
            std::cout << "Введите месяц: ";
            while (!(std::cin >> month) || (month < 1) || (month > 12) || (std::cin.peek() != '\n')) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Некорректный ввод. Пожалуйста, введите корректное значение месяца: \n";
                logger->warn("Некорректный ввод месяца");
            }
            
            std::string monthName;
            int daysInMonth = 0;
            
            switch (month) {
                case 1: monthName = "Январь"; daysInMonth = 31; break;
                case 2: monthName = "Февраль"; 
                    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                        daysInMonth = 29;
                        std::cout << "В феврале " << year << " года 29 дней." << std::endl;
                    } else {
                        daysInMonth = 28;
                        std::cout << "В феврале " << year << " года 28 дней." << std::endl;
                    }
                    break;
                case 3: monthName = "Март"; daysInMonth = 31; break;
                case 4: monthName = "Апрель"; daysInMonth = 30; break;
                case 5: monthName = "Май"; daysInMonth = 31; break;
                case 6: monthName = "Июнь"; daysInMonth = 30; break;
                case 7: monthName = "Июль"; daysInMonth = 31; break;
                case 8: monthName = "Август"; daysInMonth = 31; break;
                case 9: monthName = "Сентябрь"; daysInMonth = 30; break;
                case 10: monthName = "Октябрь"; daysInMonth = 31; break;
                case 11: monthName = "Ноябрь"; daysInMonth = 30; break;
                case 12: monthName = "Декабрь"; daysInMonth = 31; break;
            }
            
            if (month != 2) {
                std::cout << "В месяце " << daysInMonth << " дней." << std::endl;
            }
            
            logger->info("Дней в месяце: {} {} = {} дней", monthName, year, daysInMonth);
            historyManager->addCommand("Дата/Время", "Дней в месяце", 
                                      monthName + " " + std::to_string(year),
                                      std::to_string(daysInMonth));
            break;
        }
        case 3: 
        case 4: {
            std::cout << "Введите дату:\n";
            date1.inputDate();
            
            std::cout << "Введите количество дней: ";
            while (!(std::cin >> day) || (std::cin.peek() != '\n')) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Некорректный ввод. Пожалуйста, введите число: \n";
                logger->warn("Некорректный ввод количества дней");
            }
            
            std::string operation = (num == 4) ? "Вычитание" : "Сложение";
            std::string operationSymbol = (num == 4) ? "-" : "+";
            
            if (num == 4) {
                date1 = date1 - day;
            } else {
                date1 = date1 + day;
            }
            
            std::cout << "Искомая дата: ";
            date1.printDate();
            std::cout << std::endl;
            
            std::string resultStr = std::to_string(date1.day) + "." + 
                                   std::to_string(date1.month) + "." + 
                                   std::to_string(date1.year);
            
            std::string inputStr = operationSymbol + std::to_string(day) + " дней";
            
            logger->info("Операция с датой: {} дней = {}", operation, resultStr);
            historyManager->addCommand("Дата/Время", operation, inputStr, resultStr);
            break;
        }
    }
    
    logger->debug("Работа с датами завершена");
}