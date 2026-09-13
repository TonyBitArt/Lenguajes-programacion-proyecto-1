#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/config.h"
#include "../headers/dateUtils.h"
#include "../headers/inputUtils.h"
#include "../headers/lendBook.h"
#include "../headers/userUtils.h"

static char *readLoanInput(const char *message, int *cancelled) {
    char *input;

    printf("%s", message);
    input = readInput();

    if (input == NULL) {
        printf("Error: No se pudo leer la entrada.\n");
        *cancelled = 1;
        return NULL;
    }

    if (strcmp(input, "0") == 0) {
        free(input);
        *cancelled = 1;
        return NULL;
    }

    if (isEmptyString(input)) {
        printf("Error: No se puede ingresar un campo vacío.\n");
        free(input);
        return NULL;
    }

    return input;
}

void handleLendBook(void) {
    char *bookName = NULL;
    char *loanDate = NULL;
    char *returnDate = NULL;
    char *userID = NULL;
    int cancelled = 0;

    clearScreen();
    printf("\n--- Préstamo de ejemplares ---\n");
    printf("Escriba 0 en cualquier campo para volver.\n\n");

    bookName = readLoanInput("Nombre exacto del libro: ", &cancelled);
    if (!cancelled && bookName == NULL) {
        pauseScreen();
        return;
    }

    if (!cancelled) {
        loanDate = readLoanInput("Fecha de préstamo (YYYY-MM-DD): ", &cancelled);
    }
    if (!cancelled && loanDate == NULL) {
        free(bookName);
        pauseScreen();
        return;
    }

    if (!cancelled) {
        returnDate = readLoanInput("Fecha de devolución (YYYY-MM-DD): ", &cancelled);
    }
    if (!cancelled && returnDate == NULL) {
        free(bookName);
        free(loanDate);
        pauseScreen();
        return;
    }

    if (!cancelled) {
        userID = readLoanInput("ID del usuario: ", &cancelled);
    }

    if (cancelled) {
        free(bookName);
        free(loanDate);
        free(returnDate);
        free(userID);
        return;
    }

    if (userID == NULL) {
        free(bookName);
        free(loanDate);
        free(returnDate);
        pauseScreen();
        return;
    }

    if (!isValidDateFormat(loanDate) || !isValidDateFormat(returnDate)) {
        printf("Error: Las fechas deben tener el formato YYYY-MM-DD.\n");
    } else if (!validateID(userID)) {
        printf("Error: El usuario no existe o el ID no es válido.\n");
    } else {
        struct User *user = getUserByID(USERS_FILE_PATH, userID);

        if (user == NULL) {
            printf("Error: El usuario no existe.\n");
        } else {
            int loanID;
            int result = lendBookWithID(bookName, loanDate, returnDate, userID,
                                        &loanID);

            if (result == 0) {
                printf("Préstamo registrado exitosamente.\n");
                printf("\n========== COMPROBANTE DE PRÉSTAMO ==========\n");
                printf("Identificador de préstamo: %d\n", loanID);
                printf("Usuario: %s %s (ID: %s)\n", user->name,
                       user->lastName, userID);
                printf("Fecha inicio: %s\n", loanDate);
                printf("Fecha de entrega: %s\n", returnDate);
                printf("Nombre de libro: %s\n", bookName);
                printf("==============================================\n");
            } else if (result == -1) {
                printf("Error: La fecha de devolución debe ser posterior a la fecha de préstamo.\n");
            } else if (result == -2) {
                printf("Error: El libro no existe o no hay ejemplares disponibles.\n");
            } else {
                printf("Error: No se pudo registrar el préstamo.\n");
            }

            freeUserData(user);
            free(user);
        }
    }

    free(bookName);
    free(loanDate);
    free(returnDate);
    free(userID);
    pauseScreen();
}