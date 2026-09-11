#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H


/**
 * @brief lee una línea de texto ingresada por el usuario
 * @return char* puntero a la cadena terminada en '\0', o NULL en caso de que de error
 */
char *readInput(void);

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
int isEmptyString(const char *string);


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
 * @brief cuenta la cantidad de dígitos en un número entero
 * @param number el número del cual contar los dígitos
 * @return int la cantidad de dígitos en el número
 */
int countDigits(int number);


#endif