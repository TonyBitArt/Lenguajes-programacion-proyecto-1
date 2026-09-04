#include <stdio.h>
#include "headers/jsonHandler.h"


int main() {

    int loanCount = 0;
    struct Loan *loans = parseLoans("data/loans.json", &loanCount);

    printf("Number of loans: %d\n", loanCount);

    return 0;
}