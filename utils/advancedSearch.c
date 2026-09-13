#include "../headers/jsonHandler.h"
#include <stdio.h>
#include <string.h>

static void printBook(struct Book *book) {
    printf("-------------------------\n");
    printf("Nombre: %s\n", book->name);
    printf("Resumen: %s\n", book->summary);
    printf("-------------------------\n");
}

void advancedSearch(char **searchValues, char **techniques) {
    int bookCount;
    struct Book *books = parseBooks("./data/books.json", &bookCount);

    for (int i = 0; i < 4; i++) {
        if (!techniques[i]) continue;

        for (int k = 0; k < bookCount; k++) {

            if (i == 0) { // Buscando filtros de nombre

                if (strcmp(techniques[i], "contains") == 0) {
                    if (strstr(books[k].name, searchValues[i]) != NULL) {
                        printBook(&books[k]);
                    }
                }

                else if (strcmp(techniques[i], "exact") == 0) {
                    if (strcmp(books[k].name, searchValues[i]) == 0) {
                        printBook(&books[k]);
                    }
                }
            }

            else if (i == 1) { // Buscando filtros de autor

                if (strcmp(techniques[i], "contains") == 0) {
                    if (strstr(books[k].author, searchValues[i]) != NULL) {
                        printBook(&books[k]);
                    }
                }

                else if (strcmp(techniques[i], "exact") == 0) {
                    if (strcmp(books[k].author, searchValues[i]) == 0) {
                        printBook(&books[k]);
                    }
                }
            }

            else if (i == 2) { // Buscando filtros de género

                if (strcmp(techniques[i], "contains") == 0) {
                    if (strstr(books[k].genre, searchValues[i]) != NULL) {
                        printBook(&books[k]);
                    }
                }

                else if (strcmp(techniques[i], "exact") == 0) {
                    if (strcmp(books[k].genre, searchValues[i]) == 0) {
                        printBook(&books[k]);
                    }
                }
            }

            else if (i == 3) { // Buscando filtros de resumen

                if (strcmp(techniques[i], "contains") == 0) {
                    if (strstr(books[k].summary, searchValues[i]) != NULL) {
                        printBook(&books[k]);
                    }
                }

                else if (strcmp(techniques[i], "exact") == 0) {
                    if (strcmp(books[k].summary, searchValues[i]) == 0) {
                        printBook(&books[k]);
                    }
                }
            }
        }
        
    }

    freeBooks(books, bookCount);
}