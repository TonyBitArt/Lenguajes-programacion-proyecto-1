#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/dateUtils.h"
#include "../headers/inputUtils.h"
#include "../headers/returnBook.h"
#include "../headers/loanUtils.h"
#include "../headers/jsonHandler.h"
#include "../PDFGen/pdfgen.h"

/**
 * @brief Genera un comprobante PDF de la devolución de un préstamo.
 * @param loan El préstamo devuelto.
 * @param normalCharge Monto del cobro normal.
 * @param lateCharge Monto del cobro por tardía (0 si no aplica).
 * @return int 1 si el PDF se generó correctamente, 0 en caso de error.
 */
int generateReturnReceipt(struct Loan *loan, int normalCharge, int lateCharge) {

    struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, NULL);
    if (!pdf) {
        printf("Error: No se pudo crear el comprobante PDF.\n");
        return 0;
    }

    pdf_set_font(pdf, "Helvetica");
    pdf_append_page(pdf);

    float margin = 50.0f;
    float y = pdf_height(pdf) - 60.0f;

    pdf_add_text(pdf, NULL, "Comprobante de Devolucion", 18, margin, y, PDF_BLACK);
    y -= 18;

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "ID del prestamo: %d", loan->loanID);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 16;

    snprintf(buffer, sizeof(buffer), "ID del usuario: %s", loan->userID);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 16;

    snprintf(buffer, sizeof(buffer), "Libro: %s (copia %d)", loan->bookName, loan->bookCopyNumber);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 16;

    snprintf(buffer, sizeof(buffer), "Fecha de prestamo: %s", loan->loanDate);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 16;

    snprintf(buffer, sizeof(buffer), "Fecha limite de devolucion: %s", loan->returnDate);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 16;

    snprintf(buffer, sizeof(buffer), "Fecha real de devolucion: %s", loan->actualReturnDate);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 30;

    pdf_add_text(pdf, NULL, "Desglose de cobros", 13, margin, y, PDF_BLACK);
    y -= 18;

    int total = normalCharge + lateCharge;

    snprintf(buffer, sizeof(buffer), "Cobro normal: %d Colones", normalCharge);
    pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
    y -= 16;

    if (lateCharge > 0) {
        snprintf(buffer, sizeof(buffer), "Cobro por tardia: %d Colones", lateCharge);
        pdf_add_text(pdf, NULL, buffer, 11, margin, y, PDF_BLACK);
        y -= 16;
    } else {
        pdf_add_text(pdf, NULL, "Cobro por tardia: 0 Colones", 11, margin, y, PDF_BLACK);
        y -= 16;
    }

    y -= 16;

    snprintf(buffer, sizeof(buffer), "TOTAL A PAGAR: %d Colones", total);
    pdf_add_text(pdf, NULL, buffer, 14, margin, y, PDF_BLACK);
    y -= 40;


    char filename[128];
    snprintf(filename, sizeof(filename), "comprobante_%d.pdf", loan->loanID);

    int result = pdf_save(pdf, filename);
    pdf_destroy(pdf);

    if (result < 0) {
        printf("Error: No se pudo guardar el comprobante PDF.\n");
        return 0;
    }

    printf("Comprobante generado: %s\n", filename);
    return 1;
}

void handleReturnBook(void) {
    char *loanIDInput;
    char *actualReturnDate;
    int loanID;
    int loanCount;

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

        /* Generar comprobante PDF con el desglose de cobros */
        struct Loan *loans = parseLoans("./data/loans.json", &loanCount);
        for (int i = 0; i < loanCount; i++) {
            if (loans[i].loanID == loanID) {
                int normalCharge = 0;
                int lateCharge = 0;

                long start = parseDays(loans[i].loanDate);
                long end = parseDays(loans[i].returnDate);
                if (start >= 0 && end >= 0) {
                    int days = (int)(end - start);
                    if (days < 1) days = 1;
                    normalCharge = days * dailyRate(days);
                }

                if (loans[i].actualReturnDate) {
                    start = parseDays(loans[i].returnDate);
                    end = parseDays(loans[i].actualReturnDate);
                    if (start >= 0 && end >= 0) {
                        int days = (int)(end - start);
                        if (days > 0) {
                            lateCharge = days * dailyRateWithPenalty(days);
                        }
                    }
                }

                generateReturnReceipt(&loans[i], normalCharge, lateCharge);
                break;
            }
        }
        freeAllLoans(loans, loanCount);
    } else {
        printf("Error: No se encontró un préstamo con ese ID.\n");
    }

    free(actualReturnDate);
    pauseScreen();
}