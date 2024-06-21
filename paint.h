//h file for paint.c
#ifndef PAINT_H
#define PAINT_H

#include "canvas.h"

//Function declarations
void draw_line(canvas *c, int start_row, int start_col, int end_row, int end_col);
void erase_line(canvas *c, int row, int col);
void resize_canvas(canvas *c, int new_rows, int new_cols);
void add_row(canvas *c, int position);
void add_column(canvas *c, int position);
void delete_row(canvas *c, int position);
void delete_column(canvas *c, int position);

#endif // PAINT_H
