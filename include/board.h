#ifndef board_h
#define board_h

#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include <bits/stdc++.h>
using namespace std;

class Board {
    private:
        Piece board[5][5][5];
        // map<string, bool> whitePieces; // dead or alive white pieces
        // map<string, bool> blackPieces; // the like for black pieces
    public:
        Board();
        Piece getPieceAt(Coordinate square);
        void updateLocation(Coordinate square, Move movement);
        string getGameState();
};

#endif