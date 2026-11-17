#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class TicTacToe {
public:
    TicTacToe();

    void displayBoard() const;
    bool makeMove(int player, int row, int col);
    int checkGameStatus() const;
    void resetBoard();

private:
    int board[3][3];
};

TicTacToe::TicTacToe() {
    resetBoard();
}

void TicTacToe::resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
}

void TicTacToe::displayBoard() const {
    cout << "\n     0     1     2  " << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " |";
        for (int j = 0; j < 3; j++) {
            char symbol = ' ';
            if (board[i][j] == 1) symbol = 'X';
            else if (board[i][j] == 2) symbol = 'O';

            cout << "  " << symbol << "  |";
        }
    }
    cout << endl;
}

bool TicTacToe::makeMove(int player, int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == 0) {
        board[row][col] = player;
        return true;
    }
    return false;
}

int TicTacToe::checkGameStatus() const {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                isFull = false;
                break;
            }
        }
    }

    if (isFull) {
        return 3;
    }

    return 0;
}

int main() {
    TicTacToe game;
    int currentPlayer = 1;
    int row, col;

    cout << "=== TIC-TAC-TOE GAME ===" << endl;
    cout << "Player 1: X" << endl;
    cout << "Player 2: O" << endl;

    while (game.checkGameStatus() == 0) {
        game.displayBoard();
        cout << "Player " << currentPlayer << " (" << (currentPlayer == 1 ? 'X' : 'O') << ")" << endl;
        cout << "Enter row (0-2) and column (0-2): ";
        cin >> row >> col;

        if (!game.makeMove(currentPlayer, row, col)) {
            cout << "Invalid move! The cell is already taken or out of bounds. Try again." << endl;
            continue;
        }

        int status = game.checkGameStatus();
        if (status != 0) {
            game.displayBoard();
            if (status == 1) {
                cout << "Congratulations! Player 1 (X) wins!" << endl;
            } else if (status == 2) {
                cout << "Congratulations! Player 2 (O) wins!" << endl;
            } else if (status == 3) {
                cout << "It's a draw!" << endl;
            }
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}