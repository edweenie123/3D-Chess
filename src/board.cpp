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
                Piece emptyCell;
                emptyCell.isAlive = false;
                Piece* emptyCellPtr = &emptyCell;
                board[i][j][k] = emptyCellPtr;
            }
        }
    }
    // set the board (bottom left back corner is 0, 0, 0)

    // set pieces for Level A
    Piece leftWhiteRook = Rook(0, 0, 0, 1);
    board[0][0][0] = &leftWhiteRook;
    Piece rightWhiteRook = Rook(0, 4, 0, 1);
    board[0][4][0] = &rightWhiteRook;
    Piece leftWhiteKnight = Knight(0, 1, 0, 1);
    board[0][1][0] = &leftWhiteKnight;
    Piece rightWhiteKnight = Knight(0, 3, 0, 1);
    board[0][3][0] = &rightWhiteKnight;
    Piece whiteKing = King(0, 2, 0, 1);
    board[0][2][0] = &whiteKing;

    Piece whitePawn0 = Pawn(1, 0, 0, 1);
    board[1][0][0] = &whitePawn0;
    Piece whitePawn1 = Pawn(1, 1, 0, 1);
    board[1][1][0] = &whitePawn1;
    Piece whitePawn2 = Pawn(1, 2, 0, 1);
    board[1][2][0] = &whitePawn2;
    Piece whitePawn3 = Pawn(1, 3, 0, 1);
    board[1][3][0] = &whitePawn3;
    Piece whitePawn4 = Pawn(1, 4, 0, 1);
    board[1][4][0] = &whitePawn4;
    // for (int i = 0; i < 5; ++i) {
    //     board[1][i][0] = &Pawn(1, i, 0, 1);
    // }

    // set pieces for Level B
    Piece leftWhiteBishop = Bishop(0, 0, 1, 1);
    board[0][0][1] = &leftWhiteBishop;
    Piece rightWhiteBishop = Bishop(0, 3, 1, 1);
    board[0][3][1] = &rightWhiteBishop;
    Piece leftWhiteUnicorn = Unicorn(0, 1, 1, 1);
    board[0][1][1] = &leftWhiteUnicorn;
    Piece rightWhiteUnicorn = Unicorn(0, 4, 1, 1);
    board[0][4][1] = &rightWhiteUnicorn;
    Piece whiteQueen = Queen(0, 2, 1, 1);
    board[0][2][1] = &whiteQueen;

    Piece whitePawn5 = Pawn(1, 0, 1, 1);
    board[1][0][1] = &whitePawn5;
    Piece whitePawn6 = Pawn(1, 1, 1, 1);
    board[1][1][1] = &whitePawn6;
    Piece whitePawn7 = Pawn(1, 2, 1, 1);
    board[1][2][1] = &whitePawn7;
    Piece whitePawn8 = Pawn(1, 3, 1, 1);
    board[1][3][1] = &whitePawn8;
    Piece whitePawn9 = Pawn(1, 4, 1, 1);
    board[1][4][1] = &whitePawn9;
    // for (int i = 0; i < 5; ++i) {
    //     board[1][i][1] = &Pawn(1, i, 1, 1);
    // }

    // set pieces for Level D
    Piece leftBlackBishop = Bishop(4, 0, 3, -1);
    board[4][0][3] = &leftBlackBishop; // colour -1 means black
    Piece rightBlackBishop = Bishop(4, 3, 3, -1);
    board[4][3][3] = &rightBlackBishop;
    Piece leftBlackUnicorn = Unicorn(4, 1, 3, -1);
    board[4][1][3] = &leftBlackUnicorn;
    Piece rightBlackUnicorn = Unicorn(4, 4, 3, -1);
    board[4][4][3] = &rightBlackUnicorn;
    Piece blackQueen = Queen(4, 2, 3, -1);
    board[4][2][3] = &blackQueen;

    Piece blackPawn0 = Pawn(3, 0, 3, -1);
    board[3][0][3] = &blackPawn0;
    Piece blackPawn1 = Pawn(3, 1, 3, -1);
    board[3][1][3] = &blackPawn1;
    Piece blackPawn2 = Pawn(3, 2, 3, -1);
    board[3][2][3] = &blackPawn2;
    Piece blackPawn3 = Pawn(3, 3, 3, -1);
    board[3][3][3] = &blackPawn3;
    Piece blackPawn4 = Pawn(3, 4, 3, -1);
    board[3][4][3] = &blackPawn4;
    // for (int i = 0; i < 5; ++i) {
    //     board[3][i][3] = &Pawn(3, i, 3, -1);
    // }

    // set pieces for Level E
    Piece leftBlackRook = Rook(4, 0, 4, -1);
    board[4][0][4] = &leftBlackRook;
    Piece rightBlackRook = Rook(4, 4, 4, -1);
    board[4][4][4] = &rightBlackRook;
    Piece leftBlackKnight = Knight(4, 1, 4, -1);
    board[4][1][4] = &leftBlackKnight;
    Piece rightBlackKnight = Knight(4, 3, 4, -1);
    board[4][3][4] = &rightBlackKnight;
    Piece blackKing = King(4, 2, 4, -1);
    board[4][2][4] = &blackKing;

    Piece blackPawn5 = Pawn(3, 0, 4, -1);
    board[3][0][4] = &blackPawn5;
    Piece blackPawn6 = Pawn(3, 1, 4, -1);
    board[3][1][4] = &blackPawn6;
    Piece blackPawn7 = Pawn(3, 2, 4, -1);
    board[3][2][4] = &blackPawn7;
    Piece blackPawn8 = Pawn(3, 3, 4, -1);
    board[3][3][4] = &blackPawn8;
    Piece blackPawn9 = Pawn(3, 4, 4, -1);
    board[3][4][4] = &blackPawn9;
    // for (int i = 0; i < 5; ++i) {
    //     board[3][i][4] = &Pawn(3, i, 4, -1);
    // }
}

Piece Board::getPieceAt(Coordinate square) {
    return *board[square.row][square.col][square.lvl];
}

Piece Board::getPieceAt(int row, int col, int lvl) {
    return *board[row][col][lvl];
}

bool Board::isOnBoard(Coordinate c) {
    if (c.row >= 0 && c.row < 5 && c.col >= 0 && c.col < 5 && c.lvl >= 0 && c.lvl < 5) {
        return true; // this coordinate lies within te 5x5x5 board
    }
    return false;
}

bool Board::isVacant(Coordinate c) {
    Piece curPiece = *board[c.row][c.col][c.lvl];
    if (curPiece.isAlive) {
        return false; // this square is occupied
    }
    return true;
}

void Board::updateLocation(Coordinate square, Move movement) {
    Piece curPiece = getPieceAt(square);

    // FIRST check if the move is legal
    int newRow = curPiece.location.row + movement.row;
    int newCol = curPiece.location.col + movement.col;
    int newLvl = curPiece.location.lvl + movement.lvl;
    Piece nextSquare = *board[newRow][newCol][newLvl]; // the piece in the square the current piece is about to move to

    bool legal = true;

    if (isOnBoard({newRow, newCol, newLvl}) == false) {
        legal = false;
    } else if (isVacant({newRow, newCol, newLvl}) == false && nextSquare.color == curPiece.color) {
        legal = false;
    }
    // haven't added king checks, and check checks (king can't place itself in a check)
    if (!legal) return;

    // The move should be legal, so we update it on the board,and for the piece

    // update the piece
    curPiece.location.row = newRow;
    curPiece.location.col = newCol;
    curPiece.location.lvl = newLvl;

    // We need to update the board
    /* To Denote an empty cell, we simply use a dead piece */
    Piece emptyCell;
    emptyCell.isAlive = false;
    board[curPiece.location.row][curPiece.location.col][curPiece.location.lvl] = &emptyCell;

    // update board with the piece's new location

    // if there is a black piece currently occupying the new location, we destroy it
    if (!isVacant({newRow, newCol, newLvl})) {
        nextSquare.isAlive = false;
    }
    nextSquare = curPiece;
}

string Board::getGameState() {
    // Check for checkmate on both sides
    // i believe I need pieces class to be finished (legal moves for each piece to complete this part)
    // Check for check on both sides

    // Check for stalemate on both sides

    return "placehold";
}
