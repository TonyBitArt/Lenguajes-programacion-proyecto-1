// Includes de la librería estándar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Includes de los archivos de cabecera del proyecto
#include "../headers/jsonHandler.h"
#include "../headers/inputUtils.h"
#include "../headers/dateUtils.h"


/**
 * @brief Lee una línea de texto ingresada por el usuario.
 * Lee los caracteres uno por uno y almacena la entrada en memoria
 * dinámica hasta encontrar un salto de línea o EOF.
 * 
 * @return char* Cadena ingresada terminada en '\0', o NULL si
 * ocurre un error de memoria.
 */
char* readInput(void) {
    char* input = NULL;
    char* temp;
    int size = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        temp = realloc(input, (size + 1) * sizeof(char));

        if (temp == NULL) {
            free(input);
            return NULL;
        }

        input = temp;
        input[size] = character;
        size++;
    }

    temp = realloc(input, (size + 1) * sizeof(char));

    if (temp == NULL) {
        free(input);
        return NULL;
    }

    input = temp;
    input[size] = '\0';

    return input;
}


/**
 * @brief Lee una entrada y valida que sea un número entero.
 * @return int El número ingresado, o -1 si el input tiene letras o símbolos.
 */
int validateInt(void) {
    char *input = readInput();
    if (input == NULL) {
        return -1;
    }

    int esNumero = 1;
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            esNumero = 0;
            break;
        }
    }

    int selection = -1;
    if (esNumero && strlen(input) > 0) {
        selection = atoi(input);
    }

    free(input);   
    return selection;
}


/**
 * @brief Valida la entrada del usuario.
 * @param message El mensaje a mostrar al usuario.
 * @param funcion Un puntero a la función que se ejecutará si la entrada es inválida.
 * @param cancelFlag Un puntero a un entero que indica si el usuario desea cancelar.
 * @return char* La entrada del usuario.
 */
char* validateUserInput(const char* message, void (*funcion)(), int* cancelFlag) {
    while(1) {
        printf("%s", message);
        char* input = readInput();

        if (input == NULL) {
            printf("Error: No se pudo asignar memoria.\n");
            *cancelFlag = 1;
            return NULL;
        }

        if (strcmp(input, "0") == 0) {
            free(input);
            *cancelFlag = 1;
            return NULL;
        }

        if (isEmptyString(input)) {
            printf("Error: No se puede ingresar un campo vacío.\n");
            pauseScreen();
            clearScreen();
            funcion();
            free(input);
            continue;
        }

        return input;
    }
}


/**
 * @brief Verifica si una cadena de caracteres está vacía o contiene solo espacios en blanco.
 * @param string La cadena a verificar.
 * @return int 1 si la cadena está vacía o contiene solo espacios en blanco, 0 en caso contrario.
 */
int isEmptyString(const char* string) {
    if (string == NULL) {
        return 1;
    }
    while (*string) {
        if (!isspace((unsigned char)*string)) {
            return 0;
        }
        string++;
    }
    return 1;
}


/**
 * @brief Limpia la pantalla de la consola.
 * Dependiendo del sistema operativo, ejecuta el comando adecuado para limpiar la pantalla.
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


/**
 * @brief Pausa la ejecución del programa hasta que el usuario presione Enter.
 */
void pauseScreen() {
    printf("Presione Enter para continuar: ");
    free(readInput());
}


/**
 * @brief Valida si un ID es válido
 * @param id El ID a validar
 * @return int 1 si el ID es válido, 0 en caso contrario
 */
int validateID(char* id) {
    if (id[0] == '-') {
        printf("Error: El ID no puede ser negativo.\n");
        return 0;
    }

    if (strlen(id) > 9) {
        printf("Error: El ID no tiene 9 dígitos.\n");
        return 0;
    }

    if (id[0] < '1' || id[0] > '9') {
        printf("Error: El primer dígito del ID debe estar entre 1 y 9.\n");
        return 0;
    }

    return 1;
}

/**
 * @brief Calcula la longitud de una cadena ignorando los bytes de continuación UTF-8.
 * @param text La cadena a medir.
 * @return int La cantidad real de caracteres visibles.
 */
int utf8Length(const char* text) {
    int length = 0;

    if (text == NULL) {
        return 0;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if ((text[i] & 0xC0) != 0x80) {
            length++;
        }
    }

    return length;
}


/**
 * @brief Imprime una celda de tabla formateada y alineada.
 * @param text El texto a imprimir.
 * @param width El ancho total que debe ocupar la celda.
 */
void printCell(const char* text, int width){
    int length = utf8Length(text);
    printf(" %s", text ? text : "N/A");

    for (int i = length; i < width; i++) {
        printf(" ");
    }

    printf(" |");
}

int parseYearMonth(const char *date, int *year, int *month) {
    if (!date) return -1;
    int y, m, d;
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) != 3) return -1;
    *year = y;
    *month = m;
    return 0;
}

int dailyRate(int days) {
    if (days >= 1 && days <= 7) return 175;
    if (days >= 8 && days <= 15) return 150;
    return 100; /* 16 dias o mas */
}

int dailyRateWithPenalty(int days) {
    if (days >= 1 && days <= 7) return 100;
    if (days >= 8 && days <= 15) return 75;
    return 50; /* 16 dias o mas */  
}

int loanAmount(struct Loan *loan) {

    int loanAmount = 0;

    // Calcular tarifa diaria normal

    long start = parseDays(loan->loanDate);
    long end = parseDays(loan->returnDate);

    if (start < 0 || end < 0) return 0;
    int days = (int)(end - start);
    if (days < 1) days = 1; // prestamos del mismo dia cuentan como 1 dia
    loanAmount += days * dailyRate(days);

    // Calcular tarifa diaria con penalización si el libro fue devuelto tarde

    if (loan->actualReturnDate) {
        start = parseDays(loan->returnDate);
        end = parseDays(loan->actualReturnDate);

        if (start < 0 || end < 0) return loanAmount;
        days = (int)(end - start);
        if (days > 0) {
            loanAmount += days * dailyRateWithPenalty(days);
        }
    }
    return loanAmount;
}
