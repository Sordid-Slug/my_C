#ifndef file_moving_h
#define file_moving_h

#include <stdio.h>

#include "MyStruct.h"

struct Data read_record(FILE *file, int index);
void print_file(struct Data data);
void write_file(FILE *file);
int file_size(const char *file_path);

#endif
