#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/dateUtils.h"
#include "../headers/inputUtils.h"
#include "../headers/returnBook.h"

void handleReturnBook(void) {
    char *loanIDInput;
    char *actualReturnDate;
    int loanID;

    clearScreen();
    printf("\n--- Devolución de ejemplares ---\n");
    printf("Escriba 0 en cualquier campo para volver.\n\n");

    printf("ID del préstamo: ");
    loanIDInput = readInput();

    if (loanIDInput == NULL) {
        printf("Error: No se pudo leer el ID del préstamo.\n");
        pauseScreen();
        return;
    }

    if (strcmp(loanIDInput, "0") == 0) {
        free(loanIDInput);
        return;
    }

    loanID = atoi(loanIDInput);
    for (int i = 0; loanIDInput[i] != '\0'; i++) {
        if (!isdigit((unsigned char)loanIDInput[i])) {
            printf("Error: El ID del préstamo debe ser un número positivo.\n");
            free(loanIDInput);
            pauseScreen();
            return;
        }
    }

    if (loanID <= 0) {
        printf("Error: El ID del préstamo debe ser un número positivo.\n");
        free(loanIDInput);
        pauseScreen();
        return;
    }
    free(loanIDInput);

    printf("Fecha real de devolución (YYYY-MM-DD): ");
    actualReturnDate = readInput();

    if (actualReturnDate == NULL) {
        printf("Error: No se pudo leer la fecha de devolución.\n");
        pauseScreen();
        return;
    }

    if (strcmp(actualReturnDate, "0") == 0) {
        free(actualReturnDate);
        return;
    }

    if (isEmptyString(actualReturnDate) || !isValidDateFormat(actualReturnDate)) {
        printf("Error: La fecha debe tener el formato YYYY-MM-DD.\n");
    } else if (returnBook(loanID, actualReturnDate)) {
        printf("Devolución registrada exitosamente.\n");
    } else {
        printf("Error: No se encontró un préstamo con ese ID.\n");
    }

    free(actualReturnDate);
    pauseScreen();
}