#ifndef CONSTANS_H
#define CONSTANS_H

//стандартные функции
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//размерные константы
#define MANT_SIZE 35
#define POW_SIZE 8

//знаковые константы для массивов чисел
#define END_OF_MASS_INT -1
#define PHANTOM_POINT -2

//константы сравнения чисел
#define FIRST_GREATER 1
#define SECOND_GREATER -1

//названия файлов
#define INPUT_FILE "indata.txt"
#define OUTPUT_FILE "outdata.txt"

//коды ошибок
#define OK 0
#define END_READ 1
#define NOT_DIGIT 2
#define TOO_LONG_NUMBER 3
#define ENTRY_POWER_UNLIM 4
#define UNLIMITED_POWER 5
#define DIVISION_BY_ZERO 6

#endif