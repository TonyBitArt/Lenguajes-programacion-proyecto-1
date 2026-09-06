#include <stdio.h>
#include <stdlib.h>
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

        users[i].name = nameJson ? nameJson->valuestring : NULL;
        users[i].lastName = lastNameJson ? lastNameJson->valuestring : NULL;
        users[i].ID = IDJson ? IDJson->valueint : 0;
        users[i].address = addressJson ? addressJson->valuestring : NULL;
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

        books[i].name = nameJson ? nameJson->valuestring : NULL;
        books[i].author = authorJson ? authorJson->valuestring : NULL;
        books[i].year = yearJson ? yearJson->valueint : 0;
        books[i].genre = genreJson ? genreJson->valuestring : NULL;
        books[i].summary = summaryJson ? summaryJson->valuestring : NULL;
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
        cJSON *userJson = cJSON_GetObjectItem(loanJson, "user");
        cJSON *bookNameJson = cJSON_GetObjectItem(loanJson, "bookName");
        cJSON *bookIDJson = cJSON_GetObjectItem(loanJson, "bookID");
        cJSON *loanDateJson = cJSON_GetObjectItem(loanJson, "loanDate");
        cJSON *returnDateJson = cJSON_GetObjectItem(loanJson, "returnDate");

        loans[i].loanID = loanIDJson ? loanIDJson->valueint : 0;
        loans[i].user = userJson ? userJson->valuestring : NULL;
        loans[i].bookName = bookNameJson ? bookNameJson->valuestring : NULL;
        loans[i].bookID = bookIDJson ? bookIDJson->valueint : 0;
        loans[i].loanDate = loanDateJson ? loanDateJson->valuestring : NULL;
        loans[i].returnDate = returnDateJson ? returnDateJson->valuestring : NULL;
    }
    cJSON_Delete(loansJson);
    return loans;
}

