#include "../headers/jsonHandler.h"
#include <stdlib.h>
#include <string.h>

#include "../headers/inputUtils.h"
#include "../headers/dateUtils.h"
#include "../headers/lendBook.h"
#include "../headers/loanUtils.h"
#include "../headers/bookUtils.h"

struct Book *findBook(char *bookName) {
    int bookCount;
    struct Book *books = parseBooks("./data/books.json", &bookCount);

    struct Book *book = NULL;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].name, bookName) == 0 && books[i].quantity > 0) {
            book = malloc(sizeof(struct Book));
            *book = books[i];
            book->name = strdup(books[i].name);
            book->author = strdup(books[i].author);
            book->year = strdup(books[i].year);
            book->summary = strdup(books[i].summary);
            book->genre = strdup(books[i].genre);
            break;
        }
    }

    freeBooks(books, bookCount);
    return book;

}

int getLastLoanID() {
    int loanCount;
    struct Loan *loans = parseLoans("./data/loans.json", &loanCount);

    int lastLoanID = 0;
    for (int i = 0; i < loanCount; i++) {
        if (loans[i].loanID > lastLoanID) {
            lastLoanID = loans[i].loanID;
        }
    }

    freeAllLoans(loans, loanCount);
    return lastLoanID;
}

int lendBook(char *bookName, char *loanDate, char *returnDate, char *userID) {

    if (parseDays(returnDate) - parseDays(loanDate) < 1) {
        return -1;
    }    

    struct Book *book = findBook(bookName);
    if (!book) return -2;

    struct Loan *newLoan = (struct Loan *)malloc(sizeof(struct Loan));
    newLoan->loanID = getLastLoanID() + 1;
    newLoan->userID = strdup(userID);
    newLoan->bookName = strdup(book->name);
    newLoan->bookCopyNumber = getNextCopyNumber(book->name);
    newLoan->loanDate = strdup(loanDate);
    newLoan->returnDate = strdup(returnDate);

    if (!saveLoan(newLoan)) {
        return -3;
    }

    editBookQuantity(book->name, -1);

    free(book->name);
    free(book->author);
    free(book->year);
    free(book);

    free(newLoan->userID);
    free(newLoan->bookName);
    free(newLoan->loanDate);
    free(newLoan->returnDate);
    free(newLoan);

    return 0;
}