#include <stdio.h>
#include <stdlib.h>

void input(int **mas, int *MAS_LEN, int *flag);
void swap(int *el_l, int *el_r);
void bubble_sort(int *mas, int n);
void output(int *mas, int n);

int main() {
    int *mas, MAS_LEN, flag = 0;
    input(&mas, &MAS_LEN, &flag);
    if (flag > 0) {
        printf("n/a");
        return 0;
    }
    bubble_sort(mas, MAS_LEN);
    output(mas, MAS_LEN);
    free(mas);
    return 0;
}

void input(int **mas, int *MAS_LEN, int *flag) {
    printf("Enter: ");
    if (scanf("%d", MAS_LEN) != 1 && getchar() != '\n') {
        *flag = 1;
        return;
    }
    *mas = (int *)malloc(*MAS_LEN * sizeof(int));
    if (*mas) {
        for (int i = 0; i < *MAS_LEN; i++) {
            if (scanf("%d", *mas + i) != 1) {
                *flag = 2;
                break;
            }
        }
    } else
        *flag = 4;
}
void swap(int *el_l, int *el_r) {
    int temp = *el_l;
    *el_l = *el_r;
    *el_r = temp;
}

void bubble_sort(int *mas, int MAS_LEN) {
    for (int i = 0; i < MAS_LEN; i++) {
        for (int j = 0; j < MAS_LEN - i - 1; j++) {
            if (mas[j] > mas[j + 1]) {
                swap(mas + j, mas + j + 1);
            }
        }
    }
}

void output(int *mas, int MAS_LEN) {
    for (int i = 0; i < MAS_LEN; i++) {
        printf("%d ", mas[i]);
    }
}
