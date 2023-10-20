// 1 - чтение из файла, 2 - запись в файл. Потом вводите имя директории с "/" в конце.
// 3 - шифр Цезаря. Вводите имя директории с "/" в конце. В данном случае это "for_cipher/", потом сдвиг по алфавиту, и файлы .c все будут зашифрованы, а .h полностью очищены.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void open_print_folder(char *folder_path, int *flag) {
    folder_path[strcspn(folder_path, "\n")] = '\0';
    FILE *file = fopen(folder_path, "r");
    if (file != NULL) {
        if (fgetc(file)) {
            fseek(file, 0, SEEK_SET);
            size_t fstr_len = 0;
            char *fstr = malloc(sizeof(char));
            while (getline(&fstr, &fstr_len, file) != -1) printf("%s", fstr);
            free(fstr);
            fclose(file);
        } else {
            *flag = 0;
            fclose(file);
        }
    } else
        *flag = 0;
}

void open_Write_folder(char *folder_path, int *flag) {
    folder_path[strcspn(folder_path, "\n")] = '\0';
    FILE *file = fopen(folder_path, "r");
    if (file == NULL) {
        *flag = 0;
        return;
    } else {
        fclose(file);
        file = fopen(folder_path, "a");
    }
    char *teXtToAdd = NULL;
    size_t put_len = 1;
    getline(&teXtToAdd, &put_len, stdin);
    fprintf(file, "\n%s", teXtToAdd);
    free(teXtToAdd);
    fclose(file);
}

char *filename_assemble(char *direct, char *eXp) {
    char *ls = "ls ";
    int command_len = strlen(ls) + strlen(eXp) + strlen(direct) + 1;
    char *command = malloc(command_len * sizeof(char));
    strcpy(command, ls);
    strcat(command, direct);
    strcat(command, eXp);
    return command;
}

void hcrypt(FILE *fp) {
    char filename[256];
    while (fgets(filename, sizeof(filename), fp) != NULL) {
        filename[strcspn(filename, "\n")] = '\0';
        FILE *cfile = fopen(filename, "w");
        if (cfile == NULL) {
            printf("n/a");
        } else
            fclose(cfile);
    }
}

void ccrypt(FILE *fpc) {
    int shift;
    if (scanf("%d", &shift) != 1 && getchar() != '\n') {
        printf("n/a\n");
        return;
    }
    char filename[256];
    while (fgets(filename, sizeof(filename), fpc) != NULL) {
        filename[strcspn(filename, "\n")] = '\0';
        FILE *cfile = fopen(filename, "r+");
        if (cfile == NULL) {
            printf("n/a");
            return;
        }  // открываются файлы из вывода команды
        char ch;
        while ((ch = fgetc(cfile)) != EOF) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = (ch - 'A' + shift) % 26 + 'A';
                fseek(cfile, -1, SEEK_CUR);
                fputc(ch, cfile);
            } else if (ch >= 'a' && ch <= 'z') {
                ch = (ch - 'a' + shift) % 26 + 'a';
                fseek(cfile, -1, SEEK_CUR);
                fputc(ch, cfile);
            }
        }
        fclose(cfile);
    }
}

void encrypt() {
    char *direct = malloc(sizeof(char));
    size_t len_dir = 1;
    if (getline(&direct, &len_dir, stdin) == -1) {
        printf("1n/a\n");
        free(direct);
        return;
    };
    direct[strcspn(direct, "\n")] = '\0';
    char *command = filename_assemble(direct, "*.h");   // считали директорию
    char *commandc = filename_assemble(direct, "*.c");  //
    FILE *fp = popen(command, "r");                     // выполнили команду ls
    hcrypt(fp);
    pclose(fp);

    FILE *fpc = popen(commandc, "r");
    ccrypt(fpc);
    pclose(fpc);

    free(direct);
    free(command);
    free(commandc);
}

void menu() {  // сделай проверку на ввод choice
    int flag = 1;
    while (flag) {
        char *choice = malloc(sizeof(char));
        size_t len = 1;
        if (getline(&choice, &len, stdin) == -1) flag = 0;
        int flagna = 1;
        if (strcmp(choice, "1\n") == 0) {
            char *folder_path = malloc(sizeof(char));
            size_t path_len = 1;
            if (getline(&folder_path, &path_len, stdin) == -1) {
                printf("n/a\n");
                free(folder_path);
                return;
            }
            open_print_folder(folder_path, &flagna);
            if (!flagna) printf("n/a\n");
            free(folder_path);
        } else if (strcmp(choice, "-1\n") == 0) {
            flag = 0;
        } else if (strcmp(choice, "2\n") == 0) {
            char *folder_path = malloc(sizeof(char));
            size_t path_len = 1;
            if (getline(&folder_path, &path_len, stdin) == -1) {
                printf("n/a\n");
                free(folder_path);
                return;
            }
            open_Write_folder(folder_path, &flagna);
            open_print_folder(folder_path, &flagna);
            if (!flagna) printf("n/a\n");
            free(folder_path);
            printf("\n");
        } else if (strcmp(choice, "3\n") == 0) {
            encrypt();
            getchar();
            // clearbuffer();
        } else
            printf("n/a\n");
        free(choice);
    }
}

int main() {
    menu();
    return 0;
}

