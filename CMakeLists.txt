cmake_minimum_required(VERSION 3.15)
project(CalculatorWithLogging CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    arithmetic.cpp
    balans.cpp
    conversion.cpp
    data.cpp
    logarithms.cpp
    logic.cpp
    other.cpp
    string.cpp
    trigonometric.cpp
    history.cpp
    history_manager.cpp  # ← Добавьте
    // logger.cpp           # ← Добавьте если используете Вариант 2
)

# Поиск или загрузка spdlog
find_package(spdlog 1.10.0 QUIET)

if(NOT spdlog_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
    )
    FetchContent_MakeAvailable(spdlog)
endif()

# Создание директории для логов
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)

# Список всех исходных файлов
set(SOURCES
    main.cpp
    arithmetic.cpp
    balans.cpp
    conversion.cpp
    data.cpp
    logarithms.cpp
    logic.cpp
    other.cpp
    string.cpp
    trigonometric.cpp
    history.cpp
    history_manager.cpp  # Добавьте этот файл
)

# Список заголовочных файлов
set(HEADERS
    calculator.h
    balans.h
    conversion.h
    data.h
    string.h
    logger.h
    history_manager.h
)

# Создание исполняемого файла
add_executable(calculator ${SOURCES} ${HEADERS})

# Подключение spdlog
target_link_libraries(calculator PRIVATE spdlog::spdlog)

# Установка директорий включения
target_include_directories(calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Дополнительные флаги для Windows
if(WIN32)
    target_compile_definitions(calculator PRIVATE 
        _CRT_SECURE_NO_WARNINGS 
        NOMINMAX
    )
endif()