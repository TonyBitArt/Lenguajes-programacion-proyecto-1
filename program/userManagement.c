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
    struct User* users = NULL;
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

        struct User* user = getUserByID(USERS_FILE_PATH, userID);

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
 * @brief Modifica un usuario existente en el sistema.
 * Solicita al usuario que ingrese el ID del usuario a modificar y los nuevos datos.
 * 
 * @return void
 */
void modifyUser() {
    char* userID = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        printModifyUserMessage();

        userID = validateUserInput("Ingrese el ID del usuario a modificar: ", &printModifyUserMessage, &cancelFlag);

        if (cancelFlag) {
            free(userID);
            return;
        }

        if (validateID(userID) == 0) {
            pauseScreen();
            free(userID);
            continue;
        }

        struct User* user = getUserByID(USERS_FILE_PATH, userID);

        if (user == NULL) {
            printf("Usuario con ID %s no encontrado.\n", userID);
            pauseScreen();
            clearScreen();
            free(user);
            continue;
        }

        modifyUserData(USERS_FILE_PATH, user);
        free(user);
        return;

    } while(cancelFlag == 0);
}


/**
 * @brief Elimina un usuario existente en el sistema.
 * Solicita al usuario que ingrese el ID del usuario a eliminar y lo elimina del archivo JSON.
 * 
 * @return void
 */
void deleteUser() {
    char* userID = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        printDeleteUserMessage();

        userID = validateUserInput("Ingrese el ID del usuario a eliminar: ", &printDeleteUserMessage, &cancelFlag);

        if (cancelFlag) {
            free(userID);
            return;
        }

        if (validateID(userID) == 0) {
            pauseScreen();
            free(userID);
            continue;
        }

        struct User* user = getUserByID(USERS_FILE_PATH, userID);

        if (user == NULL) {
            printf("Usuario con ID %s no encontrado.\n", userID);
            pauseScreen();
            clearScreen();
            free(user);
            continue;
        }

        if (!deleteUserByID(USERS_FILE_PATH, userID)) {
            printf("Error: No se pudo eliminar el usuario del archivo JSON.\n");
        } else {
            printf("Usuario eliminado exitosamente del archivo JSON.\n");
        }

        free(user);
        free(userID);
        pauseScreen();
        clearScreen();
        return;

    } while(cancelFlag == 0);
}


/**
 * @brief Muestra el menú de opciones de gestión de usuarios y maneja la interacción del usuario.
 * @return void
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
                modifyUser();
                break;
            
            case 4:
                deleteUser();
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