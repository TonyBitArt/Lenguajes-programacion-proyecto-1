#ifndef USER_UTILS_H
#define USER_UTILS_H


// Includes de los archivos de cabecera del proyecto
#include "../headers/jsonHandler.h"


/**
 * @brief Muestra las opciones de gestión de usuarios.
 * @return void
 */
void printUserOptions();


/**
 * @brief Muestra el mensaje de agregar un nuevo usuario.
 * @return void
 */
void addUserMessage();


/**
 * @brief Muestra el mensaje de búsqueda de usuario por ID.
 * @return void
 */
void searchUserMessage();


/**
 * @brief Muestra las opciones de búsqueda de usuario.
 * @return void
 */
void printSearchUserOptions();


/**
 * @brief Muestra la información de un usuario.
 * @param user El usuario a mostrar.
 * @return void
 */
void printUser(struct User user);


/**
 * @brief Muestra la información de todos los usuarios.
 * @param users Un array de usuarios a mostrar.
 * @param userCount El número de usuarios en el array.
 * @return void
 */
void printAllUsers(struct User *users, int userCount);


/**
 * @brief Crea un nuevo usuario.
 * @param ID El ID del usuario.
 * @param name El nombre del usuario.
 * @param lastName El apellido del usuario.
 * @param address La dirección del usuario.
 * @return struct User La estructura del nuevo usuario creado.
 */
struct User createUser(int ID, const char *name, const char *lastName, const char *address);


/**
 * @brief Libera la memoria asignada para un usuario.
 * @param user Un puntero al usuario a liberar.
 * @return void
 */
void freeUser(struct User *user);


/**
 * @brief Libera la memoria asignada para un array de usuarios.
 * @param users Un puntero al array de usuarios a liberar.
 * @param userCount El número de usuarios en el array.
 * @return void
 */
void freeAllUsers(struct User *users, int userCount);


/**
 * @brief Valida la entrada del usuario.
 * @param message El mensaje a mostrar al usuario.
 * @param cancelFlag Un puntero a un entero que indica si el usuario desea cancelar.
 * @return char* La entrada del usuario.
 */
char* validateUserInput(const char* message, int* cancelFlag);


/**
 * @brief obtiene un usuario por su ID
 * @param path la ruta del archivo donde se encuentra el usuario
 * @param userID el ID del usuario a obtener
 * @return struct User* puntero al usuario encontrado, o NULL si no se encuentra
 */
struct User* getUserByID(const char *path, int userID);


/**
 * @brief Guarda un nuevo usuario en el archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param newUser La estructura del nuevo usuario a guardar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int saveUser(const char *path, struct User newUser);


/**
 * @brief Verifica si un usuario con un ID específico existe en el archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param userID El ID del usuario a verificar.
 * @return 1 si el usuario existe, 0 si no existe.
 */
int existsUser(const char *path, int userID);

#endif // USER_UTILS_H