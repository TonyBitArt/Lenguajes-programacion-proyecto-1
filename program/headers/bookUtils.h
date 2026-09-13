#ifndef BOOKUTILS_H
#define BOOKUTILS_H

/**
 * @brief Libera la memoria asignada para un arreglo de libros.
 * @param books Puntero al arreglo de libros.
 * @param bookCount Cantidad de libros en el arreglo.
 * @return void
 */
void freeAllBooks(struct Book *books, int bookCount);

/**
 * @brief Edita la cantidad de un libro en el archivo JSON de libros.
 * @param bookName El nombre del libro a editar.
 * @param change La cantidad a sumar o restar a la cantidad actual del libro.
 * @return void
 */
void editBookQuantity(char *bookName, int change);

#endif // BOOKUTILS_H