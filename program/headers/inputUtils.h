#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include "./jsonHandler.h"


/**
 * @brief lee una línea de texto ingresada por el usuario
 * @return char* puntero a la cadena terminada en '\0', o NULL en caso de que de error
 */
char* readInput(void);


/**
 * @brief lee una entrada y valida que sea un número entero
 * @return int el número ingresado, o -1 si el input tiene letras o símbolos
 */
int validateInt(void);


/**
 * @brief valida si una cadena está vacía o contiene solo espacios en blanco
 * @param string la cadena a validar
 * @return int 1 si la cadena está vacía o contiene solo espacios en blanco, 0 en caso contrario
 */
int isEmptyString(const char* string);


/**
 * @brief limpia la pantalla
 */
void clearScreen();


/**
 * @brief pausa la ejecución del programa hasta que el usuario presione Enter
 */
void pauseScreen();


/**
 * @brief valida si un ID es válido
 * @param id el ID a validar
 * @return int 1 si el ID es válido, 0 en caso contrario
 */
int validateID(char* id);

/**
 * @brief Valida la entrada del usuario.
 * @param message El mensaje a mostrar al usuario.
 * @param funcion Un puntero a la función que se ejecutará si la entrada es inválida.
 * @param cancelFlag Un puntero a un entero que indica si el usuario desea cancelar.
 * @return char* La entrada del usuario.
 */
char* validateUserInput(const char* message, void (*funcion)(), int* cancelFlag);


/**
 * @brief Calcula la longitud de una cadena ignorando los bytes de continuación UTF-8.
 * @param text La cadena a medir.
 * @return int La cantidad real de caracteres visibles.
 */
int utf8Length(const char* text);


/**
 * @brief Imprime una celda de tabla formateada y alineada.
 * @param text El texto a imprimir.
 * @param width El ancho total que debe ocupar la celda.
 */
void printCell(const char* text, int width);

int dailyRate(int days);

int dailyRateWithPenalty(int days);

int loanAmount(struct Loan *loan);

int parseYearMonth(const char *date, int *year, int *month);


#endif