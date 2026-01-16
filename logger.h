// logger.h
#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <memory>
#include <string>

class Logger {
private:
    // Определение inline (C++17 и выше)
    inline static std::shared_ptr<spdlog::logger> instance = nullptr;

public:
    static void init(const std::string& logFile = "logs/calculator.log") {
        try {
            if (instance) return; // Уже инициализирован

            // Создаем сенки для вывода в консоль и файл
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile, true);

            std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };

            instance = std::make_shared<spdlog::logger>("calculator", sinks.begin(), sinks.end());

            // Настройка формата
            instance->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] %v");
            instance->set_level(spdlog::level::info);

            spdlog::register_logger(instance);
            spdlog::set_default_logger(instance);

            instance->info("========== Логгер инициализирован ==========");
        }
        catch (const spdlog::spdlog_ex& ex) {
            std::cerr << "Ошибка инициализации логгера: " << ex.what() << std::endl;
        }
    }

    static std::shared_ptr<spdlog::logger> get() {
        if (!instance) {
            init();
        }
        return instance;
    }
};

#endif