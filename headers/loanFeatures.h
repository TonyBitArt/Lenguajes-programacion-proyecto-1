#ifndef LOAN_FEATURES_H
#define LOAN_FEATURES_H

#include "../headers/jsonHandler.h"


/**
 * @brief Muestra el historial de préstamos.
 * @param loans Un puntero a un array de estructuras Loan.
 * @param loanCount El número de préstamos en el array.
 * @return void
 */
void loanHistory(struct Loan* loans, int loanCount);


/**
 * @brief Muestra los préstamos que están vencidos o próximos a vencer.
 * @param loans Un puntero a un array de estructuras Loan.
 * @param loanCount El número de préstamos en el array.
 * @return void
 */
void printExpiringLoans(struct Loan* loans, int loanCount);


/**
 * @brief Ejecuta una función de característica de préstamo.
 * @param featureFunction Un puntero a la función que implementa la característica de préstamo.
 * @return void
 */
void executeLoanFeature(void (*featureFunction)(struct Loan *, int));


#endif // LOAN_FEATURES_H

