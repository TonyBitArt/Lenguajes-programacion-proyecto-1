#ifndef MENU_H
#define MENU_H

/* macros del preprocesador para las opciones del menú principal */
#define MAIN_MENU_OPERATIONAL 1
#define MAIN_MENU_GENERAL 2
#define MAIN_MENU_EXIT 3

/* macros del preprocesador para las opciones del menú operativo */
#define OPERATIONAL_MENU_CATALOG 1
#define OPERATIONAL_MENU_USERS 2
#define OPERATIONAL_MENU_HISTORY 3
#define OPERATIONAL_MENU_EXPIRATION 4
#define OPERATIONAL_MENU_STATISTICS 5
#define OPERATIONAL_MENU_BACK 6

/* macros del preprocesador para el menú de opciones generales */
#define GENERAL_MENU_SIMPLE_SEARCH 1
#define GENERAL_MENU_ADVANCED_SEARCH 2
#define GENERAL_MENU_LOAN 3
#define GENERAL_MENU_RETURN 4
#define GENERAL_MENU_BACK 5

/**
 * @brief muestra el menú principal y toma la opción del usuario
 * Entradas: niguna
 * Salidas: un int que es la opción seleccionada por el usuario
 * Restricciones: solo acepta números enteros
 */
int displayMainMenu(void);

/**
 * @brief controlador para el submenú de funciones operativas
 * Entradas: ninguna
 * Salidas: ninguna
 */
void handleOperationalOptions(void);

/**
 * @brief controlador para el submenú de opciones generales
 * Entradas: ninguna
 * Salidas: ninguna
 */
void handleGeneralOptions(void);

#endif