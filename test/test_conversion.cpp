#include <gtest/gtest.h>
#include "conversion.h"

TEST(UnitConverterTest, MetersToKilometers) {
    UnitConverter converter;
    double result = converter.convert(1000, Unit::Meters, Unit::Kilometers);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(UnitConverterTest, InchesToCentimeters) {
    UnitConverter converter;
    double result = converter.convert(1, Unit::Inches, Unit::Centimeters);
    EXPECT_NEAR(result, 2.54, 0.001);
}

TEST(UnitConverterTest, FeetToMeters) {
    UnitConverter converter;
    double result = converter.convert(1, Unit::Feet, Unit::Meters);
    EXPECT_NEAR(result, 0.3048, 0.0001);
}

TEST(UnitConverterTest, GetUnitName) {
    UnitConverter converter;
    EXPECT_EQ(converter.getUnitName(Unit::Meters), "метры");
    EXPECT_EQ(converter.getUnitName(Unit::Kilometers), "километры");
}