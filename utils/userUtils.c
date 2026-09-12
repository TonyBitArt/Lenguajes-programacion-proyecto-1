// Includes de la librería estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Includes de los archivos de cabecera del proyecto
#include "../headers/inputUtils.h"
#include "../headers/userUtils.h"


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
    printf("Ingrese los datos del nuevo usuario:\n");
}


/**
 * @brief Muestra el mensaje de búsqueda de usuario por ID.
 * @return void
 */
void searchUserMessage() {
    printf("\n========================================\n");
    printf("          BUSCAR USUARIO POR ID\n");
    printf("========================================\n");
    printf("Ingrese el ID del usuario a buscar.\n");
    printf("Escriba 0 para volver.\n");
    printf("========================================\n");
}


/**
 * @brief Muestra las opciones de búsqueda de usuario.
 * @return void
 */
void printSearchUserOptions() {
    printf("\n========================================\n");
    printf("          BUSCAR USUARIO\n");
    printf("========================================\n");
    printf("1. Ver todos los usuarios\n");
    printf("2. Buscar por ID\n");
    printf("3. Volver\n");
    printf("========================================\n");
    printf("Seleccione una opción: ");
}


/**
 * @brief Muestra la información de un usuario.
 * @param user El usuario a mostrar.
 * @return void
 */
void printUser(struct User user) {
    printf("\n========================================\n");
    printf("          INFORMACIÓN DEL USUARIO\n");
    printf("========================================\n");
    printf("ID:        %s\n", user.ID);
    printf("Nombre:    %s\n", user.name);
    printf("Apellido:  %s\n", user.lastName);
    printf("Dirección: %s\n", user.address);
    printf("========================================\n");
}


/**
 * @brief Muestra la información de todos los usuarios.
 * @param users Un array de usuarios a mostrar.
 * @param userCount El número de usuarios en el array.
 * @return void
 */
void printAllUsers(struct User *users, int userCount) {
    printf("\n========================================\n");
    printf("          LISTA DE USUARIOS\n");
    printf("========================================\n");
    for (int i = 0; i < userCount; i++) {
        printUser(users[i]);
    }
}


/**
 * @brief Muestra el mensaje de modificación de usuario.
 * @return void
 */
void printModifyUserMessage() {
    printf("\n========================================\n");
    printf("          MODIFICAR USUARIO\n");
    printf("========================================\n");
    printf("Ingrese el ID del usuario que desea modificar.\n");
    printf("Escriba 0 para volver.\n");
    printf("========================================\n");
}


/**
 * @brief Muestra el mensaje de modificación de datos de usuario.
 * @return void
 */
void printModifyUserDataMessage() {
    printf("\n========================================\n");
    printf("     MODIFICAR DETALLES DEL USUARIO\n");
    printf("========================================\n");
    printf("Ingrese los nuevos datos del usuario.\n");
    printf("Escriba 0 en cualquier campo para cancelar.\n");
    printf("========================================\n");
}


/**
 * @brief Muestra el mensaje de eliminación de usuario.
 * @return void
 */
void printDeleteUserMessage() {
    printf("\n========================================\n");
    printf("          ELIMINAR USUARIO\n");
    printf("========================================\n");
    printf("Ingrese el ID del usuario que desea eliminar.\n");
    printf("Escriba 0 para volver.\n");
    printf("========================================\n");
}


/**
 * @brief Obtiene todos los usuarios de un archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param users Un puntero a un array de estructuras User.
 * @param userCount Un puntero a un entero que se llenará con el número de usuarios en el archivo.
 * @return struct User* Un array de estructuras User. NULL si ocurre un error.
 */
struct User* getAllUsers(const char* path, struct User** users, int* userCount) {
    *users = parseUsers(path, userCount);
    return *users;
}


/**
 * @brief Crea un nuevo usuario.
 * @param ID El ID del usuario.
 * @param name El nombre del usuario.
 * @param lastName El apellido del usuario.
 * @param address La dirección del usuario.
 * @return struct User La estructura del nuevo usuario creado.
 */
struct User createUser(char* ID, const char* name, const char* lastName, const char* address) {
    struct User newUser;
    newUser.ID = strdup(ID);
    newUser.name = strdup(name);
    newUser.lastName = strdup(lastName);
    newUser.address = strdup(address);
    return newUser;
}


/**
 * @brief Libera la memoria asignada para un usuario.
 * @param user Un puntero al usuario a liberar.
 * @return void
 */
void freeUserData(struct User* user) {
    if (user) {
        free(user->ID);
        free(user->name);
        free(user->lastName);
        free(user->address);
    }
}


/**
 * @brief Libera la memoria asignada para un array de usuarios.
 * @param users Un puntero al array de usuarios a liberar.
 * @param userCount El número de usuarios en el array.
 * @return void
 */
void freeAllUsers(struct User* users, int userCount) {
    for (int i = 0; i < userCount; i++) {
        freeUserData(&users[i]);
    }
    free(users);
}


/**
 * @brief Valida la entrada del usuario.
 * @param message El mensaje a mostrar al usuario.
 * @param funcion Un puntero a la función que se ejecutará si la entrada es inválida.
 * @param cancelFlag Un puntero a un entero que indica si el usuario desea cancelar.
 * @return char* La entrada del usuario.
 */
char* validateUserInput(const char* message, void (*funcion)(), int* cancelFlag) {
    while(1) {
        printf("%s", message);
        char* input = readInput();

        if (input == NULL) {
            printf("Error: No se pudo asignar memoria.\n");
            *cancelFlag = 1;
            return NULL;
        }

        if (strcmp(input, "0") == 0) {
            free(input);
            *cancelFlag = 1;
            return NULL;
        }

        if (isEmptyString(input)) {
            printf("Error: No se puede ingresar un campo vacío.\n");
            pauseScreen();
            clearScreen();
            funcion();
            free(input);
            continue;
        }

        return input;
    }
}


/**
 * @brief obtiene un usuario por su ID
 * @param path la ruta del archivo donde se encuentra el usuario
 * @param userID el ID del usuario a obtener
 * @return struct User* puntero al usuario encontrado, o NULL si no se encuentra
 */
struct User* getUserByID(const char* path, char* userID) {
    int userCount = 0;
    struct User* users = parseUsers(path, &userCount);
    
    if (!users) return NULL;

    struct User* foundUser = NULL;

    for (int i = 0; i < userCount; i++) {
        if (users[i].ID != NULL && strcmp(users[i].ID, userID) == 0 && foundUser == NULL) {
            foundUser = malloc(sizeof(struct User));
            
            if (foundUser) {
                *foundUser = users[i];
                continue;
            }
        }
        
        freeUserData(&users[i]);
    }
    
    free(users);
    return foundUser; 
}


/**
 * @brief Guarda un nuevo usuario en el archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param newUser La estructura del nuevo usuario a guardar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int saveUser(const char* path, struct User newUser) {
    cJSON *usersArray = parseJsonFile(path);
    
    if (!usersArray) {
        usersArray = cJSON_CreateArray();
    }

    cJSON *userObject = cJSON_CreateObject();

    if (!userObject) {
        cJSON_Delete(usersArray);
        return 0;
    }

    cJSON_AddStringToObject(userObject, "name", newUser.name);
    cJSON_AddStringToObject(userObject, "lastName", newUser.lastName);
    cJSON_AddStringToObject(userObject, "ID", newUser.ID);
    cJSON_AddStringToObject(userObject, "address", newUser.address);


    cJSON_AddItemToArray(usersArray, userObject);
    int success = saveJsonToFile(path, usersArray);

    cJSON_Delete(usersArray);
    return success; 
}


/**
 * @brief Verifica si un usuario con un ID específico existe en el archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param userID El ID del usuario a verificar.
 * @return 1 si el usuario existe, 0 si no existe.
 */
int existsUser(const char* path, char* id) {
    struct User* user = getUserByID(path, id);
    
    if (user != NULL) {
        freeUserData(user);
        free(user);

        printf("Error: El ID ya existe en el sistema.\n");
        return 1;
    }
    
    return 0;
}


/**
 * @brief Modifica los detalles de un usuario existente.
 * @param path La ruta del archivo JSON.
 * @param user Un puntero al usuario a modificar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int saveModifiedUser(const char* path, struct User modifiedUser) {
    cJSON* usersArray = parseJsonFile(path);
    
    if (!usersArray) {
        printf("Error: No se pudo leer el archivo JSON.\n");
        return 0;
    }

    int userCount = cJSON_GetArraySize(usersArray);
    int found = 0;

    for (int i = 0; i < userCount; i++) {
        cJSON* userObject = cJSON_GetArrayItem(usersArray, i);
        cJSON* idItem = cJSON_GetObjectItem(userObject, "ID");

        if (cJSON_IsString(idItem) && (idItem->valuestring != NULL) && strcmp(idItem->valuestring, modifiedUser.ID) == 0) {
            
            cJSON_ReplaceItemInObject(userObject, "name", cJSON_CreateString(modifiedUser.name));
            cJSON_ReplaceItemInObject(userObject, "lastName", cJSON_CreateString(modifiedUser.lastName));
            cJSON_ReplaceItemInObject(userObject, "address", cJSON_CreateString(modifiedUser.address));
            
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Error: Usuario con ID %s no encontrado.\n", modifiedUser.ID);
        cJSON_Delete(usersArray);
        return 0;
    }

    int success = saveJsonToFile(path, usersArray);
    cJSON_Delete(usersArray);

    return success; 
}


/**
 * @brief Modifica los detalles de un usuario existente.
 * @param path La ruta del archivo JSON.
 * @param user Un puntero al usuario a modificar.
 * @return void
 */
void modifyUserData(const char* path, struct User* user) {
    char* newUserName = NULL;
    char* newUserLastName = NULL;
    char* newUserAddress = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        printModifyUserDataMessage();
        
        newUserName = validateUserInput("Nuevo nombre: ", &printModifyUserDataMessage, &cancelFlag);

        if (!cancelFlag) {
            newUserLastName = validateUserInput("Nuevo apellido: ", &printModifyUserDataMessage, &cancelFlag);
        }
        
        if (!cancelFlag) {
            newUserAddress = validateUserInput("Nueva direccion: ", &printModifyUserDataMessage, &cancelFlag);
        }

        if (cancelFlag) {
            if (newUserName) free(newUserName);
            if (newUserLastName) free(newUserLastName);
            if (newUserAddress) free(newUserAddress);
            clearScreen();
            return;
        }

        free(user->name);
        free(user->lastName);
        free(user->address);

        user->name = newUserName;
        user->lastName = newUserLastName;
        user->address = newUserAddress;

        printUser(*user);
        
        if (!saveModifiedUser(path, *user)) {
            printf("Error: No se pudo guardar el usuario modificado en el archivo JSON.\n");
        } else {
            printf("Usuario modificado exitosamente en el archivo JSON.\n");
        }

        free(newUserName);
        free(newUserLastName);
        free(newUserAddress);

        pauseScreen();
        clearScreen();
        return;

    } while (1);
}


/**
 * @brief Elimina un usuario por su ID.
 * @param path La ruta del archivo JSON.
 * @param userID El ID del usuario a eliminar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int deleteUserByID(const char* path, char* userID) {
    cJSON* usersArray = parseJsonFile(path);
    
    if (!usersArray) {
        printf("Error: No se pudo leer el archivo JSON.\n");
        return 0;
    }

    int userCount = cJSON_GetArraySize(usersArray);
    int found = 0;

    for (int i = 0; i < userCount; i++) {
        cJSON* userObject = cJSON_GetArrayItem(usersArray, i);
        cJSON* idItem = cJSON_GetObjectItem(userObject, "ID");

        if (cJSON_IsString(idItem) && (idItem->valuestring != NULL) && strcmp(idItem->valuestring, userID) == 0) {
            cJSON_DeleteItemFromArray(usersArray, i);
            found = 1;
            break;
        }
    }


    if (!found) {
        printf("Error: Usuario con ID %s no encontrado.\n", userID);
        cJSON_Delete(usersArray);
        return 0;
    }

    int success = saveJsonToFile(path, usersArray);
    cJSON_Delete(usersArray);

    return success; 
}