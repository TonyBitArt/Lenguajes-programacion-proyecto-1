// Includes de la librería estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Includes de los archivos de cabecera del proyecto
#include "../headers/config.h"
#include "../headers/dateUtils.h"
#include "../headers/inputUtils.h"
#include "../headers/userUtils.h"
#include "../headers/loanFeatures.h"


// Constantes para los anchos de las columnas
const int ID_WIDTH = 8;
const int NAME_WIDTH = 20;  
const int BOOK_WIDTH = 30; 
const int COPY_WIDTH = 11; 


/**
 * @brief Muestra el mensaje de historial de préstamos.
 * @return void
 */
void loanHistoryMessage() {
    printf("\n========================================\n");
    printf("          HISTORIAL DE PRÉSTAMOS\n");
    printf("========================================\n");
    printf("Ingrese el rango de fechas para el historial de préstamos (YYYY-MM-DD).\n");
    printf("Escriba 0 para cancelar.\n");
    printf("========================================\n");
}

/**
 * @brief Muestra el mensaje de préstamos vencidos o próximos a vencer.
 * @return void
 */
void printExpiringLoansMessage() {
    printf("\n========================================\n");
    printf("      PRÉSTAMOS VENCIDOS O PRÓXIMOS A VENCER\n");
    printf("========================================\n");
    printf("Se mostrarán los préstamos que están vencidos o próximos a vencer.\n");
    printf("Escriba 0 para cancelar.\n");
    printf("========================================\n");
}


/**
 * @brief Muestra el encabezado tabular del historial de préstamos.
 * @param STATUS_WIDTH Ancho de la columna de estado.
 * @param LATE_WIDTH Ancho de la columna de entrega tardía.
 * @return void
 */
void printLoanHistoryHeader(const int STATUS_WIDTH, const int LATE_WIDTH) {
    printf("\n");
    printf("+----------+--------------+----------------------+--------------+--------------------------------+-------------+----------------+\n");
    printf("|");
    printCell("ID", ID_WIDTH);
    printCell("ID Usuario", USER_ID_WIDTH);
    printCell("Nombre", NAME_WIDTH);
    printCell("Estado", STATUS_WIDTH);
    printCell("Libro", BOOK_WIDTH);
    printCell("ID Ejemplar", COPY_WIDTH);
    printCell("Entrega Tardía", LATE_WIDTH);
    printf("\n");
    printf("+----------+--------------+----------------------+--------------+--------------------------------+-------------+----------------+\n");
}


/**
 * @brief Imprime el encabezado tabular de los préstamos próximos a vencer.
 * @param DATE_WIDTH Ancho de la columna de fecha.
 * @param STATUS_WIDTH Ancho de la columna de estado.
 * @return void
 */
void printExpiringLoansHeader(const int DATE_WIDTH, const int STATUS_WIDTH ) {
    printf("+----------+--------------+----------------------+-----------------+----------------------+--------------------------------+-------------+\n");
    printf("|");
    printCell("ID", ID_WIDTH);
    printCell("ID Usuario", USER_ID_WIDTH);
    printCell("Nombre", NAME_WIDTH);
    printCell("Fecha Entrega", DATE_WIDTH);
    printCell("Estatus", STATUS_WIDTH);
    printCell("Libro", BOOK_WIDTH);
    printCell("ID Ejemplar", COPY_WIDTH);
    printf("\n");
    printf("+----------+--------------+----------------------+-----------------+----------------------+--------------------------------+-------------+\n");
}


/**
 * @brief Busca un usuario en un array cargado en memoria
 * @param users Array de usuarios
 * @param userCount Número de usuarios en el array
 * @param userID ID del usuario a buscar
 * @return Puntero al usuario encontrado, o NULL si no se encuentra
 */
static struct User* findUserInMemory(struct User* users, int userCount, const char* userID) {
    if (!users || !userID) return NULL;

    for (int i = 0; i < userCount; i++) {
        if (users[i].ID && strcmp(users[i].ID, userID) == 0) {
            return &users[i];
        }
    }
    return NULL;
}


/**
 * @brief Imprime una fila individual para el historial de préstamos.
 * @param loan El préstamo a imprimir.
 * @param user El usuario asociado al préstamo.
 * @param currentStatus El estado actual del préstamo.
 * @param lateReturn Indica si el préstamo se ha devuelto tarde.
 */
static void printHistoryRow(struct Loan loan, struct User* user, const char* currentStatus, const char* lateReturn) {
    printf("|");
    
    char *copyLoanID = malloc(20 * sizeof(char));
    if (copyLoanID) { 
        snprintf(copyLoanID, 20, "%d", loan.loanID); 
        printCell(copyLoanID, ID_WIDTH); 
        free(copyLoanID); 
    }
    
    printCell(loan.userID ? loan.userID : "Desconocido", USER_ID_WIDTH);
    printCell(user && user->name ? user->name : "Desconocido", NAME_WIDTH);
    printCell(currentStatus ? currentStatus : "Desconocido", 12);
    printCell(loan.bookName ? loan.bookName : "Desconocido", BOOK_WIDTH);
    
    char *copyID = malloc(20 * sizeof(char));
    if (copyID) { 
        snprintf(copyID, 20, "%d", loan.bookCopyNumber); 
        printCell(copyID, COPY_WIDTH); 
        free(copyID); 
    }
    
    printCell(lateReturn, 14);
    printf("\n");
    printf("+----------+--------------+----------------------+--------------+--------------------------------+-------------+----------------+\n");
}


/**
 * @brief Imprime una fila individual para los préstamos próximos a vencer.
 * @param loan El préstamo a imprimir.
 * @param user El usuario asociado al préstamo.
 * @param currentStatus El estado actual del préstamo.
 */
static void printExpiringRow(struct Loan loan, struct User* user, const char* currentStatus) {
    printf("|");
    
    char *copyLoanID = malloc(20 * sizeof(char));
    if (copyLoanID) { 
        snprintf(copyLoanID, 20, "%d", loan.loanID); 
        printCell(copyLoanID, ID_WIDTH); 
        free(copyLoanID); 
    }
    
    printCell(loan.userID ? loan.userID : "Desconocido", USER_ID_WIDTH);
    printCell(user && user->name ? user->name : "Desconocido", NAME_WIDTH);
    printCell(loan.returnDate ? loan.returnDate : "Desconocida", 15);
    printCell(currentStatus, 20);
    printCell(loan.bookName ? loan.bookName : "Desconocido", BOOK_WIDTH);
    
    char *copyID = malloc(20 * sizeof(char));
    if (copyID) { 
        snprintf(copyID, 20, "%d", loan.bookCopyNumber); 
        printCell(copyID, COPY_WIDTH); 
        free(copyID); 
    }
    
    printf("\n");
    printf("+----------+--------------+----------------------+-----------------+----------------------+--------------------------------+-------------+\n");
}


/**
 * @brief Imprime el historial de préstamos en un formato tabular optimizado.
 */
void printLoanHistory(struct Loan *loans, int loanCount, long startDays, long endDays) {
    const int STATUS_WIDTH = 12;
    const int LATE_WIDTH = 14;

    char *systemDate = malloc(12 * sizeof(char));
    if (systemDate == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    getSystemDate(systemDate, 12);
    long sysDays = parseDays(systemDate);

    int totalUsers = 0;
    struct User *allUsers = NULL;
    getAllUsers(USERS_FILE_PATH, &allUsers, &totalUsers);

    printLoanHistoryHeader(STATUS_WIDTH, LATE_WIDTH);   
    int found = 0;

    for (int i = 0; i < loanCount; i++) {
        long returnDays = parseDays(loans[i].returnDate);

        if (returnDays >= startDays && returnDays <= endDays) {
            found = 1;

            struct User *user = findUserInMemory(allUsers, totalUsers, loans[i].userID);
            char *lateReturn = "N/A";
            
            char *displayStatus = loans[i].status;

            if (loans[i].status && strcmp(loans[i].status, "finalizado") == 0) {
                long actualDays = parseDays(loans[i].actualReturnDate);

                if (actualDays > returnDays) {
                    lateReturn = "Sí";
                } else {
                    lateReturn = "No";
                }
            } else {
                if (sysDays > returnDays) {
                    displayStatus = "vencido";
                }
            }
            
            printHistoryRow(loans[i], user, displayStatus, lateReturn);
        }
    }

    if (!found) {
        printf("|");
        printCell("No se encontraron préstamos en el rango indicado.", 125);
        printf("\n");
        printf("+-------------------------------------------------------------------------------------------------------------------------------+\n");
    }

    free(systemDate);
    printf("\n");

    if (allUsers != NULL) {
        freeAllUsers(allUsers, totalUsers);
    }
}


/**
 * @brief Muestra el historial de préstamos.
 * @param loans Un puntero a un array de estructuras Loan.
 * @param loanCount El número de préstamos en el array.
 * @return void
 */
void loanHistory(struct Loan* loans, int loanCount) {
    char* startDate = NULL;
    char* endDate = NULL;
    int cancelFlag = 0;

    do {
        clearScreen();
        loanHistoryMessage();

        startDate = validateUserInput("Fecha de inicio: ", &loanHistoryMessage, &cancelFlag);
        if (cancelFlag) {
            clearScreen();
            return;
        }

        if (isValidDateFormat(startDate) == 0) {
            printf("Error: Formato de fecha inicio inválido.\n");
            pauseScreen();
            free(startDate);
            continue;
        }
        
        if (!cancelFlag) {
            endDate = validateUserInput("Fecha de fin: ", &loanHistoryMessage, &cancelFlag);
        }

        if (cancelFlag) {
            if (startDate) free(startDate);
            if (endDate) free(endDate);
            clearScreen();
            return;
        }

        if (isValidDateFormat(endDate) == 0) {
            printf("Error: Formato de fecha fin inválido.\n");
            pauseScreen();
            free(startDate);
            free(endDate);
            continue;
        }

        if(strcmp(startDate, endDate) > 0) {
            printf("Error: La fecha de inicio no puede ser mayor que la fecha de fin.\n");
            pauseScreen();
            free(startDate);
            free(endDate);
            continue;
        }

        if(parseDays(startDate) < 0 || parseDays(endDate) < 0) {
            printf("Error: Una de las fechas es de formato 0000-00-00.\n");
            pauseScreen();
            free(startDate);
            free(endDate);
            continue;
        }

        long startDays = parseDays(startDate);
        long endDays = parseDays(endDate);
        
        printLoanHistory(loans, loanCount, startDays, endDays);
        free(startDate);
        free(endDate);

        pauseScreen();
        clearScreen();
    } while (1);
}


/**
 * @brief Muestra los préstamos que están vencidos o próximos a vencer.
 * @param loans Un puntero a un array de estructuras Loan.
 * @param loanCount El número de préstamos en el array.
 * @return void
 */
void printExpiringLoans(struct Loan* loans, int loanCount) {
    char* systemDate = malloc(12 * sizeof(char));
    if (systemDate == NULL) {
        printf("Error: No se pudo asignar memoria para la fecha del sistema.\n");
        return;
    }
    
    getSystemDate(systemDate, 12);
    long sysDays = parseDays(systemDate);

    const int DATE_WIDTH = 15;
    const int STATUS_WIDTH = 20;

    int totalUsers = 0;
    struct User *allUsers = NULL;
    getAllUsers(USERS_FILE_PATH, &allUsers, &totalUsers);

    printf("\n--- Vencimientos y Próximos a Vencer (Fecha Sistema: %s) ---\n", systemDate);
    printExpiringLoansHeader(DATE_WIDTH, STATUS_WIDTH);

    int found = 0;

    for (int i = 0; i < loanCount; i++) {
        if (loans[i].status && strcmp(loans[i].status, "finalizado") == 0) continue;

        long expectedReturnDays = parseDays(loans[i].returnDate);
        long diffDays = expectedReturnDays - sysDays;

        char *currentStatus = NULL;

        if (diffDays < 0) {
            currentStatus = "Vencido";
        } else if (diffDays >= 0 && diffDays <= 5) {
            currentStatus = "Próximo a vencer";
        }

        if (currentStatus != NULL) {
            found = 1;
            
            struct User *user = findUserInMemory(allUsers, totalUsers, loans[i].userID);
            
            printExpiringRow(loans[i], user, currentStatus);
        }
    }

    if (!found) {
        printf("|");
        printCell("No se encontraron préstamos vencidos o próximos a vencer.", 134);
        printf("\n");
        printf("+----------------------------------------------------------------------------------------------------------------------------------------+\n"); 
    }

    printf("\n");
    free(systemDate);
    
    if (allUsers != NULL) {
        freeAllUsers(allUsers, totalUsers);
    }
}


/**
 * @brief Ejecuta una función de característica de préstamo.
 * @param featureFunction Un puntero a la función que implementa la característica de préstamo.
 * @return void
 */
void executeLoanFeature(void (*featureFunction)(struct Loan *, int)) {
    int loanCount = 0;
    struct Loan* loans = parseLoans(LOANS_FILE_PATH, &loanCount);
    
    if (loans != NULL) {
        featureFunction(loans, loanCount);
        
        for(int i = 0; i < loanCount; i++) {
            free(loans[i].userID);
            free(loans[i].bookName);
            free(loans[i].loanDate);
            free(loans[i].returnDate);
            if (loans[i].actualReturnDate) free(loans[i].actualReturnDate);
            if (loans[i].status) free(loans[i].status);
        }

        free(loans);
    } else {
        printf("\n Error al cargar el archivo de préstamos.\n");
    }
}