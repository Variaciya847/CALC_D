// history_manager.cpp
#include "history_manager.h"

// Определение статических членов
HistoryManager* HistoryManager::instance = nullptr;
std::mutex HistoryManager::mutex;
