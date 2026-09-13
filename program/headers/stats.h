#ifndef STATS_H
#define STATS_H

#include "jsonHandler.h"

/**
 * @brief Imprime el top N de libros (nombre) mas prestados con su cantidad.
 * @param loans Array de prestamos ya parseado.
 * @param loanCount Numero de prestamos.
 * @param topN Cantidad de posiciones a mostrar (ej. 3).
 */
void printTopBooksLoaned(struct Loan *loans, int loanCount, int topN);

/**
 * @brief Imprime el top N de usuarios con mas prestamos con su cantidad.
 * @param loans Array de prestamos ya parseado.
 * @param loanCount Numero de prestamos.
 * @param users Array de usuarios ya parseado.
 * @param userCount Numero de usuarios.
 * @param topN Cantidad de posiciones a mostrar (ej. 3).
 */
void printTopUsersLoaned(struct Loan *loans, int loanCount, struct User *users, int userCount, int topN);

/**
 * @brief Imprime el top N de mes-anio con mayor monto recaudado.
 * @param loans Array de prestamos ya parseado.
 * @param loanCount Numero de prestamos.
 * @param topN Cantidad de posiciones a mostrar (ej. 5).
 */
void printTopMonthsRevenue(struct Loan *loans, int loanCount, int topN);

/**
 * @brief Imprime el genero con mas prestamos y el genero con menos prestamos
 * @param loans Array de prestamos ya parseado.
 * @param loanCount Numero de prestamos.
 * @param books Array de libros ya parseado.
 * @param bookCount Numero de libros.
 */
void printGenreLoanStats(struct Loan *loans, int loanCount, struct Book *books, int bookCount);

/**
 * @brief Imprime todas las estadisticas del sistema.
 */
void printStats(void);

#endif // STATS_H