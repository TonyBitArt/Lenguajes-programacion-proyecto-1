#include <stdio.h>
#include "../headers/catalog.h"
#include "../headers/inputUtils.h"

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
            case CATALOG_MENU_VIEW:
                printf("\n Ejemplares del catálogo...\n");
                break;
                
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