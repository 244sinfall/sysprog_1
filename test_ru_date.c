#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

// Подключение заголовочного файла вашей программы
#include "ru_date.h"


void test_get_day(){
    char result1[50] = "";
    get_day(1, result1);
    CU_ASSERT_STRING_EQUAL(result1, "первое");
    char result2[50] = "";
    get_day(12, result2);
    CU_ASSERT_STRING_EQUAL(result2, "двенадцатое");
    char result3[50] = "";
    get_day(31, result3);
    CU_ASSERT_STRING_EQUAL(result3, "тридцать первое");
    char result4[50] = "";
    get_day(30, result4);
    CU_ASSERT_STRING_EQUAL(result4, "тридцатое");
}

void test_get_month(){
    char result1[50] = "";
    get_month(1, result1);
    CU_ASSERT_STRING_EQUAL(result1, "января");
    char result2[50] = "";
    get_month(9, result2);
    CU_ASSERT_STRING_EQUAL(result2, "сентября");
}


void test_get_date_string(){
    char result1[500] = "";
    get_date_string(result1, 29, 12, 1998);
    CU_ASSERT_STRING_EQUAL(result1, "двадцать девятое декабря тысяча девятьсот девяносто восьмого года");
    char result2[500] = "";
    get_date_string(result2, 28, 7, 988);
    CU_ASSERT_STRING_EQUAL(result2, "двадцать восьмое июля девятьсот восемьдесят восьмого года");
    char result3[500] = "";
    get_date_string(result3, 1, 1, 2007);
    CU_ASSERT_STRING_EQUAL(result3, "первое января две тысячи седьмого года");
}


void test_get_year(){
    char result1[200] = "";
    get_year(2016, result1);
    CU_ASSERT_STRING_EQUAL(result1, "две тысячи шестнадцатого");
    char result2[200] = "";
    get_year(668, result2);
    CU_ASSERT_STRING_EQUAL(result2, "шестьсот шестьдесят восьмого");
    char result3[200] = "";
    get_year(1991, result3);
    CU_ASSERT_STRING_EQUAL(result3, "тысяча девятьсот девяносто первого");
    char result4[200] = "";
    get_year(394, result4);
    CU_ASSERT_STRING_EQUAL(result4, "триста девяносто четвертого");
    char result5[200] = "";
    get_year(666, result5);
    CU_ASSERT_STRING_EQUAL(result5, "шестьсот шестьдесят шестого");
    
    char result6[200] = "";
    get_year(1000, result6);
    CU_ASSERT_STRING_EQUAL(result6, "тысячного");
    char result7[200] = "";
    get_year(2000, result7);
    CU_ASSERT_STRING_EQUAL(result7, "двухтысячного");
    char result8[200] = "";
    get_year(200, result8);
    CU_ASSERT_STRING_EQUAL(result8, "двухсотого");
}

void test_validate_date(){
    struct Date* date1 = validate_date("29.12.1998");
    struct Date* date2 = validate_date("18.02.2005");
    struct Date* date3 = validate_date("35.02.2001");
    struct Date* date4 = validate_date("5.02.1918");
    CU_ASSERT_PTR_NULL(date4);
    CU_ASSERT_PTR_NULL(date3);
    CU_ASSERT_EQUAL(date2->day, 18);
    CU_ASSERT_EQUAL(date2->month, 2);
    CU_ASSERT_EQUAL(date2->year, 2005)
    CU_ASSERT_EQUAL(date1->day, 29);
    CU_ASSERT_EQUAL(date1->month, 12);
    CU_ASSERT_EQUAL(date1->year, 1998)
    
}

// Функция для инициализации тестов
int init_suite(void) {
    return 0;
}

// Функция для очистки тестов
int clean_suite(void) {
    return 0;
}

int main() {
    CU_pSuite pSuite = NULL;
    
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    
    pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((NULL == CU_add_test(pSuite, "Test of get_day()", test_get_day)) ||
        (NULL == CU_add_test(pSuite, "Test of get_month()", test_get_month)) ||
        (NULL == CU_add_test(pSuite, "Test of get_year()", test_get_year)) || 
        (NULL == CU_add_test(pSuite, "Test of get_date_string()", test_get_date_string)) || 
        (NULL == CU_add_test(pSuite, "Test of validate_date()", test_validate_date))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
