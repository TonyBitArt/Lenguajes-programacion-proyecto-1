#ifndef RETURNBOOK_H
#define RETURNBOOK_H

/**
 * @brief Devuelve un libro prestado.
 * @param loanID El ID del préstamo a devolver.
 * @param actualReturnDate La fecha real de devolución del libro.
 * @return int 1 si la devolución fue exitosa, 0 si hubo un error
 */
int returnBook(int loanID, const char *actualReturnDate);

/**
 * @brief Solicita los datos al usuario y registra una devolución.
 */
void handleReturnBook(void);

#endif // RETURNBOOK_H