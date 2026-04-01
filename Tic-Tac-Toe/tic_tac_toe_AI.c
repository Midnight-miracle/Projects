#include <stdio.h>

char board[3][3];

/* Function to initialize the board */
void initializeBoard() {
    char count = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = count++;
        }
    }
}

/* Function to display the board */
void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2)
            printf("\n---|---|---\n");
    }
    printf("\n\n");
}

/* Function to check for win */
int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

/* Function to check draw */
int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
        }
    }
    return 1;
}

/* Main function */
int main() {
    int player = 1;
    int choice;
    int row, col;
    char mark;

    initializeBoard();

    while (1) {
        displayBoard();

        player = (player % 2) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("Player %d (%c), enter a position (1-9): ", player, mark);
        scanf("%d", &choice);

        if (choice < 1 || choice > 9) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Position already taken! Try again.\n");
            continue;
        }

        board[row][col] = mark;

        if (checkWin()) {
            displayBoard();
            printf("🎉 Player %d wins!\n", player);
            break;
        }

        if (checkDraw()) {
            displayBoard();
            printf("🤝 It's a draw!\n");
            break;
        }

        player++;
    }

    return 0;
}
