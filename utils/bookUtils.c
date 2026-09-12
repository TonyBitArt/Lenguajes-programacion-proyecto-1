#include "../headers/jsonHandler.h"
#include "../headers/bookUtils.h"
#include <stdlib.h>


void freeAllBooks(struct Book *books, int bookCount) {
    for (int i = 0; i < bookCount; i++) {
        free(books[i].name);
        free(books[i].author);
        free(books[i].genre);
        free(books[i].summary);
    }
    free(books);
}