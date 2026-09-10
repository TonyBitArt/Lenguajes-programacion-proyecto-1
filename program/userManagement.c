/**
 * @file userManagement.c
 * @brief Archivo que contiene la implementación de la gestión de usuarios.
 */


// Includes de la librería estándar
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Includes de los archivos de cabecera del proyecto
#include "../headers/userManagement.h"
#include "../headers/jsonHandler.h"
#include "../headers/userUtils.h"
#include "../headers/inputUtils.h"
#include "../headers/config.h"


/**
 * @brief Busca y muestra todos los usuarios registrados.
 * @return void
 */
void searchAllUsers() {
    struct User *users = NULL;
    int userCount = 0;

    if (!getAllUsers(USERS_FILE_PATH, &users, &userCount)) {
        printf("Error: No se pudo leer el archivo JSON.\n");
        pauseScreen();
        return;
    }

    if (userCount == 0) {
        printf("No hay usuarios registrados.\n");
    } else {
        printAllUsers(users, userCount);
    }

    freeAllUsers(users, userCount);
    pauseScreen();
}


/**
 * @brief Busca un usuario por su ID.
 * @return void
 */
void searchUserByID() {
    do {
        clearScreen();
        searchUserMessage();

        printf("Ingrese el ID del usuario a buscar: ");
        int userID = validateInt();

        if (userID == 0) {
            clearScreen();
            return;
        }

        if (validateID(userID) == 0) {
            pauseScreen();
            continue;
        }

        struct User *user = getUserByID(USERS_FILE_PATH, userID);

        if (user == NULL) {
            printf("Usuario con ID %d no encontrado.\n", userID);
        } else {
            printUser(*user);
            freeUser(user);
            free(user);
        }

        pauseScreen();

    } while(1);
}



/**
 * @brief Muestra el menú de búsqueda de usuarios.
 * @return void
 */
void searchUserMenu() {
    do {
        clearScreen();
        printSearchUserOptions();

        int input = validateInt();
        
        if (input == -1) {
            printf("Error: Entrada inválida.\n");
            pauseScreen();
            continue;
        }

        switch (input) {
            case 1:
                searchAllUsers();
                break;
            
            case 2:
                searchUserByID();
                break;

            case 3:
                return;
            
            default:
                printf("Error: Opcion ingresada invalida\n");
                pauseScreen();
                break;
            }

    } while(1);
}


/**
 * @brief Agrega un nuevo usuario al sistema.
 * Solicita al usuario que ingrese los datos del nuevo usuario y los guarda en un archivo JSON.
 * 
 * @return void
 */
void addUser() {
    char *userName = NULL;
    char *userLastName = NULL;
    char *userAddress = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        addUserMessage();

        printf("Numero de identificacion: ");
        int userID = validateInt();

        if (userID == 0) {
            clearScreen();
            return;
        }

        if (validateID(userID) == 0 || existsUser(USERS_FILE_PATH, userID)) {
            pauseScreen();
            continue;
        }

        userName = validateUserInput("Nombre: ", &cancelFlag);

        if (!cancelFlag) {
            userLastName = validateUserInput("Apellido: ", &cancelFlag);
        }
        
        if (!cancelFlag) {
            userAddress = validateUserInput("Direccion: ", &cancelFlag);
        }

        if (cancelFlag) {
            free(userName);
            free(userLastName);
            free(userAddress);
            clearScreen();
            return;
        }

        struct User newUser = createUser(userID, userName, userLastName, userAddress);

        if (!saveUser(USERS_FILE_PATH, newUser)) {
            printf("Error: No se pudo guardar el usuario en el archivo JSON.\n");
        } else {
            printf("Usuario guardado exitosamente en el archivo JSON.\n");
        }

        freeUser(&newUser);
        pauseScreen();
        clearScreen();

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
                searchUserMenu();
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