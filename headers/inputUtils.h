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

#endif