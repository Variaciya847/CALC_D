// conversion.h
#ifndef CONVERSION_H    // Исключение повторного вкл. заголовоного файла
#define CONVERSION_H

#include <iostream>
#include <map>
#include <string>

// Перечисление поддерживаемых единиц измерения
enum class Unit {
    Meters,
    Kilometers,
    Centimeters,
    Millimeters,
    Inches,
    Feet
};

class UnitConverter {
private:
    // Таблица коэффициентов преобразования относительно базовой единицы (метра)
    std::map<Unit, double> conversionTable;

public:
    // Конструктор инициализирует таблицу преобразования
    UnitConverter() {
        conversionTable[Unit::Meters] = 1.0;
        conversionTable[Unit::Kilometers] = 1000.0;
        conversionTable[Unit::Centimeters] = 0.01;
        conversionTable[Unit::Millimeters] = 0.001;
        conversionTable[Unit::Inches] = 0.0254;
        conversionTable[Unit::Feet] = 0.3048;
    }

    // Основной метод конвертации
    double convert(double value, Unit from, Unit to) {
        // Сначала переводим в метры, затем в целевую единицу
        double meters = value * conversionTable[from];
        return meters / conversionTable[to];
    }

    // Вспомогательный метод для вывода названий
    std::string getUnitName(Unit unit) {
        switch (unit) {
        case Unit::Meters:      return "метры";
        case Unit::Kilometers:  return "километры";
        case Unit::Centimeters: return "сантиметры";
        case Unit::Millimeters: return "миллиметры";
        case Unit::Inches:      return "дюймы";
        case Unit::Feet:        return "футы";
        default:                return "неизвестно";
        }
    }
friend void conversion(UnitConverter& converter);
};
#endif CONVERSION_H
