#ifndef JSONHANDLER_H
#define JSONHANDLER_H


#include "../cJSON/cJSON.h"

struct User {
    char *name;
    char *lastName;
    char *ID;
    char *address;
};


struct Book {
    char *name;
    char *author;
    int year;
    char *genre;
    char *summary;
    int quantity;
};


struct Loan {
    int loanID;
    char *userID;
    char *bookName;
    int bookCopyNumber;
    char *loanDate;
    char *returnDate;
};


/**
 * @brief Lee un archivo y devuelve su contenido como una cadena de caracteres.
 * @param path La ruta del archivo a leer.
 * @return char* Una cadena de caracteres que contiene el contenido del archivo. NULL si ocurre un error.
 */
char* readFile(const char *path);


/**
 * @brief Parsea un archivo JSON y devuelve un array de estructuras User.
 * @param path La ruta del archivo JSON a parsear.
 * @param userCount Un puntero a un entero que se llenará con el número de usuarios en el archivo.
 * @return struct User* Un array de estructuras User. NULL si ocurre un error.
 */
struct User *parseUsers(const char *path, int *userCount);


/**
 * @brief Parsea un archivo JSON y devuelve un array de estructuras Book.
 * @param path La ruta del archivo JSON a parsear.
 * @param bookCount Un puntero a un entero que se llenará con el número de libros en el archivo.
 * @return struct Book* Un array de estructuras Book. NULL si ocurre un error.
 */
struct Book *parseBooks(const char *path, int *bookCount);


/**
 * @brief Parsea un archivo JSON y devuelve un array de estructuras Loan.
 * @param path La ruta del archivo JSON a parsear.
 * @param loanCount Un puntero a un entero que se llenará con el número de préstamos en el archivo.
 * @return struct Loan* Un array de estructuras Loan. NULL si ocurre un error.
 */
struct Loan *parseLoans(const char *path, int *loanCount);


/**
 * @brief Parsea un archivo JSON y devuelve un objeto cJSON.
 * @param path La ruta del archivo JSON a parsear.
 * @return cJSON* Un objeto cJSON. NULL si ocurre un error.
 */
cJSON *parseJsonFile(const char *path);

/**
 * @brief guarda un objeto JSON en un archivo
 * @param path la ruta del archivo donde se guardará el JSON
 * @param jsonObject el objeto JSON a guardar
 * @return int 1 si se guardó exitosamente, 0 si ocurrió un error
 */
int saveJsonToFile(const char *path, cJSON *jsonObject);

/**
 * @brief agrega un nuevo libro al archivo JSON de catálogo (lee, valida
 * unicidad por nombre, agrega y reescribe el archivo)
 * @param path la ruta del archivo JSON de libros
 * @param newBook el libro a agregar
 * @return int 1 si se guardó, 0 si el nombre ya existe en el catálogo
 */
int saveBook(const char *path, struct Book newBook);

/**
 * @brief libera la memoria dinámica de un arreglo de Book obtenido con
 * parseBooks
 * @param books el arreglo a que se va a liberar
 * @param bookCount cantidad de elementos que tiene el arreglo
 */
void freeBooks(struct Book *books, int bookCount);

#endif // JSONHANDLER_H