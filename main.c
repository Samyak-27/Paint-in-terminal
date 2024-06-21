//Main program to run the paint
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "canvas.h"
#include "file.h"
#include "commands.h"
#include "print_statements.h"

//Funtion to validate input row in command line
int check_row(const char* str) {//takes in the second and third argument vector and a prompt
    int i = 0;

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            // Use atoi to convert the substring starting from i to an integer
            return atoi(&str[i]);
        }
        i++;
    }

    // Return 0 if no integer is found
    return 0;
}


int check_column(const char* str) {//takes in the second and third argument vector and a prompt
    int i = 0;

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            // Use atoi to convert the substring starting from i to an integer
            return atoi(&str[i]);
        }
        i++;
    }

    // Return 0 if no integer is found
    return 0;
}


//Function to validate input in command line
canvas validate_input(int argc, char* argv[]) {
    canvas c;

    // Initialize canvas with default values
    c.rows = 10;
    c.cols = 10;
    c.data = NULL;

    if (argc < 0 || argc == 2 || argc > 3) {//checks for the number of argument counts
        printf("Wrong number of command line arguments entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]\n");
        printf("Making default board of 10 X 10.\n");
    }

    if (argc == 3) {
        if(atoi(argv[1]) < 0){
            printf("The number of rows is less than 1.\n");
            printf("Making default board of 10 X 10.\n");
            return c;
        }
        if(atoi(argv[2]) < 0){
            printf("The number of columns is less than 1.\n");
            printf("Making default board of 10 X 10.\n");
            return c;
        }
        c.rows = check_row(argv[1]);
        c.cols = check_column(argv[2]);
    }

    return c;//returns canvas struct
}

//Main program
int main(int argc, char *argv[]) {
    canvas c;

    c = validate_input(argc, argv);//validate input
    
    //creating canvas with provided number of rows and columns
    canvas *c_ptr = create_canvas(c.rows, c.cols);

    //printing the canvas
    print_canvas(c_ptr);

    char command[100];
    //loop to get user input
    while (1) {

        // Get user input
        printf("Enter your command: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("Error reading command.\n");
            break;
        }

        // Remove trailing newline
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        // Execute the command if it's not empty
        if (strcmp(command, "") != 0) {
            execute_command(c_ptr, command); // executes the command in commands.h
        } else {
            continue;  // Repeat the loop if the user simply presses Enter
        }

        // Break the loop if the user enters "q"
        if (strcmp(command, "q") == 0) {
            break;
        }
    }  // Repeat until the user enters "q"

    // Cleanup: Free allocated memory for the canvas
    free_canvas(c_ptr);

    return 0;
}