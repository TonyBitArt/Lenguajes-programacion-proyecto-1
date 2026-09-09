#include <stdio.h>
#include <stdlib.h>
#include "../headers/catalog.h"
#include "../headers/inputUtils.h"
#include "../headers/jsonHandler.h"

int displayCatalogMenu(void) {
    printf("\n--- Submenú de Gestión de Catálogo ---\n");
    printf("%d. Ver ejemplares\n", CATALOG_MENU_VIEW);
    printf("%d. Agregar ejemplar\n", CATALOG_MENU_ADD);
    printf("%d. Editar ejemplar\n", CATALOG_MENU_EDIT);
    printf("%d. Volver\n", CATALOG_MENU_BACK);
    printf("Seleccione una opción: ");
    
    return validateInt();
}

void handleCatalogOptions(void) {
    int selectedOption;
    
    do {
        selectedOption = displayCatalogMenu();
        
        switch (selectedOption) {
            case CATALOG_MENU_VIEW:{
                int bookCount = 0;
                struct Book *books = parseBooks("data/books.json", &bookCount);

                if (!books || bookCount == 0) {
                    printf("\n No hay libros registrados \n");
                    break;
                }
                
                printf("\n---- LISTA DE LIBROS (%d) ----\n", bookCount);
                for (int i = 0; i < bookCount; i++) {
                    printf("Libro %d:\n", i + 1);
                    printf("  Nombre: %s\n", books[i].name);
                    printf("  Autor: %s\n", books[i].author);
                    printf("  Año: %d\n", books[i].year);
                    printf("  Género: %s\n", books[i].genre);
                    printf("  Resumen: %s\n", books[i].summary);
                    printf("  Cantidad: %d\n", books[i].quantity);
                    printf("-----------------------------\n");
                }
                
                free(books);
                break;
            }
                
            case CATALOG_MENU_ADD:
                printf("\n Agregar ejemplar...\n");
                break;
                
            case CATALOG_MENU_EDIT:
                printf("\n Editar ejemplar...\n");
                break;
                
            case CATALOG_MENU_BACK:
                printf("\n Volviendo al menú operativo...\n");
                break;
                
            default:
                printf("\n Opción inválida, por favor seleccione una opción válida\n");
                break;
        }
        
    } while (selectedOption != CATALOG_MENU_BACK);
}