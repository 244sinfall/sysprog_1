/**
 * @file ru_date.c
 * @brief A C program to convert dates from numeric format to textual format in Russian language.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Array of textual representations for numbers from 0 to 9.
 */
const char *onesDefault[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};

/**
 * @brief Array of textual representations for teens (numbers from 11 to 19).
 */
const char *teensDefault[] = {"", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};

/**
 * @brief Array of textual representations for tens (multiples of 10).
 */
const char *tensDefault[] = {"", "десять", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};

/**
 * @brief Array of textual representations for ordinal numbers of days.
 */
const char *onesDay[] = {"", "первое", "второе", "третье", "четвертое", "пятое", "шестое", "седьмое", "восьмое", "девятое"};

/**
 * @brief Array of textual representations for ordinal numbers of teens in days.
 */
const char *teensDay[] = {"", "одиннадцатое", "двенадцатое", "тринадцатое", "четырнадцатое", "пятнадцатое", "шестнадцатое", "семнадцатое", "восемнадцатое", "девятнадцатое"};

/**
 * @brief Array of textual representations for ordinal numbers of tens in days.
 */
const char *tensDay[] = {"", "десятое", "двадцатое", "тридцатое", "сороковое", "пятьдесятое", "шестьдесятое", "семьдесятое", "восемьдесятое", "девяностое"};

/**
 * @brief Array of textual representations for ordinal numbers of thousands in years.
 */
const char *thousandsYear[] = {"", "тысяча", "две тысячи", "три тысячи", "четыре тысячи", "пять тысяч", "шесть тысяч", "семь тысяч", "восемь тысяч", "девять тысяч"};

/**
 * @brief Array of textual representations for ordinal numbers of thousands in flat form.
 */
const char *flatThousandsYear[] = {"", "тысячного", "двухтысячного", "трехтысячного", "четырехтысячного", "пятитысячного", "шеститысячного", "семитысячного", "восеметысячного", "девятитысячного"};

/**
 * @brief Array of textual representations for ordinal numbers of hundreds in years.
 */
const char *hundredsYears[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};

/**
 * @brief Array of textual representations for ordinal numbers of hundreds in flat form.
 */
const char *flatHundredsYears[] = {"", "сотого", "двухсотого", "трехсотого", "четырехсотого", "пятисотого", "шестисотого", "семисотого", "восьмесотого", "девятьсотого"};

/**
 * @brief Array of textual representations for ordinal numbers of tens in years in flat form.
 */
const char *flatTensYears[] = {"", "десятого", "двадцатого", "тридцатого", "сорокового", "пятидесятого", "шестидесятого", "семидесятого", "восьмидесятого", "девяностого"};

/**
 * @brief Array of textual representations for ordinal numbers of teens in years.
 */
const char *teenYears[] = {"", "одиннацатого", "двенадцатого", "тринадцатого", "четырнадцатого", "пятнадцатого", "шестнадцатого", "семнадцатого", "восемнадцатого", "девятнадцатого"};

/**
 * @brief Array of textual representations for ordinal numbers of ones in years.
 */
const char *onesYears[] = {"", "первого", "второго", "третьего", "четвертого", "пятого", "шестого", "седьмого", "восьмого", "девятого"};


/**
 * @struct Date
 * @brief Structure to represent a date with year, month, and day components.
 */
struct Date {
    int year; /**< The year component of the date. */
    int month;  /**< The month component of the date. */
    int day; /**< The day component of the date. */
};

/**
 * @brief Converts a year number to its textual representation.
 * 
 * @param year The year to be converted.
 * @param result The buffer to store the resulting textual representation.
 */
void get_year(int year, char* result){
    if (year < 1 || year > 9999){
        return;
    } else if(year % 1000 == 0){
        strcat(result, flatThousandsYear[year / 1000]);
    } else if(year % 100 == 0){
        if(year > 1000){
            strcat(result, thousandsYear[year / 1000]);
            strcat(result, " ");
            year = year % 1000;
        }
        strcat(result, flatHundredsYears[year / 100]);
    } else {
        if(year > 1000){
            strcat(result, thousandsYear[year / 1000]);
            strcat(result, " ");
            year = year % 1000;
        }
        if(year > 100){
            strcat(result, hundredsYears[year / 100]);
            strcat(result, " ");
            year = year % 100;
        }
        if(year % 10 == 0){
            strcat(result, flatTensYears[year / 10]);
        } else if(year > 10 && year < 20){
            strcat(result, teenYears[year - 10]);
        } else {
            if(year > 10){
                strcat(result, tensDefault[year / 10]);
                strcat(result, " ");
            }
            strcat(result, onesYears[year % 10]);
        }
    }
}

/**
 * @brief Converts a day number to its textual representation.
 * 
 * @param day The day to be converted.
 * @param result The buffer to store the resulting textual representation.
 */
void get_day(int day, char* result){
    if (day >= 100 || day < 1){
        return;
    }   
    if (day < 10){
        strcat(result, onesDay[day]);
    } else if(day % 10 == 0){
        strcat(result, tensDay[day / 10]);
    } else if(day > 10 && day < 20){
        strcat(result, teensDay[day - 10]);
    } else {
        strcat(result, tensDefault[day / 10]);
        strcat(result, " ");
        strcat(result, onesDay[day % 10]);
    }
}

/**
 * @brief Converts a month number to its textual representation.
 * 
 * @param month The month to be converted.
 * @param result The buffer to store the resulting textual representation.
 */
void get_month(int month, char* result) {
    if(month < 1 || month > 12){
        return;
    }
    const char *months[] = {"", "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};
    strcat(result, months[month]);
}

/**
 * @brief Generates a textual representation of a date in Russian language.
 * 
 * @param result The buffer to store the resulting textual representation.
 * @param day The day component of the date.
 * @param month The month component of the date.
 * @param year The year component of the date.
 */
void get_date_string(char* result, int day, int month, int year){
    get_day(day, result);
    strcat(result, " ");
    get_month(month, result);
    strcat(result, " ");
    get_year(year, result);
    strcat(result, " года");
}

/**
 * @brief Checks if a given year is a leap year.
 * 
 * @param year The year to be checked.
 * @return true if the year is a leap year, false otherwise.
 */
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Validates a date string and returns its components as a Date structure.
 * 
 * @param date_str The date string to be validated.
 * @return A pointer to a Date structure if the date string is valid, NULL otherwise.
 */
struct Date* validate_date(const char* date_str){
    struct Date* date = malloc(sizeof(struct Date));
    // Проверка длины строки
    if (strlen(date_str) != 10)
        return NULL;

    // Проверка формата
    if (date_str[2] != '.' || date_str[5] != '.')
        return NULL;

    // Извлечение компонентов даты
    char *endptr;
    int day = strtol(date_str, &endptr, 10);
    if (*endptr != '.')
        return NULL;
    int month = strtol(endptr + 1, &endptr, 10);
    if (*endptr != '.')
        return NULL;
    int year = strtol(endptr + 1, &endptr, 10);

    // Проверка года
    if (year < 1601)
        return NULL;

    // Проверка месяца
    if (month < 1 || month > 12)
        return NULL;

    // Проверка дня
    if (day < 1)
        return NULL;

    // Определение числа дней в месяце
    int days_in_month;
    if (month == 2) {
        days_in_month = is_leap_year(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        days_in_month = 30;
    } else {
        days_in_month = 31;
    }

    // Проверка числа дней в месяце
    if (day > days_in_month)
        return NULL;

    // Проверка периода 1-13 февраля для России после 1918 года
    if (year > 1918 && month == 2 && day >= 1 && day <= 13)
        return NULL;
    date->day = day;
    date->month = month;
    date->year = year;
    return date;
}