#include <stdio.h>
#include "menu.h"
#include "catalog.h"

int displayMainMenu(void) {
    int selection;
    
    printf("\n========================================\n");
    printf("      SISTEMA DE GESTIÓN DE BIBLIOTECA\n");
    printf("========================================\n");
    printf("%d. Menú de funciones operativas\n", MAIN_MENU_OPERATIONAL);
    printf("%d. Menú de funciones generales\n", MAIN_MENU_GENERAL);
    printf("%d. Salir\n", MAIN_MENU_EXIT);
    printf("========================================\n");
    printf("Seleccione una opción: ");
    
    scanf("%d", &selection);
    
    return selection;
}

void handleOperationalOptions(void) {
    int selectedOption;
    
    do {
        printf("\n--- Menú de funciones operativas ---\n");
        printf("%d. Gestión de catálogo\n", OPERATIONAL_MENU_CATALOG);
        printf("%d. Gestión de usuarios\n", OPERATIONAL_MENU_USERS);
        printf("%d. Historial de préstamos\n", OPERATIONAL_MENU_HISTORY);
        printf("%d. Vencimiento de préstamos\n", OPERATIONAL_MENU_EXPIRATION);
        printf("%d. Estadísticas\n", OPERATIONAL_MENU_STATISTICS);
        printf("%d. Volver\n", OPERATIONAL_MENU_BACK);
        printf("Seleccione una opción: ");
        
        scanf("%d", &selectedOption);
        
        switch (selectedOption) {
            case OPERATIONAL_MENU_CATALOG:
                handleCatalogOptions();
                break;
                
            case OPERATIONAL_MENU_USERS:
                printf("\n Gestión de usuarios...\n");
                break;
                
            case OPERATIONAL_MENU_HISTORY:
                printf("\n Historial de préstamos...\n");
                break;
                
            case OPERATIONAL_MENU_EXPIRATION:
                printf("\n Vencimiento de préstamos...\n");
                break;
                
            case OPERATIONAL_MENU_STATISTICS:
                printf("\n Estadísticas...\n");
                break;
                
            case OPERATIONAL_MENU_BACK:
                printf("\n Volviendo al menú principal...\n");
                break;
                
            default:
                printf("\n Opción inválida, por favor seleccione una opción válida\n");
                break;
        }
        
    } while (selectedOption != OPERATIONAL_MENU_BACK);
}

void handleGeneralOptions(void) {
    int selectedOption;
    
    do {
        printf("\n--- Menú de funciones generales ---\n");
        printf("%d. Búsqueda simple\n", GENERAL_MENU_SIMPLE_SEARCH);
        printf("%d. Búsqueda avanzada\n", GENERAL_MENU_ADVANCED_SEARCH);
        printf("%d. Préstamo de ejemplares\n", GENERAL_MENU_LOAN);
        printf("%d. Devolución de ejemplares\n", GENERAL_MENU_RETURN);
        printf("%d. Volver\n", GENERAL_MENU_BACK);
        printf("Seleccione una opción: ");
        
        scanf("%d", &selectedOption);
        
        switch (selectedOption) {
            case GENERAL_MENU_SIMPLE_SEARCH:
                printf("\n Búsqueda simple...\n");
                break;
                
            case GENERAL_MENU_ADVANCED_SEARCH:
                printf("\n Búsqueda avanzada...\n");
                break;
                
            case GENERAL_MENU_LOAN:
                printf("\n Préstamo de ejemplares...\n");
                break;
                
            case GENERAL_MENU_RETURN:
                printf("\n Devolución de ejemplares...\n");
                break;
                
            case GENERAL_MENU_BACK:
                printf("\n Volviendo al menú principal...\n");
                break;
                
            default:
                printf("\n Opción inválida, por favor seleccione una opción válida\n");
                break;
        }
        
    } while (selectedOption != GENERAL_MENU_BACK);
}