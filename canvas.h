//h file for canvas.c
#ifndef CANVAS_H
#define CANVAS_H

typedef struct canvas_t{//defining a struct for the canvas
    int rows;
    int cols;
    int *data;
} canvas;

//Function declarations
canvas *create_canvas(int rows, int cols);
void free_canvas(canvas *c);
void quit(canvas *c);
void print_help();

#endif // CANVAS_H
