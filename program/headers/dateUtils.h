// Archivo: headers/dateUtils.h
#ifndef DATE_UTILS_H
#define DATE_UTILS_H


/**
 * @brief Parsea una fecha en formato YYYY-MM-DD y devuelve el número de días desde el 1 de enero del año 1.
 * @param date La fecha a parsear.
 * @return long El número de días desde el 1 de enero del año 1. -1 si la fecha es inválida.
 */
long parseDays(const char *date);


/**
 * @brief Valida si una cadena cumple estrictamente con el formato YYYY-MM-DD.
 * @param dateStr La cadena de texto a validar.
 * @return int 1 si el formato es válido, 0 si es inválido.
 */
int isValidDateFormat(const char* dateString);


/**
 * @brief Obtiene la fecha del sistema en formato YYYY-MM-DD.
 * @param buffer Un puntero a un buffer donde se almacenará la fecha.
 * @param bufferSize El tamaño del buffer.
 * @return void
 */
void getSystemDate(char* buffer, size_t bufferSize);


#endif // DATE_UTILS_H