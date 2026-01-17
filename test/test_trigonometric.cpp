#include <gtest/gtest.h>
#include <cmath>
#include "trigonometric.cpp"  // Для доступа к factorial и taylor_sin/cos

TEST(TrigonometricTest, Factorial) {
    EXPECT_DOUBLE_EQ(factorial(0), 1.0);
    EXPECT_DOUBLE_EQ(factorial(1), 1.0);
    EXPECT_DOUBLE_EQ(factorial(5), 120.0);
    EXPECT_DOUBLE_EQ(factorial(10), 3628800.0);
}

TEST(TrigonometricTest, TaylorSin) {
    // sin(0) = 0
    EXPECT_NEAR(taylor_sin(0.0), 0.0, 1e-10);
    
    // sin(π/6) = 0.5
    EXPECT_NEAR(taylor_sin(M_PI/6), 0.5, 1e-6);
    
    // sin(π/2) = 1
    EXPECT_NEAR(taylor_sin(M_PI/2), 1.0, 1e-6);
}

TEST(TrigonometricTest, TaylorCos) {
    // cos(0) = 1
    EXPECT_NEAR(taylor_cos(0.0), 1.0, 1e-10);
    
    // cos(π/3) = 0.5
    EXPECT_NEAR(taylor_cos(M_PI/3), 0.5, 1e-6);
    
    // cos(π/2) = 0
    EXPECT_NEAR(taylor_cos(M_PI/2), 0.0, 1e-6);
}