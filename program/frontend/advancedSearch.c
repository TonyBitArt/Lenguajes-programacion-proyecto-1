#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/advancedSearch.h"
#include "../headers/inputUtils.h"

static void freeSearchData(char **searchValues, char **techniques) {
    for (int i = 0; i < 4; i++) {
        free(searchValues[i]);
        free(techniques[i]);
    }
}

void handleAdvancedSearch(void) {
    char *searchValues[4] = {NULL, NULL, NULL, NULL};
    char *techniques[4] = {NULL, NULL, NULL, NULL};
    const char *fieldNames[] = {"nombre", "autor", "género", "resumen"};
    int selectedOption;

    do {
        clearScreen();
        printf("\n--- Búsqueda avanzada ---\n");
        for (int i = 0; i < 4; i++) {
            printf("%d. Filtrar por %s%s\n", i + 1, fieldNames[i],
                   techniques[i] ? " (configurado)" : "");
        }
        printf("5. Buscar\n");
        printf("6. Cancelar\n");
        printf("Seleccione una opción: ");

        selectedOption = validateInt();

        if (selectedOption >= 1 && selectedOption <= 4) {
            int techniqueOption;

            printf("\nIngrese el valor para %s (0 para cancelar): ",
                   fieldNames[selectedOption - 1]);
            char *value = readInput();

            if (value == NULL) {
                printf("Error: No se pudo leer el valor de búsqueda.\n");
                pauseScreen();
                continue;
            }

            if (strcmp(value, "0") == 0) {
                free(value);
                continue;
            }

            if (isEmptyString(value)) {
                printf("Error: No se puede ingresar un valor vacío.\n");
                free(value);
                pauseScreen();
                continue;
            }

            printf("1. Contiene\n");
            printf("2. Coincidencia exacta\n");
            printf("Seleccione la técnica: ");
            techniqueOption = validateInt();

            if (techniqueOption != 1 && techniqueOption != 2) {
                printf("Error: Técnica inválida.\n");
                free(value);
                pauseScreen();
                continue;
            }

            const char *technique = techniqueOption == 1 ? "contains" : "exact";

            free(searchValues[selectedOption - 1]);
            free(techniques[selectedOption - 1]);
            searchValues[selectedOption - 1] = value;
            techniques[selectedOption - 1] = malloc(strlen(technique) + 1);

            if (techniques[selectedOption - 1] == NULL) {
                free(searchValues[selectedOption - 1]);
                searchValues[selectedOption - 1] = NULL;
                printf("Error: No se pudo asignar memoria.\n");
                pauseScreen();
                continue;
            }

            strcpy(techniques[selectedOption - 1], technique);
        } else if (selectedOption == 5) {
            int hasFilters = 0;

            for (int i = 0; i < 4; i++) {
                if (techniques[i] != NULL) {
                    hasFilters = 1;
                    break;
                }
            }

            if (!hasFilters) {
                printf("Error: Configure al menos un filtro.\n");
                pauseScreen();
                continue;
            }

            advancedSearch(searchValues, techniques);
            freeSearchData(searchValues, techniques);
            pauseScreen();
            return;
        } else if (selectedOption == 6) {
            freeSearchData(searchValues, techniques);
            return;
        } else {
            printf("Error: Opción inválida.\n");
            pauseScreen();
        }
    } while (1);
}