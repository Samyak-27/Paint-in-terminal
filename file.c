//C file for file control functions
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "canvas.h"
#include "file.h"
#include "commands.h"
#include "print_statements.h"

//Function to save the canvas to a file
void save_canvas(const canvas *c, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    // Write the canvas size to the file
    fprintf(file, "%d %d\n", c->rows, c->cols);

    // Write the canvas data to the file
    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < c->cols; j++) {
            fprintf(file, "%c", (char)c->data[i * c->cols + j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

//Function to load a canvas
int load_canvas(canvas *c, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;  // Failed to open file
    }

    // Read the canvas size from the file
    if (fscanf(file, "%d %d", &(c->rows), &(c->cols)) != 2) {
        fclose(file);
        return 0;  // Failed to read canvas size
    }

    // Allocate memory for the canvas data
    c->data = (int *)malloc(c->rows * c->cols * sizeof(int));
    if (c->data == NULL) {
        fclose(file);
        return 0;  // Failed to allocate memory
    }

    // Read the canvas data from the file
    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < c->cols; j++) {
            int value = fgetc(file);
            if (value != EOF && value != '\n') {
                c->data[i * c->cols + j] = (char)value;
            } else {
                // If a newline is encountered, skip it
                j--;
            }
        }
    }

    fclose(file);
    return 1;  // Successful load
}
