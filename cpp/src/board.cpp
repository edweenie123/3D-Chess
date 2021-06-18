#include "../include/board.h"
#include "../include/rook.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/unicorn.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "../include/piece.h"
#include "../include/empty.h"
#include "../include/globals.h"

Board::Board() {
    // initialize the board
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            for (int k = 0; k < BOARD_SIZE; ++k) {
                /* To Denote an empty cell, we simply use a dead piece */
                board[i][j][k] = new Empty();
                board[i][j][k]->setIsAlive(false);
            }
        }
    }
    // set the board (bottom left back corner is 0, 0, 0)

    // set pieces for Level A
    board[0][0][0] = new Rook(0, 0, 0, WHITE);
    board[0][4][0] = new Rook(0, 4, 0, WHITE);
    board[0][1][0] = new Knight(0, 1, 0, WHITE);
    board[0][3][0] = new Knight(0, 3, 0, WHITE);
    board[0][2][0] = new King(0, 2, 0, WHITE);
    for (int i = 0; i < 5; ++i) {
        board[1][i][0] = new Pawn(1, i, 0, WHITE);
    }


    // set pieces for Level B
    board[0][0][1] = new Bishop(0, 0, 1, WHITE);
    board[0][3][1] = new Bishop(0, 3, 1, WHITE);
    board[0][1][1] = new Unicorn(0, 1, 1, WHITE);
    board[0][4][1] = new Unicorn(0, 4, 1, WHITE);
    board[0][2][1] = new Queen(0, 2, 1, WHITE);
    for(int i = 0; i < 5; ++i) {
        board[1][i][1] = new Pawn(1, i, 1, WHITE);
    }

    // set pieces for Level D
    board[4][0][3] = new Bishop(4, 0, 3, BLACK); // colour -1 means black
    board[4][3][3] = new Bishop(4, 3, 3, BLACK);
    board[4][1][3] = new Unicorn(4, 1, 3, BLACK);
    board[4][4][3] = new Unicorn(4, 4, 3, BLACK);
    board[4][2][3] = new Queen(4, 2, 3, BLACK);
    for(int i = 0; i < 5; ++i) {
        board[3][i][3] = new Pawn(3, i, 3, BLACK);
    }

    // set pieces for Level E
    board[4][0][4] = new Rook(4, 0, 4, BLACK);
    board[4][4][4] = new Rook(4, 4, 4, BLACK);
    board[4][1][4] = new Knight(4, 1, 4, BLACK);
    board[4][3][4] = new Knight(4, 3, 4, BLACK);
    board[4][2][4] = new King(4, 2, 4, BLACK);
    for(int i = 0; i < 5; ++i) {
        board[3][i][4] = new Pawn(3, i, 4, BLACK);
    }
}

void Board::printBoard() {
    for (int lvl = 0; lvl < BOARD_SIZE; ++lvl) {
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                if (board[row][col][lvl]->getId() == ' ') cout << '.' << ' ';
                else cout << board[row][col][lvl]->getId() << ' ';
            }
            cout << '\n';
        }
        cout << '\n' << '\n';
    }
}

Piece* Board::getPieceAt(Coordinate square) {
    if (!isOnBoard(square)) return nullptr;
    return board[square.row][square.col][square.lvl];
}

Piece* Board::getPieceAt(int row, int col, int lvl) {
    if (!isOnBoard({row, col, lvl})) return nullptr;
    return board[row][col][lvl];
}

bool Board::isOnBoard(Coordinate c) {
    // this coordinate lies within te 5x5x5 board
    return c.row >= 0 && c.row < BOARD_SIZE && c.col >= 0 && c.col < BOARD_SIZE && c.lvl >= 0 && c.lvl < BOARD_SIZE;
}

bool Board::isVacant(Coordinate c) {
    if (!isOnBoard(c)) return false;
    // this square is occupied
    return !board[c.row][c.col][c.lvl]->getIsAlive();
}

bool Board::isEnemySquare(Coordinate c, int pieceColor) {
    if (!isOnBoard(c) || isVacant(c)) return false;
    // return true if the piece at C is an enemy of pieceColor
    return board[c.row][c.col][c.lvl]->getColor() != pieceColor;
}


void Board::updateLocation(Coordinate square, Move movement) {
    Piece* curPiece = getPieceAt(square);

    // FIRST check if the move is legal
    int newRow = curPiece->getLocation().row + movement.row;
    int newCol = curPiece->getLocation().col + movement.col;
    int newLvl = curPiece->getLocation().lvl + movement.lvl;
    Coordinate newCord = {newRow, newCol, newLvl};
    if (!isOnBoard(newCord)) return;
    Piece* nextSquare = board[newRow][newCol][newLvl]; // the piece in the square the current piece is about to move to

    if (!isVacant(newCord) && nextSquare->getColor() == curPiece->getColor()) return;

    // The move should be legal, so we update it on the board,and for the piece

    // update the piece
    curPiece->setLocation(newCord.row, newCord.col, newCord.lvl);

    // We need to update the board
    /* To Denote an empty cell, we simply use a dead piece */
    board[square.row][square.col][square.lvl] = new Empty();
    board[square.row][square.col][square.lvl]->setIsAlive(false);

    // update board with the piece's new location

    // if there is a piece of opposite colour currently occupying the new location, we destroy it
    nextSquare->setIsAlive(false);
    board[newRow][newCol][newLvl] = curPiece;
}

bool Board::isChecked(int pieceColor) {
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            for (int z = 0; z < BOARD_SIZE; ++z) {
                // if the current cell contains a piece, process its possible moves
                // only process enemy pieces
                if (board[x][y][z]->getIsAlive() && board[x][y][z]->getColor() != pieceColor) {
                    vector<Move> possibleMoves = board[x][y][z]->getMoves(*this, false);
                    if (board[x][y][z]->getId() == 'p') {
                        // filter down the passive moves for the pawn
                        for (int i = int(possibleMoves.size()) - 1; i >= 0; --i) {
                            // count the number of 0's in this move
                            int zeros = (possibleMoves[i].row == 0) + (possibleMoves[i].col == 0) + (possibleMoves[i].lvl == 0);
                            if (zeros > 1) {
                                // its a passive move, delete it
                                swap(possibleMoves[i], possibleMoves.back());
                                possibleMoves.pop_back();
                            }
                        }
                    }
                    for (Move m : possibleMoves) {
                        if (board[x + m.row][y + m.col][z + m.lvl]->getId() == 'k') {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmated(int pieceColor) {
    // Naive approach: try all possible moves, and if there exists at least 1 move that puts the king
    // out of check, return false
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            for (int k = 0; k < BOARD_SIZE; ++k) {
                if (board[i][j][k]->getIsAlive() && board[i][j][k]->getColor() == pieceColor) {
                    // try out all possible moves of this piece, and check if the king is still checked
                    for (Move m : board[i][j][k]->getMoves(*this, false)) {
                        Coordinate newCoord = Coordinate(i, j, k) + m;
                        Piece* oldPiece = board[newCoord.row][newCoord.col][newCoord.lvl];
                        updateLocation({i, j, k}, m);
                        bool checked = isChecked(pieceColor);
                        // undo the move
                        updateLocation(newCoord, -m);
                        if(oldPiece->getId() != ' '){
                            board[newCoord.row][newCoord.col][newCoord.lvl] = oldPiece;
                            oldPiece->setIsAlive(true);
                        }
                        if(!checked) return false;
                    }
                }
            }
        }
    }
    return true; // game over
}

bool Board::isStalemated(int pieceColor) {
    // By definition of stalemate, the king should not be currently in check
    if (isChecked(pieceColor)) return false;
    // If we manage to find even one valid move for the current turn player, return false
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            for (int k = 0; k < BOARD_SIZE; ++k) {
                if (board[i][j][k]->getIsAlive() && board[i][j][k]->getColor() == pieceColor) {
                    if (board[i][j][k]->hasAnyMoves(*this, {i,j,k})) {
                        // Found a legal valid move
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

string Board::getGameState(int turnPlayer) {

    // Get your opponent's color
    int opponent = -turnPlayer;

    string yourColour = (turnPlayer == WHITE ? "White" : "Black");
    string oppColour = (turnPlayer == WHITE ? "Black" : "White");

    // Check for checkmate
    if (isChecked(turnPlayer) && isCheckmated(turnPlayer)) {
        return "Checkmate! " + oppColour + " Wins.";
    }

    // Check for a check
    if (isChecked(turnPlayer)) {
        return yourColour + " King is Checked!";
    }

    // Check for stalemate
    if (isStalemated(turnPlayer)) {
        return "Stalemate.";
    }

    // To indicate that no special events happened
    return "No special events. Game proceeding normally...";
}
