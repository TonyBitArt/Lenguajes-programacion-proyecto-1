#ifndef BOOKUTILS_H
#define BOOKUTILS_H

/**
 * @brief Libera la memoria asignada para un arreglo de libros.
 * @param books Puntero al arreglo de libros.
 * @param bookCount Cantidad de libros en el arreglo.
 * @return void
 */
void freeAllBooks(struct Book *books, int bookCount);

#endif // BOOKUTILS_H