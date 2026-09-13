#include "../headers/jsonHandler.h"
#include "../headers/bookUtils.h"
#include <stdlib.h>
#include <string.h>


void freeAllBooks(struct Book *books, int bookCount) {
    for (int i = 0; i < bookCount; i++) {
        free(books[i].name);
        free(books[i].author);
        free(books[i].genre);
        free(books[i].summary);
    }
    free(books);
}

void editBookQuantity(char *bookName, int change) {
    int bookCount;
    struct Book *books = parseBooks("./data/books.json", &bookCount);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].name, bookName) == 0) {
            books[i].quantity += change;
            break;
        }
    }

    cJSON *booksJson = cJSON_CreateArray();
    for (int i = 0; i < bookCount; i++) {
        cJSON *bookJson = cJSON_CreateObject();
        cJSON_AddStringToObject(bookJson, "name", books[i].name);
        cJSON_AddStringToObject(bookJson, "author", books[i].author);
        cJSON_AddStringToObject(bookJson, "year", books[i].year);
        cJSON_AddStringToObject(bookJson, "genre", books[i].genre);
        cJSON_AddStringToObject(bookJson, "summary", books[i].summary);
        cJSON_AddNumberToObject(bookJson, "quantity", books[i].quantity);
        cJSON_AddItemToArray(booksJson, bookJson);
    }

    saveJsonToFile("./data/books.json", booksJson);

    freeAllBooks(books, bookCount);
    cJSON_Delete(booksJson);
}

