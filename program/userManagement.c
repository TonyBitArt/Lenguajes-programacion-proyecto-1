#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/userManagement.h"
#include "../headers/inputUtils.h"
#include "../headers/jsonHandler.h"



/**
 * @brief Muestra las opciones de gestión de usuarios.
 * @return void
 */
void printUserOptions() {
    printf("\n========================================\n");
    printf("          GESTIÓN DE USUARIOS\n");
    printf("========================================\n");
    printf("1. Ver usuarios\n");
    printf("2. Agregar usuario\n");
    printf("3. Modificar usuario\n");
    printf("4. Eliminar usuario\n");
    printf("5. Volver\n");
    printf("========================================\n");
    printf("Seleccione una opción: ");
}


/**
 * @brief Muestra el mensaje de agregar un nuevo usuario.
 * @return void
 */
void addUserMessage() {
    printf("\n========================================\n");
    printf("          AGREGAR NUEVO USUARIO\n");
    printf("========================================\n");
    printf("Datos solicitados:\n");
    printf("- Número de identificación\n");
    printf("- Nombre completo\n");
    printf("- Dirección\n");
    printf("Escriba 0 en cualquier campo para volver.\n");
    printf("========================================\n");
}


/**
 * @brief Agrega un nuevo usuario al sistema.
 * Solicita al usuario que ingrese los datos del nuevo usuario y los guarda en un archivo JSON.
 * 
 * @return void
 */
void addUser() {
    do {
        clearScreen();
        addUserMessage();

        printf("Ingrese los datos del nuevo usuario:\n");

        printf("Numero de identificacion: ");
        int userID = validateInt();

        if (validateID(userID) == 0) {
            pauseScreen();
            continue;
        }

        if (userID == 0) {
            clearScreen();
            return;
        }

        printf("Nombre: ");
        char *userName = readInput();

        if (userName == NULL) {
            printf("Error: No se pudo asignar memoria.\n");
            pauseScreen();
            return;
        }

        if (strcmp(userName, "0") == 0) {
            free(userName);
            clearScreen();
            return;
        }

        if (isEmptyString(userName)) {
            printf("Error: No se puede ingresar un campo vacío.\n");
            free(userName);
            pauseScreen();
            continue;
        }

        printf("Apellido: ");
        char *userLastName = readInput();

        if (userLastName == NULL) {
            printf("Error: No se pudo asignar memoria.\n");
            free(userName);
            pauseScreen();
            return;
        }

        if (strcmp(userLastName, "0") == 0) {
            free(userName);
            free(userLastName);
            clearScreen();
            return;
        }

        if (isEmptyString(userLastName)) {
            printf("Error: No se puede ingresar un campo vacío.\n");
            free(userName);
            free(userLastName);
            pauseScreen();
            continue;
        }

        printf("Direccion: ");
        char *userAddress = readInput();

        if (userAddress == NULL) {
            printf("Error: No se pudo asignar memoria.\n");
            free(userName);
            free(userLastName);
            pauseScreen();
            return;
        }

        if (strcmp(userAddress, "0") == 0) {
            free(userName);
            free(userLastName);
            free(userAddress);
            clearScreen();
            return;
        }

        if (isEmptyString(userAddress)) {
            printf("Error: No se puede ingresar un campo vacío.\n");
            free(userName);
            free(userAddress);
            free(userLastName);
            pauseScreen();
            continue;
        }

        struct User newUser;
        newUser.ID = userID;
        newUser.name = userName;
        newUser.lastName = userLastName;
        newUser.address = userAddress;

        if (!saveUser("./data/users.json", newUser)) {
            printf("Error: No se pudo guardar el usuario en el archivo JSON.\n");
        } else {
            printf("Usuario guardado exitosamente en el archivo JSON.\n");
        }

        pauseScreen();
        clearScreen();

        free(userName);
        free(userLastName);
        free(userAddress);
        
        return;
    } while (1);
}


/**
 * @brief Muestra las opciones de gestión de usuarios.
 */
void userOptions() {
    do {
        clearScreen();
        printUserOptions();
        int input = validateInt();
        
        if (input == -1) {
            printf("Error: Entrada inválida.\n");
            pauseScreen();
            continue;
        }

        switch (input) {
            case 1:
                printf("selecciono la opcion ver usuarios");
                break;
            
            case 2:
                addUser();
                break;

            case 3:
                printf("selecciono la opcion modificar usuarios");
                break;
            
            case 4:
                printf("selecciono la opcion ver usuarios");
                break;

            case 5:
                return;

            default:
                printf("Error: Opcion ingresada invalida\n");
                pauseScreen();
                break;
            }

    } while(1);

    clearScreen();
}