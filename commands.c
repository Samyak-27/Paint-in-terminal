//C file containing executable directives and validation for paint
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "commands.h"
#include "canvas.h"
#include "paint.h"
#include "print_statements.h"
#include "file.h"

//Function to remove trailing white spaces
void trim_trailing_whitespace(char *str) {//takes in the string as input
    if (str == NULL) {
        return;
    }

    // Find the last non-whitespace character
    int last_char = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            last_char = i;
        }
    }

    // If the string is all whitespaces, set it to an empty string
    if (last_char == -1) {
        str[0] = '\0';
    } else {
        // Trim trailing whitespaces
        str[last_char + 1] = '\0';
    }
}


// Function to execute the write command
void execute_write(canvas *c, const char *params) {//takes in canvas pointer and arguments
    int start_row, start_col, end_row, end_col;
    char character;

    // Attempt to parse the arguments
    if (sscanf(params, "%d %d %d %d %c", &start_row, &start_col, &end_row, &end_col, &character) == 5){
        printf("Improper draw command.\n");
        print_canvas(c);
        return;
    }
    if (sscanf(params, "%d %d %d %d", &start_row, &start_col, &end_row, &end_col) != 4) {
        printf("Improper draw command.\n");
        print_canvas(c);
        return;
    }

    draw_line(c, start_row, start_col, end_row, end_col);

    // Print the updated canvas
    print_canvas(c);
}


// Function to erase the character at the specified position and print the updated canvas
void execute_erase(canvas *c, const char *args) {//takes in canvas pointer and arguments
    int row, col;
    char character;

    // Attempt to parse the arguments
    if (sscanf(args, "%d %d %c", &row, &col, &character) == 3) {
        printf("Improper erase command.\n");
        print_canvas(c);
        return;
    }

    // Read the row and column from the command
    if (sscanf(args, "%d %d", &row, &col) != 2) {
        printf("Improper erase command.\n");
        print_canvas(c);
        return;
    }

    // Check if the provided row and column are within the canvas bounds
    if (row < 0 || row >= c->rows || col < 0 || col >= c->cols) {
        printf("Improper erase command.\n");
        print_canvas(c);
        return;
    }

    // Erase the character at the specified position
    erase_line(c, row, col);

    // Print the updated canvas
    print_canvas(c);
}


//Function to execute the resize command
void execute_resize(canvas *c, const char *args) {//takes in canvas pointer and arguments
    int new_rows, new_cols;
    char character;

    // Attempt to parse the arguments
    if (sscanf(args, "%d %d %c", &new_rows, &new_cols, &character) == 3) {
        printf("Improper resize command.\n");
        print_canvas(c);
        return;
    }

    // Read the new number of rows and columns from the command
    if (sscanf(args, "%d %d", &new_rows, &new_cols) != 2) {
        printf("Improper resize command.\n");
        print_canvas(c);
        return;
    }

    // Validate the new dimensions
    if (new_rows <= 0 || new_cols <= 0) {
        printf("Improper resize command.\n");
        print_canvas(c);
        return;
    }

    // Resize the canvas
    resize_canvas(c, new_rows, new_cols);

    // Print the updated canvas
    print_canvas(c);
}


//Function to execute the add command
void execute_add(canvas *c, const char *args) {//takes in canvas pointer and arguments
    char type;
    int position;

    // Read the type (row or column) and position from the command
    if (sscanf(args, " %c %d", &type, &position) != 2) {
        printf("Improper add command.\n");
        print_canvas(c);
        return;
    }

    // Validate the type
    if (type != 'r' && type != 'c') {
        printf("Improper add command.\n");
        print_canvas(c);
        return;
    }

    // Validate the position
    if (position < 0 || (type == 'r' && position > c->rows) || (type == 'c' && position > c->cols)) {
        printf("Improper add command.\n");
        print_canvas(c);
        return;
    }

    // Add a new row or column based on the type
    if (type == 'r') {
        add_row(c, position);
    } else {
        add_column(c, position);
    }

    // Print the updated canvas
    print_canvas(c);
}


//Function to execute the delete command
void execute_delete(canvas *c, const char *args) {//takes in canvas pointer and arguments
    char type;
    int position;
    char character;

    // Read the type (row or column) and position from the command
    if (sscanf(args, " %c %d %c", &type, &position, &character) == 3 || sscanf(args, " %c %d", &type, &position) != 2) {
        printf("Improper delete command.\n");
        print_canvas(c);
        return;
    }

    // Validate the type
    if (type != 'r' && type != 'c') {
        printf("Improper delete command.\n");
        print_canvas(c);
        return;
    }

    // Validate the position
    if (position < 0 || (type == 'r' && position >= c->rows) || (type == 'c' && position >= c->cols)) {
        printf("Improper delete command.\n");
        print_canvas(c);
        return;
    }

    // Delete a row or column based on the type
    if (type == 'r') {
        delete_row(c, position);
    } else {
        delete_column(c, position);
    }

    // Print the updated canvas
    print_canvas(c);
}


//Function to execute the save file command
void execute_save(const canvas *c, char *filename) {//takes in canvas pointer and arguments
    // Check if the filename is empty
    if (filename[0] == '\0') {
        print_canvas(c);
        return;
    }

    while (isspace(*filename)) {
        filename++;
    }

    trim_trailing_whitespace(filename);

    save_canvas(c, filename);

    print_canvas(c);
}

void execute_load(canvas *c,char *filename) {
    // Check if the filename is empty
    if (filename[0] == '\0') {
        print_canvas(c);
        return;
    }
    
    while (isspace(*filename)) {
        filename++;
    }

    trim_trailing_whitespace(filename);
    // Call the save_canvas function from file.c
    load_canvas(c, filename);

    print_canvas(c);  // Print the loaded canvas

}


//Function to execute the action 
void execute_command(canvas *c, char *command) {//takes in canvas pointer and arguments
    // Parse the command and determine the action to take
    while (isspace(*command)) {
        command++;
    }
    
    char action;

    if (sscanf(command, " %c", &action) != 1) {
        return;
    }

    trim_trailing_whitespace(command);

    switch (action) {
        case 'q':
            if (strlen(command) == 1){
                quit(c);           
                break;
            }else{
                printf("Unrecognized command. Type h for help.\n");
                print_canvas(c);
                break;
            }
        case 'h':
            if (strlen(command) == 1){
                print_help();
                print_canvas(c);
            break;
            }else{
                printf("Unrecognized command. Type h for help.\n");
                print_canvas(c);
                break;
            }
        case 'w':
            execute_write(c, command + 1); // Skip the first character (action)
            break;
        case 'e':
            execute_erase(c, command + 1);
            break;
        case 'r':
            execute_resize(c, command + 1);
            break;
        case 'a':
            execute_add(c, command + 1);
            break;
        case 'd':
            execute_delete(c, command + 1);
            break;
        case 's':
            execute_save(c, command + 1);
            break;
        case 'l':
            execute_load(c, command + 1);
            break;
        default:
            printf("Unrecognized command. Type h for help.\n");
            print_canvas(c);
            break;
    }
}