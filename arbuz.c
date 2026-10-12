#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_board(int n, char a[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("'%c'", a[i][j]);
            if (j < n - 1) printf(", ");
        }
        printf("]\n");
    }
    printf("\n");
}

int check_win_or_draw(int n, char a[MAX_SIZE][MAX_SIZE], int counth) {
    char symbols[2] = {'X', 'O'};
    
    for (int s = 0; s < 2; s++) {
        char sym = symbols[s];

        for (int i = 0; i < n; i++) {
            int row_win = 1, col_win = 1;
            for (int j = 0; j < n; j++) {
                if (a[i][j] != sym) row_win = 0;
                if (a[j][i] != sym) col_win = 0;
            }
            if (row_win || col_win) {
                if (sym == 'X') printf("Крестики победили!\n");
                else printf("Нолики победили!\n");
                return 1; 
            }
        }

        int diag_main = 1, diag_rec = 1;
        for (int i = 0; i < n; i++) {
            if (a[i][i] != sym) diag_main = 0;
            if (a[n - i - 1][i] != sym) diag_rec = 0;
        }
        if (diag_main || diag_rec) {
            if (sym == 'X') printf("Крестики победили!\n");
            else printf("Нолики победили!\n");
            return 1;
        }
    }

    if (counth == n * n) {
        printf("Ничья!\n");
        return 1;
    }

    return 0; 
}

void player_move(int n, char a[MAX_SIZE][MAX_SIZE], char symbol) {
    int row, col;
    while (1) {
        printf("Игрок (%c), введите строку и столбец через пробел: ", symbol);
        
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Некорректный ввод! Введите два числа.\n");
            clear_buffer();
            continue;
        }
        
        if (row < 1 ||  row > n || col < 1 || col > n) {
            printf("Введите координаты от 1 до %d.\n", n);
            continue;
        }
        
        if (a[row - 1][col - 1] != '.') {
            printf("Это поле уже занято! Повторите попытку.\n");
            continue;
        }
        
        a[row - 1][col - 1] = symbol;
        break;
    }
}

void bot_move(int n, char a[MAX_SIZE][MAX_SIZE], char symbol) {
    int empty_count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '.') empty_count++;
        }
    }

    if (empty_count == 0) return;

    int choice = rand() % empty_count;
    int current = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '.') {
                if (current == choice) {
                    a[i][j] = symbol;
                    printf("Бот походил: %d %d\n", i + 1, j + 1);
                    return;
                }
                current++;
            }
        }
    }
}

int main() {
    system("chcp 65001 > nul"); 
    
    srand(time(NULL)); 

    int n;
    printf("Введите размерность поля: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Размерность поля должна быть больше нуля!\n");
        return 1;
    }

    if (n > MAX_SIZE) {
        printf("Максимальный поддерживаемый размер поля: %d\n", MAX_SIZE);
        return 1;
    }

    char a[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = '.';
        }
    }

    int r;
    printf("Выберите режим игры (1 — с компьютером, 2 — с другим игроком): ");
    if (scanf("%d", &r) != 1) return 1;

    int ind = 0;
    int counth = 0;
if (r == 1) {
        char player_symbol;
        while (1) {
            printf("Кем будете играть — X или O? ");
            scanf(" %c", &player_symbol);
            
            if (player_symbol == 'x') player_symbol = 'X';
            if (player_symbol == 'o') player_symbol = 'O';
            
            if (player_symbol == 'X' || player_symbol == 'O') break;
            printf("Введите X или O!\n");
        }

        char bot_symbol = (player_symbol == 'X') ? 'O' : 'X';

        printf("Ты играешь за %c\n", player_symbol);
        printf("Бот играет за %c\n", bot_symbol);
        print_board(n, a);

        if (player_symbol == 'O') {
            bot_move(n, a, bot_symbol);
            counth++;
            print_board(n, a);
            ind = check_win_or_draw(n, a, counth);
        }

        while (!ind) {
            player_move(n, a, player_symbol);
            counth++;
            print_board(n, a);
            ind = check_win_or_draw(n, a, counth);
            if (ind) break;

            bot_move(n, a, bot_symbol);
            counth++;
            print_board(n, a);
            ind = check_win_or_draw(n, a, counth);
        }

    } else if (r == 2) {
        printf("Игрок 1 играет за X, игрок 2 — за O\n");
        print_board(n, a);

        while (!ind) {
            player_move(n, a, 'X');
            counth++;
            print_board(n, a);
            ind = check_win_or_draw(n, a, counth);
            if (ind) break;

            player_move(n, a, 'O');
            counth++;
            print_board(n, a);
            ind = check_win_or_draw(n, a, counth);
        }
    } else {
        printf("Неизвестный режим игры!\n");
    }

    return 0;
}