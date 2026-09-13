#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"
#include "../headers/jsonHandler.h"

char *readFile(const char *path) {
    FILE *file = fopen(path, "rb"); // Abrir el archivo en modo lectura/binario
    if (!file) return NULL;

    fseek(file, 0, SEEK_END); // Ir al final del archivo
    long len = ftell(file); // Obtener la posición actual del cursor (tamaño de archivo)
    fseek(file, 0, SEEK_SET); // Volver al inicio del archivo

    char *bufer = malloc(len + 1); 
    if (!bufer) {
        fclose(file);
        return NULL;
    }

    fread(bufer, 1, len, file); 
    bufer[len] = '\0'; 
    fclose(file);
    return bufer;
}

cJSON *parseJsonFile(const char *path) {
    char *jsonString = readFile(path);
    if (!jsonString) {
        return NULL;
    }

    cJSON *json = cJSON_Parse(jsonString);
    free(jsonString);
    
    return json;

}

struct User *parseUsers(const char *path, int *userCount) {
    cJSON *usersJson = parseJsonFile(path);
    if (!usersJson) {
        return NULL;
    }

    *userCount = cJSON_GetArraySize(usersJson);

    struct User *users = malloc(sizeof(struct User) * *userCount);
    if (!users) {
        cJSON_Delete(usersJson);
        return NULL;
    }

    for (int i = 0; i < *userCount; i++) {
        cJSON *userJson = cJSON_GetArrayItem(usersJson, i);
        if (!userJson) {
            continue;
        }

        cJSON *nameJson = cJSON_GetObjectItem(userJson, "name");
        cJSON *lastNameJson = cJSON_GetObjectItem(userJson, "lastName");
        cJSON *IDJson = cJSON_GetObjectItem(userJson, "ID");
        cJSON *addressJson = cJSON_GetObjectItem(userJson, "address");

        users[i].name = nameJson && nameJson->valuestring ? strdup(nameJson->valuestring) : NULL;
        users[i].lastName = lastNameJson && lastNameJson->valuestring ? strdup(lastNameJson->valuestring) : NULL;
        users[i].ID = IDJson && IDJson->valuestring ? strdup(IDJson->valuestring) : NULL;
        users[i].address = addressJson && addressJson->valuestring ? strdup(addressJson->valuestring) : NULL;
    }
    cJSON_Delete(usersJson);
    return users;
}

struct Book *parseBooks(const char *path, int *bookCount) {
    cJSON *booksJson = parseJsonFile(path);
    if (!booksJson) return NULL;

    *bookCount = cJSON_GetArraySize(booksJson);

    struct Book *books = malloc(sizeof(struct Book) * *bookCount);
    if (!books) {
        cJSON_Delete(booksJson);
        return NULL;
    }

    for (int i = 0; i < *bookCount; i++){
        cJSON *bookJson = cJSON_GetArrayItem(booksJson, i);
        if (!bookJson) continue;

        cJSON *nameJson = cJSON_GetObjectItem(bookJson, "name");
        cJSON *authorJson = cJSON_GetObjectItem(bookJson, "author");
        cJSON *yearJson = cJSON_GetObjectItem(bookJson, "year");
        cJSON *genreJson = cJSON_GetObjectItem(bookJson, "genre");
        cJSON *summaryJson = cJSON_GetObjectItem(bookJson, "summary");
        cJSON *quantityJson = cJSON_GetObjectItem(bookJson, "quantity");

        // Uso strdup para proteger la memoria de los textos
        books[i].name = (nameJson && nameJson->valuestring) ? strdup(nameJson->valuestring) : NULL;
        books[i].author = (authorJson && authorJson->valuestring) ? strdup(authorJson->valuestring) : NULL;
        books[i].year = yearJson && yearJson->valuestring ? strdup(yearJson->valuestring) : NULL;
        books[i].genre = (genreJson && genreJson->valuestring) ? strdup(genreJson->valuestring) : NULL;
        books[i].summary = (summaryJson && summaryJson->valuestring) ? strdup(summaryJson->valuestring) : NULL;
        books[i].quantity = quantityJson ? quantityJson->valueint : 0;
    }
    cJSON_Delete(booksJson);
    return books;

}

struct Loan *parseLoans(const char *path, int *loanCount){
    cJSON *loansJson = parseJsonFile(path);
    if (!loansJson) return NULL;

    *loanCount = cJSON_GetArraySize(loansJson);

    struct Loan *loans = malloc(sizeof(struct Loan) * *loanCount);
    if (!loans) {
        cJSON_Delete(loansJson);
        return NULL;
    }

    for (int i = 0; i < *loanCount; i++){
        cJSON *loanJson = cJSON_GetArrayItem(loansJson, i);
        if (!loanJson) continue;

        cJSON *loanIDJson = cJSON_GetObjectItem(loanJson, "loanID");
        cJSON *userIDJson = cJSON_GetObjectItem(loanJson, "userID");
        cJSON *bookNameJson = cJSON_GetObjectItem(loanJson, "bookName");
        cJSON *bookCopyNumberJson = cJSON_GetObjectItem(loanJson, "bookCopyNumber");
        cJSON *loanDateJson = cJSON_GetObjectItem(loanJson, "loanDate");
        cJSON *returnDateJson = cJSON_GetObjectItem(loanJson, "returnDate");
        cJSON *actualReturnDateJson = cJSON_GetObjectItem(loanJson, "actualReturnDate");
        cJSON *statusJson = cJSON_GetObjectItem(loanJson, "status");

        loans[i].loanID = loanIDJson ? loanIDJson->valueint : 0;
        loans[i].userID = userIDJson && userIDJson->valuestring ? strdup(userIDJson->valuestring) : NULL;
        loans[i].bookName = bookNameJson && bookNameJson->valuestring ? strdup(bookNameJson->valuestring) : NULL;
        loans[i].bookCopyNumber = bookCopyNumberJson ? bookCopyNumberJson->valueint : 0;
        loans[i].loanDate = loanDateJson && loanDateJson->valuestring ? strdup(loanDateJson->valuestring) : NULL;
        loans[i].returnDate = returnDateJson && returnDateJson->valuestring ? strdup(returnDateJson->valuestring) : NULL;
        loans[i].actualReturnDate = actualReturnDateJson && actualReturnDateJson->valuestring ? strdup(actualReturnDateJson->valuestring) : NULL;
        loans[i].status = statusJson && statusJson->valuestring ? strdup(statusJson->valuestring) : NULL;
    }
    cJSON_Delete(loansJson);
    return loans;
}

/**
 * @brief guarda un objeto JSON en un archivo
 * @param path la ruta del archivo donde se guardará el JSON
 * @param jsonObject el objeto JSON a guardar
 * @return int 1 si se guardó exitosamente, 0 si ocurrió un error
 */
int saveJsonToFile(const char *path, cJSON *jsonObject) {
    if (!jsonObject) {
        return 0;
    }

    char *jsonString = cJSON_Print(jsonObject);
    if (!jsonString) {
        return 0;
    }

    FILE *file = fopen(path, "wb");
    if (!file) {
        free(jsonString);
        return 0;
    }

    fwrite(jsonString, sizeof(char), strlen(jsonString), file);
    fclose(file);

    free(jsonString);
    return 1;
}

/**
 * @brief libera la memoria dinámica de un arreglo de Book obtenido con
 * parseBooks
 * @param books el arreglo a que se va a liberar
 * @param bookCount cantidad de elementos que tiene el arreglo
 */
void freeBooks(struct Book *books, int bookCount) {
    if (!books) return;
    for (int i = 0; i < bookCount; i++) {
        free(books[i].name);
        free(books[i].author);
        free(books[i].genre);
        free(books[i].summary);
    }
    free(books);
}

/**
 * @brief agrega un nuevo libro al archivo JSON de catálogo (lee, valida
 * unicidad por nombre, agrega y reescribe el archivo)
 * @param path la ruta del archivo JSON de libros
 * @param newBook el libro a agregar
 * @return int 1 si se guardó, 0 si el nombre ya existe en el catálogo
 */
int saveBook(const char *path, struct Book newBook) {
    cJSON *booksArray = parseJsonFile(path);

    if (!booksArray) {
        booksArray = cJSON_CreateArray();
    }

    // valida la unicidad por nombre
    int arraySize = cJSON_GetArraySize(booksArray);
    for (int i = 0; i < arraySize; i++) {
        cJSON *bookJson = cJSON_GetArrayItem(booksArray, i);
        cJSON *nameJson = bookJson ? cJSON_GetObjectItem(bookJson, "name") : NULL;
        if (nameJson && nameJson->valuestring && newBook.name &&
            strcmp(nameJson->valuestring, newBook.name) == 0) {
            cJSON_Delete(booksArray);
            return 0; // ya existe
        }
    }

    cJSON *bookObject = cJSON_CreateObject();
    if (!bookObject) {
        cJSON_Delete(booksArray);
        return 0;
    }

    cJSON_AddStringToObject(bookObject, "name", newBook.name ? newBook.name : "");
    cJSON_AddStringToObject(bookObject, "author", newBook.author ? newBook.author : "");
    cJSON_AddStringToObject(bookObject, "year", newBook.year ? newBook.year : "");
    cJSON_AddStringToObject(bookObject, "genre", newBook.genre ? newBook.genre : "");
    cJSON_AddStringToObject(bookObject, "summary", newBook.summary ? newBook.summary : "");
    cJSON_AddNumberToObject(bookObject, "quantity", newBook.quantity);

    cJSON_AddItemToArray(booksArray, bookObject);
    int success = saveJsonToFile(path, booksArray);

    cJSON_Delete(booksArray);
    return success;
}

int editBook(const char *path, const char *currentName, struct Book updatedBook) {
    if (!path || !currentName) return 0;

    cJSON *root = parseJsonFile(path);
    if (!root || !cJSON_IsArray(root)) {
        if (root) cJSON_Delete(root);
        return 0;
    }

    cJSON *target = NULL;
    cJSON *item = NULL;

    cJSON_ArrayForEach(item, root) {
        cJSON *nameItem = cJSON_GetObjectItem(item, "name");
        if (nameItem && nameItem->valuestring) {
            if (strcmp(nameItem->valuestring, currentName) == 0) {
                target = item;
            } else if (updatedBook.name && strcmp(nameItem->valuestring, updatedBook.name) == 0) {
                cJSON_Delete(root);
                return 0;
            }
        }
    }

    if (!target) {
        cJSON_Delete(root);
        return 0; // no se encontró el libro a editar
    }

    // actualizar campos
    if (updatedBook.name) {
        cJSON_ReplaceItemInObject(target, "name", cJSON_CreateString(updatedBook.name));
    }
    if (updatedBook.author) {
        cJSON_ReplaceItemInObject(target, "author", cJSON_CreateString(updatedBook.author));
    }
    if (updatedBook.year) {
        cJSON_ReplaceItemInObject(target, "year", cJSON_CreateString(updatedBook.year));
    }
    if (updatedBook.genre) {
        cJSON_ReplaceItemInObject(target, "genre", cJSON_CreateString(updatedBook.genre));
    }
    if (updatedBook.summary) {
        cJSON_ReplaceItemInObject(target, "summary", cJSON_CreateString(updatedBook.summary));
    }
    cJSON_ReplaceItemInObject(target, "quantity", cJSON_CreateNumber(updatedBook.quantity));

    // guardar cambios en el archivo
    int success = saveJsonToFile(path, root);
    cJSON_Delete(root);
    return success;
}