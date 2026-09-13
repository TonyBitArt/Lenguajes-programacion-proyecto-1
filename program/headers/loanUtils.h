#ifndef LOANUTILS_H
#define LOANUTILS_H

#include "jsonHandler.h"

/**
 * @brief Libera la memoria asignada para un arreglo de préstamos.
 * @param loans Puntero al arreglo de préstamos.
 * @param loanCount Cantidad de préstamos en el arreglo.
 * @return void
 */
void freeAllLoans(struct Loan *loans, int loanCount);

/**
 * @brief Guarda un préstamo en el archivo JSON de préstamos.
 * @param loan La estructura del préstamo a guardar.
 * @return int 1 si se guardó exitosamente, 0 si ocurrió un error.
 */
int saveLoan(struct Loan *loan);

/**
 * @brief Obtiene el siguiente número de copia disponible para un libro específico.
 * @param bookName El nombre del libro.
 * @return int El siguiente número de copia disponible, o 0 si no hay copias disponibles.
 */
int getNextCopyNumber(char *bookName);

/**
 * @brief Guarda todos los préstamos en el archivo JSON de préstamos.
 * @param loans Puntero al arreglo de préstamos.
 * @param loanCount Cantidad de préstamos en el arreglo.
 * @return void
 */
void saveAllLoans(struct Loan *loans, int loanCount);

#endif // LOANUTILS_H