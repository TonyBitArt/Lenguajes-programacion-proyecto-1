#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../headers/dateUtils.h"
#include "../headers/jsonHandler.h"
#include "../headers/stats.h"
#include "../headers/inputUtils.h"

static struct User getUserByID(struct User *users, int userCount, char* ID) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].ID, ID) == 0) {
            return users[i];
        }
    }
    struct User emptyUser = {NULL, NULL, 0, NULL};
    return emptyUser;
}

static struct Book getBookByName(struct Book *books, int bookCount, const char *name) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].name, name) == 0) {
            return books[i];
        }
    }
    printf("First book: %s\n", books[0].name);
    printf("Book not found: %s\n", name);
    struct Book emptyBook = {NULL, NULL, 0, NULL, NULL, 0};
    return emptyBook;
}

static int* getSortedIndex(int *toSort, int size) {
    if (size <= 0) return NULL;

    int* copy = malloc((sizeof(int)) * size);
    int* sortedIndex = malloc((sizeof(int)) * size);

    if (!copy || !sortedIndex) {
        free(copy);
        free(sortedIndex);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        copy[i] = toSort[i];
        sortedIndex[i] = i;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (copy[j] > copy[i]) {

                // Ordena lista
                int temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;

                // Ordena indices
                int tempIndex = sortedIndex[i];
                sortedIndex[i] = sortedIndex[j];
                sortedIndex[j] = tempIndex;
            }
        }
    }

    free(copy);
    return sortedIndex;

}

void printTopBooksLoaned(struct Loan *loans, int loanCount, int topN) {
    char **names = malloc(sizeof(char *) * loanCount);
    int *counts = malloc(sizeof(int) * loanCount);
    int distinct = 0;

    for (int i = 0; i < loanCount; i++) {
        int j;
        for (j = 0; j < distinct; j++) {
            if (strcmp(names[j], loans[i].bookName) == 0) { counts[j]++; break; }
        }
        if (j == distinct) { names[distinct] = loans[i].bookName; counts[distinct] = 1; distinct++; }
    }

    int* sortedIndex = getSortedIndex(counts, distinct);

    if (!sortedIndex) {
        free(names);
        free(counts);
        return;
    }

    printf("A. Top %d producciones más prestadas:\n", topN);
    for (int i = 0; i < topN && i < distinct; i++) {
        printf("\t- %s: %d Préstamos.\n", names[sortedIndex[i]], counts[sortedIndex[i]]);
    }

    free(sortedIndex);
    free(names);
    free(counts);
}

void printTopUsersLoaned(struct Loan *loans, int loanCount, struct User *users, int userCount, int topN) {
    char **userIDs = malloc(sizeof(char *) * loanCount);
    int *counts = malloc(sizeof(int) * loanCount);
    int distinct = 0;

    for (int i = 0; i < loanCount; i++) {
        int j;
        for (j = 0; j < distinct; j++) {
            if (strcmp(userIDs[j], loans[i].userID) == 0) { counts[j]++; break; }
        }
        if (j == distinct) { userIDs[distinct] = loans[i].userID; counts[distinct] = 1; distinct++; }
    }

    int* sortedIndex = getSortedIndex(counts, distinct);

    if (!sortedIndex) {
        free(userIDs);
        free(counts);
        return;
    }

    char **userNames = malloc(sizeof(char *) * distinct);
    struct User user;
    for (int i = 0; i < distinct; i++) {
        user = getUserByID(users, userCount, userIDs[sortedIndex[i]]);
        if (user.name) {
            userNames[i] = malloc(strlen(user.name) + strlen(user.lastName) + 2);
            sprintf(userNames[i], "%s %s", user.name, user.lastName);
        } else {
            userNames[i] = strdup("Usuario desconocido");
        }
    }

    printf("B. Top %d usuarios con más préstamos:\n", topN);
    for (int i = 0; i < topN && i < distinct; i++) {
        printf("\t- %s: %d Préstamos.\n", userNames[sortedIndex[i]], counts[sortedIndex[i]]);
    }

    free(sortedIndex);
    free(userIDs);
    free(counts);
    free(userNames);
}

void printTopMonthsRevenue(struct Loan *loans, int loanCount, int topN) {
    // Clave de mes-anio: anio * 100 + mes
    int *keys = malloc(sizeof(int) * loanCount);
    int *revenue = malloc(sizeof(int) * loanCount);
    int distinct = 0;

    for (int i = 0; i < loanCount; i++) {
        int y, m;
        if (parseYearMonth(loans[i].loanDate, &y, &m) != 0) continue;
        int key = y * 100 + m;
        int j;
        for (j = 0; j < distinct; j++) {
            if (keys[j] == key) { revenue[j] += loanAmount(&loans[i]); break; }
        }
        if (j == distinct) { keys[distinct] = key; revenue[distinct] = loanAmount(&loans[i]); distinct++; }
    }

    int* sortedIndex = getSortedIndex(revenue, distinct);
    
    if (!sortedIndex) {
        free(keys);
        free(revenue);
        return;
    }

    printf("C. Top %d mes-anio con mayor monto recaudado:\n", topN);
    for (int i = 0; i < topN && i < distinct; i++) {
        printf("\t- %d-%02d: $%d\n", keys[sortedIndex[i]] / 100, keys[sortedIndex[i]] % 100, revenue[sortedIndex[i]]);
    }

    free(sortedIndex);
    free(keys);
    free(revenue);
}

void printGenreLoanStats(struct Loan *loans, int loanCount, struct Book *books, int bookCount) {
    char **bookNames = malloc(sizeof(char *) * loanCount);
    int *counts = malloc(sizeof(int) * loanCount);
    int distinct = 0;

    for (int i = 0; i < loanCount; i++) {
       
        int j;
        for (j = 0; j < distinct; j++) {
            if (strcmp(bookNames[j], loans[i].bookName) == 0) { counts[j]++; break; }
        }
        if (j == distinct) { bookNames[distinct] = loans[i].bookName; counts[distinct] = 1; distinct++; }
    }

    int* sortedIndex = getSortedIndex(counts, distinct);

    if (!sortedIndex) {
        free(bookNames);
        free(counts);
        return;
    }

    char **genres = malloc(sizeof(char *) * distinct);
    struct Book book;
    for (int i = 0; i < distinct; i++) {
        book = getBookByName(books, bookCount, bookNames[sortedIndex[i]]);
        if (book.author) {
            genres[i] = book.genre ? strdup(book.genre) : strdup("Género desconocido");
        } else {
            genres[i] = strdup("Libro desconocido");
        }
    }

    printf("D. Género con más y con menos préstamos\n");
    printf("\t- Género con más préstamos: %s (%d préstamos)\n", genres[sortedIndex[0]], counts[sortedIndex[0]]);
    printf("\t- Género con menos préstamos: %s (%d préstamos)\n", genres[sortedIndex[distinct - 1]], counts[sortedIndex[distinct - 1]]);

    free(sortedIndex);
    free(genres);
    free(counts);
    free(bookNames);
}
