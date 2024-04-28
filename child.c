#include <stdio.h>
#include <stdlib.h>
#include "ru_date.h"

int main(int argc, char **argv) {
    if(argc != 2){
        printf("Передайте дату формата ДД.ММ.ГГГГ. Она должна быть единственным аргументом;\n");
        return EXIT_FAILURE;
    }
    struct Date* date = validate_date(argv[1]);
    if(NULL==date){
        printf("Некорректная дата!\n");
        return EXIT_FAILURE;
    }
    char result[500] = "";
    get_date_string(result, date->day, date->month, date->year);
    printf("%s\n", result);
    return EXIT_SUCCESS;
}