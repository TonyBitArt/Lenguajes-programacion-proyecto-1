#include "../headers/jsonHandler.h"
#include "../headers/bookUtils.h"
#include "../headers/simpleSearch.h"
#include <stdio.h>
#include <string.h>


void simpleSearch(const char *searchValue) {
    int bookCount;
    struct Book *books = parseBooks("./data/books.json", &bookCount);

    printf("Resultados de la búsqueda para \"%s\":\n", searchValue);

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].name, searchValue) != NULL ||
            strstr(books[i].author, searchValue) != NULL ||
            strstr(books[i].summary, searchValue) != NULL) {

            printf("-------------------------\n");
            printf("Nombre: %s\n", books[i].name);
            printf("Resumen: %s\n", books[i].summary);
            printf("Disponibilidad: %s\n", books[i].quantity > 0 ? "Disponible" : "No disponible");
            printf("-------------------------\n");
        }
    }

    freeAllBooks(books, bookCount);
}