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
 * @brief Cuenta la cantidad de dígitos en un número entero
 * @param number El número del cual contar los dígitos
 * @return int la cantidad de dígitos en el número
 */
int countDigits(int number) {
    if (number == 0) return 1;
    
    int count = 0;
    while (number != 0) {
        number /= 10;
        count++;
    }

    return count;
}


/**
 * @brief Valida si un ID es válido
 * @param id El ID a validar
 * @return int 1 si el ID es válido, 0 en caso contrario
 */
int validateID(int id) {
    if (id < 0) {
        printf("Error: El ID no puede ser negativo.\n");
        return 0;
    }

    if (countDigits(id) > 9) {
        printf("Error: El ID no tiene 9 dígitos.\n");
        return 0;
    }

    int firstDigit = id / 100000000;
    if (firstDigit < 1 || firstDigit > 9) {
        printf("Error: El primer dígito del ID debe estar entre 1 y 9.\n");
        return 0;
    }

    return 1;
}


/**
 * @brief Guarda un objeto JSON en un archivo.
 * @param path La ruta del archivo donde se guardará el JSON.
 * @param jsonObject El objeto JSON a guardar.
 * @return int 1 si se guardó exitosamente, 0 si ocurrió un error.
 */
int saveJsonToFile(const char *path, cJSON *jsonObject) {
    if (!jsonObject) {
        return 0;
    }

    char *jsonString = cJSON_Print(jsonObject);
    if (!jsonString) {
        return 0;
    }

    FILE *file = fopen(path, "wb");
    if (!file) {
        free(jsonString);
        return 0;
    }

    fwrite(jsonString, sizeof(char), strlen(jsonString), file);
    fclose(file);

    free(jsonString);
    return 1;
}