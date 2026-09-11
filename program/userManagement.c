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

//============================================================================ REFACTOR URGENTE, CAMBIAR LA LOGICA POR CAMBIO DE ARCHIVO, NO POR ID, YA QUE EL ID ES UN STRING Y NO UN INT.

/**
 * @brief Busca un usuario por su ID.
 * @return void
 */
void searchUserByID() {
    char* userID = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        searchUserMessage();

        userID = validateUserInput("Ingrese el ID del usuario a buscar: ", &searchUserMessage, &cancelFlag);

        if (cancelFlag) {
            free(userID);
            return;
        }

        if (validateID(userID) == 0) {
            pauseScreen();
            free(userID);
            continue;
        }

        struct User *user = getUserByID(USERS_FILE_PATH, userID);

        if (user == NULL) {
            printf("Usuario con ID %s no encontrado.\n", userID);
        } else {
            printUser(*user);
            freeUserData(user);
            free(user);
        }

        pauseScreen();
        free(userID);

    } while(cancelFlag == 0);
}

// ================================= VALIDAR REFACTOR DE SEARUSER BY ID 



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
    char* userID = NULL;
    char* userName = NULL;
    char* userLastName = NULL;
    char* userAddress = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        addUserMessage();

        userID = validateUserInput("Numero de identificacion: ", &addUserMessage, &cancelFlag);

        if (cancelFlag) {
            clearScreen();
            return;
        }

        if (validateID(userID) == 0 || existsUser(USERS_FILE_PATH, userID)) {
            pauseScreen();
            free(userID);
            continue;
        }

        userName = validateUserInput("Nombre: ", &addUserMessage, &cancelFlag);

        if (!cancelFlag) {
            userLastName = validateUserInput("Apellido: ", &addUserMessage, &cancelFlag);
        }
        
        if (!cancelFlag) {
            userAddress = validateUserInput("Direccion: ", &addUserMessage, &cancelFlag);
        }

        if (cancelFlag) {
            if (userID) free(userID);
            if (userName) free(userName);
            if (userLastName) free(userLastName);
            if (userAddress) free(userAddress);
            clearScreen();
            return;
        }

        struct User newUser = createUser(userID, userName, userLastName, userAddress);

        if (!saveUser(USERS_FILE_PATH, newUser)) {
            printf("Error: No se pudo guardar el usuario en el archivo JSON.\n");
        } else {
            printf("Usuario guardado exitosamente en el archivo JSON.\n");
        }

        freeUserData(&newUser);
        free(userID);
        free(userName);
        free(userLastName);
        free(userAddress);
        
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