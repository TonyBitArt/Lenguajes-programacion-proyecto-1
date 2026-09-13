#include <stdio.h>
#include <regex.h>
#include <time.h>
#include "../headers/dateUtils.h"


/**
 * @brief Parsea una fecha en formato YYYY-MM-DD y devuelve el número de días desde el 1 de enero del año 1.
 * @param date La fecha a parsear.
 * @return long El número de días desde el 1 de enero del año 1. -1 si la fecha es inválida.
 */
long parseDays(const char *date) {
    if (!date) return -1;
    int y, m, d;
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) != 3) return -1;
    
    long a = (14 - m) / 12;
    long yy = y + 4800 - a;
    long mm = m + 12 * a - 3;
    return d + (153 * mm + 2) / 5 + 365 * yy + yy / 4 - yy / 100 + yy / 400 - 32045;
}


/**
 * @brief Valida si una cadena cumple estrictamente con el formato YYYY-MM-DD.
 * @param dateStr La cadena de texto a validar.
 * @return int 1 si el formato es válido, 0 si es inválido.
 */
int isValidDateFormat(const char* dateString) {
    if (!dateString) return 0;

    regex_t regex;
    const char* pattern = "^[0-9]{4}-(0[1-9]|1[0-2])-([1-9]|0[1-9]|[12][0-9]|3[01])$";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    int matchResult = regexec(&regex, dateString, 0, NULL, 0);

    regfree(&regex);
    return (matchResult == 0) ? 1 : 0;
}


/**
 * @brief Obtiene la fecha del sistema en formato YYYY-MM-DD.
 * @param buffer Un puntero a un buffer donde se almacenará la fecha.
 * @param bufferSize El tamaño del buffer.
 * @return void
 */
void getSystemDate(char* buffer, size_t bufferSize) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, bufferSize, "%Y-%m-%d", tm_info);
}

