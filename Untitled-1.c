// Пробел перед %c нужен, чтобы проигнорировать оставшийся в буфере Enter
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