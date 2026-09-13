#ifndef SIMPLE_SEARCH_H
#define SIMPLE_SEARCH_H

/**
 * @brief Realiza una búsqueda simple de libros por nombre.
 * @param searchValue El valor a buscar en los nombres de los libros.
 * @return void
 */
void simpleSearch(const char *searchValue);

/**
 * @brief Solicita al usuario un texto y ejecuta una búsqueda simple.
 */
void handleSimpleSearch(void);

#endif // SIMPLE_SEARCH_H