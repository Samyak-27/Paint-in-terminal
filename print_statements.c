//C file to print the canvas and its modifications
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "canvas.h"
#include "file.h"
#include "commands.h"
#include "print_statements.h"

void print_canvas(const canvas *c) {
    // Print the canvas
    for (int i = c->rows - 1; i >= 0; i--) {
        printf("%d ", i);
        for (int j = 0; j < c->cols; j++) {
            printf("%c ", (char)c->data[i * c->cols + j]);
        }
        printf("\n");
    }

    // Print column indices
    printf(" ");
    for (int j = 0; j < c->cols; j++) {
        printf(" %d", j);
    }
    printf("\n");
}