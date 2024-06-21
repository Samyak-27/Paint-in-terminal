//C file containing functions to paint on  the canvas
#include <stdio.h>
#include <stdlib.h>
#include "paint.h"
#include "canvas.h"
#include "file.h"
#include "commands.h"
#include "print_statements.h"

//Function to draw a line on the canvas
void draw_line(canvas *c, int start_row, int start_col, int end_row, int end_col) {//Parameter include the canvas pointer, the start and end of rows and columns
    // Validate that the coordinates form a straight line
    if (start_row != end_row && start_col != end_col && abs(end_row - start_row) != abs(end_col - start_col)) {
        printf("Invalid coordinates: The given points do not form a straight line.\n");
        return;
    }

    // Validate that the coordinates are within the canvas bounds
    if (start_row < 0 || start_row >= c->rows || end_row < 0 || end_row >= c->rows ||
        start_col < 0 || start_col >= c->cols || end_col < 0 || end_col >= c->cols) {
        printf("Invalid coordinates: Points are outside the canvas bounds.\n");
        return;
    }

    // If start and end points are the same, print a single '-' character
    if (start_row == end_row && start_col == end_col) {
    if (c->data[start_row * c->cols + start_col] == '/' || c->data[start_row * c->cols + start_col] == '\\' || 
        c->data[start_row * c->cols + start_col] == '|' || c->data[start_row * c->cols + start_col] == '+'){
            c->data[start_row * c->cols + start_col] = '+';
            return;
        }
        else{
        c->data[start_row * c->cols + start_col] = '-';
        return;
        }
    }

    // Determine the direction of the line
    int row_step = (start_row < end_row) ? 1 : (start_row > end_row) ? -1 : 0;
    int col_step = (start_col < end_col) ? 1 : (start_col > end_col) ? -1 : 0;

    // Determine the character based on the direction
    char character;
    if (row_step != 0 && col_step != 0 && row_step == col_step) {
        character = '/';  // forward diagonal line
    } else if (row_step != 0 && col_step != 0 && row_step == -col_step) {
        character = '\\';  // Backward diagonal line
    } else if (row_step != 0) {
        character = '|';  // Vertical line
    } else if (col_step != 0) {
        character = '-';  // Horizontal line
    } else {
        character = '*';  // Single cell line
    }

    // Draw the line
    for (int row = start_row, col = start_col; row != end_row + row_step || col != end_col + col_step;
         row += row_step, col += col_step) {
        // Check if the current cell is already occupied
        if (c->data[row * c->cols + col] == ' ' || c->data[row * c->cols + col] == '*') {
            c->data[row * c->cols + col] = character;
        } //Check if the character in the place is same as the charaater to be painted
        else if(c->data[row * c->cols + col] == character){
            c->data[row * c->cols + col] = character;
        }
        else {
            // Intersection, use '+'
            c->data[row * c->cols + col] = '+';
        }
    }
}


//Function to erase a line at a point
void erase_line(canvas *c, int row, int col){// Parameters include canvas pointer and row and column number
    c->data[row * c->cols + col] = '*';
}


//Function to resize the canvas
void resize_canvas(canvas *c, int new_rows, int new_cols) {//Takes in canvas pointer and the new number of rows and columns
    // Allocate memory for the new canvas size
    int *new_data = (int *)malloc(sizeof(int) * new_rows * new_cols);

    if (new_data == NULL) {
        // Memory allocation failed, handle the error
        printf("Memory allocation failed during resize. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the new canvas with empty values
    for (int i = 0; i < new_rows * new_cols; i++) {
        new_data[i] = '*'; //Initializes board to *
    }

    // Copy the existing canvas data to the corresponding position in the new canvas
    int copy_rows = (c->rows < new_rows) ? c->rows : new_rows;
    int copy_cols = (c->cols < new_cols) ? c->cols : new_cols;

    for (int i = 0; i < copy_rows; i++) {
        for (int j = 0; j < copy_cols; j++) {
            new_data[i * new_cols + j] = c->data[i * c->cols + j];
        }
    }

    // Free the old canvas data
    free(c->data);

    // Update the canvas structure with the new dimensions and data
    c->rows = new_rows;
    c->cols = new_cols;
    c->data = new_data;
}


//Function to add a new row at a specefied location
void add_row(canvas *c, int position) {//Takes in canvas pointer and the position where the row will be added
    // Increase the number of rows
    c->rows++;

    // Reallocate memory for the new canvas size
    int *new_data = (int *)realloc(c->data, sizeof(int) * c->rows * c->cols);

    if (new_data == NULL) {
        // Memory allocation failed, handle the error
        printf("Memory allocation failed during add row. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Update the canvas structure with the new data
    c->data = new_data;

    // Shift rows below the new row down
    for (int i = c->rows - 1; i > position; i--) {
        for (int j = 0; j < c->cols; j++) {
            c->data[i * c->cols + j] = c->data[(i - 1) * c->cols + j];
        }
    }

    // Initialize the new row with empty values
    for (int i = 0; i < c->cols; i++) {
        c->data[position * c->cols + i] = '*';
    }
}


//Function to add column at a specefied location
void add_column(canvas *c, int position) {//Takes in canvas pointer and the position where the column will be added
    // Increase the number of columns
    c->cols++;

    // Allocate memory for the new canvas size
    int *new_data = (int *)malloc(sizeof(int) * c->rows * c->cols);

    if (new_data == NULL) {
        // Memory allocation failed, handle the error
        printf("Memory allocation failed during add column. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Copy the existing canvas data to the corresponding positions in the new canvas
    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < position; j++) {
            new_data[i * c->cols + j] = c->data[i * (c->cols - 1) + j];
        }
        // Initialize the new column with empty values
        new_data[i * c->cols + position] = '*';
        for (int j = position + 1; j < c->cols; j++) {
            new_data[i * c->cols + j] = c->data[i * (c->cols - 1) + j - 1];
        }
    }

    // Free the old canvas data
    free(c->data);

    // Update the canvas structure with the new data
    c->data = new_data;
}


//Function to delete a row at a specefied location
void delete_row(canvas *c, int position) {//Takes in canvas pointer and the position where the row will be deleted
    // Decrease the number of rows
    c->rows--;

    // Reallocate memory for the new canvas size
    int *new_data = (int *)realloc(c->data, sizeof(int) * c->rows * c->cols);

    if (new_data == NULL) {
        // Memory allocation failed, handle the error
        printf("Memory allocation failed during delete row. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Update the canvas structure with the new data
    c->data = new_data;

    // Shift rows below the deleted row up
    for (int i = position; i < c->rows; i++) {
        for (int j = 0; j < c->cols; j++) {
            c->data[i * c->cols + j] = c->data[(i + 1) * c->cols + j];
        }
    }
}

//Function to delete a column at a specefied location
void delete_column(canvas *c, int position) {//Takes in canvas pointer and the position where the column will be added
    // Decrease the number of columns
    c->cols--;

    // Allocate memory for the new canvas size
    int *new_data = (int *)malloc(sizeof(int) * c->rows * c->cols);

    if (new_data == NULL) {
        // Memory allocation failed, handle the error
        printf("Memory allocation failed during delete column. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Copy the existing canvas data to the corresponding positions in the new canvas
    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < position; j++) {
            new_data[i * c->cols + j] = c->data[i * (c->cols + 1) + j];
        }
        for (int j = position; j < c->cols; j++) {
            new_data[i * c->cols + j] = c->data[i * (c->cols + 1) + j + 1];
        }
    }

    // Free the old canvas data
    free(c->data);

    // Update the canvas structure with the new data
    c->data = new_data;
}

