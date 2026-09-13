#include "../headers/jsonHandler.h"
#include "../headers/loanUtils.h"
#include "../headers/bookUtils.h"
#include "../headers/inputUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int returnBook(int loanID, const char *actualReturnDate) {
    int loanCount;
    struct Loan *loans = parseLoans("./data/loans.json", &loanCount);

    for (int i = 0; i < loanCount; i++) {
        if (loans[i].loanID == loanID) {
            free(loans[i].actualReturnDate);
            loans[i].actualReturnDate = strdup(actualReturnDate);
            loans[i].status = strdup("finalizado");

            int amountDue = loanAmount(&loans[i]);

            // Incrementar la cantidad del libro correspondiente
            editBookQuantity(loans[i].bookName, 1);

            printf("El monto a pagar por el préstamo es: %d\n", amountDue);

            saveAllLoans(loans, loanCount);
            freeAllLoans(loans, loanCount);
            return 1;
        }
    }

    freeAllLoans(loans, loanCount);
    return 0; // No se encontró el préstamo con el ID proporcionado
}