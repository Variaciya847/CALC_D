#include <gtest/gtest.h>
#include "string.h"

TEST(StringCalculatorTest, SimpleAddition) {
    Calculator_String calc("5 + 3");
    calc.compute();
    EXPECT_DOUBLE_EQ(calc.getResult(), 8.0);
}

TEST(StringCalculatorTest, SimpleSubtraction) {
    Calculator_String calc("10 - 4");
    calc.compute();
    EXPECT_DOUBLE_EQ(calc.getResult(), 6.0);
}

TEST(StringCalculatorTest, SimpleMultiplication) {
    Calculator_String calc("6 * 7");
    calc.compute();
    EXPECT_DOUBLE_EQ(calc.getResult(), 42.0);
}

TEST(StringCalculatorTest, SimpleDivision) {
    Calculator_String calc("15 / 3");
    calc.compute();
    EXPECT_DOUBLE_EQ(calc.getResult(), 5.0);
}

TEST(StringCalculatorTest, DivisionByZero) {
    Calculator_String calc("10 / 0");
    calc.compute();
    // Результат должен быть 0.0 при ошибке (согласно коду)
    EXPECT_DOUBLE_EQ(calc.getResult(), 0.0);
}

TEST(StringCalculatorTest, InvalidFormat) {
    Calculator_String calc("10 + ");
    calc.compute();
    EXPECT_DOUBLE_EQ(calc.getResult(), 0.0);
}