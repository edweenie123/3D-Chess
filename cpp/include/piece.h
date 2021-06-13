#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include "move.h"
#include "globals.h"
#include<string>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

class Board;

class Piece {
    private:
    public:
        bool isAlive = true;
        Coordinate location;
        int color;
        Piece();
        Piece(int row, int col, int lvl, int color);

        int getColor();
        Coordinate getLocation();
        void setLocation(int row, int col, int lvl);
        string toString();
        vector<Move> getAllMovesInLine(vector<Move>, Board, bool); // bool is to specify if we want to prune for checks
        vector<Move> pruneMoves(vector<Move>, Board, Coordinate);
        bool hasAnyMoves(Board, Coordinate); // Checks if a piece has any legal moves
        virtual vector<Move> getMoves(Board, bool);
        virtual char getId();
};

#endif
