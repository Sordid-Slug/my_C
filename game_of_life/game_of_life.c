#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define ROWS 25
#define COLUMNS 80
#define min_delay 100
#define max_delay 100000000

void print_matrix(int matrix[ROWS][COLUMNS]);

int neighbour_sum(int buffer[ROWS + 2][COLUMNS + 2], int i, int j);

void matrix_check(int matrix[ROWS][COLUMNS], int buffer[ROWS + 2][COLUMNS + 2]);

void copy_matrix_to_buffer(int matrix[ROWS][COLUMNS], int buffer[ROWS + 2][COLUMNS + 2]);

void input(int matrix[ROWS][COLUMNS]);

void copy_matrix_to_check_die(int matrix[ROWS][COLUMNS], int buffer_for_check_die[ROWS][COLUMNS]);

int equal_of_matrixes(int matrix[ROWS][COLUMNS], int buffer_for_check_die[ROWS][COLUMNS]);

void end_of_game(int matrix[ROWS][COLUMNS], int buffer_for_check_die[ROWS][COLUMNS], bool *Flag);

void game_die(int matrix[ROWS][COLUMNS], int buffer_for_check_die_first[ROWS][COLUMNS],
              int buffer_for_check_die_second[ROWS][COLUMNS], int count_of_epochs, bool *Flag);

void speed_control(int *speed, bool *is_live);

void nullify_buffer(int buffer[ROWS + 2][COLUMNS + 2]);

int main() {
    int matrix[ROWS][COLUMNS];
    int buffer[ROWS + 2][COLUMNS + 2];
    int buffer_for_check_die_first[ROWS][COLUMNS], buffer_for_check_die_second[ROWS][COLUMNS];
    int count_of_epochs = 0;
    bool Flag = true;
    nullify_buffer(buffer);
    if (initscr() == NULL) {
        printf("нет initscr");
        Flag = false;
    }
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    input(matrix);
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        Flag = false;
        printf("не открывается /dev/tty");
    }
    int delay = 100000;
    while (Flag) {
        count_of_epochs++;
        print_matrix(matrix);
        copy_matrix_to_buffer(matrix, buffer);
        matrix_check(matrix, buffer);
        game_die(matrix, buffer_for_check_die_first, buffer_for_check_die_second, count_of_epochs, &Flag);
        usleep(delay);
        speed_control(&delay, &Flag);
        printw("Epoch: %d\nDelay: %d ms", count_of_epochs, (delay));
        refresh();
    }
    refresh();
    endwin();
    return 0;
}

void print_matrix(int matrix[ROWS][COLUMNS]) {
    clear();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (matrix[i][j] == 1) {
                mvprintw(i, j, "#");
            }
        }
        printw("\n");
    }
}

void copy_matrix_to_check_die(int matrix[ROWS][COLUMNS], int buffer_for_check_die[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            buffer_for_check_die[i][j] = matrix[i][j];
        }
    }
}

int equal_of_matrixes(int matrix[ROWS][COLUMNS], int buffer_for_check_die[ROWS][COLUMNS]) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (matrix[i][j] == buffer_for_check_die[i][j]) {
                count += 1;
            }
        }
    }
    if (count == (ROWS * COLUMNS)) {
        return 1;
    }
    return 0;
}

void end_of_game(int matrix[ROWS][COLUMNS], int buffer_for_check_die[ROWS][COLUMNS], bool *Flag) {
    if (equal_of_matrixes(matrix, buffer_for_check_die) == 1) *Flag = false;
}

void game_die(int matrix[ROWS][COLUMNS], int buffer_for_check_die_first[ROWS][COLUMNS],
              int buffer_for_check_die_second[ROWS][COLUMNS], int count_of_epochs, bool *Flag) {
    if ((count_of_epochs % 3 == 0)) {  // проверка на каждом третьем поколении
        end_of_game(matrix, buffer_for_check_die_second, Flag);
        copy_matrix_to_check_die(matrix, buffer_for_check_die_second);
    }
    if ((count_of_epochs % 2 == 0)) {  // проверка на каждом втором поколении
        end_of_game(matrix, buffer_for_check_die_first, Flag);
        copy_matrix_to_check_die(matrix, buffer_for_check_die_first);
    }
}

void speed_control(int *delay, bool *is_live) {
    char c = getch();
    if (c == 'u') {
        *delay -= 5000;
        if (*delay < min_delay) *delay = min_delay;
    } else if (c == 'd') {
        *delay += 5000;
        if (*delay > max_delay) *delay = max_delay;
    } else if (c == 'q')
        *is_live = false;
}

void nullify_buffer(int buffer[ROWS + 2][COLUMNS + 2]) {
    for (int i = 0; i < ROWS + 2; i++) {
        for (int j = 0; j < COLUMNS + 2; j++) {
            buffer[i][j] = 0;
        }
    }
}

int neighbour_sum(int buffer[ROWS + 2][COLUMNS + 2], int i, int j) {
    int sum = 0;
    sum += buffer[i - 1][j - 1] + buffer[i + 1][j + 1] + buffer[i + 1][j] + buffer[i][j + 1] +
           buffer[i - 1][j] + buffer[i][j - 1] + buffer[i - 1][j + 1] + buffer[i + 1][j - 1];
    return sum;
}

void matrix_check(int matrix[ROWS][COLUMNS], int buffer[ROWS + 2][COLUMNS + 2]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int sum = neighbour_sum(buffer, i + 1, j + 1);
            if (buffer[i + 1][j + 1] == 1) {
                if (sum != 3 && sum != 2) matrix[i][j] = 0;
            } else if (buffer[i + 1][j + 1] == 0)
                if (sum == 3) matrix[i][j] = 1;
        }
    }
}

void copy_matrix_to_buffer(int matrix[ROWS][COLUMNS], int buffer[ROWS + 2][COLUMNS + 2]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            buffer[i + 1][j + 1] = matrix[i][j];
        }
    }
    for (int j = 0; j < COLUMNS; j++) {
        buffer[ROWS + 1][j + 1] = matrix[0][j];
    }
    for (int j = 0; j < COLUMNS; j++) {
        buffer[0][j + 1] = matrix[ROWS - 1][j];
    }

    for (int i = 0; i < ROWS; i++) {
        buffer[i + 1][COLUMNS + 1] = matrix[i][0];
    }

    for (int i = 0; i < ROWS; i++) {
        buffer[i + 1][0] = matrix[i][COLUMNS - 1];
    }
    buffer[0][0] = matrix[ROWS - 1][COLUMNS - 1];
    buffer[ROWS + 1][COLUMNS + 1] = matrix[0][0];
    buffer[0][COLUMNS + 1] = matrix[ROWS - 1][0];
    buffer[ROWS + 1][0] = matrix[0][COLUMNS - 1];
}

void input(int matrix[ROWS][COLUMNS]) {
    char temp;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            scanf("%c", &temp);
            matrix[i][j] = (int)temp - 48;
        }
        getchar();
    }
}
