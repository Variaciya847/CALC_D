// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include "logger.h"
#include "history_manager.h"
#include "conversion.h" 

// Объявление функций 
void arithmetic();
void trigonometric();
void logarithms();
void logic();
void balans();
void data();
void string();
void other();
void conversion(UnitConverter& converter);

// Дополнительные функции для работы с историей
void showHistory();
void undoOperation();
void redoOperation();
void clearHistory();

#endif