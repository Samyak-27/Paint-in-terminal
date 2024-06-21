// Implement functions related to canvas manipulation
#include "canvas.h"
#include <stdio.h>
#include <stdlib.h>

//Function to create and allocate space for the canvas
canvas* create_canvas(int rows, int cols) {
    canvas *c = (canvas *)malloc(sizeof(canvas));
    if (c == NULL) {
        fprintf(stderr, "Memory allocation error for canvas\n");
        exit(0);
    }
    
    c->rows = rows;
    c->cols = cols;
    c->data = (int *)calloc(rows * cols, sizeof(int));
    if (c->data == NULL) {
        fprintf(stderr, "Memory allocation error for canvas data\n");
        free(c);
        exit(0);
    }
    
    for (int i = 0; i < rows * cols; i++) {
        c->data[i] = '*';
    }


    return c; //returns canvas struct c
}

//Function to free allocated memory space
void free_canvas(canvas *c) {
    free(c->data);
    free(c);
}

//Function to quit the program
void quit(canvas *c) {
    free_canvas(c);
    exit(0);
}

//Function to print the commands for the user
void print_help(){

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

