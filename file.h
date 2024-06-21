//h file for file.c
#ifndef FILE_H
#define FILE_H

//Function declarations
void save_canvas(const canvas *c, const char *filename);
int load_canvas(canvas *c, const char *filename);

#endif // FILE_H
