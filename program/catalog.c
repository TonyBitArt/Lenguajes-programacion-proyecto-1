#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/catalog.h"
#include "../headers/inputUtils.h"
#include "../headers/jsonHandler.h"

#define BOOKS_FILE "./data/books.json"

int displayCatalogMenu(void) {
    printf("\n--- Submenú de Gestión de Catálogo ---\n");
    printf("%d. Ver ejemplares\n", CATALOG_MENU_VIEW);
    printf("%d. Agregar ejemplar\n", CATALOG_MENU_ADD);
    printf("%d. Editar ejemplar\n", CATALOG_MENU_EDIT);
    printf("%d. Volver\n", CATALOG_MENU_BACK);
    printf("Seleccione una opción: ");
    
    return validateInt();
}

// muestra todos los libros del catálogo
static void viewCatalog(void) {
    int bookCount = 0;
    struct Book *books = parseBooks(BOOKS_FILE, &bookCount);

    if (!books || bookCount == 0) {
        printf("\n No hay libros registrados \n");
        freeBooks(books, bookCount);
        return;
    }

    printf("\n---- LISTA DE LIBROS (%d) ----\n", bookCount);
    for (int i = 0; i < bookCount; i++) {
        printf("Libro %d:\n", i + 1);
        printf("  Nombre: %s\n", books[i].name ? books[i].name : "");
        printf("  Autor: %s\n", books[i].author ? books[i].author : "");
        printf("  Año: %s\n", books[i].year ? books[i].year : "");
        printf("  Género: %s\n", books[i].genre ? books[i].genre : "");
        printf("  Resumen: %s\n", books[i].summary ? books[i].summary : "");
        printf("  Cantidad: %d\n", books[i].quantity);
        printf("-----------------------------\n");
    }

    freeBooks(books, bookCount);
}

/**
 * @brief solicita al usuario los datos de un solo libro y lo guarda en el
 * archivo JSON de catálogo
 * @return void
 */
static void addSingleBook(void) {
    do {
        clearScreen();
        printf("\n--- Agregar libro manualmente ---\n");
        printf("Ingrese los datos del nuevo libro:\n\n");

        printf("Nombre del libro: ");
        char *bookName = readInput();
        if (bookName == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria\n");
            pauseScreen();
            return;
        }
        if (isEmptyString(bookName)) {
            fprintf(stderr, "Error: No se puede ingresar un campo vacío\n");
            free(bookName);
            pauseScreen();
            continue;
        }

        printf("Autor: ");
        char *bookAuthor = readInput();
        if (bookAuthor == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria\n");
            free(bookName);
            pauseScreen();
            return;
        }
        if (isEmptyString(bookAuthor)) {
            fprintf(stderr, "Error: No se puede ingresar un campo vacío\n");
            free(bookName);
            free(bookAuthor);
            pauseScreen();
            continue;
        }

        printf("Año de publicación: ");
        char *bookYear = readInput();
        if (bookYear == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria\n");
            free(bookName);
            free(bookAuthor);
            pauseScreen();
            return;
        }
        if (isEmptyString(bookYear)) {
            fprintf(stderr, "Error: No se puede ingresar un campo vacío\n");
            free(bookName);
            free(bookAuthor);
            free(bookYear);
            pauseScreen();
            continue;
        }

        printf("Género literario: ");
        char *bookGenre = readInput();
        if (bookGenre == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria\n");
            free(bookName);
            free(bookAuthor);
            free(bookYear);
            pauseScreen();
            return;
        }
        if (isEmptyString(bookGenre)) {
            fprintf(stderr, "Error: No se puede ingresar un campo vacío\n");
            free(bookName);
            free(bookAuthor);
            free(bookYear);
            free(bookGenre);
            pauseScreen();
            continue;
        }

        printf("Resumen: ");
        char *bookSummary = readInput();
        if (bookSummary == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria.\n");
            free(bookName);
            free(bookAuthor);
            free(bookYear);
            free(bookGenre);
            pauseScreen();
            return;
        }
        if (isEmptyString(bookSummary)) {
            fprintf(stderr, "Error: No se puede ingresar un campo vacío\n");
            free(bookName);
            free(bookAuthor);
            free(bookYear);
            free(bookGenre);
            free(bookSummary);
            pauseScreen();
            continue;
        }

        printf("Cantidad en inventario: ");
        int bookQuantity = validateInt();

        struct Book newBook;
        newBook.name = bookName;
        newBook.author = bookAuthor;
        newBook.year = bookYear;
        newBook.genre = bookGenre;
        newBook.summary = bookSummary;
        newBook.quantity = bookQuantity;

        if (!saveBook(BOOKS_FILE, newBook)) {
            fprintf(stderr, "Error: el libro ya existe o no se pudo guardar en el archivo JSON\n");
        } else {
            printf("Libro guardado exitosamente\n");
        }

        pauseScreen();
        clearScreen();

        free(bookName);
        free(bookAuthor);
        free(bookYear);
        free(bookGenre);
        free(bookSummary);

        return;
    } while (1);
}

/**
 * @brief lee un archivo de texto con registros separados por '#' y agrega
 * en lote los libros nuevos al catálogo JSON 
 * y muestra un reporte de los registros que no se pudieron procesar
 * @return void
 */
static void addBooksBatch(void) {
    char *filepath = malloc(256 * sizeof(char));
    if (!filepath) {
        fprintf(stderr, "\nError: No se pudo asignar memoria para la ruta\n");
        return;
    }

    printf("\n--- Agregar ejemplares en lote ---\n");
    printf("Ingrese la ruta del archivo de texto (ejemplo: entrada.txt): ");
    scanf("%255s", filepath);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    FILE *file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "\nError: No se pudo abrir el archivo '%s', verifique la ruta\n", filepath);
        free(filepath); // liberar antes de salir
        return;
    }

    char *line = malloc(512 * sizeof(char));
    char *originalLine = malloc(512 * sizeof(char));

    if (!line || !originalLine) {
        fprintf(stderr, "\nError: No se pudo asignar memoria para la lectura\n");
        free(filepath);
        if (line) free(line);
        if (originalLine) free(originalLine);
        fclose(file);
        return;
    }

    int processedCount = 0;
    int errorCount = 0;

    printf("\nProcesando archivo...\n");
    printf("--- Reporte de registros NO procesados ---\n");

    while (fgets(line, 512, file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        strcpy(originalLine, line);

        char *name = strtok(line, "#");
        char *author = strtok(NULL, "#");
        char *yearStr = strtok(NULL, "#");
        char *genre = strtok(NULL, "#");
        char *summary = strtok(NULL, "#");
        char *quantityStr = strtok(NULL, "#");

        if (!name || !author || !yearStr || !genre || !summary || !quantityStr) {
            fprintf(stderr, "- Formato incorrecto: %s\n", originalLine);
            errorCount++;
            continue;
        }

        int quantity = atoi(quantityStr);
        if (quantity <= 0) {
            fprintf(stderr, "- Cantidad inválida: %s\n", originalLine);
            errorCount++;
            continue;
        }

        struct Book newBook;
        newBook.name = name;
        newBook.author = author;
        newBook.year = yearStr;
        newBook.genre = genre;
        newBook.summary = summary;
        newBook.quantity = quantity;

        if (!saveBook(BOOKS_FILE, newBook)) {
            fprintf(stderr, "- El libro ya existe: %s\n", originalLine);
            errorCount++;
            continue;
        }

        processedCount++;
    }

    fclose(file);

    free(filepath);
    free(line);
    free(originalLine);

    printf("------------------------------------------\n");
    printf("Resumen: %d procesados exitosamente, %d no procesados\n", processedCount, errorCount);
}

// controlador para la gestión del catálogo
void handleCatalogOptions(void) {
    int selectedOption;

    do {
        selectedOption = displayCatalogMenu();

        switch (selectedOption) {
            case CATALOG_MENU_VIEW:
                viewCatalog();
                break;

            case CATALOG_MENU_ADD: {
                printf("\n--- Menú de Agregar Ejemplar ---\n");
                printf("1. Agregar un solo libro\n");
                printf("2. Agregar por lote (desde un archivo .txt)\n");
                printf("3. Cancelar y volver\n");
                printf("Seleccione una opción: ");

                int addOption = validateInt();

                switch (addOption) {
                    case 1:
                        addSingleBook();
                        break;
                    case 2:
                        addBooksBatch();
                        break;
                    case 3:
                        printf("\nCancelando ingreso...\n");
                        break;
                    default:
                        printf("\nOpción inválida, volviendo al menú del catálogo...\n");
                        break;
                }
                break;
            }

            case CATALOG_MENU_EDIT:
                printf("\n Editar ejemplar...\n");
                break;

            case CATALOG_MENU_BACK:
                printf("\n Volviendo al menú operativo...\n");
                break;

            default:
                printf("\n Opción inválida, por favor seleccione una opción válida\n");
                break;
        }

    } while (selectedOption != CATALOG_MENU_BACK);
}