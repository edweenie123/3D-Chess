#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include "move.h"
#include "globals.h"
#include<string>
#include<vector>

using namespace std;

class Board;

class Piece {
    private:
    public:
        bool isAlive = true;
        Coordinate location;
        int color;
        char id;
        Piece();
        Piece(int row, int col, int lvl, int color);

        int getColor();
        Coordinate getLocation();
        void setLocation(int row, int col, int lvl);
        string toString();
        vector<Move> getAllMovesInLine(vector<Move>, Board);
        // bool isEnemy(Piece other);


        virtual vector<Move> getMoves(Board board);
        virtual char getId();
};

#endif
