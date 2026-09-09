#include <stdio.h>
#include "../headers/menu.h"
#include "../headers/inputUtils.h"



int main() {
    int selectedOption;
    
    /* 
     * ciclo do-while que muestra el menú después de cada opción realizada, 
     * excepto la opción de (Salir)
     */
    do {
        selectedOption = displayMainMenu();
        
        switch (selectedOption) {
            case MAIN_MENU_OPERATIONAL:
                handleOperationalOptions();
                break;
                
            case MAIN_MENU_GENERAL:
                handleGeneralOptions();
                break;
                
            case MAIN_MENU_EXIT:
                printf("\n Saliendo del sistema...\n");
                break;
                
            default:
                printf("\n Opción inválida, por favor seleccione una opción válida\n");
                break;
        }
        
    } while (selectedOption != MAIN_MENU_EXIT);
    
    return 0;
}