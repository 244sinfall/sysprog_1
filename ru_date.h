#ifndef DATE_CONVERTER_FILIN_H
#define DATE_CONVERTER_FILIN_H


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
 * @brief Converts a day number to its textual representation.
 * 
 * @param day The day to be converted.
 * @param result The buffer to store the resulting textual representation.
 */
void get_day(int day, char* result);
/**
 * @brief Converts a month number to its textual representation.
 * 
 * @param month The month to be converted.
 * @param result The buffer to store the resulting textual representation.
 */
void get_month(int month, char* result);
/**
 * @brief Converts a year number to its textual representation.
 * 
 * @param year The year to be converted.
 * @param result The buffer to store the resulting textual representation.
 */
void get_year(int year, char* result);

struct Date* validate_date(const char* date_str);

char* get_date_string(char* result, int day, int month, int year);

#endif