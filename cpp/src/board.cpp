#include "../include/board.h"
#include "../include/rook.h"
#include "../include/king.h"
#include "../include/bishop.h"
#include "../include/unicorn.h"
#include "../include/queen.h"
#include "../include/pawn.h"
#include "../include/knight.h"
#include "../include/piece.h"

Board::Board() {
    // initialize the board
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                /* To Denote an empty cell, we simply use a dead piece */
                board[i][j][k] = new Piece();
                board[i][j][k]->isAlive = false;
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
    for (int lvl = 0; lvl < 5; ++lvl) {
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (board[row][col][lvl]->getId() == ' ') cout << '.' << ' ';
                else cout << board[row][col][lvl]->getId() << ' ';
            }
            cout << '\n';
        }
        cout << '\n' << '\n';
    }
}

Piece* Board::getPieceAt(Coordinate square) {
    return board[square.row][square.col][square.lvl];
}

Piece* Board::getPieceAt(int row, int col, int lvl) {
    return board[row][col][lvl];
}

bool Board::isOnBoard(Coordinate c) {
    if (c.row >= 0 && c.row < 5 && c.col >= 0 && c.col < 5 && c.lvl >= 0 && c.lvl < 5) {
        return true; // this coordinate lies within te 5x5x5 board
    }
    return false;
}

bool Board::isVacant(Coordinate c) {
    if (!isOnBoard(c)) return false;
    Piece* curPiece = board[c.row][c.col][c.lvl];
    if (curPiece->isAlive) {
        return false; // this square is occupied
    }
    return true;
}

bool Board::isEnemySquare(Coordinate c, int pieceColor) {
    if (isVacant(c)) return false;
    if (!isOnBoard(c)) return false;

    Piece* pieceAtC = getPieceAt(c);
    // return true if the piece at C is an enemy of pieceColor
    return pieceAtC->color != pieceColor;
}


void Board::setPieceAt(Piece *piece) {

    // This method will only set a piece at an emtpy square
    if(!isOnBoard(piece->location) || !isVacant(piece->location))
        return;
    // Don't re-add a dead piece
    if(!piece->isAlive)
        return;

    // Add the pointer
    board[piece->location.row][piece->location.col][piece->location.lvl] = piece;
}

void Board::updateLocation(Coordinate square, Move movement) {
    Piece* curPiece = getPieceAt(square);

    // FIRST check if the move is legal
    int newRow = curPiece->location.row + movement.row;
    int newCol = curPiece->location.col + movement.col;
    int newLvl = curPiece->location.lvl + movement.lvl;
    Coordinate newCord = {newRow, newCol, newLvl};
    if (!isOnBoard(newCord)) return;
    Piece* nextSquare = board[newRow][newCol][newLvl]; // the piece in the square the current piece is about to move to

    bool legal = true;
    if (isOnBoard(newCord) == false) {
        legal = false;
    } else if (isVacant(newCord) == false && nextSquare->color == curPiece->color) {
        legal = false;
    }
    // haven't added king checks, and check checks (king can't place itself in a check)
    if (!legal) return;

    // The move should be legal, so we update it on the board,and for the piece

    // update the piece
    curPiece->location.row = newRow;
    curPiece->location.col = newCol;
    curPiece->location.lvl = newLvl;

    // We need to update the board
    /* To Denote an empty cell, we simply use a dead piece */
    board[square.row][square.col][square.lvl] = new Piece();
    board[square.row][square.col][square.lvl]->isAlive = false;

    // update board with the piece's new location

    // if there is a piece of opposite colour currently occupying the new location, we destroy it
    if (!isVacant({newRow, newCol, newLvl})) {
        nextSquare->isAlive = false;
    }
    board[newRow][newCol][newLvl] = curPiece;
}

void Board::updateThreatenedSquares() {
    /* Update all the threatened squares */

    // clear both sets
    threatenedByWhite.clear();
    threatenedByBlack.clear();
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                // if the current cell contains a piece, process its possible moves
                if (board[i][j][k]->isAlive) {
                    vector<Move> possibleMoves;
                    if (board[i][j][k]->getId() == 'p') {
                        possibleMoves = board[i][j][k]->getMoves(*this);
                        // filter down the passive moves for the pawn
                        for (int i = possibleMoves.size() - 1; i >= 0; --i) {
                            // count the number of 0's in this move
                            int zeros = 0;
                            if (possibleMoves[i].row == 0) zeros++;
                            if (possibleMoves[i].col == 0) zeros++;
                            if (possibleMoves[i].lvl == 0) zeros++;
                            if (zeros > 1) {
                                // its a passive move, delete it
                                possibleMoves.erase(possibleMoves.begin() + i);
                            }
                        }
                    } else possibleMoves = board[i][j][k]->getMoves(*this);
                    for (Move m : possibleMoves) {
                        if (board[i][j][k]->color == WHITE) {
                            threatenedByWhite.insert({{i + m.row, j + m.col}, k + m.lvl});
                        } else {
                            threatenedByBlack.insert({{i + m.row, j + m.col}, k + m.lvl});
                        }
                    }
                }
            }
        }
    }
}

bool Board::isChecked(int pieceColor) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                if (board[i][j][k]->getId() == 'k') {
                    // check if this king is threatened by the opposite colour
                    if (board[i][j][k]->color == pieceColor) {
                        // we found the right coloured king, now check if he is threatened
                        if (pieceColor == WHITE) {
                            if (threatenedByBlack.find({{i, j}, k}) != threatenedByBlack.end()) {
                                // White is checked!
                                return true;
                            }
                        } else {
                            if (threatenedByWhite.find({{i, j}, k}) != threatenedByWhite.end()) {
                                // Black is checked!
                                return true;
                            }
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
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                if (board[i][j][k]->color == pieceColor) {
                    // try out all possible moves of this piece, and check if the king is still checked
                    for (Move m : board[i][j][k]->getMoves(*this)) {
                        char id = (*this).getPieceAt({i, j, k})->getId();
                        Piece* oldPiece = (*this).getPieceAt({i + m.row, j + m.col, k + m.lvl});
                        updateLocation({i, j, k}, m);
                        updateThreatenedSquares();
                        if (isChecked(pieceColor) == false) {
                            return false;
                        }
                        // undo the move
                        updateLocation({i + m.row, j + m.col, k + m.lvl}, {-m.row, -m.col, -m.lvl});
                        if (oldPiece->getId() != ' ') {
                            board[i + m.row][j + m.col][k + m.lvl] = oldPiece;
                            oldPiece->isAlive = true;
                        }
                    }
                }
            }
        }
    }
    return true; // game over
}

string Board::getGameState() {
    // Have a method that updates all the threatened squares after each move
    // If king is currently in a threatened square, then report a check
    
    // If king is currently in a threatened square AND he has nowhere to go / no pieces to block or capture attacking pieces, then report a checkmate
    // If the turn player has no possible moves he can play, then report a stalemate

    // Check for stalemate on both sides

    return "placehold";
}