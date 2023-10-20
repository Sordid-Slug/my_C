#include <stdio.h>
#define MAS_LEN 10

int input(int *mas);
void swap();
void bubble_sort(int *mas);
void output(int *mas);

int main() {
    int mas[MAS_LEN];
    if (input(mas) > 0) {
        return 0;
    }
    bubble_sort(mas);
    output(mas);
    return 0;
}

int input(int *mas) {
    printf("Enter a numbers: ");
    for (int i = 0; i < MAS_LEN; i++) {
        if ((scanf("%d", mas + i) != 1 || (i == MAS_LEN - 1 && getchar() != '\n')) ||
            (i != MAS_LEN - 1 && getchar() != ' ')) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}
void swap(int *el_l, int *el_r) {
    int temp = *el_l;
    *el_l = *el_r;
    *el_r = temp;
}

void bubble_sort(int *mas) {
    for (int i = 0; i < MAS_LEN; i++) {
        for (int j = 0; j < MAS_LEN - i - 1; j++) {
            if (mas[j] > mas[j + 1]) {
                swap(mas + j, mas + j + 1);
            }
        }
    }
}

void output(int *mas) {
    for (int i = 0; i < MAS_LEN; i++) {
        printf("%d ", mas[i]);
    }
}
