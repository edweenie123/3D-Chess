#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include "move.h"
#include<string>
#include<vector>

using namespace std;

class Board;

class Piece {
    private:
    public:
        bool isAlive;
        Coordinate location;
        int color;
        string identifier;
        Piece();
        Piece(int row, int col, int lvl, int color);

        int getColor();
        Coordinate getLocation();
        void setLocation(int row, int col, int lvl);
        string toString();

        vector<Move> getAllMovesInLine(vector<Move>, Board);

};

#endif
