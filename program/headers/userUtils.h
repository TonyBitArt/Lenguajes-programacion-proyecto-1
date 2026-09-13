#ifndef USER_UTILS_H
#define USER_UTILS_H


// Includes de los archivos de cabecera del proyecto
#include "../headers/jsonHandler.h"


/**
 * @brief Anchos de las columnas para la visualización de usuarios.
 */
#define USER_ID_WIDTH 12
#define USER_NAME_WIDTH 20
#define USER_LASTNAME_WIDTH 20
#define USER_ADDRESS_WIDTH 40


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
void printAllUsers(struct User* users, int userCount);


/**
 * @brief Muestra el mensaje de modificación de usuario.
 * @return void
 */
void printModifyUserMessage();


/**
 * @brief Muestra el mensaje de modificación de datos de usuario.
 * @return void
 */
void printModifyUserDataMessage();


/**
 * @brief Muestra el mensaje de eliminación de usuario.
 * @return void
 */
void printDeleteUserMessage();


/**
 * @brief Obtiene todos los usuarios de un archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param users Un puntero a un array de estructuras User.
 * @param userCount Un puntero a un entero que se llenará con el número de usuarios en el archivo.
 * @return struct User* Un array de estructuras User. NULL si ocurre un error.
 */
struct User* getAllUsers(const char* path, struct User** users, int* userCount);


/**
 * @brief Crea un nuevo usuario.
 * @param ID El ID del usuario.
 * @param name El nombre del usuario.
 * @param lastName El apellido del usuario.
 * @param address La dirección del usuario.
 * @return struct User La estructura del nuevo usuario creado.
 */
struct User createUser(char* ID, const char* name, const char* lastName, const char* address);


/**
 * @brief Libera la memoria asignada para un usuario.
 * @param user Un puntero al usuario a liberar.
 * @return void
 */
void freeUserData(struct User* user);


/**
 * @brief Libera la memoria asignada para un array de usuarios.
 * @param users Un puntero al array de usuarios a liberar.
 * @param userCount El número de usuarios en el array.
 * @return void
 */
void freeAllUsers(struct User* users, int userCount);


/**
 * @brief obtiene un usuario por su ID
 * @param path la ruta del archivo donde se encuentra el usuario
 * @param userID el ID del usuario a obtener
 * @return struct User* puntero al usuario encontrado, o NULL si no se encuentra
 */
struct User* getUserByID(const char* path, char* userID);


/**
 * @brief Guarda un nuevo usuario en el archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param newUser La estructura del nuevo usuario a guardar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int saveUser(const char* path, struct User newUser);


/**
 * @brief Modifica los detalles de un usuario existente.
 * @param path La ruta del archivo JSON.
 * @param user Un puntero al usuario a modificar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int saveModifiedUser(const char* path, struct User modifiedUser);


/**
 * @brief Verifica si un usuario con un ID específico existe en el archivo JSON.
 * @param path La ruta del archivo JSON.
 * @param userID El ID del usuario a verificar.
 * @return 1 si el usuario existe, 0 si no existe.
 */
int existsUser(const char* path, char* userID);


/**
 * @brief Modifica los detalles de un usuario existente.
 * @param path La ruta del archivo JSON.
 * @param user Un puntero al usuario a modificar.
 * @return void
 */
void modifyUserData(const char* path, struct User* user);


/**
 * @brief Elimina un usuario por su ID.
 * @param path La ruta del archivo JSON.
 * @param userID El ID del usuario a eliminar.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int deleteUserByID(const char* path, char* userID);


/**
 * @brief Elimina todos los préstamos asociados a un usuario por su ID.
 * @param path La ruta del archivo JSON de préstamos.
 * @param userID El ID del usuario cuyos préstamos se eliminarán.
 * @return int 1 si fue exitoso, 0 si hubo un error.
 */
int deleteLoansByUserID(const char* path, char* userID);

#endif // USER_UTILS_H