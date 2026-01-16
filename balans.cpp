// balans.cpp
#include "balans.h"
#include "calculator.h"

void balans() {
    auto logger = Logger::get();
    auto historyManager = HistoryManager::getInstance();
    
    logger->debug("Начало работы с бухгалтерским балансом");

    std::vector<AccountingEntry> journal;
    char choice;

    // Цикл создания записей
    do {
        logger->info("Создание новой проводки");
        journal.push_back(AccountingEntry());
        std::cout << "Добавить еще одну запись? (y/n): ";
        std::cin >> choice;
        if (!(choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')) {
            do {
                std::cout << "Некорректный ввод. Введите, пожалуйста y/n: \n";
                std::cin >> choice;
            } while (!(choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N'));
            logger->warn("Некорректный ввод при добавлении записи");
        }
    } while (choice == 'y' || choice == 'Y');

    // Итоговый расчет
    double totalDebit = 0, totalCredit = 0;
    std::cout << "\n--- Журнал проводок ---" << std::endl;
    for (const auto& entry : journal) {
        entry.display();
        totalDebit += entry.getDebit();
        totalCredit += entry.getCredit();
    }

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "ИТОГО:               | Д: " << totalDebit
        << " | К: " << totalCredit << std::endl;

    // Логирование итогов
    logger->info("Итоги баланса: Дебет = {}, Кредит = {}", totalDebit, totalCredit);
    
    // Проверка баланса
    if (totalDebit == totalCredit) {
        std::cout << "Баланс сошелся." << std::endl;
        logger->info("Баланс сошелся успешно");
        historyManager->addCommand("Баланс", "Проверка", 
                                  std::to_string(journal.size()) + " проводок", 
                                  "Сошлось: Д=" + std::to_string(totalDebit) + 
                                  " К=" + std::to_string(totalCredit));
    }
    else {
        double difference = totalDebit - totalCredit;
        std::cout << "ВНИМАНИЕ: Баланс не сошелся! Разница: " << difference << std::endl;
        logger->error("Баланс не сошелся! Разница: {}", difference);
        historyManager->addCommand("Баланс", "Проверка", 
                                  std::to_string(journal.size()) + " проводок", 
                                  "Не сошелся (разница=" + std::to_string(difference) + ")");
    }
    
    logger->debug("Работа с балансом завершена");
}