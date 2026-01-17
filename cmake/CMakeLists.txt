cmake_minimum_required(VERSION 3.15)
project(CalculatorWithLogging CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включение тестов
option(BUILD_TESTS "Build tests" ON)

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

# Добавление Google Test
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
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
    history_manager.cpp
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

# Добавление тестов
if(BUILD_TESTS)
    # Создаем библиотеку для тестирования (без main.cpp)
    add_library(calculator_lib 
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
        history_manager.cpp
    )
    
    target_include_directories(calculator_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(calculator_lib PRIVATE spdlog::spdlog)
    
    # Тесты
    add_executable(tests
        tests/main.cpp
        tests/test_arithmetic.cpp
        tests/test_conversion.cpp
        tests/test_date.cpp
        tests/test_string_calculator.cpp
        tests/test_trigonometric.cpp
        tests/test_accounting_entry.cpp
    )
    
    target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(tests PRIVATE calculator_lib GTest::gtest_main)
    
    # Добавляем тесты в CTest
    include(GoogleTest)
    gtest_discover_tests(tests)
endif()