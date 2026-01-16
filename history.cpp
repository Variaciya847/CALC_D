#include "calculator.h"

void showHistory() {
    auto historyManager = HistoryManager::getInstance();
    historyManager->printHistory();
}

void undoOperation() {
    auto historyManager = HistoryManager::getInstance();
    if (historyManager->undo()) {
        std::cout << "Операция отменена" << std::endl;
    } else {
        std::cout << "Нет операций для отмены" << std::endl;
    }
}

void redoOperation() {
    auto historyManager = HistoryManager::getInstance();
    if (historyManager->redo()) {
        std::cout << "Операция повторена" << std::endl;
    } else {
        std::cout << "Нет операций для повтора" << std::endl;
    }
}

void clearHistory() {
    auto historyManager = HistoryManager::getInstance();
    historyManager->clearHistory();
    std::cout << "История операций очищена" << std::endl;
}