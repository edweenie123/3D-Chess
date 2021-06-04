#ifndef board_h
#define board_h

#include "piece.h"
#include "coordinate.h"
#include "move.h"
using namespace std;

class Piece;

class Board {
    private:
        Piece* board[5][5][5];
    public:
        Board();
        Piece* getPieceAt(Coordinate square);
        Piece* getPieceAt(int row, int col, int lvl);
        void updateLocation(Coordinate square, Move movement);
        void setPieceAt(Piece *piece);
        string getGameState();

        bool isVacant(Coordinate cord); // returns true if cord is vacant
        bool isOnBoard(Coordinate cord); // return true if cord is on board
        bool isEnemySquare(Coordinate cord, int pieceColor); // returns true if cord contains an ememy piece
};

#endif
