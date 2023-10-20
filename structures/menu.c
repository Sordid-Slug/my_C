#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "menu.h"
#include "file_moving.h"
#include "MyStruct.h"

void menu() {
    int flag = 1;
    int max_index = 0;
    while (flag) {
        char *choice = malloc(sizeof(char));
        size_t len = 1;
        getline(&choice, &len, stdin);
        choice[strcspn(choice, "\n")] = '\0';
        
        if (strcmp(choice, "0") == 0) {
            printf("enter path to read\n");
            
            char *file_path = malloc(sizeof(char));
            size_t size = 1;
            getline(&file_path, &size, stdin);
            file_path[strcspn(file_path, "\n")] = '\0'; // печать данных из файла
            max_index = file_size(file_path);
            
            FILE *file = fopen(file_path, "rb");
            if (file != NULL) {
                for (int i = 0; i < max_index; i++) {
                    struct Data record = read_record(file, i);
                    print_file(record);
                }
                fclose(file);
            }
            else {
                printf("n/a1\n");
            }
            free(file_path);
        } else if (strcmp(choice, "2") == 0) { // запись в файл
            printf("enter path to write\n");
            
            char *file_path = malloc(sizeof(char));
            size_t size = 1;
            getline(&file_path, &size, stdin);
            file_path[strcspn(file_path, "\n")] = '\0'; // печать данных из файла
            max_index = file_size(file_path);
            
            FILE *file = fopen(file_path, "rb+");
            if (file != NULL) {
                write_file(file);
                fclose(file);
            } else
                printf("n/a5\n");
            free(file_path);
        } else if (strcmp(choice, "-1") == 0) {
            flag = 0;
        } else {
            printf("n/a2\n");
        }
        free(choice);
        printf("\n%d\n", max_index);
    }
}
