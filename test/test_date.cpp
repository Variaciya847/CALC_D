#include <gtest/gtest.h>
#include "data.h"

TEST(DateTest, ConstructorAndPrint) {
    Date date(15, 10, 2024);
    EXPECT_EQ(date.day, 15);
    EXPECT_EQ(date.month, 10);
    EXPECT_EQ(date.year, 2024);
}

TEST(DateTest, AdditionOperator) {
    Date date(15, 10, 2024);
    Date result = date + 15;
    
    // Проверяем упрощенную логику (30 дней в месяце)
    EXPECT_EQ(result.day, 30);  // 15 + 15
    EXPECT_EQ(result.month, 10);
    EXPECT_EQ(result.year, 2024);
    
    Date result2 = date + 20;  // Переход через месяц
    EXPECT_EQ(result2.day, 5);   // 15 + 20 - 30 = 5
    EXPECT_EQ(result2.month, 11); // Следующий месяц
    EXPECT_EQ(result2.year, 2024);
}

TEST(DateTest, SubtractionOperator) {
    Date date(15, 10, 2024);
    Date result = date - 10;
    
    EXPECT_EQ(result.day, 5);
    EXPECT_EQ(result.month, 10);
    EXPECT_EQ(result.year, 2024);
    
    Date result2 = date - 20;  // Переход через месяц назад
    EXPECT_EQ(result2.day, 25);   // 15 - 20 + 30 = 25
    EXPECT_EQ(result2.month, 9);  // Предыдущий месяц
    EXPECT_EQ(result2.year, 2024);
}