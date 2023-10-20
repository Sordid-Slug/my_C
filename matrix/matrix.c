//сначала введите выбранный тип выделения памяти под матрицу (1 - статика, 2 - 4 - динамика, затем размер матрицы, затем саму матрицу, можно подряд, можно построчно)
#include <stdio.h>
#include <stdlib.h>

void input(int **mas, int *flag);
void output(int **mas, int n, int m);
void static_alloc(int const n, int const m, int *flag);
void dynamic_1(int **mas, int n, int m, int *flag);
void dynamic_2(int **pointer_arr, int n, int m, int *flag);
void dynamic_3(int **single_array_matrix, int n, int m, int *flag);

int main() {
    int **mas = 0, flag = 0;
    input(mas, &flag);
    if (flag > 0) printf("n/a");
    return 0;
}

void dynamic_1(int **mas, int n, int m, int *flag) {
    mas = (int **)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mas[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &mas[i][j]) != 1) {
                *flag = 1;
                return;
            }
        }
    }
    output(mas, n, m);
    for (int i = 0; i < n; i++) free(mas[i]);
    free(mas);
}

void dynamic_2(int **pointer_arr, int n, int m, int *flag) {
    int *val_arr = malloc(m * n * sizeof(int));
    pointer_arr = malloc(m * n * sizeof(int *));
    for (int i = 0; i < n; i++) pointer_arr[i] = val_arr + m * i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &pointer_arr[i][j]) != 1) {
                *flag = 1;
                return;
            }
        }
    }
    output(pointer_arr, n, m);
    free(pointer_arr);
    free(val_arr);
}

void dynamic_3(int **single_array_matrix, int n, int m, int *flag) {
    single_array_matrix = malloc(m * n * sizeof(int) + n * sizeof(int *));
    int *ptr = (int *)(single_array_matrix + n);
    for (int i = 0; i < n; i++) single_array_matrix[i] = ptr + m * i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &single_array_matrix[i][j]) != 1) {
                *flag = 1;
                return;
            }
        }
    }
    output(single_array_matrix, n, m);
    free(single_array_matrix);
}

void static_alloc(int const n, int const m, int *flag) {
    int mas[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &mas[i][j]) != 1) {
                *flag = 1;
                return;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%d ", mas[i][j]);
        }
        printf("%d\n", mas[i][m - 1]);
    }
}

void input(int **mas, int *flag) {
    int n, m;
    printf("Enter: ");
    int mode;
    if (scanf("%d", &mode) != 1 || getchar() != '\n') {
        *flag = 1;
        return;
    }
    if (scanf("%d %d", &n, &m) != 2 || getchar() != '\n' || n < 0 || m < 0 ||
        (mode == 1 && (n > 100 || m > 100))) {
        *flag = 1;
        return;
    }
    switch (mode) {
        case 1:
            static_alloc(n, m, flag);
            break;
        case 2:
            dynamic_1(mas, n, m, flag);
            break;
        case 3:
            dynamic_2(mas, n, m, flag);
            break;
        case 4:
            dynamic_3(mas, n, m, flag);
            break;
        default:
            break;
    }
}

void output(int **mas, int n, int m) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            printf("%d ", mas[i][j]);
        }
        printf("%d\n", mas[i][m - 1]);
    }
}
