#include <stdio.h>
#define MAX_LEN 10

void input(int *mas, int *n, int *c, int *flag);
void swap(int *mas, int a, int b);
void cycle_shift(int *mas, int n, int c);
void output(int const *mas, int n);

int main() {
    int mas[MAX_LEN], n = 0, c, flag = 0;
    input(mas, &n, &c, &flag);
    if (flag > 0) {
        printf("n/a");
        return 0;
    } else {
        cycle_shift(mas, n, c);
        output(mas, n);
    }

    return 0;
}

void input(int *mas, int *n, int *c, int *flag) {
    printf("Enter: ");
    if (scanf("%d", n) != 1 || getchar() != '\n' || *n > MAX_LEN || *n <= 0) {
        *flag = 1;
        return;
    }
    for (int i = 0; i < *n; i++)
        if (scanf("%d", mas + i) != 1 || (i != *n - 1 && getchar() != ' ') ||
            (i == *n - 1 && getchar() != '\n')) {
            *flag = 3;
            return;
        }
    if (scanf("%d", c) != 1 && getchar() != '\n') *flag = 3;
}

void swap(int *mas, int a, int b) {
    int temp = mas[a];
    mas[a] = mas[b];
    mas[b] = temp;
}

void cycle_shift(int *mas, int n, int c) {
    if (c == 0) return;
    if (c > 0) {
        for (int k = 0; k < c; k++) {
            for (int i = 1; i < n; i++) {
                swap(mas, i - 1, i);
            }
        }
    } else {
        c = -c;
        for (int k = 0; k < c; k++) {
            for (int i = n - 1; i > 0; i--) {
                swap(mas, i, i - 1);
            }
        }
    }
}

void output(int const *mas, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", mas[i]);
    }
    printf("%d", mas[n - 1]);
}
