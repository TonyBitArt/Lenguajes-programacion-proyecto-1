#ifndef ADVANCED_SEARCH_H
#define ADVANCED_SEARCH_H

/**
 * @brief Reliza una búsqueda avanzada de libros.
 * @param searchValues Puntero al arreglo de valores a buscar dependiendo dependiendo del filtro.
 * @param techniques Puntero a arreglo de técnicas a utilizar dependiendo del filtro.
 * @return void
 */
void advancedSearch(char **searchValues, char **techniques);

/**
 * @brief Solicita filtros al usuario y ejecuta una búsqueda avanzada.
 */
void handleAdvancedSearch(void);

#endif // ADVANCED_SEARCH_H