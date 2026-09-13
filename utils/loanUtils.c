#include "../headers/jsonHandler.h"
#include "../headers/loanUtils.h"
#include <stdlib.h>
#include <string.h>

void freeAllLoans(struct Loan *loans, int loanCount) {
    for (int i = 0; i < loanCount; i++) {
        free(loans[i].userID);
        free(loans[i].bookName);
        free(loans[i].loanDate);
        free(loans[i].returnDate);
    }
    free(loans);
}

int saveLoan(struct Loan *loan) {
    cJSON *loansArray = parseJsonFile("./data/loans.json");
    if (!loansArray) {
        loansArray = cJSON_CreateArray();
    }

    cJSON *loanObject = cJSON_CreateObject();

    if (!loanObject) {
        cJSON_Delete(loansArray);
        return 0;
    }

    cJSON_AddNumberToObject(loanObject, "loanID", loan->loanID);
    cJSON_AddStringToObject(loanObject, "userID", loan->userID);
    cJSON_AddStringToObject(loanObject, "bookName", loan->bookName);
    cJSON_AddNumberToObject(loanObject, "bookCopyNumber", loan->bookCopyNumber);
    cJSON_AddStringToObject(loanObject, "loanDate", loan->loanDate);
    cJSON_AddStringToObject(loanObject, "returnDate", loan->returnDate);

    cJSON_AddItemToArray(loansArray, loanObject);
    int success = saveJsonToFile("./data/loans.json", loansArray);

    cJSON_Delete(loansArray);
    return success;
}

int getNextCopyNumber(char *bookName) {
    int loanCount;
    struct Loan *loans = parseLoans("./data/loans.json", &loanCount);

    int maxCopyNumber = 0;
    for (int i = 0; i < loanCount; i++) {
        if (strcmp(loans[i].bookName, bookName) == 0) {
            if (loans[i].bookCopyNumber > maxCopyNumber) {
                maxCopyNumber = loans[i].bookCopyNumber;
            }
        }
    }

    // Revisar si falta una copia en el rango de 1 a maxCopyNumber
    for (int i = 1; i <= maxCopyNumber; i++) {
        int found = 0;
        for (int j = 0; j < loanCount; j++) {
            if (strcmp(loans[j].bookName, bookName) == 0 && loans[j].bookCopyNumber == i) {
                found = 1;
                break;
            }
        }
        if (!found) {
            freeAllLoans(loans, loanCount);
            return i; // Retorna el primer número de copia faltante
        }
    }

    freeAllLoans(loans, loanCount);
    return maxCopyNumber + 1; // Retorna el siguiente número de copia disponible
}