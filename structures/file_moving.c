#include <stdio.h>

#include "file_moving.h"
#include "MyStruct.h"

struct Data read_record(FILE *file, int index) {
    int offset = index * sizeof(struct Data);
    fseek(file, offset, SEEK_SET);
    
    struct Data record;
    fread(&record, sizeof(struct Data), 1, file);
    
    rewind(file);
    return record;
}

int file_size(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

void print_file(struct Data data) {
    printf("%d ", data.year);
    printf("%d ", data.month);
    printf("%d ", data.day);
    printf("%d ", data.hour);
    printf("%d ", data.min);
    printf("%d ", data.sec);
    printf("%d ", data.status);
    printf("%d\n", data.code);
}

void write_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    
    struct Data data;
    if (scanf("%d%d%d%d%d%d%d%d", &data.year, &data.month, &data.day, &data.hour, &data.min, &data.sec, &data.status, &data.code) == 8 && getchar() == '\n')
        fwrite(&data, sizeof(struct Data), 1, file);
    else
        printf("n/a4");
    
    rewind(file);
}
