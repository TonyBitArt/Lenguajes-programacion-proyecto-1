#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/inputUtils.h"
#include "../headers/simpleSearch.h"

void handleSimpleSearch(void) {
    char *searchValue;

    clearScreen();
    printf("\n--- Búsqueda simple ---\n");
    printf("Ingrese el texto a buscar (0 para volver): ");

    searchValue = readInput();

    if (searchValue == NULL) {
        printf("Error: No se pudo leer la búsqueda.\n");
        pauseScreen();
        return;
    }

    if (strcmp(searchValue, "0") == 0) {
        free(searchValue);
        return;
    }

    if (isEmptyString(searchValue)) {
        printf("Error: No se puede ingresar una búsqueda vacía.\n");
        free(searchValue);
        pauseScreen();
        return;
    }

    simpleSearch(searchValue);
    free(searchValue);
    pauseScreen();
}