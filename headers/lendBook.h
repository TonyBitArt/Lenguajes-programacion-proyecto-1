#ifndef LENDBOOK_H
#define LENDBOOK_H

int lendBook(char *bookName, char *loanDate, char *returnDate, char *userID);

/**
 * @brief Registra un préstamo y devuelve su identificador generado.
 * @param loanID Puntero donde se almacenará el identificador del préstamo.
 * @return 0 si fue exitoso, o un código negativo si ocurrió un error.
 */
int lendBookWithID(char *bookName, char *loanDate, char *returnDate,
				   char *userID, int *loanID);

/**
 * @brief Solicita los datos al usuario y registra un préstamo.
 */
void handleLendBook(void);

#endif // LENDBOOK_H