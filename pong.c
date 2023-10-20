#include <stdio.h>

#define X_length 80
#define Y_length 25

void print(int bogie1_y, int bogie2_y, int ball_x, int ball_y);
int score1(int score_player1, int ball_x);
int score2(int score_player2, int ball_x);

int main() {
    int score_player1 = 0, score_player2 = 0, winning_score = 21;
    int ball_x = 40, ball_y = 13, ball_x_dir = 1, ball_y_dir = 1;
    int bogie1_y = 11, bogie2_y = 13;
    int temp_score_player2 = 0, temp_score_player1 = 0;
    printf("Player 1: %d", score_player1);
    for (int i = 0; i < 60; i++) {
        printf(" ");
    }
    printf("Player 2: %d\n", score_player2);
    
    print(bogie1_y, bogie2_y, ball_x, ball_y);
    char ch = ' ';
    while (ch != 'p') {
        
        if (ball_y == 1 || ball_y == 25) {
            ball_y_dir = -ball_y_dir;
        }
        if (ball_x == 2) {
            if (ball_y == bogie1_y) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = 1;
            } else if (ball_y == bogie1_y - 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = 0;
            } else if (ball_y == bogie1_y - 2) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = -1;
            }
        } else if (ball_x == 79) {
            if (ball_y == bogie2_y) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = 1;
            } else if (ball_y == bogie2_y - 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = 0;
            } else if (ball_y == bogie2_y - 2) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = -1;
            }
        }
        ch = getchar();
        switch (ch) {
            case 'k':
                if (bogie2_y < 25) bogie2_y++;
                break;
            case 'm':
                if (bogie2_y > 3) bogie2_y--;
                break;
            case 'a':
                if (bogie1_y < 25) bogie1_y++;
                break;
            case 'z':
                if (bogie1_y > 3) bogie1_y--;
                break;
            case ' ':
                break;
            default:
                break;
        }
        temp_score_player1 = score1(score_player1, ball_x);
        temp_score_player2 = score2(score_player2, ball_x);
        printf("Player 1: %d", score_player1);
        for (int i = 0; i < 60; i++) {
            printf(" ");
        }
        printf("Player 2: %d\n", score_player2);
        if (temp_score_player1 != score_player1 || temp_score_player2 != score_player2) {
            ball_x = 40;
            ball_y = 13;
        }
        ball_x += ball_x_dir;
        ball_y += ball_y_dir;
        print(bogie1_y, bogie2_y, ball_x, ball_y);
        score_player1 = score1(score_player1, ball_x);
        score_player2 = score2(score_player2, ball_x);
        if (score_player1 >= winning_score) {
            printf("Победа первого игрока");
            return 0;
        }
        else if (score_player2 >= winning_score) {
            printf("Победа второго игрока");
            return 0;
        }
    }
    return 0;
}

void print(int bogie1_y, int bogie2_y, int ball_x, int ball_y) {
    for (int i = 0; i < 82; i++) {
        printf("=");
    }
    printf("\n");
    int bogie_length = 3, bogie2_length = 3;
    int is_bogie1 = 0, is_bogie2 = 0;
    for (int y = 25; y >= 1; y--) {
        printf("|");
        // bogie1_print
        if (bogie_length == 0) {
            is_bogie1 = 0;
        }
        if (is_bogie1 == 1) {
            printf("|");
            bogie_length--;
        } else if (y != bogie1_y) {
            printf(" ");
        }
        if (y == bogie1_y) {
            is_bogie1 = 1;
            bogie_length--;
            printf("|");
        }
        //---------------------
        for (int x = 2; x < 80; x++) {
            if (x == ball_x && y == ball_y) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        // bogie2_print
        if (bogie2_length == 0) {
            is_bogie2 = 0;
        }
        if (is_bogie2 == 1) {
            printf("|");
            bogie2_length--;
        } else if (y != bogie2_y) {
            printf(" ");
        }
        if (y == bogie2_y) {
            is_bogie2 = 1;
            bogie2_length--;
            printf("|");
        }
        //---------------------
        printf("|\n");
    }
    for (int i = 0; i < 82; i++) {
        printf("=");
    }
    printf("\n");
}

int score1(int score_player2, int ball_x) {
    if (ball_x < 2) {
        score_player2 += 1;
        return score_player2;
    }

    return score_player2;
}

int score2(int score_player1, int ball_x) {
    if (ball_x > X_length - 1) {  // Xlength - 1 = 79
        score_player1 += 1;
    }
    return score_player1;
}
