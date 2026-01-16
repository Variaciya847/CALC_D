#pragma once
#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <stack>
#include <mutex>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "logger.h"

struct Command {
    std::string module;      // Модуль калькулятора
    std::string operation;   // Операция
    std::string input;       // Входные данные
    std::string result;      // Результат
    std::string timestamp;   // Время выполнения
    
    Command(const std::string& mod, const std::string& op, 
            const std::string& inp, const std::string& res)
        : module(mod), operation(op), input(inp), result(res) {
        
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;

        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        
        timestamp = ss.str();
    }
    
    std::string toString() const {
        return timestamp + " [" + module + "] " + operation + 
               " " + input + " = " + result;
    }
};

class HistoryManager {
private:
    static HistoryManager* instance;
    static std::mutex mutex;
    
    std::vector<Command> fullHistory;
    std::stack<Command> undoStack;
    std::stack<Command> redoStack;
    size_t maxHistorySize = 100;
    
    HistoryManager() {
        Logger::get()->info("Менеджер истории инициализирован");
    }
    
public:
    HistoryManager(const HistoryManager&) = delete;
    HistoryManager& operator=(const HistoryManager&) = delete;
    
    static HistoryManager* getInstance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (instance == nullptr) {
            instance = new HistoryManager();
        }
        return instance;
    }
    
    void addCommand(const std::string& module, const std::string& operation,
                   const std::string& input, const std::string& result) {
        std::lock_guard<std::mutex> lock(mutex);
        
        Command cmd(module, operation, input, result);
        fullHistory.push_back(cmd);
        undoStack.push(cmd);
        
        // Очищаем стек redo при новой операции
        while (!redoStack.empty()) redoStack.pop();
        
        // Ограничиваем размер истории
        if (fullHistory.size() > maxHistorySize) {
            fullHistory.erase(fullHistory.begin());
        }
        
        Logger::get()->debug("Добавлена команда: {}", cmd.toString());
    }
    
    bool undo() {
        std::lock_guard<std::mutex> lock(mutex);
        
        if (undoStack.empty()) {
            Logger::get()->warn("Нет операций для отмены");
            return false;
        }
        
        Command lastCmd = undoStack.top();
        undoStack.pop();
        redoStack.push(lastCmd);
        
        Logger::get()->info("Операция отменена: {}", lastCmd.toString());
        return true;
    }
    
    bool redo() {
        std::lock_guard<std::mutex> lock(mutex);
        
        if (redoStack.empty()) {
            Logger::get()->warn("Нет операций для повтора");
            return false;
        }
        
        Command lastUndone = redoStack.top();
        redoStack.pop();
        undoStack.push(lastUndone);
        
        Logger::get()->info("Операция повторена: {}", lastUndone.toString());
        return true;
    }
    
    std::vector<Command> getHistory() const {
        std::lock_guard<std::mutex> lock(mutex);
        return fullHistory;
    }
    
    void clearHistory() {
        std::lock_guard<std::mutex> lock(mutex);
        fullHistory.clear();
        while (!undoStack.empty()) undoStack.pop();
        while (!redoStack.empty()) redoStack.pop();
        
        Logger::get()->info("История операций очищена");
    }
    
    void printHistory() const {
        auto history = getHistory();
        
        if (history.empty()) {
            std::cout << "\nИстория операций пуста\n" << std::endl;
            return;
        }
        
        std::cout << "\n=== История операций ===" << std::endl;
        for (const auto& cmd : history) {
            std::cout << cmd.toString() << std::endl;
        }
        std::cout << "========================\n" << std::endl;
    }
    
    void setMaxHistorySize(size_t size) {
        maxHistorySize = size;
    }
    
    ~HistoryManager() {
        Logger::get()->info("Менеджер истории завершает работу");
    }
};

#endif