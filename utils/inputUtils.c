#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/inputUtils.h"

/**
 * @brief Lee una línea de texto ingresada por el usuario.
 * Lee los caracteres uno por uno y almacena la entrada en memoria
 * dinámica hasta encontrar un salto de línea o EOF.
 * 
 * @return char* Cadena ingresada terminada en '\0', o NULL si
 * ocurre un error de memoria.
 */
char *readInput(void) {
    char *input = NULL;
    char *temp;
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