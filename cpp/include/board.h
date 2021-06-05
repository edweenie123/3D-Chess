#ifndef board_h
#define board_h

#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include <vector>
#include "globals.h"
using namespace std;

class Piece;

class Board {
    private:
    public:

        // I can't get embind to work with arrays, so gotta use yucky vector lol
        vector<vector<vector<Piece*>>> board = 
            vector<vector<vector<Piece*>>>(5, vector<vector<Piece*>>(5, vector<Piece*>(5, NULL)));
        // Piece* board[5][5][5];

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
