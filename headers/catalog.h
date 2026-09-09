#ifndef CATALOG_H
#define CATALOG_H

/* macros del preprocesador para las opciones del catálogo */
#define CATALOG_MENU_VIEW 1
#define CATALOG_MENU_ADD 2
#define CATALOG_MENU_EDIT 3
#define CATALOG_MENU_BACK 4

/**
 * @brief muestra el menú de catálogo y toma la opción del usuario
 * Entradas: ninguna
 * Salidas: un int que es la opción seleccionada por el usuario
 * Restricciones: solo acepta números enteros
 */
int displayCatalogMenu(void);

/**
 * @brief controlador para la gestión de catálogo
 * Entradas: ninguna
 * Salidas: ninguna
 */
void handleCatalogOptions(void);

#endif